#pragma once

#include <unordered_map>
#include <string>

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
		std::string equipName_; /*�ֶ������豸��������*/
		std::string propName_; /*�ֶ�������������*/
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

}
