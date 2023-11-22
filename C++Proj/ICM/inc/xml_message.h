#pragma once

#include <unordered_map>
#include <string>

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
		std::string equipName_; /*字段所属设备名称描述*/
		std::string propName_; /*字段所属属性描述*/
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

}
