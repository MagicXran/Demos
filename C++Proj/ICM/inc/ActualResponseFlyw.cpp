#include "ActualResponseFlyw.h"
#include "CrewMgtHelper.hpp"

shared_define::PropNameIdType& ActualResponseFlyw::CachePropNameId()
{

	//没有缓存
	if (PropNameIdTypeMap.size() < shared_define::NonZero)
	{
		try
		{
			auto res = DB::OracleDB::OracleDML::executeQuery("select PROP_ID,PROP_NAME from PROPERTY_TEMPLATE");
			while (res.rs_.Next())
			{
				PropNameIdTypeMap.emplace(res.rs_.Get<std::string>("PROP_NAME"), res.rs_.Get<shared_define::ID_TYPE>("PROP_ID"));
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("于PROPERTY_TEMPLATE表中缓存{id：值类型}失败：reason:{0}", e.what()));
		}
	}
	return PropNameIdTypeMap;
}

shared_define::EquipNameIdType& ActualResponseFlyw::CacheEquipNameId()
{
	//没有缓存
	if (EquipNameIdTypeMap.size() < shared_define::NonZero)
	{
		try
		{
			auto res = DB::OracleDB::OracleDML::executeQuery("select EQUIP_ID,NAME from EQUIPMENTS");
			while (res.rs_.Next())
			{
				EquipNameIdTypeMap.emplace(res.rs_.Get<std::string>("NAME"), res.rs_.Get<shared_define::ID_TYPE>("EQUIP_ID"));
			}
		}
		catch (const std::exception& e)
		{
			throw	std::logic_error(fmt::format("缓存EQUIPMENT表中{id：值类型}失败：reason:{0}", e.what()));
		}
	}
	return EquipNameIdTypeMap;
}

shared_define::PropNameDataType& ActualResponseFlyw::CachePropNameDataType()
{

	//没有缓存
	if (PropNameDataTypeMap.size() < shared_define::NonZero)
	{
		try
		{
			auto res = DB::OracleDB::OracleDML::executeQuery("select PROP_ID,PROP_NAME,DATATYPE from PROPERTY_TEMPLATE");
			while (res.rs_.Next())
			{
				PropNameDataTypeMap.emplace(res.rs_.Get<std::string>("PROP_NAME"), res.rs_.Get<int>("DATATYPE"));
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("于PROPERTY_TEMPLATE表中缓存{属性名：值类型}失败：reason:{0}", e.what()));
		}
	}
	return PropNameDataTypeMap;
}

shared_define::PropIdDataType& ActualResponseFlyw::CachePropIdDataType()
{

	//没有缓存
	if (PropIdDataTypeMap.size() < shared_define::NonZero)
	{
		try
		{
			auto res = DB::OracleDB::OracleDML::executeQuery("select PROP_ID,PROP_NAME,DATATYPE from PROPERTY_TEMPLATE");
			while (res.rs_.Next())
			{
				PropIdDataTypeMap.emplace(res.rs_.Get<shared_define::ID_TYPE>("PROP_ID"), res.rs_.Get<int>("DATATYPE"));
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("于PROPERTY_TEMPLATE表中缓存{id：值类型}失败：reason:{0}", e.what()));
		}
	}
	return PropIdDataTypeMap;
}

std::shared_ptr<ActualResponseFlyw> ActualResponseFlyw::FindOne(shared_define::ID_TYPE respId, const std::string& equipName, const std::string& propName, int passNo)
{
	renaissance::log::LOG_INFO_NUM(1200, fmt::format("Start in ActualResponseFlyw::FindOne: respId:{0}, equipName:{1} ,propName:{2},  passNo:{3}", respId, equipName, propName, passNo));


	auto actResps = std::make_shared<ActualResponseFlyw>();
	std::string sql_ = fmt::format("select s.ID , s.NVALUE,s.TVALUE,s.DTVALUE,s.LVALUE,s.BVALUE,s.TEMPLATE_ID,s.RESP_ID,s.PROP_ID,s.SHIFT,s.CREW,p.DATATYPE from ACTUAL_RESPONSES s inner join EQUIPMENTS e on s.TEMPLATE_ID = e.EQUIP_ID inner join PROPERTY_TEMPLATE p on s.PROP_ID = p.PROP_ID where s.RESP_ID={0} and e.NAME='{1}' and p.PROP_NAME='{2}' and s.PASS_NO = {3} and ROWNUM = 1", respId, equipName, propName, passNo);

	renaissance::log::LOG_INFO_NUM(1201, fmt::format("执行查询语句:{0}", sql_));

	try
	{
		auto res = DB::OracleDB::OracleDML::executeQuery(sql_);

		if (res.rs_.Next())
		{
			actResps->id_ = res.rs_.Get<shared_define::ID_TYPE>("ID");
			actResps->templateId_ = res.rs_.Get<shared_define::ID_TYPE>("TEMPLATE_ID");
			actResps->prodRespId_ = res.rs_.Get<shared_define::ID_TYPE>("RESP_ID");
			actResps->propId_ = res.rs_.Get<shared_define::ID_TYPE>("PROP_ID");
			actResps->dataType_ = res.rs_.Get<int>("DATATYPE");
			actResps->shift_ = res.rs_.Get<std::string>("SHIFT");
			actResps->crew_ = res.rs_.Get<std::string>("CREW");
			actResps->equipName_ = equipName;
			actResps->propName_ = propName;


			if (actResps->dataType_ == 1)
				actResps->nValue_ = res.rs_.Get<int>("NVALUE");
			else if (actResps->dataType_ == 2)
				actResps->nValue_ = res.rs_.Get<double>("NVALUE");
			else if (actResps->dataType_ == 3)
				actResps->tValue_ = res.rs_.Get<std::string>("TVALUE");
			else if (actResps->dataType_ == 4)
				actResps->dTValue_ = res.rs_.Get<ocilib::Date>("DTVALUE").ToString(DB::OracleDB::default_out_format);
			else if (actResps->dataType_ == 5)
			{
				auto clo = res.rs_.Get<ocilib::Clob>("LVALUE");
				actResps->clobValue_ = clo.Read(static_cast<unsigned int>(clo.GetLength()));
			}
			else if (actResps->dataType_ == 6)
			{
				auto blo = res.rs_.Get<ocilib::Blob>("BVALUE");
				actResps->blobValue_ = blo.Read(static_cast<unsigned int>(blo.GetLength()));
			}
			else
			{
				throw std::invalid_argument(fmt::format("数据类型无效：ACTUAL_RESPONSES id:{0}, dataType_{1}, equipName:{2}, PropName:{3}", actResps->id_, actResps->dataType_, equipName, propName));
			}

		}
		else
		{
			actResps.reset();
#ifdef ENABLE_DEBUG
			renaissance::log::LOG_WARN_NUM(1203, fmt::format("没发现记录，在FindOne中执行sql: {0}", sql_));
#endif
		}
	}
	catch (const std::exception& e)
	{
		actResps.reset();
		renaissance::log::LOG_ERR_NUM(1204, fmt::format("The error occurred in FindOne(): equipName:{2}, PropName:{3} ,sql:{0},  reason:{1}", sql_, e.what(), equipName, propName));
	}

	return actResps;
}

std::shared_ptr<ActualResponseFlyw> ActualResponseFlyw::FindOne(shared_define::ID_TYPE respId, shared_define::ID_TYPE templateId, shared_define::ID_TYPE propId, int passNo)
{

	renaissance::log::LOG_INFO_NUM(1205, fmt::format("Start in ActualResponseFlyw::FindOne: respId:{0}, templateId:{1} ,propId:{2},  passNo:{3}", respId, templateId, propId, passNo));


	auto actResps = std::make_shared<ActualResponseFlyw>();
	std::string sql_ = fmt::format("select s.ID ,s.NVALUE,s.TVALUE,s.DTVALUE,s.LVALUE,s.BVALUE,s.TEMPLATE_ID,s.RESP_ID,s.PROP_ID,s.SHIFT,s.CREW,p.DATATYPE,e.NAME,p.PROP_NAME from ACTUAL_RESPONSES s inner join EQUIPMENTS e on s.TEMPLATE_ID = e.EQUIP_ID inner join PROPERTY_TEMPLATE p on s.PROP_ID = p.PROP_ID where s.RESP_ID={0} and e.EQUIP_ID={1} and p.PROP_ID={2} and s.PASS_NO = {3} and ROWNUM = 1", respId, templateId, propId, passNo);

	renaissance::log::LOG_INFO_NUM(1206, fmt::format("执行查询语句:{0}", sql_));

	try
	{
		auto res = DB::OracleDB::OracleDML::executeQuery(sql_);

		if (res.rs_.Next())
		{
			actResps->id_ = res.rs_.Get<shared_define::ID_TYPE>("ID");
			actResps->templateId_ = res.rs_.Get<shared_define::ID_TYPE>("TEMPLATE_ID");
			actResps->prodRespId_ = res.rs_.Get<shared_define::ID_TYPE>("RESP_ID");
			actResps->propId_ = res.rs_.Get<shared_define::ID_TYPE>("PROP_ID");
			actResps->dataType_ = res.rs_.Get<int>("DATATYPE");

			if (actResps->dataType_ == 1)
				actResps->nValue_ = res.rs_.Get<int>("NVALUE");
			else if (actResps->dataType_ == 2)
				actResps->nValue_ = res.rs_.Get<double>("NVALUE");
			else if (actResps->dataType_ == 3)
				actResps->tValue_ = res.rs_.Get<std::string>("TVALUE");
			else if (actResps->dataType_ == 4)
				actResps->dTValue_ = res.rs_.Get<ocilib::Date>("DTVALUE").ToString(DB::OracleDB::default_out_format);
			else if (actResps->dataType_ == 5)
			{
				auto clo = res.rs_.Get<ocilib::Clob>("LVALUE");
				actResps->clobValue_ = clo.Read(static_cast<unsigned int>(clo.GetLength()));
			}
			else if (actResps->dataType_ == 6)
			{
				auto blo = res.rs_.Get<ocilib::Blob>("BVALUE");
				actResps->blobValue_ = blo.Read(static_cast<unsigned int>(blo.GetLength()));
			}
			else
			{
				throw std::invalid_argument(fmt::format("数据类型无效：ACTUAL_RESPONSES id:{0}, dataType_{1}", actResps->id_, actResps->dataType_));
			}

			actResps->shift_ = res.rs_.Get<std::string>("SHIFT");
			actResps->crew_ = res.rs_.Get<std::string>("CREW");
			actResps->equipName_ = res.rs_.Get<std::string>("NAME");
			actResps->propName_ = res.rs_.Get<std::string>("PROP_NAME");

			renaissance::log::LOG_INFO_NUM(1207, fmt::format("Start in ActualResponseFlyw::FindOne: respId:{0}, templateId:{1} ,propId:{2},  passNo:{3}", respId, templateId, propId, passNo));
		}
		else
		{
			actResps.reset();
			renaissance::log::LOG_WARN_NUM(1208, fmt::format("没发现记录，在FindOne中执行sql: {0}", sql_));
		}
	}
	catch (const std::exception& e)
	{
		actResps.reset();
		renaissance::log::LOG_ERR_NUM(1209, fmt::format("The error occurred in FindOne(): sql:{0},  reason:{1}", sql_, e.what()));
	}

	return actResps;
}

int ActualResponseFlyw::DeleteActualResponses(int respId, int templateId, int passNo)
{
	auto affectRow = -1;
	std::string criteria = fmt::format("select ID from  ACTUAL_RESPONSES where RESP_ID={0} and TEMPLATE_ID={1}", respId, templateId);
	try
	{
		auto res = DB::OracleDB::OracleDML::executeQuery(criteria);

		//存在
		if (res.rs_.Next())
		{
			std::string whereclause = fmt::format("delete from ACTUAL_RESPONSES where RESP_ID={0} and TEMPLATE_ID={1} and PASS_NO > {2}", respId, templateId, passNo);

			affectRow = DB::OracleDB::OracleDML::execute(whereclause);
		}
		return affectRow;
	}
	catch (const std::exception& e)
	{
		throw std::logic_error(fmt::format("The error occurred in DeleteActualResponses, respId:{0},reason:{1}", respId, e.what()));
	}
}

int ActualResponseFlyw::getDataTypeNumber(const std::string& daty)
{
	if (daty == "I")
		return 1;
	else if (daty == "R")
		return 2;
	else if (daty == "T")
		return 3;
	else if (daty == "D")
		return 4;
	else
		throw std::invalid_argument("未知类型");
}

ActualResponseFlyw::ActualResponseFlyw(int passNo, int dateType, std::any propVal) :
	passNo_(passNo),
	value_(propVal),
	dataType_(dateType)
{
	unspecified_flag_ = true;
	setVal(propVal);
}

ActualResponseFlyw::ActualResponseFlyw(shared_define::ID_TYPE prodRespId, shared_define::ID_TYPE templateId, shared_define::ID_TYPE propId, shared_define::ID_TYPE passNo) :
	prodRespId_(prodRespId),
	templateId_(templateId),
	propId_(propId),
	passNo_(passNo)
{
	this->setDataType(propId);
}

ActualResponseFlyw::ActualResponseFlyw(std::string equipName, std::string propName, int passNo, std::any propVal) :
	equipName_(equipName),
	propName_(propName),
	passNo_(passNo),
	value_(propVal)
{
	this->templateId_ = getEquipId(this->equipName_);
	this->propId_ = getPropId(this->propName_);
	this->setDataType(propName);
	this->setVal(propVal);
}

ActualResponseFlyw::ActualResponseFlyw(shared_define::ID_TYPE prodRespId, std::string equipName, std::string propName, int passNo, std::any propVal) :
	prodRespId_(prodRespId),
	equipName_(equipName),
	propName_(propName),
	passNo_(passNo),
	value_(propVal)
{
	this->templateId_ = getEquipId(this->equipName_);
	this->propId_ = getPropId(this->propName_);
	this->setDataType(propName);
	this->setVal(propVal);
}

ActualResponseFlyw::ActualResponseFlyw(const ActualResponseFlyw& other) :
	id_(other.id_),
	prodRespId_(other.prodRespId_),
	passNo_(other.passNo_),
	templateId_(other.templateId_),
	propId_(other.propId_),
	orderBy_(other.orderBy_),
	dataType_(other.dataType_),
	nValue_(other.nValue_),
	value_(other.value_),
	propName_(other.propName_),
	equipName_(other.equipName_),
	dTValue_(other.dTValue_),
	tValue_(other.tValue_),
	category_(other.category_),
	clobValue_(other.clobValue_),
	blobValue_(other.blobValue_),
	updatedBy_(other.updatedBy_),
	shift_(other.shift_),
	crew_(other.crew_)
{
	std::cout << "拷贝构造" << std::endl;
}

ActualResponseFlyw::ActualResponseFlyw(ActualResponseFlyw&& other) noexcept :
	id_(other.id_),
	prodRespId_(other.prodRespId_),
	passNo_(other.passNo_),
	templateId_(other.templateId_),
	propId_(other.propId_),
	orderBy_(other.orderBy_),
	dataType_(other.dataType_),
	nValue_(other.nValue_),
	value_(std::move(other.value_)),
	propName_(std::move(other.propName_)),
	equipName_(std::move(other.equipName_)),
	dTValue_(std::move(other.dTValue_)),
	tValue_(std::move(other.tValue_)),
	category_(std::move(other.category_)),
	clobValue_(std::move(other.clobValue_)),
	blobValue_(std::move(other.blobValue_)),
	updatedBy_(std::move(other.updatedBy_)),
	shift_(std::move(other.shift_)),
	crew_(std::move(other.crew_))
{
	std::cout << "move 构造" << std::endl;
}

int ActualResponseFlyw::setDataType(shared_define::ID_TYPE prop_id)
{
	try
	{
		auto& propIdCache = ActualResponseFlyw::CachePropIdDataType();
		this->dataType_ = propIdCache[prop_id];
		return dataType_;

	}
	catch (const std::exception& e)
	{
		renaissance::log::LOG_ERR(fmt::format("Error getting value type. PropId;{0}, reason:{1}", this->propId_, e.what()));
		return -1;
	}
}

int ActualResponseFlyw::setDataType(const std::string& propName)
{
	try
	{
		auto& cache = ActualResponseFlyw::CachePropNameDataType();
		this->dataType_ = cache[propName];
		return dataType_;

	}
	catch (const std::exception& e)
	{
		renaissance::log::LOG_ERR(fmt::format("Error setting value type. PropId;{0}, reason:{1}", this->propId_, e.what()));
		return -1;
	}
}

shared_define::ID_TYPE ActualResponseFlyw::getPropId(const std::string& propName)
{
	auto& cache = ActualResponseFlyw::CachePropNameId();
	return cache[propName];
}

shared_define::ID_TYPE ActualResponseFlyw::getEquipId(const std::string& equipName)
{
	auto& cache = ActualResponseFlyw::CacheEquipNameId();
	return cache[equipName];
}

bool ActualResponseFlyw::CheckAttributeVal()
{
#ifdef ENABLE_DEBUG
	renaissance::log::LOG_INFO_NUM(1001, "打印ActualResponseFlyw中变量:............");
	renaissance::log::LOG_INFO_NUM(1002, fmt::format("--------: prodRespId:{0}, templateId:{1}, propId_:{2}, passNo_{3},unspecified_flag_:{4}", prodRespId_, templateId_, propId_, passNo_, unspecified_flag_));
	renaissance::log::LOG_INFO_NUM(1003, fmt::format("--------: propName_:{0}, equipName_:{1}, shift_:{2}, crew_:{3}", propName_, equipName_, shift_, crew_));
	renaissance::log::LOG_INFO_NUM(1004, fmt::format("--------: dataType_:{0}, nValue_:{1}, tValue_:{2}, dTValue_:{3}", dataType_, nValue_, tValue_, dTValue_));
#endif

	//if (unspecified_flag_)
	//{
	//	if (this->prodRespId_ < shared_define::NonZero || this->propName_.size() < shared_define::NonZero)
	//	{
	//		renaissance::log::LOG_WARN_NUM(1000, "发现存在unspecified_flag_=true,但是变量并没有完备!");
	//		return false;
	//	}
	//}
	//else
	{
		if (this->templateId_ >= shared_define::NonZero && this->propId_ >= shared_define::NonZero)
		{
			return true;
		}

		else if (this->propId_ < shared_define::NonZero && this->propName_.size() >= shared_define::NonZero)
		{
			this->propId_ = CachePropNameId()[this->propName_];

			if (this->templateId_ < shared_define::NonZero && this->equipName_.size() >= shared_define::NonZero)
			{
				this->templateId_ = CacheEquipNameId()[this->equipName_];
			}

			return true;
		}
		else
		{
			return false;
		}

	}

}

void ActualResponseFlyw::setVal(std::any value)
{
	try
	{
		auto DataType = this->dataType_;
		if (DataType == 1)
		{
			if (value.has_value())
				nValue_ = static_cast<int>(std::any_cast<int>(value));
			else
			{
				nValue_ = -1.f;
				renaissance::log::LOG_WARN(fmt::format("要设定的值不正常！prodRespId:{0}, DataType:{1}, nValue_:{2}", prodRespId_, DataType, nValue_));
			}
		}
		else if (DataType == 2)
		{
			if (value.has_value())
			{
				try
				{
					nValue_ = std::any_cast<double>(value);
				}
				catch (...)
				{
					nValue_ = std::any_cast<float>(value);
					renaissance::log::LOG_WARN_NUM(2180, fmt::format("转换失败，尝试使用float类型进行转换: DataType:{}, nValue_:{}", DataType, nValue_));
				}
			}
			else
			{
				nValue_ = -1.f;
				renaissance::log::LOG_WARN(fmt::format("要设定的值不正常！prodRespId:{0}, DataType:{1}, nValue_:{2}", prodRespId_, DataType, nValue_));
			}
		}
		else if (DataType == 3)
		{
			if (value.has_value())
				tValue_ = std::any_cast<std::string>(value);
			else
			{
				tValue_ = "";
				renaissance::log::LOG_WARN(fmt::format("要设定的值不正常！prodRespId:{0}, DataType:{1}, tValue_:{2}", prodRespId_, DataType, tValue_));
			}
		}
		else if (DataType == 4)
		{
			if (value.has_value())
				dTValue_ = std::any_cast<std::string>(value);
			else
			{
				dTValue_ = "";
				renaissance::log::LOG_WARN(fmt::format("要设定的值不正常！prodRespId:{0}, DataType:{1}, dTValue_:{2}", prodRespId_, DataType, dTValue_));
			}
		}
		else if (DataType == 5)
		{
			if (value.has_value())
			{
				ocilib::Clob lob = std::any_cast<ocilib::Clob>(value);
				clobValue_ = lob.Read(static_cast<unsigned int>(lob.GetLength()));
			}
			else
			{
				renaissance::log::LOG_WARN(fmt::format("要设定的值不正常！prodRespId:{0}, DataType:{1}, clobValue_:{2}", prodRespId_, DataType, clobValue_));
			}
		}
		else if (DataType == 6)
		{
			if (value.has_value())
			{
				ocilib::Blob lob = std::any_cast<ocilib::Blob>(value);
				blobValue_ = lob.Read(static_cast<unsigned int>(lob.GetLength()));
			}
			else
			{
				renaissance::log::LOG_WARN(fmt::format("要设定的值不正常！prodRespId:{0}, DataType:{1}, blobValue_", prodRespId_, DataType));
			}
		}
	}
	catch (const std::exception& e)
	{
		renaissance::log::LOG_ERR(fmt::format("转化值类型时出错,【请确保传入值的类型与数据库中该属性的值类型一致】！reason:{0}", e.what()));
	}
}

std::any ActualResponseFlyw::getVal()
{
	std::any val;
	if (this->dataType_ == 1 || this->dataType_ == 2)
		val = nValue_;
	if (this->dataType_ == 3)
		val = tValue_;
	if (this->dataType_ == 4)
		val = dTValue_;
	if (this->dataType_ == 5)
		val = clobValue_;
	if (this->dataType_ == 6)
		val = blobValue_;

	return val;
}

void ActualResponseFlyw::Save()
{
	if (!CheckAttributeVal())
	{
		throw std::invalid_argument("ActualResponseFlyw中属性值存在无效值,无法保存！");
	}

	try
	{
		bool isCreate = false;

		std::shared_ptr<ActualResponseFlyw>  actResp = ActualResponseFlyw::FindOne(this->prodRespId_, this->templateId_, this->propId_, this->passNo_);
		if (actResp == nullptr)
		{
			isCreate = true;

#ifdef ENABLE_DEBUG
			renaissance::log::LOG_INFO_NUM(1005, "不存在记录,向ActualResponse插入");
#endif
		}
		else
		{
#ifdef ENABLE_DEBUG
			renaissance::log::LOG_INFO_NUM(1006, "存在记录,向ActualResponse更新");
#endif
		}


		{
			auto data_type = this->dataType_;
			auto shiftinfo = CrewMgtHelper::GetCurrentShiftInfo();

#ifdef ENABLE_DEBUG
			renaissance::log::LOG_INFO_NUM(1007, fmt::format("当前班组信息: Shift:{0}, Crew:{1}", shiftinfo._shiftName, shiftinfo._crewName));
#endif

			std::string filed_name = "NVALUE";
			std::string sql_;

			if (data_type == 1)
			{
				filed_name = "NVALUE";
				if (isCreate)
				{
					sql_ = fmt::format("insert into ACTUAL_RESPONSES ( PASS_NO, TEMPLATE_ID, RESP_ID, PROP_ID, SHIFT, CREW, {0}) values({1},{2},{3},{4},'{5}','{6}',{7}) ", filed_name, this->passNo_, this->templateId_, this->prodRespId_, this->propId_, shiftinfo._shiftName, shiftinfo._crewName, static_cast<int>(nValue_));
				}
				else
				{
					sql_ = fmt::format("update ACTUAL_RESPONSES set SHIFT='{0}',CREW='{1}',{2}={3},UPDATE_TIME=sysdate where PASS_NO={4} and TEMPLATE_ID={5} and RESP_ID={6} and PROP_ID={7}", shiftinfo._shiftName, shiftinfo._crewName, filed_name, static_cast<int>(nValue_), this->passNo_, this->templateId_, this->prodRespId_, this->propId_);
				}

			}
			else if (data_type == 2)
			{
				filed_name = "NVALUE";
				if (isCreate)
				{
					sql_ = fmt::format("insert into ACTUAL_RESPONSES ( PASS_NO, TEMPLATE_ID, RESP_ID, PROP_ID, SHIFT, CREW, {0}) values({1},{2},{3},{4},'{5}','{6}',{7}) ", filed_name, this->passNo_, this->templateId_, this->prodRespId_, this->propId_, shiftinfo._shiftName, shiftinfo._crewName, nValue_);
				}
				else
				{
					sql_ = fmt::format("update ACTUAL_RESPONSES set SHIFT='{0}',CREW='{1}',{2}={3},UPDATE_TIME=sysdate where PASS_NO={4} and TEMPLATE_ID={5} and RESP_ID={6} and PROP_ID={7}", shiftinfo._shiftName, shiftinfo._crewName, filed_name, nValue_, this->passNo_, this->templateId_, this->prodRespId_, this->propId_);
				}
			}
			else if (data_type == 3)
			{
				filed_name = "TVALUE";

				if (isCreate)
				{
					sql_ = fmt::format("insert into ACTUAL_RESPONSES ( PASS_NO, TEMPLATE_ID, RESP_ID, PROP_ID, SHIFT, CREW, {0}) values({1},{2},{3},{4},'{5}','{6}','{7}') ", filed_name, this->passNo_, this->templateId_, this->prodRespId_, this->propId_, shiftinfo._shiftName, shiftinfo._crewName, this->tValue_);
				}
				else
				{
					sql_ = fmt::format("update ACTUAL_RESPONSES set SHIFT='{0}',CREW='{1}',{2}='{3}',UPDATE_TIME=sysdate where PASS_NO={4} and TEMPLATE_ID={5} and RESP_ID={6} and PROP_ID={7}", shiftinfo._shiftName, shiftinfo._crewName, filed_name, this->tValue_, this->passNo_, this->templateId_, this->prodRespId_, this->propId_);
				}
			}
			else if (data_type == 4)
			{
				filed_name = "DTVALUE";
				if (isCreate)
				{
					sql_ = fmt::format("insert into ACTUAL_RESPONSES ( PASS_NO, TEMPLATE_ID, RESP_ID, PROP_ID, SHIFT, CREW, {0}) values({1},{2},{3},{4},'{5}','{6}',to_date('{7}', 'yyyy-mm-dd hh24:mi:ss')) ", filed_name, this->passNo_, this->templateId_, this->prodRespId_, this->propId_, shiftinfo._shiftName, shiftinfo._crewName, this->dTValue_);
				}
				else
				{
					sql_ = fmt::format("update ACTUAL_RESPONSES set SHIFT='{0}',CREW='{1}',{2}=to_date('{3}', 'yyyy-mm-dd hh24:mi:ss'),UPDATE_TIME=sysdate where PASS_NO={4} and TEMPLATE_ID={5} and RESP_ID={6} and PROP_ID={7}", shiftinfo._shiftName, shiftinfo._crewName, filed_name, this->dTValue_, this->passNo_, this->templateId_, this->prodRespId_, this->propId_);
				}
			}
			else if (data_type == 5)
			{
				filed_name = "LVALUE";
				if (isCreate)
				{
					sql_ = fmt::format("insert into ACTUAL_RESPONSES ( PASS_NO, TEMPLATE_ID, RESP_ID, PROP_ID, SHIFT, CREW, {0}) values({1},{2},{3},{4},'{5}','{6}','{7}') ", filed_name, this->passNo_, this->templateId_, this->prodRespId_, this->propId_, shiftinfo._shiftName, shiftinfo._crewName, this->clobValue_);
				}
				else
				{
					sql_ = fmt::format("update ACTUAL_RESPONSES set SHIFT='{0}',CREW='{1}',{2}='{3}' ,UPDATE_TIME=sysdate where PASS_NO={4} and TEMPLATE_ID={5} and RESP_ID={6} and PROP_ID={7}", shiftinfo._shiftName, shiftinfo._crewName, filed_name, this->clobValue_, this->passNo_, this->templateId_, this->prodRespId_, this->propId_);
				}
			}
			else if (data_type == 6)
			{
				filed_name = "BVALUE";
				renaissance::log::LOG_WARN_NUM(1009, "BVALUE 类型,不做处理！");
			}
			else
				throw std::invalid_argument(fmt::format("Unknow dataType;{0}", data_type));

			renaissance::log::LOG_INFO_NUM(1010, fmt::format("执行sql: {0}", sql_));


			DB::OracleDB::OracleDML::execute(sql_);

			//renaissance::log::LOG_INFO_NUM(1008, fmt::format("操作完成！sql:{}", sql_));
		}
	}
	catch (const std::exception& e)
	{
		renaissance::log::LOG_ERR_NUM(1011, fmt::format("Failed to save the ActualResponse for prodRespId :{0}, reason:{1}", this->prodRespId_, e.what()));
		throw std::logic_error(fmt::format("Failed to save the ActualResponse for prodRespId :{0}, reason:{1}", this->prodRespId_, e.what()));
	}
}


shared_define::PropNameIdType ActualResponseFlyw::PropNameIdTypeMap;
shared_define::PropIdDataType ActualResponseFlyw::PropIdDataTypeMap;
shared_define::EquipNameIdType ActualResponseFlyw::EquipNameIdTypeMap;
shared_define::PropNameDataType ActualResponseFlyw::PropNameDataTypeMap;