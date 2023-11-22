///****************************************************************************
/// @author  : Renaissance                                                        
/// @date    :                                                                 
/// @file    :                                                                 
/// @brief   :               操作ACTUAL_RESPONSES类。
/// @note	 : vs2017 下编译器存在bug, 导致inline static variable 会多次析构，即:
/// 命名空间范围内的非易失性 const 内联变量具有外部链接。您描述的行为似乎暗示内部链接，这是编译器的错误行为。
/// 
/// 详情参考：https://stackoverflow.com/questions/58695780/multiple-destruction-of-an-inline-variable                  
///----------------------------------------------------------------------------
///                           Change History                                   
///----------------------------------------------------------------------------
///                              
///****************************************************************************
#pragma once
#include "project_shared.h"


/// <summary>
/// 这是映射ActualResponse的ORM类
/// 其中，数据类型值与字段一一对应:
/// dataType_ == 1 ==> int
/// dataType_ == 2 ==> float
/// dataType_ == 3 ==> string
/// dataType_ == 4 ==> string(date format)
/// dataType_ == 5 ==> CLOB(string)
/// dataType_ == 6 ==> BLOB(byte[])
/// 
/// </summary>
class ActualResponseFlyw
{
#pragma region declaration

public:
	shared_define::ID_TYPE id_ = 0;
	shared_define::ID_TYPE prodRespId_ = 0; // TB_PDI ID=RESP_ID
	shared_define::ID_TYPE templateId_ = 0; //EQUIP_ID
	shared_define::ID_TYPE propId_ = 0; //PROP_ID
	int passNo_ = 0;
	int orderBy_ = 0;
	int dataType_ = 0;
	double nValue_ = 0.0;
	std::any value_;
	std::string propName_ = "";
	std::string equipName_ = "";
	std::string dTValue_ = ""; // DTVALUE DateTime
	std::string tValue_ = ""; //字符型
	std::vector<unsigned char> blobValue_;
	std::string clobValue_ = "";
	std::string category_ = "";
	std::string updatedBy_ = "SYSTEM";
	std::string shift_ = "";
	std::string crew_ = "";
	bool unspecified_flag_ = false; /*变量的Tag是否为$*/

private:
	static shared_define::PropNameIdType PropNameIdTypeMap;

	static shared_define::EquipNameIdType EquipNameIdTypeMap;

	/// <summary>
	/// {PROP_NAME:DATATYPE}
	/// </summary>
	static shared_define::PropNameDataType PropNameDataTypeMap;

	/// <summary>
	/// {PROP_ID:DATATYPE}
	/// </summary>
	static shared_define::PropIdDataType PropIdDataTypeMap;


#pragma endregion


#pragma region 缓存数据库数据
public:

	/// <summary>
	/// 缓存 {PROP_NAME:PROP_ID}
	/// </summary>
	/// <returns></returns>
	static shared_define::PropNameIdType& CachePropNameId();

	static  shared_define::EquipNameIdType& CacheEquipNameId();

	/// <summary>
	/// 缓存PROPERTY_TEMPLATE表中PROP_ID和DATATYPE字段值
	/// </summary>
	/// <returns></returns>
	static shared_define::PropNameDataType& CachePropNameDataType();

	/// <summary>
	/// 缓存 {prop_id : data_type}
	/// </summary>
	/// <returns></returns>
	static shared_define::PropIdDataType& CachePropIdDataType();



#pragma endregion


#pragma region 静态查找
public:

	/// <summary>
	/// 根据指定参数查询一条记录
	/// </summary>
	/// <param name="respId">TB_PDI中ID</param>
	/// <param name="equipName">EQUIPMENTS.NAME</param>
	/// <param name="propName">PROPERTY_TEMPLATE.PROP_NAME</param>
	/// <param name="passNo"></param>
	/// <returns></returns>
	static std::shared_ptr<ActualResponseFlyw> FindOne(shared_define::ID_TYPE respId, const std::string& equipName, const std::string& propName, int passNo);



	static std::shared_ptr<ActualResponseFlyw> FindOne(shared_define::ID_TYPE respId, shared_define::ID_TYPE templateId, shared_define::ID_TYPE propId, int passNo);


	static int DeleteActualResponses(int respId, int templateId, int passNo);


	/// <summary>
	/// 根据字符串获取数据类型
	/// </summary>
	/// <param name="daty">必须是 I,R,D,T,B,U之中</param>
	/// <returns></returns>
	static inline int getDataTypeNumber(const std::string& daty);
#pragma endregion

public:

	/// <summary>
	/// 使用默认构造时，必须先赋值成员变量，才能操作成员函数!
	/// </summary>
	explicit ActualResponseFlyw() = default;


	/// <summary>
	/// 不完备的构造函数
	/// 需要指定，设备名/id,属性名/id,PDI的id
	/// </summary>
	/// <param name="passNo"></param>
	/// <param name="propVal"></param>
	ActualResponseFlyw(int passNo, int dateType, std::any propVal);

	/// <summary>
	/// 构造函数，后续需指定属性值
	/// </summary>
	/// <param name="prodRespId"></param>
	/// <param name="templateId"></param>
	/// <param name="propId"></param>
	/// <param name="passNo"></param>
	ActualResponseFlyw(shared_define::ID_TYPE prodRespId, shared_define::ID_TYPE templateId, shared_define::ID_TYPE propId, shared_define::ID_TYPE passNo);

	/// <summary>
	/// 构造函数根据名称获取指定ID,后续需要指定 prodRespId
	/// 注意：传入的值propVal，必须与其dataType 一一对应,即若dataType=2(float), input: propVal=3.14f 而不是 3.14
	/// </summary>
	/// <param name="equipName"></param>
	/// <param name="propName"></param>
	/// <param name="passNo"></param>
	/// <param name="propVal"></param>
	ActualResponseFlyw(std::string equipName, std::string propName, int passNo, std::any propVal);


	/// <summary>
	/// 构造函数，参数完备。
	/// 注意：传入的值propVal，必须与其dataType 一一对应,即若dataType=2(float), input: propVal=3.14f 而不是 3.14
	/// </summary>
	/// <param name="prodRespId">TB_PDI id</param>
	/// <param name="equipName"></param>
	/// <param name="propName"></param>
	/// <param name="passNo"></param>
	/// <param name="propVal"></param>
	ActualResponseFlyw(shared_define::ID_TYPE prodRespId, std::string equipName, std::string propName, int passNo, std::any propVal);

	/// <summary>
	/// 拷贝构造函数
	/// </summary>
	/// <param name="other"></param>
	ActualResponseFlyw(const ActualResponseFlyw& other);
	
	ActualResponseFlyw(ActualResponseFlyw&& other) noexcept;

	~ActualResponseFlyw() = default;

public:

	int setDataType(shared_define::ID_TYPE prop_id);
	int setDataType(const std::string& propName);

private:
	/// <summary>
	/// 根据 属性名 得到 属性ID
	/// </summary>
	/// <param name="propName"></param>
	/// <returns></returns>
	shared_define::ID_TYPE getPropId(const std::string& propName);

	/// <summary>
	/// 根据设备名得到 设备 ID
	/// </summary>
	/// <param name="equipName"></param>
	/// <returns></returns>
	shared_define::ID_TYPE getEquipId(const std::string& equipName);

	/// <summary>
	/// 校验属性值是否有效
	/// </summary>
	/// <returns></returns>
	bool CheckAttributeVal();

public:

	/// <summary>
	/// 设置值
	/// </summary>
	/// <param name="value"></param>
	void setVal(std::any value);

	std::any getVal();

	/// <summary>
	/// 将数据保存至表;
	/// 先根据条件判断是否存在记录，存在则更新，不存在则插入
	/// </summary>
	void Save();

};


/// <summary>
/// 补充ActualResponseFlyw信息
/// </summary>
struct ActualInfo
{
	shared_define::ID_TYPE prodRespId_ = -1;
	std::string propName_ = "";
	std::string equipName_ = "";
};


// {属性名:属性值的包装类}
using  ActualMapType = std::unordered_map<std::string, ActualResponseFlyw>;