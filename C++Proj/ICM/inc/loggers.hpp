///****************************************************************************
/// @author  : Renaissance                                                        
/// @date    :                                                                 
/// @file    :                                                                 
/// @brief   :              日志库，静态全局日志，单例模式            
///		默认每天更新一个文件，每个文件大小无限制，累计增长。                                
///----------------------------------------------------------------------------
///                           Change History                                   
///----------------------------------------------------------------------------
///        v1.0  created by renaissance                      
///****************************************************************************
#pragma  once
#pragma warning(disable : 4307)
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO

#include <iostream>
#include <iomanip>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "project_shared.h"
#include "universal_toolbox.hpp"

namespace renaissance::log
{

	/// <summary>
	/// 文件，行号，函数名等信息
	/// </summary>
	class SourceLocation
	{
	public:
		constexpr SourceLocation(const char* fileName = __FILE__, const char* funcName = "",
			int lineNum = __LINE__) noexcept
			: _fileName(fileName), _funcName(__FUNCTION__), _lineNum(lineNum)
		{
		}

		[[nodiscard]] constexpr const char* FileName() const noexcept
		{
			return _fileName;
		}

		[[nodiscard]] constexpr const char* FuncName() const noexcept
		{
			return _funcName;
		}

		[[nodiscard]] constexpr int LineNum() const noexcept
		{
			return _lineNum;
		}

	private:
		const char* _fileName;
		const char* _funcName;
		int _lineNum;
	};

	/// <summary>
	/// 获取当前信息
	/// </summary>
	/// <param name="location"></param>
	/// <returns></returns>
	inline constexpr auto GetLogSourceLocation(const SourceLocation& location)
	{
		return spdlog::source_loc{ location.FileName(), static_cast<int>(location.LineNum()), location.FuncName() };
	}

	/// <summary>
	/// 获取当前进程名称
	/// </summary>
	/// <returns></returns>
	inline std::string getProcessName() {
		std::string processName;
#ifdef _WIN32
		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		processName = std::string(buffer);
#else
		char buffer[PATH_MAX];
		ssize_t len = ::readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
		if (len != -1) {
			buffer[len] = '\0';
			processName = std::string(buffer);
		}
#endif

		std::size_t lastSeparator = processName.find_last_of("/\\");
		if (lastSeparator != std::string::npos) {
			processName = processName.substr(lastSeparator + 1);
		}
		return processName.substr(0, processName.size() - 4);
	}


	/// <summary>
	/// 使用方式：
	/// 1. 
	/// auto& logger = renaissance::log::Logger::getInstance();
	/// logger.Warn(...);
	/// 2. 使用宏定义
	/// </summary>
	class Logger
	{
	public:
		inline static Logger& getInstance(const std::string config_path = shared_define::ServerInfoPath)
		{
			static Logger instance(config_path);
			return instance;
		}

		void Debug(const std::string& message, const unsigned int number = 0000U, SourceLocation location = {})
		{
			/*spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=10l%$] %v");
			SPDLOG_LOGGER_DEBUG(logger_, message);*/
			//logger_->debug(fmt::format("[{0}] {1}", getProcessName(), message));
			//logger_->debug(fmt::format("[{:^15}] [{:^5}] {}", getProcessName(), number, message));
			logger_->debug(fmt::format("[{:^5}] [{:^15}] {}", number, getProcessName(), message));

		}

		void Info(const std::string& message, const unsigned int number = 0000U, SourceLocation location = {})
		{
			//spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=10l%$] %v");
			//SPDLOG_LOGGER_INFO(logger_, message);
			logger_->info(fmt::format("[{:^15}] {}", getProcessName(), message));
			//logger_->info(message);
		}

		void Warn(const std::string& message, const unsigned int number = 0000U, SourceLocation location = {})
		{
			//spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=10l%$] %v");
			//SPDLOG_LOGGER_WARN(logger_, message);
			//logger_->warn(message);
			logger_->warn(fmt::format("[{:^15}] {}", getProcessName(), message));
		}

		void Error(const std::string& message, const unsigned int number = 0000U, SourceLocation location = {})
		{
			//logger_->error(message);
			logger_->error(fmt::format("[{:^15}] {}", getProcessName(), message));

			//spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=10l%$] [%@] %v");
			//SPDLOG_LOGGER_ERROR(logger_, message);
		}

		void Critical(const std::string& message, const unsigned int number = 0000U, SourceLocation location = {})
		{
			//spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=10l%$] %v");
			//SPDLOG_LOGGER_CRITICAL(logger_, message);
			//logger_->critical(message);
			logger_->critical(fmt::format("[{:^5}] [{:^15}] {}", number, getProcessName(), message));
		}

		void InfoNum(const std::string& message, const unsigned int number = 0000U, SourceLocation location = {})
		{
			//spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=10l%$] %v");
			//SPDLOG_LOGGER_INFO(logger_, message);
			logger_->info(fmt::format("[{:^4}] [{:^15}] {}", number, getProcessName(), message));
			//logger_->info(message);
		}

		void WarnNum(const std::string& message, const unsigned int number = 0000U, SourceLocation location = {})
		{
			//spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=10l%$] %v");
			//SPDLOG_LOGGER_WARN(logger_, message);
			//logger_->warn(message);
			logger_->warn(fmt::format("[{:^4}] [{:^15}] {}", number, getProcessName(), message));
		}

		void ErrorNum(const std::string& message, const unsigned int number = 0000U, SourceLocation location = {})
		{
			//logger_->error(message);
			logger_->error(fmt::format("[{:^5}] [{:^15}] {}", number, getProcessName(), message));

			//spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=10l%$] [%@] %v");
			//SPDLOG_LOGGER_ERROR(logger_, message);
		}

	public:
		[[deprecated("no safe")]]
		inline std::shared_ptr<spdlog::logger> getLogger()
		{
			return logger_;
		}

	private:
		void Init(const std::string& logFileName)
		{
			try
			{
				// 创建控制台和文件的输出器
				auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
				// 追加内容到末尾
				//auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_st>(logFileName, false);
				auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(logFileName, 23, 59);

				// 自定义输出格式
				//spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%=10l%$] [%@] %v");

				std::string pattern_ = "%^[%=7l] [%Y-%m-%d %H:%M:%S.%e] %v%$";
				consoleSink->set_pattern(pattern_);
				daily_sink->set_pattern(pattern_);
				//fileSink->set_pattern(pattern_);

				// 创建日志器并添加输出器
				logger_ = std::make_shared<spdlog::logger>("Logger", spdlog::sinks_init_list({ consoleSink,daily_sink }));
				//logger_ = spdlog::daily_logger_mt("daily_logger1", "C:\\Repository\\Nercar\\ShaGang\\daily.log", 23, 59);

				// 设置日志级别为TRACE
				logger_->set_level(spdlog::level::trace);

				// 开启异步日志
				logger_->flush_on(spdlog::level::trace);
				spdlog::flush_every(std::chrono::seconds(3));
				spdlog::register_logger(logger_);

			}
			catch (const spdlog::spdlog_ex& ex)
			{
				std::cerr << "Log initialization failed: " << ex.what() << std::endl;
				throw ex;
			}
		}

	private:
		Logger(const std::string config_path)
		{
			std::string path_prefix("C:/");
			try
			{
				boost::property_tree::ptree pt;
				boost::property_tree::read_json(config_path, pt);
				path_prefix = pt.get("log_path", "C:/");

			}
			catch (...)
			{

			}
			// 可以考虑配置文件配置相关信息
			std::string filename = path_prefix + "TraceReport_.log";

			Init(filename);
		};

		~Logger() { spdlog::shutdown(); };

		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		std::shared_ptr<spdlog::logger> logger_;
	};


	//默认报警号为0
#define LOG_INFO(...)       Logger::getInstance().Info(__VA_ARGS__)

//指定报警号
#define LOG_INFO_NUM(number,msg)       Logger::getInstance().InfoNum(msg,number)

#define LOG_WARN(...)       Logger::getInstance().Warn(__VA_ARGS__)
#define LOG_WARN_NUM(number,msg)       Logger::getInstance().WarnNum(msg,number)

#define LOG_ERR(...)        Logger::getInstance().Error(__VA_ARGS__)
#define LOG_ERR_NUM(number,msg)       Logger::getInstance().ErrorNum(msg,number)

}

