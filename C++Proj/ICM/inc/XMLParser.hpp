#pragma once

#include <unordered_map>
#include <string>
#include <regex>

#include <boost/property_tree/ptree.hpp>
#include "boost/property_tree/xml_parser.hpp"

namespace renaissance::parser
{

	static const auto NoObject = "NoObject";

	/// <summary>
	/// 消息ID类型
	/// </summary>
	using  IdentifyType = int;

	/// <summary>
	/// 消息中字段定义
	/// </summary>
	struct  Variable_
	{
		std::string var_name_; /*消息中字段名*/
		std::string dataType_; /*字段类型:T,R,I,...*/
		std::string tag_; /*字段的标记*/
		std::string description_; /*字段描述*/
		std::string index_; /*字段序号*/
		std::string equipName_; /*字段所属设备名称描述*/
		std::string propName_; /*字段所属属性描述*/
		std::string unit_; /*字段所属属性描述*/
	};


	/// <summary>
	/// 消息定义
	/// </summary>
	struct  Message_
	{
		IdentifyType identity_; /*消息id*/
		std::string name_; /*消息名*/
		std::string tag_; /*消息的标识*/
		std::vector<Variable_> vars;  /*消息的字段集合*/
	};

	/// <summary>
	/// 消息集合定义
	/// </summary>
	using MsgCollectionType = std::unordered_map<IdentifyType, Message_>;


	class  XMLParser
	{
	public:
		XMLParser() = default;
		~XMLParser() = default;

		/// <summary>
		/// 从指定的XML(依规定XML格式)中读取配置信息
		/// </summary>
		/// <param name="full_path_file">xml全路径名</param>
		/// <param name="nodeName">读取节点名:只能是 Link.ReceiveMessages or Link.SendMessages</param>
		/// <returns>若不发生意外,返回含有电文集合信息,反之则返回空的集合</returns>
		inline static  MsgCollectionType resolveMessages(const std::string full_path_file, const std::string nodeName)
		{
			MsgCollectionType m_RecvMessages;
			//m_RecvMessages.clear();

			try
			{
				namespace pt = boost::property_tree;
				pt::ptree tree;
				pt::read_xml(full_path_file, tree);
				auto recvMsgs = tree.get_child(nodeName);

				int count_ = 0;
				for (auto it = recvMsgs.begin(); it != recvMsgs.end(); ++it)
				{
					//遍历属性
					if (it->first == "<xmlattr>")
					{
						continue;
					}
					//注释
					else if (it->first == "<xmlcomment>")
					{
						continue;
					}
					// 遍历每个Message
					else
					{
						Message_ wms;
						++count_;
						auto message_ = it->second.get_child("");
						for (auto& msg : message_)
						{
							//if ((msg.first != "<xmlattr>") && (msg.first != "<xmlcomment>"))
							if (msg.first == "Properties")
							{
								//cout << msg.second.get<std::string>("Property.<xmlattr>.Value") << endl;

								for (auto& property_ : msg.second)
								{
									//cout << property_.second.get<std::string>("<xmlattr>.Name") << endl;
									//cout << property_.second.get<std::string>("<xmlattr>.Value") << endl;

									if (property_.second.get<std::string>("<xmlattr>.Name") == "Name")
									{
										wms.name_ = property_.second.get<std::string>("<xmlattr>.Value");
										//cout << property_.second.get<std::string>("<xmlattr>.Value") << endl;
									}

									if (property_.second.get<std::string>("<xmlattr>.Name") == "Identity")
									{
										wms.identity_ = property_.second.get<IdentifyType>("<xmlattr>.Value");
									}

									if (property_.second.get<std::string>("<xmlattr>.Name") == "Tag")
									{
										wms.tag_ = property_.second.get<std::string>("<xmlattr>.Value");
									}

								}
							}
							else if (msg.first == "Variables")
							{
								int var_count_ = 0;

								// 遍历电文中每个变量
								for (auto& var_ : msg.second)
								{
									++var_count_;
									Variable_ variable;
									for (auto props_ : var_.second)
									{
										if (props_.first == "<xmlattr>")
										{
											continue;
										}
										else if (props_.first == "<xmlcomment>")
										{
											continue;
										}
										else
										{
											for (auto& prop_ : props_.second)
											{
												if (prop_.second.get<std::string>("<xmlattr>.Name") == "Name")
												{
													variable.var_name_ = prop_.second.get<std::string>("<xmlattr>.Value");
													//std::cout << prop_.second.get<std::string>("<xmlattr>.Value") << std::endl;
												}

												if (prop_.second.get<std::string>("<xmlattr>.Name") == "DataType")
												{
													variable.dataType_ = prop_.second.get<std::string>("<xmlattr>.Value");
													//std::cout << prop_.second.get<std::string>("<xmlattr>.Value") << std::endl;
												}

												if (prop_.second.get<std::string>("<xmlattr>.Name") == "Tag")
												{
													variable.tag_ = prop_.second.get<std::string>("<xmlattr>.Value");
													//std::cout << prop_.second.get<std::string>("<xmlattr>.Value") << std::endl;

													auto ep_ = parseData(variable.tag_);

													if (!ep_.empty())
													{
														if (ep_.size() < 2)
														{
															variable.propName_ = ep_[0];
															variable.equipName_ = NoObject;
														}
														else
														{
															variable.equipName_ = ep_[0];
															variable.propName_ = ep_[1];
														}
													}
													else
													{
														variable.propName_ = NoObject;
														variable.equipName_ = NoObject;
													}
												}

												if (prop_.second.get<std::string>("<xmlattr>.Name") == "Description")
												{
													variable.description_ = prop_.second.get<std::string>("<xmlattr>.Value");
													//std::cout << prop_.second.get<std::string>("<xmlattr>.Value") << std::endl;
												}

												if (prop_.second.get<std::string>("<xmlattr>.Name") == "Index")
												{
													variable.index_ = prop_.second.get<std::string>("<xmlattr>.Value");
												}
												//TODO: 考虑不存在节点情况如何处理
												if (prop_.second.get<std::string>("<xmlattr>.Name") == "Unit")
												{
													variable.unit_ = prop_.second.get<std::string>("<xmlattr>.Value");
												}
											}
										}
									}

									wms.vars.push_back(variable);
								}

								//std::cout << "共有变量 :" << var_count_ << "个" << std::endl;
							}
						}


						//m_RecvMessages.push_back(wms);
						m_RecvMessages.emplace(wms.identity_, wms);
					}
				}

				//std::cout << "ReceiveMessages中共有 " << m_RecvMessages.size() << "条消息" << std::endl;
			}
			catch (const std::exception& e)
			{
				//std::cerr << e.what() << std::endl;
				throw e;
			}

			return m_RecvMessages;
		}


	private:
		/// <summary>
		/// 解析数据Tag标签的属性，设备字段
		/// 排除以 $ 开头和含有@的 Tag
		/// </summary>
		/// <param name="input"></param>
		/// <returns></returns>
		inline static std::vector<std::string> parseData(const std::string& input)
		{
			std::vector<std::string> result;

			// 忽略以 "$" 开头的字符串
			if (input.find("$", 0) == 0) {
				return result;
			}

			if (input.empty())
			{
				return result;
			}

			std::regex regex("\\[([^\\]]+)\\]");
			std::regex commaRegex(",\\s*");

			std::smatch match;
			if (std::regex_search(input, match, regex)) {
				std::string extracted = match[1].str();

				// Check if extracted contains a comma
				if (extracted.find(',') != std::string::npos) {

					// Split the extracted string using comma as delimiter
					std::vector<std::string> parts;
					std::istringstream iss(extracted);
					std::string part;
					while (std::getline(iss, part, ',')) {
						// Trim leading and trailing white spaces from each part
						part = std::regex_replace(part, std::regex("^\\s+|\\s+$"), "");
						std::replace(part.begin(), part.end(), ' ', '_');
						parts.push_back(part);
					}

					result.push_back(parts[0]);
					result.push_back(parts[1]);
				}
				else {
					std::replace(extracted.begin(), extracted.end(), ' ', '_');
					result.push_back(extracted);
				}
			}
			return result;
		}

	};

}
