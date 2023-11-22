/*
* Copyright (c) 2004, 北京科技大学高效轧制国家工程研究中心
* All rights reserved.
*
* 文件名称：IPC_Message.H
* 摘    要：轧钢过程控制自动化(L2)应用程序
*
* 版本历史：
*     2007-06-14    v1.0     宋勇、荆丰伟、蔺凤琴    创建
*/

#ifndef	IPC_MESSAGE_H
#define	IPC_MESSAGE_H

#include "ProjectData.H"
//#include "SRmsg.h"

/*
*	粗轧区的启动事件号(1320-1399)
*/

#define		EVENT_RSM_PRECALCULATE_START	1320			//开始粗轧设定

//发送方：	MTK
//接收方：	RSM
//时  序：	出钢电文完成或带钢过1＃除鳞位置

/*  参数说明
*	lParam1：MILL_DATA数据区索引号；
*   lParam2：模型启动类型索引号；
*	sParam1：钢卷号；
*/
//ModelType(long)：模型启动类型(0-正常启动；1-HMI设定查看(不给L1,只更新HMI)；2-离线工具试算(不给L1和HMI)；3－HMI启动设定(发给L1和HMI)；4-L1设定补发)
#define RSU_TYPE_NORMAL			0						//正常设定
#define RSU_TYPE_HMI_TEST		1						//HMI设定查看
#define RSU_TYPE_TOOLS_TEST	    2						//离线工具试算
#define RSU_TYPE_HMI_SET	    3						//HMI启动设定
#define RSU_TYPE_L1_SET	        4						//L1设定补发


#define		EVENT_RSM_PRECALCULATE_END		1321			//粗轧设定结束

//发送方：	RSM
//接收方：	MTK
//时  序：	粗轧预设定完成

/*  参数说明
*	lParam1：MILL_DATA数据区索引号；
*   lParam2：模型启动类型索引号(0-正常，1-HMI启动试算，2-离线模型工具试算)；
*	sParam1：钢卷号；
*/

#define		EVENT_RSM_CORRCALCULATE_START   1322			//开始粗轧道次间修正设定

//发送方：	MTK
//接收方：	RSM
//时  序：	粗轧每道次轧制完成或收集完本道次实测数据后

//  参数说明：
//	lParam1：MILL_DATA数据区索引号；
//	lParam2：刚轧制完道次号(1,2,3,4,5,6,7)；
//	sParam1：钢卷号；


#define		EVENT_RSM_CORRCALCULATE_END		1323			//粗轧道次间修正设定结束

//发送方：	RSM
//接收方：	MTK
//时  序：	粗轧道次间设定完成

//  参数说明：
//  lParam1：MILL_DATA数据区索引号；
//  lParam2：刚轧制完道次号(1,2,3,4,5,6,7)；
//  sParam1：钢卷号；


#define		EVENT_RSM_POSTCALCULATE_START	1324			//开始粗轧后计算

//发送方：	MTK
//接收方：	RSM
//时  序：	粗轧末道次轧制完成或收集完所有道次实测数据后-为了SSC自学习，需要所有道次的实测数据，包括末道次的全长宽度值

//  参数说明：
//	lParam1：MILL_DATA数据区索引号；
//	lParam2：实测道次数(3；5；7)；
//	sParam1：钢卷号；


#define		EVENT_RSM_POSTCALCULATE_END		1325			//粗轧后计算结束
//  参数说明：
//	lParam1：MILL_DATA数据区索引号；
//	lParam2：实测道次数(3；5；7)；
//	sParam1：钢卷号；


#define		EVENT_RSM_SECONDWIDLRN_START	1326			//开始精轧后宽度自学习

//发送方：	MTK
//接收方：	RSM
//时  序：	收集完精轧实测数据后

//  参数说明：
//	lParam1：MILL_DATA数据区索引号；
//	sParam1：钢卷号；


#define		EVENT_RSM_SECONDWIDLRN_END		1327			//精轧后宽度自学习结束
//  参数说明：
//	lParam1：MILL_DATA数据区索引号；
//	sParam1：钢卷号；

#define		EVENT_RSM_THIRDWIDLRN_START	    1328			//卷取后宽度自学习结束

//发送方：	MTK
//接收方：	RSM
//时  序：	收集完卷取实测数据后

//  参数说明：
//	lParam1：MILL_DATA数据区索引号；
//	sParam1：钢卷号；

#define		EVENT_RSM_LASTPASS_END		1340				//粗轧末道次轧制结束(发送末道次数据给加热炉二级 RSM->MDRV->FCE L2)

//发送方：	RSM
//接收方：	MDRV
//时  序：	粗轧末道次轧制完成后

//参数说明：
//			lParam1：粗轧轧制道次数；
//			fParam1：粗轧末道次实测温度；
//			fParam2：粗轧末道次实测轧制力；
//			sParam1：钢卷号；

#define		EVENT_RE_PICKUP		1342
#define		EVENT_RE_DROPOUT	1343
#define		EVENT_HSB_PICKUP	1344
#define		EVENT_HSB_DROPOUT	1345
#define		EVENT_RET_PICKUP	1346
#define		EVENT_RET_DROPOUT	1347
#define		EVENT_RET_HEAD_FBK	1348
#define		EVENT_RET_TAIL_FBK	1349
#define		EVENT_RM_PICKUP		1350
#define		EVENT_RM_DROPOUT	1351
#define		EVENT_RM_HEAD_FBK	1352
#define		EVENT_R2DT_PICKUP	1353
#define		EVENT_R2DT_DROPOUT	1354
#define		EVENT_R2DT_HEAD_FBK	1355
#define		EVENT_R2DT_TAIL_FBK	1356
#define		EVENT_RM_SAMPLE		1357
#define		EVENT_R2DT_SAMPLE	1358
#define		EVENT_R1DT_PICKUP	1359
#define		EVENT_R1DT_DROPOUT	1360
#define		EVENT_R1_DROPOUT	1361	//2018-01-05 add by wjw R1末道次时MTK向HDS发送卷号保存R1电耗数据
#define		EVENT_R1DT_HEAD_FBK	1362

/*
 *	精轧区的启动事件号(1400-1499)
 */
#define		EVENT_L1_SETUP_REQUEST			1400

#define		EVENT_FSU_SETUP_HMI				1401			//东海强制炉设定

#define		EVENT_FSM_PRECALCULATE_START	1410			//开始精轧预设定
 //发送方：	MTK
 //接收方：	FSM
 //时  序：	轧线跟踪程序检测到带钢开始精轧一次、二次设定后启动
 //参数说明：
 //			lParam1：MILL_DATA数据区索引号；
 //			lParam2：模型启动类型索引号(0-正常,1-HMI启动试算,2-离线模型工具试算,4-L1启动设定请求)；
 //			sParam1：钢卷号；

 //ModelType(long)：模型启动类型(0-正常启动；1-HMI设定查看(不给L1,只更新HMI)；2-离线工具试算(不给L1和HMI)；3－HMI启动设定(发给L1和HMI)；4-L1设定补发)
#define FSU_TYPE_NORMAL			0						//正常设定
#define FSU_TYPE_HMI_TEST		1						//HMI设定查看
#define FSU_TYPE_TOOLS_TEST	    2						//离线工具试算
#define FSU_TYPE_HMI_SET	    3						//HMI启动设定
#define FSU_TYPE_L1_SET	        4						//L1设定补发


#define		EVENT_FSM_PRECALCULATE_END		1411			//精轧预设定结束
//发送方：	FSM
//接收方：	MTK
//时  序：	精轧设定完成后启动
//参数说明：
//			lParam1：MILL_DATA数据区索引号；
//			lParam2：模型启动类型索引号(0-正常,1-HMI启动试算,2-离线模型工具试算,4-L1启动紧急改规格)；
//			sParam1：钢卷号；


#define		EVENT_FSM_RECALCULATE_START		1412			//开始精轧穿带自适应设定
//发送方：	MTK
//接收方：	FSM
//时  序：	轧线跟踪程序收集到精轧前两个机架的实测数据后启动
//参数说明：
//			lParam1：MILL_DATA数据区索引号；
//			lParam2：咬钢机架号；
//			sParam1：钢卷号；


#define		EVENT_FSM_RECALCULATE_END		1413			//精轧穿带自适应设定结束
//发送方：	FSM
//接收方：	MTK
//时  序：	FECC设定完成后启动
//参数说明：
//			lParam1：MILL_DATA数据区索引号；
//			lParam2：咬钢机架号；
//			sParam1：钢卷号；


#define		EVENT_FSM_POSTCALCULATE_START	1414			//开始精轧后计算
//发送方：	MTK
//接收方：	FSM
//时  序：	轧线跟踪程序收集完精轧机架头部实测数据后
//参数说明：
//			lParam1：MILL_DATA数据区索引号；
//			sParam1：钢卷号；


#define		EVENT_FSM_POSTCALCULATE_END		1415			//精轧后计算结束
//发送方：	FSM
//接收方：	MTK
//时  序：	精轧后计算结束后启动
//参数说明：
//			lParam1：MILL_DATA数据区索引号；
//			sParam1：钢卷号；




//产品精度分类(by SY 09-04-20)
struct EventClassify
{
	char  MatId[MATID_LEN + 1];
	int	  RecordNo;
	char  MeasGroup[32];
	char  MeasValue[32];
	int   Flag;			//1-测量偏差值，0-测量值
	float Lr;			//仪表瞬态响应时间的长度（不计入统计）
	float Lh;			//头部长度（=v * t_meas）
	float Lt;			//尾部无效长度（=l_std * v_n / v_n-1）	
	float Tgt;    		//目标值					
	float TolUp;		//上公差				
	float TolLow;		//下公差				

};

#define		EVENT_RM_CLASSIFY				1420
#define		EVENT_FM_CLASSIFY				1421
#define		EVENT_CT_CLASSIFY				1422
#define		EVENT_FET_CLASSIFY				1423
#define		EVENT_RDT_CLASSIFY				1424

#define		EVENT_FET_SAMPLE			1441
#define		EVENT_F1_SAMPLE				1442
#define		EVENT_F2_SAMPLE				1443
#define		EVENT_F3_SAMPLE				1444
#define		EVENT_F4_SAMPLE				1445
#define		EVENT_F5_SAMPLE				1446
#define		EVENT_F6_SAMPLE				1447
#define		EVENT_FDT_SAMPLE			1448
#define		EVENT_CT_SAMPLE				1449

#define		EVENT_FET_PICKUP			1450
#define		EVENT_FET_DROPOUT			1451
#define		EVENT_FET_HEAD_FBK			1452
#define		EVENT_FM_PICKUP				1453
#define		EVENT_FM_DROPOUT			1454
#define		EVENT_FM_HEAD_FBK			1455
#define		EVENT_FDT_PICKUP			1456
#define		EVENT_FDT_DROPOUT			1457
#define		EVENT_FDT_HEAD_FBK			1458

#define		EVENT_CROWN_PICKUP			1460
#define		EVENT_CROWN_DROPOUT			1461
#define		EVENT_CROWN_HEAD_FBK		1462

#define		EVENT_F7_SAMPLE				1463
#define		EVENT_F8_SAMPLE				1464

#define		EVENT_FM_STOP				1465

/*
 *	启动层流冷却预设定和卷取预设定
 */

 //事件号：	1500
 //发送方：	MTK
 //接收方：	CSM,QAS,FSM
 //时  序：	精轧首机架咬钢(活动机架)

#define		EVENT_FM_FIRSTMILL_ON		1500

/*  参数说明
 *
 * <To CSM>
 *  lParam1：FM_DATA数据区索引号；
 *  lParam2：模型启动类型索引号(0-正常，1-HMI启动试算，2-离线模型工具试算)；
 *  lParam3：子模型(当lParam2>0时，1-CTC，2-DC)；
 *  sParam1：钢卷号；
 *
 * <To QAS>
 *  fParam1：轧制长度；
 *  fParam2：轧制重量；
 *  sParam1：钢卷号；
 *
 * <To FSM>
 *  lParam1：FM_DATA数据区索引号；
 *  sParam1：钢卷号；
*/

/*
 *	精轧末机架咬钢
 */

 //事件号：	1501
 //发送方：	MTK
 //接收方：	CSM
 //时  序：	精轧末机架咬钢

#define		EVENT_FM_LASTMILL_ON		1501

/*  参数说明
 *	lParam1：MILL_DATA数据区索引号；
 *	sParam1：钢卷号；
*/



/*
 *	精轧末机架抛钢
 */

 //事件号：	1502
 //发送方：	MTK
 //接收方：	CSM
 //时  序：	精轧末机架抛钢

#define		EVENT_FM_LASTMILL_OFF		1502

/*  参数说明
 *	lParam1：MILL_DATA数据区索引号；
 *	sParam1：钢卷号；
*/

//发送方：	MTK
//接收方：	CSM
//时  序：	精轧设定计算完成后启动
//参  数：

#define		EVENT_CTC_CALCULATE_START	1510			//启动CTC模型计算

#define CTC_TYPE_NORMAL			0						//正常设定
#define CTC_TYPE_HMI_TEST		1						//HMI设定请求
#define CTC_TYPE_SIMU		    2						//模轧启动

//发送方：	CSM
//接收方：	MTK
//时  序：	层冷设定计算结束

#define		EVENT_CTC_CALCULATE_END		1511

/*
*	启动层冷预设定
*/
//事件号：	1551
//发送方：	CSM
//接收方：	CTSC
//时  序：	启动层冷预设定,准备预设定需要数据

#define		EVENT_CTSC_STARTUP		  1551
/*
 *	层冷预设定计算结束
 */

 //事件号：	1503
 //发送方：	CTSC
 //接收方：	CSM
 //时  序：	层冷预设定计算结束

#define		EVENT_CTSC_END			  1503

/*  参数说明
 *	lParam1：数据区索引号；
 *  lParam2：模型启动类型索引号(0-正常，1-HMI启动试算，2-离线模型工具试算)；
 *	sParam1：钢卷号；
*/

/*
*	启动带钢之间自学习
*/
//事件号：	1553
//发送方：	MTK
//接收方：	CTLC
//时  序：	带钢出卷取高温计

#define		EVENT_CTLC_START		1553


#define		EVENT_CTC_FDT_PICKUP	1520
#define		EVENT_CTC_FDT_DROPOUT	1521
#define		EVENT_CTC_FDT_SAMPLE	1522

#define		EVENT_CTC_CT_PICKUP		1530
#define		EVENT_CTC_CT_DROPOUT	1531
#define		EVENT_CTC_CT_SAMPLE		1532


/*
 *	 卷取吊销消息
 */

 //事件号：	1506
 //发送方：	MTK
 //接收方：	CSM
 //时  序：	精轧没有钢，同时卷取吊销时

#define		EVENT_DCSC_REJECT		1506

/*  参数说明
 *	lParam1：CTC_SET数据区索引号；
 *	sParam1：钢卷号；
*/


/*
 *	卷取区的启动事件号(1600-1699)
 */

 /*
  *	卷取预设定计算结束
  */

  //事件号：	1600
  //发送方：	CSM
  //接收方：	MTK
  //时  序：	卷取预设定计算结束

#define		EVENT_DCSC_END		1600

/*  参数说明
 *	lParam1：DC_STC数据区索引号；
 *	sParam1：钢卷号；
*/

#define EVENT_DC_PICKUP			1610
#define EVENT_DC_DROPOUT		1611	

/*
 *	运输链区的启动事件号(1700-1799)
 */
#define		EVENT_COILWEIGHT_ARRIVAL		1701			//钢卷称重事件
#define		EVENT_PRODUCT_FINISHED			1702			//
 //		sParam1: 钢卷号
 //		lParam1：记录号
 //		

#define		EVENT_CHARGE_PDI				1704
#define		EVENT_NEXT_DISCHARGE_PDI		1705
#define		EVENT_DISCHARGE_PDI				1706


/*
 *	轧辊管理启动事件号(1800-1899)
 */
#define		EVENT_RM_ROLL_CHANGE			1802

 //事件号：	1801
 //发送方：	RDM
 //接收方：	FSM
 //参  数：	lParam1 换辊机架号 按位与
 //			lParam2 1: 工作辊	2: 支撑辊
#define		EVENT_FM_ROLL_CHANGE			1801

//事件号：	1800
//发送方：	HDS
//接收方：	PDO
#define		EVENT_ROLL_CHANGE				1800

struct RollDataLog
{
	char	StandNo[32];			//机架号								[--]
	char	RollType[1];			//轧辊类型  							[--]
	char	RollPosition[1];		//轧辊位置  						    [--]
	char	RollNo[ROLLNO_LEN + 1]; 	//辊号  								[--]
	char	OffTime[17];			//下线时间
	int		Shift;					//班
	int		Group;					//组
	float	WorkingTime;			//纯轧时间								[h]
	float	TotalLength;			//公里数								[km]
	float	TotalWeight;			//轧制重量								[ton]
};

#define		EVENT_RM_ZEROING				1803
#define		EVENT_FM_ZEROING				1804
//事件号：	1804
//发送方：	RDM
//接收方：	FSM
//参  数：	lParam1 零调机架号 按位与


//事件号：	1805
//发送方：	TAGSNAP
//接收方：	RDM
//时  序：	操作人员对精轧某工作辊的数据进行了修改
//参  数：
//			无
#define		EVENT_RM_ROLL_EDIT				1805

//事件号：	1806
//发送方：	TAGSNAP
//接收方：	RDM
//时  序：	操作人员对精轧某工作辊的数据进行了修改
//参  数：
//			无
#define		EVENT_FM_WORKROLL_EDIT			1806

//事件号：	1807
//发送方：	TAGSNAP
//接收方：	RDM
//时  序：	操作人员对精轧某支撑辊的数据进行了修改
//参  数：
//			无
#define		EVENT_FM_BACKROLL_EDIT			1807

//发送方：  MTK
//接收方:	RDM
//时  序:   粗轧或精轧的实测值处理完成时
//参  数:   sParam1 机架名称(E11,E13.., R11,R12,.. FM1..FM8)
#define		EVENT_ROLL_STATISTICS			1810


 /*
 *	其它启动事件号(1900-1999)
 */
 //(by lfq 09-04-16)
 //发送方：	TAGSNAP
 //接收方：	MTK
 //时  序：  HMI进行轧线板坯吊销操作时
 //参  数:	lParam1 吊销区域 (1-FCE,2-RM,3-CBX,4-FM,5-CTC,6-DC)
 //			lParam2 吊销原因
 //发送方：	MTK
 //接收方：	QAS
 //时  序：  HMI/L1轧线板坯吊销时
 //参  数:	fParam1：轧制长度
 //			fParam2：板坯实测重量
 //			sParam1：钢卷号
#define		EVENT_SLABONLINE_REJECT			1900			//板坯吊销

#define		EVENT_SIMULATION				1901			//模拟轧钢事件

//发送方：  MTK
//接收方:	PDM
//时  序:   FM咬钢间隔时间超过15min
#define		EVENT_MILL_DELAY				1902			//轧线休止事件
struct DelayInfo
{
	__int64 StartTime;
	__int64 EndTime;
	long	Elaspe;		//min
	long	Shift;
	char	Reason[80];
	char	Note[120];
};


//发送方：	MTK
//接收方：	MHR
//时  序：  检测到跟踪信息变化时产生
//参  数:	lParam 信息发生变化的跟踪区域	(1: 粗轧区 2:精轧区 3:卷取区)
#define		EVENT_TRACKING_UPDATE			1910			//跟踪信息更新时间

/*
//(by lfq 09-04-16)
//发送方：	TAGSNAP
//接收方：	QAS
//时  序：  HMI换班操作时
//参  数:	lParam1   shift
//          lParam2   group
#define		EVENT_SHIFT_CHANGE				1903			//换班操作
*/

//(by xxl 20090819)
//发送方：	TAGSNAP
//接收方：	QAS
//时  序：  HMI换班操作时
//参  数:	lParam1   shift
//          lParam2   group

//发送方：	QAS
//接收方：	HDS
//时  序：  HMI换班操作时
typedef struct Shift_State
{
	int	shift;
	int		    group;

	int         chargeNum;
	double      chargeWet;

	int         dischargeNum;
	double      dischargeWet;

	int         RMRollNum;
	double      RMRollWet;

	int         FMRollNum;
	double      FMRollWet;

	int         DCRollNum;
	double      DCRollWet;

	double      thkGuageRat;   //(都为平均合格率)
	double      widGuageRat;
	double      FDTGuageRat;
	double      CTGuageRat;
	double      flateGuageRat;
	double      wedgeGuageRat;

}SHIFT_STATE, * PSHIFT_STATE;

#define		EVENT_SHIFT_CHANGE				1903			//换班操作


//(by xxl 09-08-19)
//发送方：	MTK
//接收方：	QAS
//时  序：  粗轧第一道次咬钢、精轧首机架咬钢、卷取咬钢
//参  数:	lParam1    区域索引号(2: 粗轧 3: 精轧 4: 卷取) 
//          fParam1：  板坯重量        
#define		EVENT_STATE_ROLL				1904			//统计各个区域轧制带钢块数

//(by xxl 09-08-19)
//发送方：	PQE
//接收方：	QAS
//时  序：  厚度、宽度、FDT、CT、平直度、凸度统计完成
//参  数:	sParam1：  measValName(厚度、宽度、FDT、CT、平直度、凸度) 
//          fParam1：  精度
#define		EVENT_GAUGE_RATE				1905			//统计轧制带钢精度

//(by hanqing 12-08-15)
//发送方：	MTK
//接收方：	HDS
//时  序：  HSB、RDT、FET、FDT下降沿
//参  数:	lParam1    轧件在MILL_DATA的索引号
//          lParam2    保存数据类型(1: 粗轧设定值 2: 粗轧实测值 3: 精轧设定值 4: 精轧实测值)
#define		EVENT_MILLDATA_SAVE				1906			//保存轧制设定及实测数据

//(by wjw 17-09-11)
//发送方：	TagChange
//接收方：	PDR
//时  序：  磨床发送轧辊数据时
//参  数:	lParam1    1
//          
#define		EVENT_RECEIVE_MC				1907			//接收磨床发送轧辊数据

//(by wjw 18-04-27)
//发送方：	TagSnap
//接收方：	MDP
//时  序：  画面点击读取时
//参  数:	
//          
#define		EVENT_SSCTBL_READ				1909			//接收画面读取短行程表

//(by wjw 18-04-27)
//发送方：	TagSnap
//接收方：	MDP
//时  序：  画面点击保存时
//参  数:	
//          
#define		EVENT_SSCTBL_WRITE				1911			//接收画面写入短行程表

#define		EVENT_FM_SUP_TRIGGER			1954			//接收MDS->L1 精轧设定电文,通知MTK下发设定

#define		EVENT_MES_FMSUP_TRIGGER			1955			//接收MDS->MES 精轧设定电文,通知MTK下发设定

#define     EVENT_ROT_SUP_TRIGGER           1956			//接收MDS->L1 层冷设定电文,通知MTK下发设定


//发送方：	L3
//接收方：	ERP
//时  序：   L3下发轧制计划
//参  数:	
#define		EVENT_RECV_L3_ORDER				1960


//发送方：	L3
//接收方：	ERP
//时  序：   L3下发新换辊数据
//参  数:	
#define		EVENT_RECV_L3_NEW_ROLL_DATA				1961

//发送方：	L3
//接收方：	ERP
//时  序：   L3下发回复哪条电文的响应
//参  数:	
#define		EVENT_RECV_L3ACK			1962


//发送方：	L3
//接收方：	ERP
//时  序：   L3下发心跳电文
//参  数:	
#define		EVENT_RECV_L3_HEART				1963


//发送方：	ERP
//接收方：	L3
//时  序：   板坯装炉实绩
//参  数:	
#define		EVENT_SEND_L3_CHARGE			1964

//发送方：	ERP
//接收方：	L3
//时  序：   板坯出炉实绩
//参  数:	
#define		EVENT_SEND_L3_DISCHARGE			1965

//发送方：	ERP
//接收方：	L3
//时  序：   板坯取消实绩
//参  数:	
#define		EVENT_SEND_L3_CANCEL		    1966

//发送方：	ERP
//接收方：	L3
//时  序：   产品报告
//参  数:	
#define		EVENT_SEND_L3_PRODUCTION			1967

//发送方：	ERP
//接收方：	L3
//时  序：   采样实绩
//参  数:	
#define		EVENT_SEND_L3_SAMPLE			1968

//发送方：	ERP
//接收方：	ERL3P
//时  序：   钢卷称重实绩
//参  数:	
#define		EVENT_SEND_L3_WET			1969

//发送方：	ERP
//接收方：	L3
//时  序：   钢卷运输
//参  数:	
#define		EVENT_SEND_L3_TRANSPORT			1970

//发送方：	ERP
//接收方：	L3
//时  序：   换辊实绩
//参  数:	
#define		EVENT_SEND_L3_ROLL_CHANGE			1971

//发送方：	ERP
//接收方：	L3
//时  序：   心跳
//参  数:	
#define		EVENT_SEND_L3_HEART			1972

//发送方：	ERP
//接收方：	TM
//时  序：   状态改变事件
//参  数:	ID: int
#define		EVENT_STATE_CHANGE_OCCURED			1973

//发送方：	ERP
//接收方：	TM
//时  序：   数据改变事件
//参  数:	ID: char* , mode:long
#define		EVENT_DATA_CHANGE_OCCURED			1974

//发送方：	TM
//接收方：	TM
//时  序：   接收到TM发来消息数据
//参  数:	
#define     EVENT_RECV_TM_MESSAGE				1975


//发送方：	TM
//接收方：	ERP
//时  序：   通知ERP准备L3卷曲报告
//参  数:	coil_id , exitAreaNo:int
#define     NOTIFY_PREPARE_L3_COIL_RPT				1976


//发送方：	TM
//接收方：	Model
//时  序：   通知Model请求计算
//参  数:	model_l2_msg_define::MDS_CALC_REQ
#define     NOTIFY_MODEL_CALC_REQ_READY				1977


//发送方：	TM
//接收方：	ERP
//时  序：   通知ERP准备L3 charge report
//参  数:	coil_id 
#define     NOTIFY_PREPARE_L3_CHARGE_REPORT			1978


//发送方：	TM
//接收方：	ERP
//执行函数:  PrepareL3SampleReport
//时  序：   通知ERP准备L3 MLL306  Sample Report
//参  数:	coil_id ,sampleTime
#define     NOTIFY_PREPARE_L3_SAMPLE_REPORT			1979


//发送方：	TM
//接收方：	ERP
//时  序：   通知ERP准备L3 MLL307  Send Coil Weight Report to L3
//参  数:	coil_id , weight, time
#define     NOTIFY_PREPARE_L3_COIL_WEIGHT_REPORT			1980


//发送方：	TM
//接收方：	ERP
//时  序：   通知ERP准备L3 MLL309 - Roll Change Report
//参  数:	coil_id , weight, time
#define     NOTIFY_PREPARE_L3_ROLL_CHANGE_REPORT			1981


//发送方：	TM
//接收方：	ERP
//时  序：   通知ERP准备L3 MLL305 - Production Report
//参  数:	coil_id 
#define     NOTIFY_PREPARE_PRODUCT_REPORT			1982


//发送方：	L1Vip
//接收方：	Model
//时  序：   出炉请求计算
//参  数:	coil_id 
#define     DISCHARGE_CALC_EVENT			1983



//发送方：	L1Vip
//接收方：	RollMgt
//时  序：   L1发来换辊事件, L1Vip-->RollMgt-->ERP
//参  数:	coil_id 
#define     ROLL_CHANGE_EVENT			1985

struct ROLL_CHANGE_REPORT
{
	char kind;
	char loc[3];
	char charge_time[14]; //20230624142219
	char roll_tons[10];
	char roll_lens[10];
	char roll_id[10];
};



//发送方：	L1Vip
//接收方：	RollMgt
//时  序：   L1发来轧辊磨损事件
//参  数:	coil_id 
#define     ROLL_WEAR_EVENT			1986

//发送方：	RM1
//接收方：	Model
//时  序：   L1 RM1 发来模轧-->Model-->TM
//参  数:	 
#define     RM1_GHOST_REQ_EVENT			1987


//发送方：	RM1
//接收方：	ERP
//时  序：   通知ERP准备L3 MLL303 - Slab Discharge Report
//参  数:	coil_id 
#define     SLAB_DISCHARGE_EVENT			1988



//发送方：	HMI
//接收方：	ERP
//时  序：   通知ERP触发板坯吊销逻辑，传递给TM
//参  数:	coil_id 
#define     SLAB_CANCEL_EVENT			1989

//发送方：	TM
//接收方：	ERP
//时  序：   TM通知ERP准备L3 MLL304 - Slab Cancel Report
//参  数:	coil_id 
#define     PREPARE_SLAB_CANCEL_RPT			1990


//发送方：	L1Vip
//接收方：	Model
//时  序：   Next-To-Extract Calculation Request to Model for the next order in line
//参  数:	coil_id 
#define     RM1_DISCHARGE_NEXT_EXTRACT_CALC_EVENT			1991
#define     TM_DISCHARGE_NEXT_EXTRACT_CALC_EVENT			1992


//发送方：	TM
//接收方：	TM
//时  序：   立刻扫描TM
//参  数:	
#define     SCAN_TM_INTERFACE				1993




//////////////////////////////////////////////////////////////////////////
//			HMI  interface define
//////////////////////////////////////////////////////////////////////////

//发送方：	HMI
//接收方：	TM
//时  序：   HMI-->TM
//参  数:    matId 更新
#define HMI_UPD_EVENT        2023

//发送方：	HMI
//接收方：	TM
//时  序：   HMI-->TM
//参  数:    matId 吊销[matid1,matid2,...]
#define HMI_CANCEL_EVENT     2024

//发送方：	HMI
//接收方：	TM
//时  序：   HMI-->TM
//参  数:    matId copy2new
#define HMI_INSERT_EVENT     2025

#endif

