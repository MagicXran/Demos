/************************************************************************/
/*           通用工具类 V1.0											*/
/*								--for vs2005
*								--by renaissancer(xgz)					*/
/************************************************************************/

#ifndef _COMMON_TOOL_BOX_
#define _COMMON_TOOL_BOX_

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE

#define  STRBUFF  120
#define TIME_LEN 20


#include <exception>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <float.h>
#include <vector>
#include <algorithm>
#include <set>
#include <ctime>

#ifdef _WIN32 
#include <Windows.h>
#endif // DEBUG


#include "cpp_version.h"

#ifdef CPP_03_STANDARD

#endif // CPP_03_STANDARD

#ifdef CPP_11_STANDARD
#include <chrono>
#include <regex>
#include <random>
#endif // CPP_11_STANDARD
#include <iomanip>
#include <locale>
#include <cctype>



/**
* @description	: 取整型的每个位,最低位从0开始.
* @param		: x:原始整数, y:第y位
* @return		: 返回x的第y+1 位上的数字.
* @exception	:
*/
#define getBit(x,y)   ((x) >> (y)&1) 

/**
* @description	: 浮点型转字符串
* @param		: des:接收的字符数组, src: 浮点型数据, N: 保留小数点位数
* @return		: 对应字符串型数据
*/
#define FLOAT_STRING(SRC,DES,N)  sprintf(DES,"%."#N"f",SRC)


/// 浮点数0
#define  FLOAT_ZERO  0.00000000000000001


/**
* @description	: 整型转字符串, 宽度为N
* @param		: des:接收的字符数组, src: 整型数据, N: 宽度, 若N>src位数,左边补0
* @return		: 对应字符串型数据
*/
#define INTEGER_STRING(SRC,DES,N)  sprintf(DES,"%0"#N"d",SRC) \
								   return DES


namespace uni_box
{
	/// <summary>
	/// 字符集编码
	/// </summary>
	namespace coding
	{
#ifdef _WIN32
		//using namespace std;
		//utf8 转 Unicode  
		inline std::wstring Utf82Unicode(const std::string& utf8string)
		{
			int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
			if (widesize == ERROR_NO_UNICODE_TRANSLATION)
			{
				throw std::exception("Invalid UTF-8 sequence.");
			}
			if (widesize == 0)
			{
				throw std::exception("Error in conversion.");
			}

			std::vector<wchar_t> resultstring(widesize);

			int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);

			if (convresult != widesize)
			{
				throw std::exception("La falla!");
			}

			return std::wstring(&resultstring[0]);
		}

		inline	std::string WideByte2Acsi(std::wstring& wstrcode)
		{
			int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
			if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
			{
				throw std::logic_error("Invalid UTF-8 sequence.");
			}
			if (asciisize == 0)
			{
				throw std::logic_error("Error in conversion.");
			}
			std::vector<char> resultstring(asciisize);
			int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);

			if (convresult != asciisize)
			{
				throw std::logic_error("La falla!");
			}

			return std::string(&resultstring[0]);
		}

		inline std::string UTF_82ASCII(std::string& strUtf8Code)
		{
			std::string strRet("");
			//先把 utf8 转为 unicode  
			std::wstring wstr = Utf82Unicode(strUtf8Code);
			//最后把 unicode 转为 ascii  
			strRet = WideByte2Acsi(wstr);
			return strRet;
		}

#endif // _WIN32

	}

	/// @brief 时间类工具箱
	namespace time_tools
	{


		/// <summary>
		/// 根据指定格式，获取当前时间:
		/// format:"%Y-%m-%d %H:%M:%S" ms_flag=1 ==> 2023-06-27 17:08:40.030
		/// format:"%Y%m%d%H%M%S" ms_flag=0 ==> 20230627170840030
		/// </summary>
		/// <param name="format">指定年月日，时分秒格式</param>
		/// <param name="ms_flag">指定是否输出ms,if is true，则以.分割输出ms, else 直接将ms追加到末尾</param>
		/// <returns></returns>
		inline std::string getCurrentTime(const std::string& format, bool ms_flag) {
			try {
				auto now = std::chrono::system_clock::now();
				auto duration = now.time_since_epoch();
				auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

				std::time_t time = std::chrono::system_clock::to_time_t(now);
				std::tm* tm = std::localtime(&time);

				std::ostringstream oss;
				if (ms_flag)
				{
					oss << std::put_time(tm, format.c_str()) << "." << std::setfill('0') << std::setw(3) << millis % 1000;
				}
				else
				{
					oss << std::put_time(tm, format.c_str()) << std::setfill('0') << std::setw(3) << millis % 1000;
				}

				return oss.str();
			}
			catch (const std::exception& e) {
				// Handle exception
				std::cerr << "Exception occurred: " << e.what() << std::endl;
				return "";
			}
		}



		/**
		* @description	: 获取当前时间,按指定格式输出s.
		* @general		: T: 表curTime类型, 限制为char*, char[]; N为对应其大小.
		* @param		: format:默认输出格式:char[N]=2021-12-06 10:56:53
		* @return		: string类型当前时间
		* @exception	: range_error
		*/
		inline std::string getCurrentTime(char* curTime, const char* format = "%Y-%m-%d %H:%M:%S")
		{
			memset(curTime, 0x00, TIME_LEN);

			char 		current_sec[TIME_LEN];
			time_t      seconds;
			tm* today;

			time(&seconds);
			today = localtime(&seconds);
			memset(current_sec, 0x00, sizeof(current_sec));
			strftime(current_sec, sizeof(current_sec), format, today);
			//将 current_sec N-1 个字节写入 curTime. 最后添加空终止符.
			int res = sprintf_s(curTime, TIME_LEN, "%s", current_sec);
			return curTime;
		}


		/**
		* @description	: 获取当前时间,按指定格式输出s.
		* @general		: T: 表curTime类型, 限制为char*, char[]; N为对应其大小.
		* @param		: format:默认输出格式:char[N]=2021-12-06 10:56:53
		* @return		: string类型当前时间
		* @exception	: range_error
		*/
		inline std::string getCurrentTime(const char* format = "%Y-%m-%d %H:%M:%S")
		{
			char 		current_sec[TIME_LEN];
			time_t      seconds;
			tm* today;

			time(&seconds);
			today = localtime(&seconds);
			memset(current_sec, 0x00, sizeof(current_sec));
			strftime(current_sec, sizeof(current_sec), format, today);
			//将 current_sec N-1 个字节写入 curTime. 最后添加空终止符.
			return current_sec;
		}

		/**
		* @description	: 将时间戳转为时间字符串, 精确到秒
		* @param		: timeStamp:时间戳
		* @return		: time_t 类型时间戳
		* @exception	: 如果传入参数格式出错,则抛出异常
		* @note			: 注意时间字符串格式
		*/
		inline std::string TimeStamp2Str(time_t timeStamp) {
			struct tm* timeinfo = NULL;
			char buffer[80];
			timeinfo = localtime(&timeStamp);
			strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
			//printf("%s\n", buffer);
			return std::string(buffer);
		}


		/**
		* @description	: 将时间字符串转为时间戳, 精确到秒
		* @param		: str:时间字符串,格式:2022-07-21 11:01:50
		* @return		: time_t 类型时间戳
		* @exception	: 如果传入参数格式出错,则抛出异常
		* @note			: 注意时间字符串格式
		*/
		inline time_t StringToTimeStamp(std::string str) {
			struct tm tm_;
			int year, month, day, hour, minute, second;
			try
			{
				sscanf(str.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
				tm_.tm_year = year - 1900;
				tm_.tm_mon = month - 1;
				tm_.tm_mday = day;
				tm_.tm_hour = hour;
				tm_.tm_min = minute;
				tm_.tm_sec = second;
				tm_.tm_isdst = 0;
			}
			catch (std::invalid_argument& e)
			{
				std::cout << "传入参数 str 格式错误: " << e.what() << std::endl;
			}

			time_t timeStamp = mktime(&tm_);
			return timeStamp;
		}



		/// @brief months since January - [1, 12]
		/// @return months since January - [1, 12]
		inline int getCurMonth()
		{
			time_t      seconds;
			tm* today;
			time(&seconds);
			today = localtime(&seconds);
			//cout << today->tm_year + 1900 << endl;
			//cout << today->tm_yday << endl;
			return (today->tm_mon + 1);
		}

		/// @brief day of the month - [1, 31]
		/// @return day of the month - [1, 31]
		inline int getCurDay()
		{
			time_t      seconds;
			tm* today;
			time(&seconds);
			today = localtime(&seconds);
			//cout << today->tm_year + 1900 << endl;
			//cout << today->tm_yday << endl;
			return (today->tm_mday);
		}

		/// @brief 得到当前年份 eg.2023
		inline int	getYday()
		{
			time_t      seconds;
			tm* today;
			time(&seconds);
			today = localtime(&seconds);
			//cout << today->tm_year + 1900 << endl;
			//cout << today->tm_yday << endl;
			return (1900 + today->tm_year);
		}

		inline int	getCurHour()
		{
			time_t      seconds;
			tm* today;
			time(&seconds);
			today = localtime(&seconds);
			//cout << today->tm_year + 1900 << endl;
			//cout << today->tm_yday << endl;
			return (today->tm_hour);
		}

		inline int	getCurMinute()
		{
			time_t      seconds;
			tm* today;
			time(&seconds);
			today = localtime(&seconds);
			//cout << today->tm_year + 1900 << endl;
			//cout << today->tm_yday << endl;
			return (today->tm_min);
		}

	}

	/// @brief 常用工具类集合
	namespace utils
	{

#if CPP_STANDARD >= 201103L

		/// <summary>
		/// 拆分字符串，根据指定分隔符
		/// </summary>
		/// <param name="src">待拆分字符串</param>
		/// <param name="delimiter">支持regex的分隔符</param>
		/// <returns></returns>
		[[deprecated]]
		inline std::vector<std::string> split(const std::string& src, const std::string& delimiter/*, std::vector<std::string>& dst*/)
		{
			//dst.clear();
			std::regex ws_re(delimiter);
			std::vector<std::string> v(std::sregex_token_iterator(src.begin(), src.end(), ws_re, -1), std::sregex_token_iterator());
			//dst.swap(v);
			//v.clear();
			return v;
		}
#endif // 

		/**
		* @description	: 格式化字符串,返回格式化后的 std::string 对象
		* @param		: fmt: 表示格式化字符.
		* @return		: 格式化后的 std::string 对象
		* @exception	: 如果规定的格式化符号与实际参数的类型不匹配,行为未定义.
		* @note			: 尤其注意: 若 %f 对应 12.0f 而不是 12
		* @sites		: https://en.cppreference.com/w/cpp/chrono/system_clock/formatter#Format_specification
		*/
		template<class... T>
		inline std::string format(const char* fmt, const T&...t)
		{
			const auto len = snprintf(nullptr, 0, fmt, t...);
			if (len <= 0)
			{
				throw std::runtime_error("Error during formatting.[uni_box::utils::format()]");
			}
			std::string r;
			r.resize(static_cast<size_t>(len) + 1);
			snprintf(&r.front(), len + 1, fmt, t...);  // Bad boy
			r.resize(static_cast<size_t>(len));
			return r;
		}

		template<typename ... Args>
		inline std::string string_format(const std::string& format, Args ... args)
		{
			size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
			if (size <= 0) { throw std::runtime_error("Error during formatting."); }
			std::unique_ptr<char[]> buf(new char[size]);
			snprintf(buf.get(), size, format.c_str(), args ...);
			return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
		}


		/// <summary>
		/// 提出str中指定字符
		/// </summary>
		/// <param name="str"></param>
		/// <param name="character"></param>
		/// <returns></returns>
		inline std::string removeCharacter(const std::string& str, char character) {
			std::string result = str;
			result.erase(std::remove_if(result.begin(), result.end(), [character](char c) {
				return c == character;
				}), result.end());
			return result;
		}


		/// <summary>
		/// 将字符串解析为指定格式的浮点数;
		/// 根据format 长度截断 str;
		/// format长度必须 == str 长度
		/// eg: 000123, "00.0000" => 0.0123
		/// eg: -020, "0000" => -20
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="str"></param>
		/// <param name="format">指定格式，用0占位</param>
		/// <returns></returns>
		template <typename T>
		inline T parseStringToNumber(const char* str, const char* format)
		{
			bool isNegative = false;
			bool flag_ = false;
			if (str[0] == '-')
			{
				isNegative = true;
			}
			T result = 0;
			int integerPartLength = 0;
			int decimalPartLength = 0;
			int integerPartValue = 0;
			int decimalPartValue = 0;

			// Determine the length of the integer and decimal parts in the format string
			for (size_t i = 0; i < strlen(format); i++)
			{
				if (format[i] == '0')
				{
					if (decimalPartLength >= 1)
					{
						if (flag_)
						{
							flag_ = false;
						}
						else
							decimalPartLength++;
					}
					else
					{
						integerPartLength++;
					}
				}
				else if (format[i] == '.')
				{
					decimalPartLength = 1;
					flag_ = true;
				}
			}

			//cout << "integerPartLength: " << integerPartLength << ", decimalPartLength: " << decimalPartLength << endl;

			std::string data_;
			if (isNegative)
			{
				data_.assign(str, 1, integerPartLength + decimalPartLength - 1);
			}
			else
				data_.assign(str, 0, integerPartLength + decimalPartLength);


			// Parse the integer part of the input string
			if (isNegative)
			{
				--integerPartLength;
			}
			if (data_.size() >= integerPartLength)
				//if (str_len >= integerPartLength)
			{
				for (int i = 0; i < integerPartLength; i++)
				{
					int digitValue = data_[i] - '0';
					integerPartValue += digitValue * pow(10, integerPartLength - i - 1);
				}
			}
			else
			{
				throw std::invalid_argument("Input string is too short for the specified format.");
			}

			// Parse the decimal part of the input string
			if (decimalPartLength > 0)
			{
				int decimalStartIndex = integerPartLength;
				int decimalEndIndex = integerPartLength + decimalPartLength;

				if (data_.size() >= decimalEndIndex)
					//if (str.length() >= decimalEndIndex)
				{
					for (int i = decimalStartIndex; i < decimalEndIndex; i++)
					{
						int digitValue = data_[i] - '0';
						decimalPartValue += digitValue * pow(10, decimalEndIndex - i - 1);
					}

					result = (T)(integerPartValue + decimalPartValue / pow(10, decimalPartLength));
				}
				else
				{
					throw std::invalid_argument("Input string is too short for the specified format2.");
				}
			}
			else
			{
				result = (T)integerPartValue;
			}

			if (isNegative)
			{
				return -result;
			}
			else
				return result;
		}


		/// <summary>
		/// 将数值型按照格式format转为字符型；数字数据：则在不满位数(由format指定位数)时左补 0; format长度小于str时,截断.
		/// eg: -2.14  "00000" => "-0214"
		/// eg: -2.14  "0000" => "-214"
		/// eg: -2.14  "000" => "-21"
		/// </summary>
		/// <typeparam name="T">必须为数值型,否则抛出异常</typeparam>
		/// <param name="str_">数值型:其中负号'-'算一位,而小数点不算</param>
		/// <param name="format">指定位数</param>
		/// <returns></returns>
		template<typename T>
		inline std::string  parseNumberToString(const T& str_, const char* format)
		{
			// 判断 T 是否为非数值型（非整型和非浮点型）
			if (!std::is_integral<T>::value && !std::is_floating_point<T>::value)
			{
				throw std::invalid_argument("输入T为非数值型!");
			}

			// parseNumberToString(-0.045, "000000") => -00045
			// 652, "00000" => 00652

			std::stringstream  oss;
			oss << str_;
			auto str = removeCharacter(oss.str(), '.');

			std::cout << "str: " << str << std::endl;
			std::cout << "size: " << str.size() << std::endl;


			bool isNegative = false;
			bool flag_ = false;

			if (str[0] == '-')
			{
				isNegative = true;
			}

			std::string data_;
			int integerPartLength = 0;
			int decimalPartLength = 0;

			// Determine the length of the integer and decimal parts in the format string
			for (size_t i = 0; i < strlen(format); i++)
			{
				if (format[i] == '0')
				{
					if (decimalPartLength >= 1)
					{
						if (flag_)
						{
							flag_ = false;
						}
						else
							decimalPartLength++;
					}
					else
					{
						integerPartLength++;
					}

					/*	if (str[i] != '.')
						{
							data_.push_back(str[i]);
						}*/
				}
				else if (format[i] == '.')
				{
					decimalPartLength = 1;
					flag_ = true;
				}

			}

			std::cout << "integerPartLength: " << integerPartLength << std::endl;
			std::cout << "decimalPartLength: " << decimalPartLength << std::endl;

			int delta = strlen(format) - str.size();
			//左侧补零
			if (delta > 0)
			{
				if (isNegative)
					data_.assign(str, 0, str.size()).insert(1, delta, '0');
				else
					data_.assign(str, 0, str.size()).insert(0, delta, '0');
			}
			//截断
			else if (delta < 0)
			{
				data_.assign(str, 0, integerPartLength + decimalPartLength);
			}
			else
			{
				data_.assign(str, 0, str.size());
			}
			return data_;

		}

		/// <summary>
		/// 获取数组个数
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="src"></param>
		/// <returns></returns>
		template <typename T, size_t N>
		inline	size_t getArraySize(T(&src)[N])
		{
			return sizeof(src);
		}



		/// <summary>
		/// 向dest中, 填充指定个数的ele元素;
		/// 需要人工保证,dest 大小 >= size,否则未定义;
		/// </summary>
		/// <param name="ele">填充元素</param>
		/// <param name="size">填充个数:若size = 数组大小,则数组最后一字节被ele填充,无'\0'结束符</param>
		/// <param name="dest">待填充的数组</param>
		/// <returns></returns>
		inline void PaddingElement(const char ele, int size, char dest[])
		{
			//for (size_t i = 0; i < size; i++)
			//{
			//	dest[i] = ele;
			//}
			memset(dest, ele, size);
		}

		/**
		* @description	: 分割字符串
		* @param		: s:带分离字符串; tokens: 存储分割后的字符串容器; delimiters: 正则表达式
		* @return		:
		* @exception	:
		*/
		inline	void split(const std::string& s, std::vector< std::string>& tokens, const std::string& delimiters = "$")
		{
			std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
			std::string::size_type pos = s.find_first_of(delimiters, lastPos);
			while (std::string::npos != pos || std::string::npos != lastPos) {
				tokens.push_back(s.substr(lastPos, pos - lastPos));//use emplace_back after C++11
				lastPos = s.find_first_not_of(delimiters, pos);
				pos = s.find_first_of(delimiters, lastPos);
			}
		}


		/**
		* @description	: char 和 wchar 类型互转
		* @param		:
		* @return		:
		* @exception	:
		*/
		inline int Wchar2Char(char* charStr, const wchar_t* wcharStr) {
			int len = WideCharToMultiByte(CP_ACP, 0, wcharStr, wcslen(wcharStr), NULL, 0, NULL, NULL);
			WideCharToMultiByte(CP_ACP, 0, wcharStr, wcslen(wcharStr), charStr, len, NULL, NULL);
			charStr[len] = '\0';
			return len;
		}

		inline	int Char2Wchar(wchar_t* wcharStr, const char* charStr) {
			int len = MultiByteToWideChar(CP_ACP, 0, charStr, strlen(charStr), NULL, 0);

			MultiByteToWideChar(CP_ACP, 0, charStr, strlen(charStr), wcharStr, len);
			wcharStr[len] = '\0';
			return len;
		}


		/**
		* @description	: 查找vector中重复元素
		* @param		: 带查找vector, 不能是字符串:char* , string
		* @return		: 重复元素的集合
		* @exception	:
		*/
		template<typename T>
		inline std::set<T> findDuplicates(std::vector<T> vec)        // 无引用，无常量
		{
			std::set<int> duplicates;
			std::sort(vec.begin(), vec.end());
			std::set<int> distinct(vec.begin(), vec.end());
			std::set_difference(vec.begin(), vec.end(), distinct.begin(), distinct.end(),
				std::inserter(duplicates, duplicates.end()));
			return duplicates;
		}

		/**
		* @description	: 任意基本类型转换为string
		* @param		: t:任意数值类型之引用
		* @return		: string类型数值
		* @exception	:
		*/
		template<typename T>
		inline std::string TtoStr(const T& t)
		{
			std::stringstream oss;
			oss << t;
			return oss.str();
		}

		/**
		* @description	: 保留N小数(四舍五入): 注意:cout有默认精度(.2),建议采用printf打印.
		* @param		: dst:原始数值之引用, N:保留位数
		* @return		: dst(.N)
		* @exception	:
		*/
		template<typename T, unsigned short N>
		inline T setPrecision(T& dst)
		{
			dst = floor(dst * pow(10.0, N) + 0.5) / pow(10.0, N);
			return dst;
		}


		/**
		* @description	:	string --> 任意基本类型: 对于浮点数建议采用double而非float.
		* @param		:	str:原始字符串型数值之引用, T:目标类型
		* @return		:	类型为T的值t
		* @exception	:	若以字母开头,则会溢出.
		*/
		template<typename T>
		inline T StrtoT(const std::string& str)
		{
			if (str.empty() || str == " ")
			{
				std::cerr << "str is empty or  blank !" << std::endl;
				return (T)0;
			}
			T t;
			std::istringstream iss(str);
			iss >> t;
			return t;
		}

		/**
		* @description  :	string --> 任意基本类型: 对于浮点数建议采用double而非float.
		* @param		:	chr:原始字符数组, T:目标类型
		* @return		:	类型为T的值t
		* @exception	:	若以字母开头,则会溢出.
		*/
		template<typename T>
		inline T StrtoT(const char* chr)
		{
			T t;
			std::string temp_str(chr);
			std::istringstream iss(temp_str);
			iss >> t;
			return t;
		}


		/// <summary>
		/// 根据精度 precision 从字符串src中解析成指定T类型数据
		/// 注意: src 必须以 null 结尾;
		/// </summary>
		/// <typeparam name="T">指定转换类型</typeparam>
		/// <param name="src">字符串数字: "112000"</param>
		/// <param name="precision">精度: 将src转为T类型,在除以precision</param>
		/// <returns></returns>
		//template<typename T>
		//typename std::enable_if<std::is_arithmetic<T>::value>::T
		inline double Str2TWithPrecision(const char* src, size_t precision)
		{
			return (double)(StrtoT<double>(src) / precision);
		}

		/**
		* @description	: 获取当前时间,按指定格式输出s.
		* @general		: T: 表curTime类型, 限制为char*, char[]; N为对应其大小.
		* @param		: format:默认输出格式:char[20]=2021-12-06 10:56:53
		* @return		: string类型当前时间
		* @exception	:
		*/
		template<unsigned int N>
		inline void transMonth2Char(char* month_)
		{
			memset(month_, 0x00, N);
			uni_box::time_tools::getCurrentTime(month_, "%m");

			if (strcmp("10", month_) == 0)
				sprintf_s(month_, N, "%s", "A");
			else if (strcmp("11", month_) == 0)
				sprintf_s(month_, N, "%s", "B");
			else if (strcmp("12", month_) == 0)
				sprintf_s(month_, N, "%s", "C");
			else
			{
				for (unsigned int i = 0; i < N - 1; ++i)
				{
					month_[i] = month_[i + 1];
				}
			}
		}

		template<typename T>
		inline bool CharNonEmptyCheck(const T& t1)
		{
			std::cout << (typeid(t1).name()) << ":" << t1 << std::endl;
			//char
			if (std::strncmp("char", typeid(t1).name(), 4) == 0)
			{
				// 判断char* or char[] 是否为空
				if (t1 == NULL || t1[0] == '\0' || strlen(t1) < 1)
				{
					return false;
				}

				else return true;
			}

			return false;
		}


		/// @brief 检查数字型值是否有效: 建议使用StrtoT将其转换下;
		/// @tparam T 检查类型
		/// @param t1 待检查参数
		/// @param min_value 下界
		/// @param max_value 上界
		/// @param overlap 重叠标志，true：允许max_value == min_value
		/// @return t1在上下界内返回true ;[min_value,max_value] if( min_value==max_value && overlap=true)  return true else false
		template<typename T>
		inline bool NumberNonEmptyCheck(T& t1, T min_value = static_cast<T>(0), T max_value = static_cast <T>(999999), bool overlap = true)
		{
			std::cout << (typeid(t1).name()) << ":" << t1 << std::endl;

			if (max_value < min_value)
			{
				printf("%s\n", "最大值无效，不能小于下限值~");
				//throw "最大值无效，不能小于下限值~";
				return false;
			}
			if (!overlap && (max_value == min_value))
			{
				printf("%s\n", "最大值无效，不能等于下限值~");
				return false;
			}
			if ((std::strncmp("float", typeid(t1).name(), 5) == 0) || (std::strncmp("double", typeid(t1).name(), 6) == 0))
			{
				//std::cout << min_value << std::endl;
				//printf("%.20f\n", min_value);

				if ((t1 >= min_value) && (t1 <= max_value))
				{
					return true;
				}
				else return false;
			}
			else
				//if (std::strncmp("int",typeid(t1).name(),3) == 0)
			{
				if (t1 >= min_value && t1 <= max_value)
				{
					return true;
				}
				else return false;
			}
		}


		/**
		* @description	: 右侧补充0
		* @param		: src 输入参数,  des:补全后的输出目的地. len: 补全后的总长度.
		* @return		: des
		* @exception	: Buffer too small
		* @note			: len 必须小于 des[]的长度.否则抛出run-time 错误. 不保证边界校验.
		*/
		inline char* AddRightZero2Str(const char* src, char des[], size_t len)
		{

			char temp[STRBUFF];
			memset(temp, 0x00, STRBUFF);

			size_t   need_len = 0;

			if (src == NULL /*|| strlen (des) > len*/)
			{
				return NULL;
			}

			//sprintf(des,"%s",src);
			sprintf(temp, "%s", src);

			//strlen 不包含空字符的长度
			size_t cur_len = strlen(src);
			need_len = len - cur_len;

			if (need_len > len) return NULL;

			for (size_t i = 0; i < need_len; ++i)
			{
				//从cur_len之后开始填充
				sprintf(temp + cur_len + i, "%s", "0");
			}
			//若传来的src为零
			//if (strlen(src) < 1)
			sprintf_s(des, len + 1, "%s", temp);
			//else
			//sprintf(des,"%s",temp,src);

			return des;
		}

		/**
		* @description	: 左侧补充0
		* @param		: src 输入参数,  des:补全后的输出目的地. len: 补全后的总长度(不含末位空字符).
		* @return		: void
		* @exception	:
		* @note			: len 必须小于 des[]的长度.否则抛出run-time 错误.
		*/
		inline char* AddLeftZero2Str(char* src, char des[], size_t len)
		{
			char temp[STRBUFF];
			memset(temp, 0x00, STRBUFF);

			size_t  need_len = 0;
			if (src == NULL || (*src == '\0'))
			{
				return NULL;
			}
			//sprintf(temp,"%s",src);
			//strlen 不包含空字符的长度
			need_len = len - strlen(src);
			if (need_len > len) return NULL;

			for (size_t i = 0; i < need_len; ++i)
			{
				sprintf(temp + i, "%s", "0");
			}
			strncat(temp, src, strlen(src));
			sprintf(des, "%s", temp);
			return des;
		}


		/**
		* @description	: 长度校验:字符串, 整型, 浮点型
		* @param		: t 输入参数,  len: 要求的长的
		* @return		: if (size <= len) return  true
		* @exception	:
		* @note			: 其中若为浮点型,则小数点也算一个长度.
		*/
		template<typename T>
		inline bool CheckLenValid(T t, size_t len)
		{
			std::string  str_ = uni_box::utils::TtoStr(t);
			if (str_.length() > len)
			{
				std::cout << str_.length() << std::endl;
				return false;
			}
			else
				return true;
		}

		/// <summary>
		/// t.len ∈ (min_len,max_len)
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="t"></param>
		/// <param name="max_len"></param>
		/// <param name="min_len"></param>
		/// <returns></returns>
		template<typename T>
		inline bool CheckLenValid(T&& t, size_t max_len, size_t min_len)
		{
			std::string  str_ = uni_box::utils::TtoStr(t);
			if ((str_.length() > max_len) || (str_.length() < min_len))
			{
				std::cout << str_.length() << std::endl;
				return false;
			}
			else
				return true;
		}

		/**
		* @description	: 保存数据datas至文件path中.
		* @param		: datas 数据,  path: 文件全路径
		* @return		: bool
		* @exception	:
		* @note			: 其中若为浮点型,则小数点也算一个长度.
		*/
		inline void saveData2File(const char* datas, const char* path)
		{
			FILE* f;
			if ((f = fopen(path, "a+")) != NULL)
			{
				//char cur_time[20];
				//getCurrentTime<sizeof(cur_time)>(cur_time);
				//fprintf(f, cur_time);
				//fprintf(f, "\n");
				fprintf(f, datas);
				fprintf(f, "\n");
				fflush(f);
				fclose(f);
			}
		}

		/// <summary>
		/// 
		/// note:
		/// 输入字符串的长度应该小于或等于要填充的总长度。如果输入字符串长度已经大于或等于总长度，这些函数将直接返回原始字符串而不做任何处理。
		/// totalLength 参数应该是一个正整数。如果传递一个非正整数，这些函数将抛出异常或返回空字符串。
		/// 如果使用默认的填充字符 ' ' 进行填充，注意不要将其与原始字符串中可能包含的空格字符混淆。
		/// 如果输入字符串中包含多字节字符（例如 UTF-8 编码的字符串），则需要使用多字节字符函数库或 Unicode 函数库来计算字符串的长度和填充字符的个数。
		/// 如果填充字符不是 ASCII 字符，那么填充后的字符串可能无法正确地显示或处理，具体取决于使用的终端或文本编辑器的支持能力。
		/// </summary>
		/// <param name="str"></param>
		/// <param name="totalLength"></param>
		/// <param name="paddingChar"></param>
		/// <returns></returns>
		inline std::string PadLeft(const std::string str, size_t totalLength, char paddingChar = ' ')
		{
			if (str.length() >= totalLength)
				return str;

			std::string padding(totalLength - str.length(), paddingChar);

			return padding + str;
		}

		inline std::string PadRight(const std::string str, size_t totalLength, char paddingChar = ' ')
		{
			if (str.length() >= totalLength)
				return str;

			std::string padding(totalLength - str.length(), paddingChar);

			return str + padding;
		}


		/// <summary>
		/// 将字符 '0'-'9' 转为数字 0-9 
		/// </summary>
		/// <param name="src">字符型数字，范围 0-9</param>
		/// <returns></returns>
		inline unsigned int	 Char2Int(char src)
		{
			auto src_ = static_cast<unsigned int>(src);
			if (src_ < 48 || src_ > 57)
			{
				return 0;
			}
			return (src_ - 48);
		}

		/// <summary>
		/// 将Int 类型转为 char 类型，建议使用std::to_string。
		/// </summary>
		/// <param name="src"></param>
		/// <returns></returns>
		inline char Int2Char(int src)
		{
			if (src < 0 || src > 9)
			{
				std::cerr << "src is not in [0,9]" << std::endl;
				throw std::invalid_argument("error in Int2Char(): src is not in [0,9]");
			}
			return (static_cast<char>(src + 48));
		}

		/// <summary>
		/// 将浮点型转为科学计数法
		/// note：
		/// double value = 1234.56789;
		/// int precision = 2;
		/// std::string scientificStr = ToScientific(value, precision);
		/// </summary>
		/// <param name="value"></param>
		/// <param name="precision"></param>
		/// <returns></returns>
		inline std::string ToScientific(double value, int precision) {
			// step 1: rounding
			std::stringstream ss;
			ss << std::fixed << std::setprecision(precision) << value;
			double roundedValue = std::stod(ss.str());

			// step 2: move decimal point
			int exponent = 0;
			while (roundedValue >= 10.0) {
				roundedValue /= 10.0;
				exponent++;
			}
			while (roundedValue < 1.0) {
				roundedValue *= 10.0;
				exponent--;
			}

			// step 3: format mantissa
			std::stringstream mantissa;
			mantissa << std::fixed << std::setprecision(precision) << roundedValue;
			std::string mantissaStr = mantissa.str();
			mantissaStr.erase(std::remove(mantissaStr.begin(), mantissaStr.end(), '.'), mantissaStr.end());

			// step 4: format result
			std::stringstream result;
			result << std::fixed << std::setprecision(precision);
			result << mantissaStr[0] << "." << mantissaStr.substr(1);
			result << "E" << (exponent >= 0 ? "+" : "") << exponent;
			return result.str();
		}

		inline std::string ToScientific(const std::string& value, int precision) {
			double dValue = std::stod(value);

			// step 1: rounding
			std::stringstream ss;
			ss << std::fixed << std::setprecision(precision) << dValue;
			double roundedValue = std::stod(ss.str());

			// step 2: move decimal point
			int exponent = 0;
			while (roundedValue >= 10.0) {
				roundedValue /= 10.0;
				exponent++;
			}
			while (roundedValue < 1.0) {
				roundedValue *= 10.0;
				exponent--;
			}

			// step 3: format mantissa
			std::stringstream mantissa;
			mantissa << std::fixed << std::setprecision(precision) << roundedValue;
			std::string mantissaStr = mantissa.str();
			mantissaStr.erase(std::remove(mantissaStr.begin(), mantissaStr.end(), '.'), mantissaStr.end());

			// step 4: format result
			std::stringstream result;
			result << std::fixed << std::setprecision(precision);
			result << mantissaStr[0] << "." << mantissaStr.substr(1);
			result << "E" << (exponent >= 0 ? "+" : "") << exponent;
			return result.str();
		}



		/**
		* @description	: 去除字符串首尾空格
		* @param		: s：含空格的字符串
		* @return		: 返回该字符串
		* @exception	:
		* @note			:
		*/
		inline	std::string& trimBlank(std::string& s)
		{
			if (s.empty())
			{
				return s;
			}
			s.erase(0, s.find_first_not_of(" "));
			s.erase(s.find_last_not_of(" ") + 1);
			return s;
		}

		//// trim from start (in place)
		//static inline void ltrim(std::string& s) {
		//	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		//		return !std::isspace(ch);
		//		}));
		//}

		//// trim from end (in place)
		//static inline void rtrim(std::string& s) {
		//	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		//		return !std::isspace(ch);
		//		}).base(), s.end());
		//}

		//// trim from both ends (in place)
		//static inline void trim(std::string& s) {
		//	rtrim(s);
		//	ltrim(s);
		//}


		/// <summary>
		/// copy 版本，不在源字符串上修改
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		static inline  std::string trimCopy(std::string s, std::string symbol = " ")
		{
			if (s.empty())
			{
				return s;
			}
			s.erase(0, s.find_first_not_of(symbol));
			s.erase(s.find_last_not_of(symbol) + 1);
			return s;
		}

		//// trim from start (copying)
		//static inline std::string ltrim_copy(std::string s) {
		//	ltrim(s);
		//	return s;
		//}

		//// trim from end (copying)
		//static inline std::string rtrim_copy(std::string s) {
		//	rtrim(s);
		//	return s;
		//}

		//// trim from both ends (copying)
		//inline std::string trim_copy(std::string s) {
		//	trim(s);
		//	return s;

		//}

		/**
		* @description	: 去除尾部指定符号
		* @param		: symbol:指定符号的ASCII码（空格：32）
		* @return		: 返回该字符串
		* @exception	:
		* @note			:
		*/
		inline char* rtrim(char* str, int symbol)
		{
			if (str == NULL || *str == '\0')
			{
				return str;
			}
			int len = strlen(str);
			char* p = str + len - 1;
			while (p >= str && ((int)(*p) == symbol))
			{
				*p = '\0'; --p;
			}
			return str;
		}


		/**
		* @description	: 去除首部指定符号
		* @param		: ascii_code:指定符号的ASCII码（空格：32）
		* @return		: 返回该字符串
		* @exception	:
		* @note			:
		*/
		inline char* ltrim(char* str, int symbol)
		{
			if (str == NULL || *str == '\0')
			{
				return str;
			}
			int len = 0;
			char* p = str;
			while (*p != '\0' && ((int)(*p) == symbol))
			{
				++p; ++len;
			}
			memmove(str, p, strlen(str) - len + 1);
			return str;
		}



		/**
		* @description	: 去除首尾指定符号
		* @param		: ascii_code:指定符号的ASCII码（空格：32）
		* @return		: 返回该字符串
		* @exception	:
		* @note			:
		*/
		inline char* trim(char* str, int symbol)
		{
			if (str == NULL || *str == '\0')
			{
				return str;
			}
			str = rtrim(str, symbol);
			str = ltrim(str, symbol);
			return str;
		}

		/**
	* @description	: 去除尾部指定符号
	* @param		: symbol:指定符号的ASCII码（空格：32）
	* @return		: 返回该字符串
	* @exception	:
	* @note			:
	*/
		inline char* trimEnder(char* str)
		{
			if (str == NULL)
			{
				std::cerr << "为空" /*<< endl*/;
				return str;
			}
			int len = strlen(str);
			char* p = str + len + 1;
			if (*p == '\0')
			{
				--p;
			}
			return str;
		}

#define REMOVE_HEAD_SYMBOL  1
#define REMOVE_TAIL_SYMBOL  2
#define REMOVE_HEAD_TAIL_SYMBOL  0
		/**
		* @description	: 去除首尾指定符号
		* @param		: ascii_code:指定符号的ASCII码（空格：32）；head_tail：0：去除首尾指定符号，1：去除头部指定符号
		* @return		: 返回该字符串
		* @exception	:
		* @note			:  标准的空白字符包括：
		*				   ' '     (0x20)    space (SPC) 空格符
		*				   '\t'    (0x09)    horizontal tab (TAB) 水平制表符
		*				   '\n'    (0x0a)    newline (LF) 换行符
		*				   '\v'    (0x0b)    vertical tab (VT) 垂直制表符
		*			       '\f'    (0x0c)    feed (FF) 换页符
		*				   '\r'    (0x0d)    carriage return (CR) 回车符
		*				   //windows \r\n linux \n mac \r
		*/

		inline	char* removeSymbol(char* src, int ascii_code, int head_tail = 0)
		{

			if (src == NULL || *src == '\0')
			{
				return src;
			}

			//1:去除头尾指定符号
			switch (head_tail)
			{

				case REMOVE_HEAD_SYMBOL:
				{
					return ltrim(src, ascii_code);
				}
				break;

				case REMOVE_TAIL_SYMBOL:
				{
					src = rtrim(src, ascii_code);
					return src;
				}
				break;
				case REMOVE_HEAD_TAIL_SYMBOL:
				{
					return trim(src, ascii_code);
				}
				break;
				default:
				printf("error: case:%d", head_tail);
				return nullptr;
				break;
			}

		}



		/// <summary>
		/// 将input末尾加上空终止符,并copy到output中; 自动去除首尾空格
		/// output长度要大于length
		/// </summary>
		/// <param name="input"></param>
		/// <param name="output"></param>
		/// <param name="length">input的长度</param>
		/// <returns></returns>
		inline	char* AppendNullTerminator(const char* input, char* output, size_t length)
		{
			std::memset(output, 0x00, length);
			std::memcpy(output, input, length);
			output[length] = '\0';
			removeSymbol(output, 0x20);
			return output;
		}

		/// <summary>
		/// 将char* 中从头开始长度length的字符串 转入 string 容器中，默认去除首位空格
		/// </summary>
		/// <param name="input"></param>
		/// <param name="out_"></param>
		/// <param name="length"></param>
		/// <returns></returns>
		inline std::string& CharsToString(const char* input, std::string& out_, size_t length)
		{
			out_.clear();
			//std::memcpy(out_.data(), input, length);
			out_.append(input, 0, length);
			if (length > 1)
			{
				trimBlank(out_);
			}
			return out_;
		}


		/// <summary>
		/// 向src右侧填充指定内容，填充后src总长度为 totalWidth
		/// char src[5] = "123";
		/// PadRight(src,5,'0') => "12300" 无空字节结尾
		/// note： src max length <= 120 byte
		/// </summary>
		/// <param name="src">必须以空字符结尾的字符串，否则行为未定义</param>
		/// <param name="totalWidth">填充后总长度，不能超过 src 长度</param>
		/// <param name="paddingChar"></param>
		/// <returns></returns>
		inline char* PadRight(char* src, size_t totalWidth, char paddingChar)
		{
			if (!src)
			{
				std::cerr << "src is null " << std::endl;
				return nullptr;
			}

			char temp[STRBUFF];
			memset(temp, 0x00, STRBUFF);

			size_t   need_len = 0;

			sprintf(temp, "%s", src);

			//strlen 不包含空字符的长度
			size_t cur_len = strlen(src);
			need_len = totalWidth - cur_len;

			if (cur_len > totalWidth)
				throw std::invalid_argument("TotalWidth is smaller than src length.");

			for (size_t i = 0; i < need_len; ++i)
			{
				memcpy(temp + cur_len + i, &paddingChar, 1);
			}

			memcpy(src, temp, totalWidth);
			return src;
		}

		/// <summary>
		/// 向src左侧填充指定内容，填充后src总长度为 totalWidth
		/// </summary>
		/// <param name="src">必须以空字符结尾的字符串，否则行为未定义</param>
		/// <param name="totalWidth"></param>
		/// <param name="paddingChar"></param>
		/// <returns></returns>
		inline char* PadLeft(char* src, size_t totalWidth, char paddingChar)
		{
			if (!src)
			{
				std::cerr << "src is null " << std::endl;
				return nullptr;
			}

			char temp[STRBUFF];
			memset(temp, 0x00, STRBUFF);

			size_t   need_len = 0;
			sprintf(temp, "%s", src);

			//strlen 不包含空字符的长度
			size_t cur_len = strlen(src);
			need_len = totalWidth - cur_len;

			if (cur_len > totalWidth)
				throw std::invalid_argument("TotalWidth is smaller than src length.");

			for (size_t i = 0; i < need_len; ++i)
			{
				memcpy(temp + i, &paddingChar, 1);
			}
			memcpy(temp + need_len, src, cur_len);

			memcpy(src, temp, totalWidth);
			return src;
		}

	}

	/// @brief 算法工具类
	namespace algorithm
	{
	}

	/// <summary>
	/// 字节序
	/// </summary>
	enum host_endian
	{
		LittleEndian = 0, BigEndian = 1, UnkownEndian = 2
	};

	/// @brief 网络通信类
	namespace net
	{
#define MAGIC 0x12345678

		/// <summary>
		/// get the byte order of current host
		/// </summary>
		/// <returns>enum host_endian</returns>
		inline host_endian getCurHostEndian()
		{
			// 判断当前主机字节序是否为小端字节序
			static const uint16_t value = 0x0001;
			if (reinterpret_cast<const uint8_t*>(&value)[0] == 0x01)
			{
				return LittleEndian;
			}
			else
				return BigEndian;
		}

		/// <summary>
		/// 当前主机字节序是否为大端字节序(Network byte order)
		/// </summary>
		/// <returns></returns>
		inline bool isBigEndian()
		{
			static const uint16_t value = 0x0001;
			if (reinterpret_cast<const uint8_t*>(&value)[0] == 0x01)
			{
				return false;
			}
			else
				return true;
		}

		/// <summary>
		/// 转换字节序：只限整型k和浮点型
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="value"></param>
		/// <returns></returns>
		template<typename T>
		inline	typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
			& ByteSwap(T& value)
		{
			static_assert(std::is_trivially_copyable<T>::value, "ByteSwap: Unsupported type");
			constexpr size_t size = sizeof(T);
			unsigned char buffer[size];
			std::memcpy(buffer, &value, size);
			for (size_t i = 0; i < size / 2; ++i)
			{
				std::swap(buffer[i], buffer[size - 1 - i]);
			}
			//T result;
			//std::memcpy(&result, buffer, size);
			std::memcpy(&value, buffer, size);
			return value;
		}

		/// <summary>
		/// Converting host byte order to Little endian 
		/// </summary>
		/// <typeparam name="T">data type</typeparam>
		/// <param name="value">data</param>
		template <typename T>
		inline T to_little_endian(T& value)
		{
			// If not, swap the byte order of the value
			uint8_t temp[sizeof(T)];
			memcpy(temp, &value, sizeof(T));
			for (std::size_t i = 0; i < sizeof(T); ++i)
			{
				reinterpret_cast<char*>(&value)[i] = temp[sizeof(T) - 1 - i];
			}

			return value;
		}

		/// <summary>
		/// 将主机字节序转换为大端字节序;
		/// 大端字节序（Big-Endian）指的是高位字节存储在内存的低地址处，低位字节存储在内存的高地址处，这样的存储方式类似于书写时从左到右的顺序。
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="value">要转换的数据流</param>
		template<typename T>
		inline T& to_big_endian(T& value) {

			// 使用指针运算将结构体转换为 char 数组
			uint8_t* ptr = reinterpret_cast<uint8_t*>(&value);

			// 反转数组中的每个元素
			for (size_t i = 0; i < sizeof(T) / 2; i++)
			{
				char temp = ptr[i];
				ptr[i] = ptr[sizeof(T) - i - 1];
				ptr[sizeof(T) - i - 1] = temp;
			}

			return value;
		}



		// 定义一个通用的字节序转换函数，从大端转小端
		template <typename T>
		inline T ConvertBigEndianToLittle(const void* data)
		{
			T value;
			const uint8_t* bytes = static_cast<const uint8_t*>(data);
			for (std::size_t i = 0; i < sizeof(T); ++i)
			{
				reinterpret_cast<uint8_t*>(&value)[i] = bytes[sizeof(T) - i - 1];
			}
			return value;
		}

	}

	/// <summary>
	/// 随机数
	/// </summary>
	namespace random
	{

		/// <summary>
		/// 产生指定范围内的真随机数
		/// </summary>
		/// <param name="minValue">最小值</param>
		/// <param name="maxValue">最大值</param>
		/// <returns>介于最值间的真随机数</returns>
		inline int getRandomInScope(int minValue = 1, int maxValue = 20000)
		{
			std::random_device rd;
			std::mt19937 engine(rd());
			std::uniform_int_distribution<int> dist(minValue, maxValue);

			int randomNum = dist(engine);
			return randomNum;
		}
	}
}

#endif