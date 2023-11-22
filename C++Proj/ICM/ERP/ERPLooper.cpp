//#ifdef ENABLE_DEBUG
//#include "vld/vld.h"
//#endif

#include "ERPLooper.h"

#include "ERPMessage.h"
#include "mes_l2_struct.h"

#include "ERPServices.h"

#include "ERPOrderStrategyFactory.h"
#include "ERPHeartStrategyFactory.hpp"


//心跳 per minute
#define  MLL3_HEART_PER_MINITE  6000
#define  TEST_TIME_CYC  6001

ERPLooper::ERPLooper() :m_log(__FUNCTION__)
{


#ifdef ENABLE_DEBUG
	m_log << "ERPLooper() constructor:..." << end_l;
	m_log << "\t \t initialize Timer..." << end_l;
#endif

	//初始化有关L3的定时器
	AddTimer(MLL3_HEART_PER_MINITE, 1000 * 1);
//	AddTimer(TEST_TIME_CYC, 1000 * 1);


	try
	{
		DB::OracleDB::OracleDML::executeQuery("select sysdate from dual@lk_pri");
	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6099, "连接PCS 数据库失败，请检查网络是否通畅,reason:%s", e.what());
	}


}

ERPLooper::~ERPLooper()
{
	DelTimer(MLL3_HEART_PER_MINITE);
//	DelTimer(TEST_TIME_CYC);
	m_log << end_t;
}


void ERPLooper::Dispatcher(const Message& RevMsg)
{
	//判断电文种类
	static std::map<std::string, int> value = {
				{"L3ML01", shared_define::mes_message::ORDER},
				{"L3ML02", shared_define::mes_message::NEW_ROLL},
				{"L3ML03", shared_define::mes_message::RECV_ACK},
				{"999999", shared_define::mes_message::HEART},
	};

	ERPServices srv_report;

	switch (RevMsg.Id())
	{

#pragma region 接收L3计划

	case EVENT_TELE_ARRIVAL:					//处理MES电文
	{
		try
		{
			auto datas = std::make_shared<msg::ERPMessage>(RevMsg.Data());
			auto id = datas->m_identity;

			ALARM(AL_INFO, 6000, "收到L3传来电文id=%s", id.c_str());

			switch (value[id])
			{
			case shared_define::mes_message::ORDER:
			{
				//std::thread order_task([datas, this]
				{
					//事件处理句柄
					ERPServices srv(std::make_shared<ERPOrderStrategyFactory>(), std::move(datas));
					srv.EPRSrvEventHandler();
				}
				//});

			//tasks.push(order_task);
			}
			break;

			case shared_define::mes_message::HEART:
			{
				//ERPServices srv(std::make_shared<ERPHeartStrategyFactory>(), std::move(datas));
				//srv.EPRSrvEventHandler();
				//m_log << "收到L3下发心跳电文，不予理会！" << end_l;
			}
			break;
			case shared_define::mes_message::NEW_ROLL:
			{
				//ERPServices srv(std::make_shared<ERPRollStrategyFactory>(), std::move(datas));
				//srv.EPRSrvEventHandler();
				m_log << "收到L3下发NEW_ROLL事件，不予理会！" << end_l;
			}
			break;
			case shared_define::mes_message::RECV_ACK:
			{
				//TODO: 后期补充逻辑,但应答为No时，需要记录数据，然后定时周期发送，直到应答为Yes
				//ERPServices src(std::make_shared<ERPAckStrategyFactory>(), std::move(datas));
				//src.EPRSrvEventHandler();
				m_log << "收到L3下发RECV_ACK事件，不予理会！" << end_l;
			}
			break;

			default:
			{
				ALARM(AL_WARNING, 6001, "未知类型:%s", id.c_str());
			}
			break;
			}

		}
		catch (std::exception& e)
		{
			ALARM(AL_ERROR, 6003, "发生错误:%s", e.what());
		}
	}
	break;

#pragma endregion


#pragma region 实绩报告

	//MLL302 - Slab Charge Report
	case  NOTIFY_PREPARE_L3_CHARGE_REPORT:
	{
		char matId[MATID_LEN];
		memset(matId, 0x00, sizeof(matId));

		RevMsg.GetParam("matId", matId, sizeof(matId));
		ALARM(AL_INFO, 6008, "收到TM发来准备装炉报告事件, matId=%s", matId);

		srv_report.PrepareL3ChargeReport(matId);
	}
	break;

	//MLL303 - Slab Discharge Report
	case SLAB_DISCHARGE_EVENT:
	{
		ALARM(AL_INFO, 6009, "收到RM1发来出炉事件,准备MLL303 Slab Discharge Report 报告");
		srv_report.PrepareL3DischargeReport(static_cast<mes_l2_msg_define::MLL303*>(const_cast<void*>(RevMsg.Data())));
	}
	break;

	// 准备MLL304 报告
	case PREPARE_SLAB_CANCEL_RPT:
	{
		char matId[MATID_LEN];
		memset(matId, 0x00, sizeof(matId));

		RevMsg.GetParam("matId", matId, sizeof(matId));
		ALARM(AL_INFO, 6010, "收到TM发来准备板坯吊销报告事件, matId=%s", matId);

		srv_report.PrepareL3SlabCancelReport(matId);
	}
	break;

	//MLL305 - Production Report
	case NOTIFY_PREPARE_PRODUCT_REPORT:
	{
		char matId[MATID_LEN];
		memset(matId, 0x00, sizeof(matId));
		RevMsg.GetParam("matId", matId, sizeof(matId));
		ALARM(AL_INFO, 6011, "收到TM发来产品报告事件,准备MLL305 Product report 报告: matId:%s", matId);
		srv_report.PrepareL3ProductReport(matId);
	}
	break;

	//电文已废弃
	//MLL306 - Sample Report
	case NOTIFY_PREPARE_L3_SAMPLE_REPORT:
	{
		char sampleTime[20];
		char matId[MATID_LEN];

		memset(sampleTime, 0x00, sizeof(sampleTime));
		memset(matId, 0x00, sizeof(matId));

		RevMsg.GetParam("matId", matId, sizeof(matId));
		RevMsg.GetParam("sampleTime", sampleTime, sizeof(sampleTime));
		ALARM(AL_INFO, 6012, "收到TM发来准备MLL306 采样报告请求,matId:%s,sampleTime:%s", matId, sampleTime);
		srv_report.PrepareL3SampleReport(matId, sampleTime);
	}
	break;

	// 钢卷称重报告 MLL307 - Weight Report
	case NOTIFY_PREPARE_L3_COIL_WEIGHT_REPORT:
	{
		float coilWeight = 0.f;
		char weighTime[20];
		char matId[MATID_LEN];

		memset(weighTime, 0x00, sizeof(weighTime));
		memset(matId, 0x00, sizeof(matId));

		RevMsg.GetParam("matId", matId, sizeof(matId));
		RevMsg.GetParam("weighTime", weighTime, sizeof(weighTime));
		RevMsg.GetParam("coilWeight", coilWeight);

		ALARM(AL_INFO, 6013, "收到TM发来MLL307 准备钢卷称重报告请求,matId:%s,coilWeight=%f,weighTime:%s", matId, coilWeight, weighTime);

		srv_report.PrepareL3WeightReport(matId, coilWeight, weighTime);
	}
	break;

	//钢卷运输报告 MLL308 - Coil Transport Report
	case NOTIFY_PREPARE_L3_COIL_RPT:
	{
		long exitAreaNo = 0;
		char matId[MATID_LEN];
		memset(matId, 0x00, sizeof(matId));

		RevMsg.GetParam("matId", matId, sizeof(matId));
		RevMsg.GetParam("exitAreaNo", exitAreaNo);
		ALARM(AL_INFO, 6014, "收到TM发来 MLL308 准备卷取报告事件, matId=%s , no=%d", matId, exitAreaNo);
		srv_report.PrepareL3CoilTransportReport(matId, exitAreaNo);
	}
	break;

	//MLL309 - Roll Change Report
	case ROLL_CHANGE_EVENT:
	{

		ALARM(AL_INFO, 6015, "收到RollMgt发来准备MLL309 Roll Change report ");

		srv_report.PrepareL3RollChangeReport(const_cast<void*>(RevMsg.Data()));
	}
	break;

#pragma endregion


#pragma region HMI API

	case EVENT_HMI_REQUEST:
	{
		// 板坯吊销需要检查板坯状态是否符合规范。
		//: 修改：HMI给我 {MATID}  msgid:2023
		//: 吊销：HMI给我 {MATID1,MATID2}  msgid:2024
		//: 新增一条：HMI给我 {MATID}  msgid:2025


		Records reply;
		reply[0]["status_code"] = 1;
		reply[0]["msg"] = "ok";

		long msg_id = 0;
		char ticket[32];
		long param_no = 0; //默认值传递一个参数，类型为 Records,param_no=1

		memset(ticket, 0x00, sizeof(ticket));
		RevMsg.GetParam("MsgId", (long&)msg_id);
		RevMsg.GetParam("Ticket", ticket, sizeof(ticket));
		RevMsg.GetParam("ParamNum", (long&)param_no);

		switch (msg_id)
		{

		case HMI_UPD_EVENT:
		{
			ALARM(AL_INFO, 6015, "收到HMI传来更新操作!");
			Records&& p1 = TagCenter.FetchMsg(ticket, "p1");

			try
			{
				srv_report.ProdReqUpdated((const char*)(FormatString)p1[0]["MATID"], ticket, reply);
			}
			catch (const std::exception& ex)
			{
				ALARM(AL_ERROR, 6016, "HMI_UPD_EVENT 获取HMI传来参数时失败:%s", ex.what());
				reply[0]["status_code"] = 0;
				reply[0]["msg"] = ex.what();
			}


			TagCenter.ReplyMsg(ticket, "r1", reply);
			TagCenter.ReplyMsg(ticket);
			p1.Clear();
			reply.Clear();
		}
		break;

		case HMI_CANCEL_EVENT:
		{
			ALARM(AL_INFO, 6017, "收到HMI传来吊销操作! ");

			Records&& p1 = TagCenter.FetchMsg(ticket, "p1");

			std::vector<std::string>  matIds;

			try
			{
				for (auto i = 0; i < p1.GetLength(); ++i)
				{
					matIds.push_back((const char*)(FormatString)(p1[i]["MATID"]));
				}

				srv_report.ProdScheduleCancel(std::move(matIds), ticket, reply);
			}
			catch (const std::exception& ex)
			{
				ALARM(AL_ERROR, 6018, "HMI_CANCEL_EVENT 获取HMI传来参数时失败:%s", ex.what());
				reply[0]["status_code"] = 0;
				reply[0]["msg"] = ex.what();
			}

			TagCenter.ReplyMsg(ticket, "r1", reply);
			TagCenter.ReplyMsg(ticket);
			p1.Clear();
			reply.Clear();
		}
		break;

		case HMI_INSERT_EVENT:
		{
			ALARM(AL_INFO, 6019, "收到HMI传来新增操作!");
			Records&& p1 = TagCenter.FetchMsg(ticket, "p1");

			try
			{
				srv_report.ProdReqCreated((const char*)(FormatString)p1[0]["MATID"], ticket, reply);
			}
			catch (const std::exception& ex)
			{
				ALARM(AL_ERROR, 6020, "HMI_INSERT_EVENT 获取HMI传来参数时失败:%s", ex.what());
				reply[0]["status_code"] = 0;
				reply[0]["msg"] = ex.what();
			}


			TagCenter.ReplyMsg(ticket, "r1", reply);
			TagCenter.ReplyMsg(ticket);
			p1.Clear();
			reply.Clear();
		}
		break;

		default:
			ALARM(AL_ERROR, 6021, "接收到HMI传来未知消息，id=%d", msg_id);
			break;
		}
	}
	break;

#pragma endregion



	default:
		ALARM(AL_ERROR, 6022, "收到未知消息%d", RevMsg.Id());
		break;
	}
}

void ERPLooper::Cycle(WORD Timer)
{
	if (Timer == MLL3_HEART_PER_MINITE)
	{
		ERPServices::SendMESAliveL3();
	}

#if 0

	if (Timer == TEST_TIME_CYC)
	{
		if (TAG("TEST_SWITCH") == 1)
		{
			ERPServices srv_report;
			auto id_ = ReadTagLong("PDI_ID");
			ALARM(AL_INFO, 6023, "收到 HMI 发来板坯吊销事件 ID=%d", id_);
			srv_report.ReceiveSlabCancelNotify(id_);

			WriteTagLong("TEST_SWITCH", 0);
		}

		if (TAG("TEST_SLAB_CANCEL") == 1)
		{
			ERPServices srv_report;
			char matId[MATID_LEN];
			memset(matId, 0x00, MATID_LEN);
			ReadTagString("CANCEL_COIL", matId, MATID_LEN);
			ALARM(AL_INFO, 6024, "收到 TM 发来板坯吊销事件 matId=%s", matId);
			srv_report.PrepareL3SlabCancelReport(matId);

			WriteTagLong("TEST_SLAB_CANCEL", 0);
		}

#ifdef TEST_CAST
		if (TAG("TEST_MLL308") == 1)
		{
			ERPServices srv_report;
			char matId[MATID_LEN];
			memset(matId, 0x00, MATID_LEN);
			ReadTagString("MLL308_matId", matId, MATID_LEN);
			auto exitAreaNo = ReadTagLong("MLL308_coiler_no");

			ALARM(AL_INFO, 6025, "收到TM发来 MLL308 准备卷取报告事件, matId=%s , no=%d", matId, exitAreaNo);
			srv_report.PrepareL3CoilTransportReport(matId, exitAreaNo);

			WriteTagLong("TEST_MLL308", 0);
		}
#endif // TEST_CAST

	}

#endif

}

