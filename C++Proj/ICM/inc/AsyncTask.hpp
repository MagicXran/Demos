#pragma once

#include <future>
#include <functional>
#include <vector>
#include <queue>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <stdexcept>


namespace renaissance::asyn
{

	/// <summary>
	/// 异步任务框架
	/// </summary>
	class AsyncTask {

	public:
		AsyncTask() : m_stop(false)
		{
			// 创建线程池
			for (size_t i = 0; i < m_thread_count; ++i) {
				m_threads.emplace_back(std::bind(&AsyncTask::worker_thread, this));
			}
		}

		~AsyncTask()
		{
			{
				// 停止所有线程
				std::unique_lock<std::mutex> lock(m_mutex);
				m_stop = true;
				m_condition.notify_all();
			}

			// 等待所有线程完成
			for (auto& thread : m_threads) {
				thread.join();
			}
		}

		// 提交任务
		template<typename Func, typename... Args>
		inline auto submit(Func&& func, Args&&... args) -> std::future<typename std::result_of<Func(Args...)>::type> {
			using return_type = typename std::result_of<Func(Args...)>::type;

			// 创建一个packaged_task，将函数和参数绑定在一起
			auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

			// 获取future对象，以便在将来的某个时间点获取结果
			std::future<return_type> result = task->get_future();

			{
				// 将任务添加到队列中
				std::unique_lock<std::mutex> lock(m_mutex);
				if (m_stop) {
					throw std::runtime_error("submit on stopped AsyncTask");
				}
				m_tasks.emplace([task]() { (*task)(); });
			}

			// 通知一个线程来执行任务
			m_condition.notify_one();

			return result;
		}

	private:
		// 工作线程函数
		inline void worker_thread() {
			while (true) {
				std::function<void()> task;

				{
					std::unique_lock<std::mutex> lock(m_mutex);

					// 等待任务或停止信号
					m_condition.wait(lock, [this]() { return m_stop || !m_tasks.empty(); });

					if (m_stop && m_tasks.empty()) {
						return;
					}

					// 获取下一个任务
					task = std::move(m_tasks.front());
					m_tasks.pop();
				}

				// 执行任务
				task();
			}
		}

	private:
		const size_t m_thread_count = std::thread::hardware_concurrency();
		std::vector<std::thread> m_threads;
		std::queue<std::function<void()>> m_tasks;
		std::mutex m_mutex;
		std::condition_variable m_condition;
		bool m_stop;
	};

}
