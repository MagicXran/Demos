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
	/// ��ϢID����
	/// </summary>
	using  IdentifyType = int;

	/// <summary>
	/// ��Ϣ���ֶζ���
	/// </summary>
	struct  Variable_
	{
		std::string var_name_; /*��Ϣ���ֶ���*/
		std::string dataType_; /*�ֶ�����:T,R,I,...*/
		std::string tag_; /*�ֶεı��*/
		std::string description_; /*�ֶ�����*/
		std::string index_; /*�ֶ����*/
		std::string equipName_; /*�ֶ������豸��������*/
		std::string propName_; /*�ֶ�������������*/
		std::string unit_; /*�ֶ�������������*/
	};


	/// <summary>
	/// ��Ϣ����
	/// </summary>
	struct  Message_
	{
		IdentifyType identity_; /*��Ϣid*/
		std::string name_; /*��Ϣ��*/
		std::string tag_; /*��Ϣ�ı�ʶ*/
		std::vector<Variable_> vars;  /*��Ϣ���ֶμ���*/
	};

	/// <summary>
	/// ��Ϣ���϶���
	/// </summary>
	using MsgCollectionType = std::unordered_map<IdentifyType, Message_>;


	class  XMLParser
	{
	public:
		XMLParser() = default;
		~XMLParser() = default;

		/// <summary>
		/// ��ָ����XML(���涨XML��ʽ)�ж�ȡ������Ϣ
		/// </summary>
		/// <param name="full_path_file">xmlȫ·����</param>
		/// <param name="nodeName">��ȡ�ڵ���:ֻ���� Link.ReceiveMessages or Link.SendMessages</param>
		/// <returns>������������,���غ��е��ļ�����Ϣ,��֮�򷵻ؿյļ���</returns>
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
					//��������
					if (it->first == "<xmlattr>")
					{
						continue;
					}
					//ע��
					else if (it->first == "<xmlcomment>")
					{
						continue;
					}
					// ����ÿ��Message
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

								// ����������ÿ������
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
												//TODO: ���ǲ����ڽڵ������δ���
												if (prop_.second.get<std::string>("<xmlattr>.Name") == "Unit")
												{
													variable.unit_ = prop_.second.get<std::string>("<xmlattr>.Value");
												}
											}
										}
									}

									wms.vars.push_back(variable);
								}

								//std::cout << "���б��� :" << var_count_ << "��" << std::endl;
							}
						}


						//m_RecvMessages.push_back(wms);
						m_RecvMessages.emplace(wms.identity_, wms);
					}
				}

				//std::cout << "ReceiveMessages�й��� " << m_RecvMessages.size() << "����Ϣ" << std::endl;
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
		/// ��������Tag��ǩ�����ԣ��豸�ֶ�
		/// �ų��� $ ��ͷ�ͺ���@�� Tag
		/// </summary>
		/// <param name="input"></param>
		/// <returns></returns>
		inline static std::vector<std::string> parseData(const std::string& input)
		{
			std::vector<std::string> result;

			// ������ "$" ��ͷ���ַ���
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
