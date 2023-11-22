/*
* Copyright (c) 2004, �����Ƽ���ѧ��Ч���ƹ��ҹ����о�����
* All rights reserved.
*
* �ļ����ƣ�IPC_Message.H
* ժ    Ҫ�����ֹ��̿����Զ���(L2)Ӧ�ó���
*
* �汾��ʷ��
*     2007-06-14    v1.0     ���¡�����ΰ��������    ����
*/

#ifndef	IPC_MESSAGE_H
#define	IPC_MESSAGE_H

#include "ProjectData.H"
//#include "SRmsg.h"

/*
*	�������������¼���(1320-1399)
*/

#define		EVENT_RSM_PRECALCULATE_START	1320			//��ʼ�����趨

//���ͷ���	MTK
//���շ���	RSM
//ʱ  ��	���ֵ�����ɻ���ֹ�1������λ��

/*  ����˵��
*	lParam1��MILL_DATA�����������ţ�
*   lParam2��ģ���������������ţ�
*	sParam1���־�ţ�
*/
//ModelType(long)��ģ����������(0-����������1-HMI�趨�鿴(����L1,ֻ����HMI)��2-���߹�������(����L1��HMI)��3��HMI�����趨(����L1��HMI)��4-L1�趨����)
#define RSU_TYPE_NORMAL			0						//�����趨
#define RSU_TYPE_HMI_TEST		1						//HMI�趨�鿴
#define RSU_TYPE_TOOLS_TEST	    2						//���߹�������
#define RSU_TYPE_HMI_SET	    3						//HMI�����趨
#define RSU_TYPE_L1_SET	        4						//L1�趨����


#define		EVENT_RSM_PRECALCULATE_END		1321			//�����趨����

//���ͷ���	RSM
//���շ���	MTK
//ʱ  ��	����Ԥ�趨���

/*  ����˵��
*	lParam1��MILL_DATA�����������ţ�
*   lParam2��ģ����������������(0-������1-HMI�������㣬2-����ģ�͹�������)��
*	sParam1���־�ţ�
*/

#define		EVENT_RSM_CORRCALCULATE_START   1322			//��ʼ�������μ������趨

//���ͷ���	MTK
//���շ���	RSM
//ʱ  ��	����ÿ����������ɻ��ռ��걾����ʵ�����ݺ�

//  ����˵����
//	lParam1��MILL_DATA�����������ţ�
//	lParam2������������κ�(1,2,3,4,5,6,7)��
//	sParam1���־�ţ�


#define		EVENT_RSM_CORRCALCULATE_END		1323			//�������μ������趨����

//���ͷ���	RSM
//���շ���	MTK
//ʱ  ��	�������μ��趨���

//  ����˵����
//  lParam1��MILL_DATA�����������ţ�
//  lParam2������������κ�(1,2,3,4,5,6,7)��
//  sParam1���־�ţ�


#define		EVENT_RSM_POSTCALCULATE_START	1324			//��ʼ���������

//���ͷ���	MTK
//���շ���	RSM
//ʱ  ��	����ĩ����������ɻ��ռ������е���ʵ�����ݺ�-Ϊ��SSC��ѧϰ����Ҫ���е��ε�ʵ�����ݣ�����ĩ���ε�ȫ�����ֵ

//  ����˵����
//	lParam1��MILL_DATA�����������ţ�
//	lParam2��ʵ�������(3��5��7)��
//	sParam1���־�ţ�


#define		EVENT_RSM_POSTCALCULATE_END		1325			//������������
//  ����˵����
//	lParam1��MILL_DATA�����������ţ�
//	lParam2��ʵ�������(3��5��7)��
//	sParam1���־�ţ�


#define		EVENT_RSM_SECONDWIDLRN_START	1326			//��ʼ����������ѧϰ

//���ͷ���	MTK
//���շ���	RSM
//ʱ  ��	�ռ��꾫��ʵ�����ݺ�

//  ����˵����
//	lParam1��MILL_DATA�����������ţ�
//	sParam1���־�ţ�


#define		EVENT_RSM_SECONDWIDLRN_END		1327			//����������ѧϰ����
//  ����˵����
//	lParam1��MILL_DATA�����������ţ�
//	sParam1���־�ţ�

#define		EVENT_RSM_THIRDWIDLRN_START	    1328			//��ȡ������ѧϰ����

//���ͷ���	MTK
//���շ���	RSM
//ʱ  ��	�ռ����ȡʵ�����ݺ�

//  ����˵����
//	lParam1��MILL_DATA�����������ţ�
//	sParam1���־�ţ�

#define		EVENT_RSM_LASTPASS_END		1340				//����ĩ�������ƽ���(����ĩ�������ݸ�����¯���� RSM->MDRV->FCE L2)

//���ͷ���	RSM
//���շ���	MDRV
//ʱ  ��	����ĩ����������ɺ�

//����˵����
//			lParam1���������Ƶ�������
//			fParam1������ĩ����ʵ���¶ȣ�
//			fParam2������ĩ����ʵ����������
//			sParam1���־�ţ�

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
#define		EVENT_R1_DROPOUT	1361	//2018-01-05 add by wjw R1ĩ����ʱMTK��HDS���;�ű���R1�������
#define		EVENT_R1DT_HEAD_FBK	1362

/*
 *	�������������¼���(1400-1499)
 */
#define		EVENT_L1_SETUP_REQUEST			1400

#define		EVENT_FSU_SETUP_HMI				1401			//����ǿ��¯�趨

#define		EVENT_FSM_PRECALCULATE_START	1410			//��ʼ����Ԥ�趨
 //���ͷ���	MTK
 //���շ���	FSM
 //ʱ  ��	���߸��ٳ����⵽���ֿ�ʼ����һ�Ρ������趨������
 //����˵����
 //			lParam1��MILL_DATA�����������ţ�
 //			lParam2��ģ����������������(0-����,1-HMI��������,2-����ģ�͹�������,4-L1�����趨����)��
 //			sParam1���־�ţ�

 //ModelType(long)��ģ����������(0-����������1-HMI�趨�鿴(����L1,ֻ����HMI)��2-���߹�������(����L1��HMI)��3��HMI�����趨(����L1��HMI)��4-L1�趨����)
#define FSU_TYPE_NORMAL			0						//�����趨
#define FSU_TYPE_HMI_TEST		1						//HMI�趨�鿴
#define FSU_TYPE_TOOLS_TEST	    2						//���߹�������
#define FSU_TYPE_HMI_SET	    3						//HMI�����趨
#define FSU_TYPE_L1_SET	        4						//L1�趨����


#define		EVENT_FSM_PRECALCULATE_END		1411			//����Ԥ�趨����
//���ͷ���	FSM
//���շ���	MTK
//ʱ  ��	�����趨��ɺ�����
//����˵����
//			lParam1��MILL_DATA�����������ţ�
//			lParam2��ģ����������������(0-����,1-HMI��������,2-����ģ�͹�������,4-L1���������Ĺ��)��
//			sParam1���־�ţ�


#define		EVENT_FSM_RECALCULATE_START		1412			//��ʼ������������Ӧ�趨
//���ͷ���	MTK
//���շ���	FSM
//ʱ  ��	���߸��ٳ����ռ�������ǰ�������ܵ�ʵ�����ݺ�����
//����˵����
//			lParam1��MILL_DATA�����������ţ�
//			lParam2��ҧ�ֻ��ܺţ�
//			sParam1���־�ţ�


#define		EVENT_FSM_RECALCULATE_END		1413			//������������Ӧ�趨����
//���ͷ���	FSM
//���շ���	MTK
//ʱ  ��	FECC�趨��ɺ�����
//����˵����
//			lParam1��MILL_DATA�����������ţ�
//			lParam2��ҧ�ֻ��ܺţ�
//			sParam1���־�ţ�


#define		EVENT_FSM_POSTCALCULATE_START	1414			//��ʼ���������
//���ͷ���	MTK
//���շ���	FSM
//ʱ  ��	���߸��ٳ����ռ��꾫������ͷ��ʵ�����ݺ�
//����˵����
//			lParam1��MILL_DATA�����������ţ�
//			sParam1���־�ţ�


#define		EVENT_FSM_POSTCALCULATE_END		1415			//������������
//���ͷ���	FSM
//���շ���	MTK
//ʱ  ��	������������������
//����˵����
//			lParam1��MILL_DATA�����������ţ�
//			sParam1���־�ţ�




//��Ʒ���ȷ���(by SY 09-04-20)
struct EventClassify
{
	char  MatId[MATID_LEN + 1];
	int	  RecordNo;
	char  MeasGroup[32];
	char  MeasValue[32];
	int   Flag;			//1-����ƫ��ֵ��0-����ֵ
	float Lr;			//�Ǳ�˲̬��Ӧʱ��ĳ��ȣ�������ͳ�ƣ�
	float Lh;			//ͷ�����ȣ�=v * t_meas��
	float Lt;			//β����Ч���ȣ�=l_std * v_n / v_n-1��	
	float Tgt;    		//Ŀ��ֵ					
	float TolUp;		//�Ϲ���				
	float TolLow;		//�¹���				

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
 *	����������ȴԤ�趨�;�ȡԤ�趨
 */

 //�¼��ţ�	1500
 //���ͷ���	MTK
 //���շ���	CSM,QAS,FSM
 //ʱ  ��	�����׻���ҧ��(�����)

#define		EVENT_FM_FIRSTMILL_ON		1500

/*  ����˵��
 *
 * <To CSM>
 *  lParam1��FM_DATA�����������ţ�
 *  lParam2��ģ����������������(0-������1-HMI�������㣬2-����ģ�͹�������)��
 *  lParam3����ģ��(��lParam2>0ʱ��1-CTC��2-DC)��
 *  sParam1���־�ţ�
 *
 * <To QAS>
 *  fParam1�����Ƴ��ȣ�
 *  fParam2������������
 *  sParam1���־�ţ�
 *
 * <To FSM>
 *  lParam1��FM_DATA�����������ţ�
 *  sParam1���־�ţ�
*/

/*
 *	����ĩ����ҧ��
 */

 //�¼��ţ�	1501
 //���ͷ���	MTK
 //���շ���	CSM
 //ʱ  ��	����ĩ����ҧ��

#define		EVENT_FM_LASTMILL_ON		1501

/*  ����˵��
 *	lParam1��MILL_DATA�����������ţ�
 *	sParam1���־�ţ�
*/



/*
 *	����ĩ�����׸�
 */

 //�¼��ţ�	1502
 //���ͷ���	MTK
 //���շ���	CSM
 //ʱ  ��	����ĩ�����׸�

#define		EVENT_FM_LASTMILL_OFF		1502

/*  ����˵��
 *	lParam1��MILL_DATA�����������ţ�
 *	sParam1���־�ţ�
*/

//���ͷ���	MTK
//���շ���	CSM
//ʱ  ��	�����趨������ɺ�����
//��  ����

#define		EVENT_CTC_CALCULATE_START	1510			//����CTCģ�ͼ���

#define CTC_TYPE_NORMAL			0						//�����趨
#define CTC_TYPE_HMI_TEST		1						//HMI�趨����
#define CTC_TYPE_SIMU		    2						//ģ������

//���ͷ���	CSM
//���շ���	MTK
//ʱ  ��	�����趨�������

#define		EVENT_CTC_CALCULATE_END		1511

/*
*	��������Ԥ�趨
*/
//�¼��ţ�	1551
//���ͷ���	CSM
//���շ���	CTSC
//ʱ  ��	��������Ԥ�趨,׼��Ԥ�趨��Ҫ����

#define		EVENT_CTSC_STARTUP		  1551
/*
 *	����Ԥ�趨�������
 */

 //�¼��ţ�	1503
 //���ͷ���	CTSC
 //���շ���	CSM
 //ʱ  ��	����Ԥ�趨�������

#define		EVENT_CTSC_END			  1503

/*  ����˵��
 *	lParam1�������������ţ�
 *  lParam2��ģ����������������(0-������1-HMI�������㣬2-����ģ�͹�������)��
 *	sParam1���־�ţ�
*/

/*
*	��������֮����ѧϰ
*/
//�¼��ţ�	1553
//���ͷ���	MTK
//���շ���	CTLC
//ʱ  ��	���ֳ���ȡ���¼�

#define		EVENT_CTLC_START		1553


#define		EVENT_CTC_FDT_PICKUP	1520
#define		EVENT_CTC_FDT_DROPOUT	1521
#define		EVENT_CTC_FDT_SAMPLE	1522

#define		EVENT_CTC_CT_PICKUP		1530
#define		EVENT_CTC_CT_DROPOUT	1531
#define		EVENT_CTC_CT_SAMPLE		1532


/*
 *	 ��ȡ������Ϣ
 */

 //�¼��ţ�	1506
 //���ͷ���	MTK
 //���շ���	CSM
 //ʱ  ��	����û�и֣�ͬʱ��ȡ����ʱ

#define		EVENT_DCSC_REJECT		1506

/*  ����˵��
 *	lParam1��CTC_SET�����������ţ�
 *	sParam1���־�ţ�
*/


/*
 *	��ȡ���������¼���(1600-1699)
 */

 /*
  *	��ȡԤ�趨�������
  */

  //�¼��ţ�	1600
  //���ͷ���	CSM
  //���շ���	MTK
  //ʱ  ��	��ȡԤ�趨�������

#define		EVENT_DCSC_END		1600

/*  ����˵��
 *	lParam1��DC_STC�����������ţ�
 *	sParam1���־�ţ�
*/

#define EVENT_DC_PICKUP			1610
#define EVENT_DC_DROPOUT		1611	

/*
 *	���������������¼���(1700-1799)
 */
#define		EVENT_COILWEIGHT_ARRIVAL		1701			//�־�����¼�
#define		EVENT_PRODUCT_FINISHED			1702			//
 //		sParam1: �־��
 //		lParam1����¼��
 //		

#define		EVENT_CHARGE_PDI				1704
#define		EVENT_NEXT_DISCHARGE_PDI		1705
#define		EVENT_DISCHARGE_PDI				1706


/*
 *	�������������¼���(1800-1899)
 */
#define		EVENT_RM_ROLL_CHANGE			1802

 //�¼��ţ�	1801
 //���ͷ���	RDM
 //���շ���	FSM
 //��  ����	lParam1 �������ܺ� ��λ��
 //			lParam2 1: ������	2: ֧�Ź�
#define		EVENT_FM_ROLL_CHANGE			1801

//�¼��ţ�	1800
//���ͷ���	HDS
//���շ���	PDO
#define		EVENT_ROLL_CHANGE				1800

struct RollDataLog
{
	char	StandNo[32];			//���ܺ�								[--]
	char	RollType[1];			//��������  							[--]
	char	RollPosition[1];		//����λ��  						    [--]
	char	RollNo[ROLLNO_LEN + 1]; 	//����  								[--]
	char	OffTime[17];			//����ʱ��
	int		Shift;					//��
	int		Group;					//��
	float	WorkingTime;			//����ʱ��								[h]
	float	TotalLength;			//������								[km]
	float	TotalWeight;			//��������								[ton]
};

#define		EVENT_RM_ZEROING				1803
#define		EVENT_FM_ZEROING				1804
//�¼��ţ�	1804
//���ͷ���	RDM
//���շ���	FSM
//��  ����	lParam1 ������ܺ� ��λ��


//�¼��ţ�	1805
//���ͷ���	TAGSNAP
//���շ���	RDM
//ʱ  ��	������Ա�Ծ���ĳ�����������ݽ������޸�
//��  ����
//			��
#define		EVENT_RM_ROLL_EDIT				1805

//�¼��ţ�	1806
//���ͷ���	TAGSNAP
//���շ���	RDM
//ʱ  ��	������Ա�Ծ���ĳ�����������ݽ������޸�
//��  ����
//			��
#define		EVENT_FM_WORKROLL_EDIT			1806

//�¼��ţ�	1807
//���ͷ���	TAGSNAP
//���շ���	RDM
//ʱ  ��	������Ա�Ծ���ĳ֧�Ź������ݽ������޸�
//��  ����
//			��
#define		EVENT_FM_BACKROLL_EDIT			1807

//���ͷ���  MTK
//���շ�:	RDM
//ʱ  ��:   ����������ʵ��ֵ�������ʱ
//��  ��:   sParam1 ��������(E11,E13.., R11,R12,.. FM1..FM8)
#define		EVENT_ROLL_STATISTICS			1810


 /*
 *	���������¼���(1900-1999)
 */
 //(by lfq 09-04-16)
 //���ͷ���	TAGSNAP
 //���շ���	MTK
 //ʱ  ��  HMI�������߰�����������ʱ
 //��  ��:	lParam1 �������� (1-FCE,2-RM,3-CBX,4-FM,5-CTC,6-DC)
 //			lParam2 ����ԭ��
 //���ͷ���	MTK
 //���շ���	QAS
 //ʱ  ��  HMI/L1���߰�������ʱ
 //��  ��:	fParam1�����Ƴ���
 //			fParam2������ʵ������
 //			sParam1���־��
#define		EVENT_SLABONLINE_REJECT			1900			//��������

#define		EVENT_SIMULATION				1901			//ģ�������¼�

//���ͷ���  MTK
//���շ�:	PDM
//ʱ  ��:   FMҧ�ּ��ʱ�䳬��15min
#define		EVENT_MILL_DELAY				1902			//������ֹ�¼�
struct DelayInfo
{
	__int64 StartTime;
	__int64 EndTime;
	long	Elaspe;		//min
	long	Shift;
	char	Reason[80];
	char	Note[120];
};


//���ͷ���	MTK
//���շ���	MHR
//ʱ  ��  ��⵽������Ϣ�仯ʱ����
//��  ��:	lParam ��Ϣ�����仯�ĸ�������	(1: ������ 2:������ 3:��ȡ��)
#define		EVENT_TRACKING_UPDATE			1910			//������Ϣ����ʱ��

/*
//(by lfq 09-04-16)
//���ͷ���	TAGSNAP
//���շ���	QAS
//ʱ  ��  HMI�������ʱ
//��  ��:	lParam1   shift
//          lParam2   group
#define		EVENT_SHIFT_CHANGE				1903			//�������
*/

//(by xxl 20090819)
//���ͷ���	TAGSNAP
//���շ���	QAS
//ʱ  ��  HMI�������ʱ
//��  ��:	lParam1   shift
//          lParam2   group

//���ͷ���	QAS
//���շ���	HDS
//ʱ  ��  HMI�������ʱ
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

	double      thkGuageRat;   //(��Ϊƽ���ϸ���)
	double      widGuageRat;
	double      FDTGuageRat;
	double      CTGuageRat;
	double      flateGuageRat;
	double      wedgeGuageRat;

}SHIFT_STATE, * PSHIFT_STATE;

#define		EVENT_SHIFT_CHANGE				1903			//�������


//(by xxl 09-08-19)
//���ͷ���	MTK
//���շ���	QAS
//ʱ  ��  ������һ����ҧ�֡������׻���ҧ�֡���ȡҧ��
//��  ��:	lParam1    ����������(2: ���� 3: ���� 4: ��ȡ) 
//          fParam1��  ��������        
#define		EVENT_STATE_ROLL				1904			//ͳ�Ƹ����������ƴ��ֿ���

//(by xxl 09-08-19)
//���ͷ���	PQE
//���շ���	QAS
//ʱ  ��  ��ȡ���ȡ�FDT��CT��ƽֱ�ȡ�͹��ͳ�����
//��  ��:	sParam1��  measValName(��ȡ���ȡ�FDT��CT��ƽֱ�ȡ�͹��) 
//          fParam1��  ����
#define		EVENT_GAUGE_RATE				1905			//ͳ�����ƴ��־���

//(by hanqing 12-08-15)
//���ͷ���	MTK
//���շ���	HDS
//ʱ  ��  HSB��RDT��FET��FDT�½���
//��  ��:	lParam1    ������MILL_DATA��������
//          lParam2    ������������(1: �����趨ֵ 2: ����ʵ��ֵ 3: �����趨ֵ 4: ����ʵ��ֵ)
#define		EVENT_MILLDATA_SAVE				1906			//���������趨��ʵ������

//(by wjw 17-09-11)
//���ͷ���	TagChange
//���շ���	PDR
//ʱ  ��  ĥ��������������ʱ
//��  ��:	lParam1    1
//          
#define		EVENT_RECEIVE_MC				1907			//����ĥ��������������

//(by wjw 18-04-27)
//���ͷ���	TagSnap
//���շ���	MDP
//ʱ  ��  ��������ȡʱ
//��  ��:	
//          
#define		EVENT_SSCTBL_READ				1909			//���ջ����ȡ���г̱�

//(by wjw 18-04-27)
//���ͷ���	TagSnap
//���շ���	MDP
//ʱ  ��  ����������ʱ
//��  ��:	
//          
#define		EVENT_SSCTBL_WRITE				1911			//���ջ���д����г̱�

#define		EVENT_FM_SUP_TRIGGER			1954			//����MDS->L1 �����趨����,֪ͨMTK�·��趨

#define		EVENT_MES_FMSUP_TRIGGER			1955			//����MDS->MES �����趨����,֪ͨMTK�·��趨

#define     EVENT_ROT_SUP_TRIGGER           1956			//����MDS->L1 �����趨����,֪ͨMTK�·��趨


//���ͷ���	L3
//���շ���	ERP
//ʱ  ��   L3�·����Ƽƻ�
//��  ��:	
#define		EVENT_RECV_L3_ORDER				1960


//���ͷ���	L3
//���շ���	ERP
//ʱ  ��   L3�·��»�������
//��  ��:	
#define		EVENT_RECV_L3_NEW_ROLL_DATA				1961

//���ͷ���	L3
//���շ���	ERP
//ʱ  ��   L3�·��ظ��������ĵ���Ӧ
//��  ��:	
#define		EVENT_RECV_L3ACK			1962


//���ͷ���	L3
//���շ���	ERP
//ʱ  ��   L3�·���������
//��  ��:	
#define		EVENT_RECV_L3_HEART				1963


//���ͷ���	ERP
//���շ���	L3
//ʱ  ��   ����װ¯ʵ��
//��  ��:	
#define		EVENT_SEND_L3_CHARGE			1964

//���ͷ���	ERP
//���շ���	L3
//ʱ  ��   ������¯ʵ��
//��  ��:	
#define		EVENT_SEND_L3_DISCHARGE			1965

//���ͷ���	ERP
//���շ���	L3
//ʱ  ��   ����ȡ��ʵ��
//��  ��:	
#define		EVENT_SEND_L3_CANCEL		    1966

//���ͷ���	ERP
//���շ���	L3
//ʱ  ��   ��Ʒ����
//��  ��:	
#define		EVENT_SEND_L3_PRODUCTION			1967

//���ͷ���	ERP
//���շ���	L3
//ʱ  ��   ����ʵ��
//��  ��:	
#define		EVENT_SEND_L3_SAMPLE			1968

//���ͷ���	ERP
//���շ���	ERL3P
//ʱ  ��   �־����ʵ��
//��  ��:	
#define		EVENT_SEND_L3_WET			1969

//���ͷ���	ERP
//���շ���	L3
//ʱ  ��   �־�����
//��  ��:	
#define		EVENT_SEND_L3_TRANSPORT			1970

//���ͷ���	ERP
//���շ���	L3
//ʱ  ��   ����ʵ��
//��  ��:	
#define		EVENT_SEND_L3_ROLL_CHANGE			1971

//���ͷ���	ERP
//���շ���	L3
//ʱ  ��   ����
//��  ��:	
#define		EVENT_SEND_L3_HEART			1972

//���ͷ���	ERP
//���շ���	TM
//ʱ  ��   ״̬�ı��¼�
//��  ��:	ID: int
#define		EVENT_STATE_CHANGE_OCCURED			1973

//���ͷ���	ERP
//���շ���	TM
//ʱ  ��   ���ݸı��¼�
//��  ��:	ID: char* , mode:long
#define		EVENT_DATA_CHANGE_OCCURED			1974

//���ͷ���	TM
//���շ���	TM
//ʱ  ��   ���յ�TM������Ϣ����
//��  ��:	
#define     EVENT_RECV_TM_MESSAGE				1975


//���ͷ���	TM
//���շ���	ERP
//ʱ  ��   ֪ͨERP׼��L3��������
//��  ��:	coil_id , exitAreaNo:int
#define     NOTIFY_PREPARE_L3_COIL_RPT				1976


//���ͷ���	TM
//���շ���	Model
//ʱ  ��   ֪ͨModel�������
//��  ��:	model_l2_msg_define::MDS_CALC_REQ
#define     NOTIFY_MODEL_CALC_REQ_READY				1977


//���ͷ���	TM
//���շ���	ERP
//ʱ  ��   ֪ͨERP׼��L3 charge report
//��  ��:	coil_id 
#define     NOTIFY_PREPARE_L3_CHARGE_REPORT			1978


//���ͷ���	TM
//���շ���	ERP
//ִ�к���:  PrepareL3SampleReport
//ʱ  ��   ֪ͨERP׼��L3 MLL306  Sample Report
//��  ��:	coil_id ,sampleTime
#define     NOTIFY_PREPARE_L3_SAMPLE_REPORT			1979


//���ͷ���	TM
//���շ���	ERP
//ʱ  ��   ֪ͨERP׼��L3 MLL307  Send Coil Weight Report to L3
//��  ��:	coil_id , weight, time
#define     NOTIFY_PREPARE_L3_COIL_WEIGHT_REPORT			1980


//���ͷ���	TM
//���շ���	ERP
//ʱ  ��   ֪ͨERP׼��L3 MLL309 - Roll Change Report
//��  ��:	coil_id , weight, time
#define     NOTIFY_PREPARE_L3_ROLL_CHANGE_REPORT			1981


//���ͷ���	TM
//���շ���	ERP
//ʱ  ��   ֪ͨERP׼��L3 MLL305 - Production Report
//��  ��:	coil_id 
#define     NOTIFY_PREPARE_PRODUCT_REPORT			1982


//���ͷ���	L1Vip
//���շ���	Model
//ʱ  ��   ��¯�������
//��  ��:	coil_id 
#define     DISCHARGE_CALC_EVENT			1983



//���ͷ���	L1Vip
//���շ���	RollMgt
//ʱ  ��   L1���������¼�, L1Vip-->RollMgt-->ERP
//��  ��:	coil_id 
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



//���ͷ���	L1Vip
//���շ���	RollMgt
//ʱ  ��   L1��������ĥ���¼�
//��  ��:	coil_id 
#define     ROLL_WEAR_EVENT			1986

//���ͷ���	RM1
//���շ���	Model
//ʱ  ��   L1 RM1 ����ģ��-->Model-->TM
//��  ��:	 
#define     RM1_GHOST_REQ_EVENT			1987


//���ͷ���	RM1
//���շ���	ERP
//ʱ  ��   ֪ͨERP׼��L3 MLL303 - Slab Discharge Report
//��  ��:	coil_id 
#define     SLAB_DISCHARGE_EVENT			1988



//���ͷ���	HMI
//���շ���	ERP
//ʱ  ��   ֪ͨERP�������������߼������ݸ�TM
//��  ��:	coil_id 
#define     SLAB_CANCEL_EVENT			1989

//���ͷ���	TM
//���շ���	ERP
//ʱ  ��   TM֪ͨERP׼��L3 MLL304 - Slab Cancel Report
//��  ��:	coil_id 
#define     PREPARE_SLAB_CANCEL_RPT			1990


//���ͷ���	L1Vip
//���շ���	Model
//ʱ  ��   Next-To-Extract Calculation Request to Model for the next order in line
//��  ��:	coil_id 
#define     RM1_DISCHARGE_NEXT_EXTRACT_CALC_EVENT			1991
#define     TM_DISCHARGE_NEXT_EXTRACT_CALC_EVENT			1992


//���ͷ���	TM
//���շ���	TM
//ʱ  ��   ����ɨ��TM
//��  ��:	
#define     SCAN_TM_INTERFACE				1993




//////////////////////////////////////////////////////////////////////////
//			HMI  interface define
//////////////////////////////////////////////////////////////////////////

//���ͷ���	HMI
//���շ���	TM
//ʱ  ��   HMI-->TM
//��  ��:    matId ����
#define HMI_UPD_EVENT        2023

//���ͷ���	HMI
//���շ���	TM
//ʱ  ��   HMI-->TM
//��  ��:    matId ����[matid1,matid2,...]
#define HMI_CANCEL_EVENT     2024

//���ͷ���	HMI
//���շ���	TM
//ʱ  ��   HMI-->TM
//��  ��:    matId copy2new
#define HMI_INSERT_EVENT     2025

#endif

