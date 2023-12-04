//
// Created by Renaissance on 12/1/2023.
//


#include <iostream>
#include <thread>
#include <future>

int thread_func(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(3)); // 模拟耗时操作
    return x * x; // 返回结果
}

int main() {
    // 使用std::async创建异步任务，返回一个std::future对象
    std::future<int> f1 = std::async(std::launch::async, thread_func, 10); // 异步执行
    // std::future<int> f1 = std::async(std::launch::deferred, thread_func, 10); // 延迟执行
    // 使用std::packaged_task创建异步任务，返回一个std::future对象
    std::packaged_task<int(int)> task(thread_func); // 将函数包装为任务
    std::future<int> f2 = task.get_future(); // 获取future对象
    std::thread t(std::move(task), 20); // 在新线程中执行任务
    // 使用std::promise创建异步任务，返回一个std::future对象
    std::promise<int> p; // 创建一个promise对象
    std::future<int> f3 = p.get_future(); // 获取future对象
    std::thread([&p]{
        p.set_value(thread_func(30)); // 在新线程中设置promise的值
    }).detach(); // 分离线程
    // 等待异步任务的结果
    std::cout << "Waiting for results..." << std::endl;
    std::cout << "Result from async: " << f1.get() << std::endl; // 调用get方法获取结果，如果结果未就绪则阻塞
    std::cout << "Result from packaged_task: " << f2.get() << std::endl;
    std::cout << "Result from promise: " << f3.get() << std::endl;
    t.join(); // 等待线程结束
    return 0;
}
