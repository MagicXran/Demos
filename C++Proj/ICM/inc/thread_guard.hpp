/************************************************************************/
/*	FileName	:		thread_guard.cpp
/*	User		:		renaissance
/*	Time		:		3/12/2023 9:04:07 AM
/*	clr_version	:		4.0.30319.42000
/*	Description :		Thread的RAII 式资源管理类
/*
/*
/*
/************************************************************************/

#pragma once
#include <thread>
#include <vector>
constexpr auto INITIALIZED_LEN = 5;

class thread_guard
{
public:
	thread_guard() = default;
	explicit thread_guard(std::thread& th);
	~thread_guard();

	thread_guard(const thread_guard&) = delete;
	thread_guard& operator=(const thread_guard&) = delete;

public:
	template<typename T>
	void push(T&& t);
private:
	std::vector<std::thread> m_tv;
	std::thread& th_;
};

inline thread_guard::~thread_guard()
{
	if (!m_tv.empty())
	{
		for (size_t i = 0; i < m_tv.size(); i++)
		{
			if (m_tv[i].joinable())
			{
				m_tv[i].join();
			}
		}
	}

	if (th_.joinable())
	{
		th_.join();
	}
}

template<typename T>
inline void thread_guard::push(T&& t)
{
	m_tv.push_back(std::move(t));
}

inline thread_guard::thread_guard(std::thread& th) :th_(th)
{

}