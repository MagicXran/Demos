/*
* Copyright (c) 2011, �����Ƽ���ѧ��Ч���ƹ��ҹ����о�����
* All rights reserved.
*
* �ļ����ƣ�ProjectData.H

* ժ    Ҫ�����ֹ��̿����Զ���(L2)Ӧ�ó���
*
* �汾��ʷ��
*     2009-09-27    v1.0     ����   ����
*	  2012-05-28    v1.1     ����ΰ �޸�
*/

#ifndef	_PROJECT_DATA_H_
#define	_PROJECT_DATA_H_


/*
 *	PDI�������
 */

#ifndef PDI_STR_LEN
#define	PDI_STR_LEN											//����PDI���ַ�������(4*N-1)

#define MATID_LEN_USE			12							//�־��ʵ�ʳ���
#define MATID_LEN				15							//�־���ַ�������
#define STEEL_GRADE_LEN			23							//���Ϻ��ַ�������
#define QUALCODE_LEN			3							//���ʴ����ַ������ȣ�PXX��
#define BATCHNO_LEN				15							//�����ַ�������
#define SLABNO_LEN				15							//�������ַ�������
#define SCHNUMBER_LEN			12							//�ƻ����ַ�������
#define ROLLNO_LEN				12							//�������ַ������� 

#define PRODUCTSTD_LEN			23							//��Ʒ��׼�ַ�������
#define	MATID_FORMAT			"%s%02d0"					//�־�Ÿ�ʽ

#endif



/*
 *	�豸����
 */

#ifndef	FACTORY_NUM
#define	FACTORY_NUM

#define	MAX_FCE_COUNT			3							//���ļ���¯����
#define	MAX_FCEROW_COUNT		2							//����¯�����������

#define	FCE_MAXSLABNUM			100							//����¯ÿ�������������
const float SLABLENCRITICAL = 5800.0f;						//���������ȷֽ綨��(����,�������̷�ΧΪ6000-11000mm)[mm]   

#define SLAB_THK			   160
#define MIN_SLAB_WID		   750
#define MIN_SLAB_LEN		   7200
#define MAX_SLAB_WET           33000.0	//kg
#define MIN_SLAB_WET		   (SLAB_THK/1000.0)*(MIN_SLAB_WID/1000.0)*(MIN_SLAB_LEN/1000.0)*7800.0	//kg

#define	RM_STAND_NUM			2							//����������
#define	RM_EDGER_STAND_NUM		2							//����������������


#define	FM_STAND_NUM			7							//����������
#define MAX_FM_STAND_NUM 		8							//�����������
#define	FECC_STAND_NO			3							//����ҧ������Ӧҧ�������
#define NFMOILRPM				11							//ABB number of FM oil film model speed points (x)
#define NFMOILFRC				11							//ABB number of FM oil film model force points (y)
//#define ABB_SLIP				 0							//�Ƿ�ʹ��Abbǰ�� ��Ϊʹ���ڲ���������
#define ABB_COILNO_NUM			9							//ABB����¯������R2���ٵ���TM�ֶ���Ŀ
#define ABB_COILNO_LEN			16							//ABB����ַ�����


#define	DC_NUM					3							//��ȡ����

#define	R1_MIN_PASS				1							//R1��С���Ƶ�����
#define	R1_MAX_PASS				7							//R1������Ƶ�����

#define	R2_MIN_PASS				1							//R2��С���Ƶ�����
#define	R2_MAX_PASS				7							//R2������Ƶ�����

#define	RM_MIN_PASS				1							//�����ܺ���С���Ƶ�����
#define	RM_MAX_PASS				11							//�����ܺ�������Ƶ�����

#define	CTC_R_NUM				(16*4)
#define	CTC_F_NUM				(3*8)

#define	PHT_NUM					8

#define	MAT_CLASS_NUM			100							//���ʷ�����
#define	WID_CLASS_NUM			10							//��Ʒ��ȷ�����
#define	THK_CLASS_NUM			24							//��Ʒ��ȷ�����
#define STRAINRATE_CLASS_NUM	20							//�������ʷ�����-����
#define MATTEMP_CLASS_NUM		20							//�����¶ȷ�����-����
#define	R1THK_CLASS_NUM			14							//R1��ں�ȷ�����
#define	E1WIDCUT_CLASS_NUM		10							//E1��Ʒ���������
#define R1STRAINRATE_CLASS_NUM	10							//�������ʷ�����-����R1
#define R1MATTEMP_CLASS_NUM		10							//�����¶ȷ�����-����R1
#define R1TORQUE_CLASS_NUM		10							//�������ط�����-����R1
#define	PLAN_CLASS_NUM			50							//���ƹ��շ�����


#define MIDTHERMOMETER_NUM		0							//CTC�м��¶ȼƵĸ���
#define MAX_VALVE_NUM          	128							//��󼯹ܸ���
#define MAX_WORD_NUM           	8							//���״̬��

#define MAX_SSC_POINT			100							//SSCͷβȡ��������	- ��ѧϰ��ʹ��,SSCģ�������ⶨ����һ�� Ӧ��һ��,��Ϊ������Ŀ��ѧϰ���Ѿ��������ˡ�			

#define STRETCH_DATA_NUM		2000						//�նȴ���������������
/*
 *	����������
 */
//��������������
#define MILLLINE_DATA_AREANAME			"MILL_DATA"
#define STAND_ROLL_AREANAME				"ROLL_DATA"
#define ROLL_STATE_AREANAME				"ROLL_STATE"
#define COM_CON_DATA_AREANAME			"COM_CON_DATA"

//����ģ������������
#define RSU_STC_DATA_AREANAME			"RSU_STC_DATA"
#define RSU_CON_DATA_AREANAME			"RSU_CON_DATA"
#define RSU_SCH_DATA_AREANAME			"RSU_SCH_DATA"
#define RSU_BAR_LRN_AREANAME			"RSU_BAR_LRN"
#define RSU_LOT_LRN_AREANAME			"RSU_LOT_LRN"
#define RSU_LRN_BLOCK_AREANAME			"RSU_LRN_BLOCK"
#define RSU_SSC_DATA_AREANAME			"RSU_SSC_DATA"
#define RSU_SSC_DATA_CUT_AREANAME		"RSU_SSC_DATA_CUT"
#define STRETCH_RAW_DATA_AREANAME		"STRETCH_RAW_DATA"

//����ģ������������
#define FSU_STC_DATA_AREANAME			"FSU_STC_DATA"
#define FSU_CON_DATA_AREANAME			"FSU_CON_DATA"
#define FSU_SCH_DATA_AREANAME			"FSU_SCH_DATA"
#define FSU_BAR_LRN_AREANAME			"FSU_BAR_LRN"
#define FSU_LOT_LRN_AREANAME			"FSU_LOT_LRN"
#define FSU_LRN_BLOCK_AREANAME			"FSU_LRN_BLOCK"
#define FSU_GAP0_LRN_AREANAME			"FSU_GAP0_LRN"
#define FTC_DATA_AREANAME				"FTC_DATA"
#define FSU_AGC_DATA_AREANAME			"FSU_AGC_DATA"

#define FSU_SCH_DATA_CBXDUM_AREANAME	"FSU_SCH_DATA_CBX_DUM"
#define FSU_LOT_LRN_CBXDUM_AREANAME		"FSU_LOT_LRN_CBX_DUM"

// ����ģ������������
#define SSU_CONSTANT_AREANAME			"SSU_CONSTANT"
#define SSU_DATA_AREANAME				"SSU_DATA"
#define SSU_RCT_AREANAME				"SSU_RCT"
#define SSU_HIERARCHY_AREANAME			"SSU_HIERARCHY"
#define SSU_LEARNING_AREANAME			"SSU_LEARNING"
#define SSU_ROLL_TEMP_AREANAME          "ROLL_TEMP_DATA"

//��ȡģ������������
#define CSU_STC_DATA_AREANAME			"CSU_STC_DATA"
#define CSU_CON_DATA_AREANAME			"CSU_CON_DATA"
#define CSU_SCH_DATA_AREANAME			"CSU_SCH_DATA"

//CTCģ������������
#define CTC_STC_DATA_AREANAME			"CTC_STC_DATA"
#define CTC_CON_DATA_AREANAME			"CTC_CON_DATA"
#define CTC_SCH_DATA_AREANAME			"CTC_SCH_DATA"
#define CTC_BAR_LRN_AREANAME			"CTC_BAR_LRN"
#define CTC_LOT_LRN_AREANAME			"CTC_LOT_LRN"
#define CTC_GTK_DATA_AREANAME			"CTC_GTK_DATA"

#endif


/*
 *	ϵͳ�Ƿ�װHTKģ��
 *	���û����ע����һ��
 */

#define _HTK_MDL


/*
 *	����¯����ϵͳ�Ƿ�е�¯������
 *	���û����ע����һ�У�����У�����ע�͵�_HTK_MDL��
 */

#define _FCE_SYS_TRK

/*
 *ϵͳ�Ƿ�װ������ȴģ��, ���û����ע����һ��
 *
 */

#define _HAS_CTC_MODULE_

/*
 *ϵͳ�Ƿ�װ������ȴ�м���¼�, ���û����ע����һ��
 *
 */

//#define _HAS_MIDCT_LRN_


/*
 *ϵͳ�Ƿ�װ����ǰ�����֣����û����ע����һ��
 *
 */

//#define _HAS_RM_TBX_


/*
 *ϵͳ�Ƿ�װ���������֣����û����ע����һ��
 *
 */

//#define _HAS_FM_TBX_

/*
 *ϵͳ�Ƿ�װ�Ⱦ��䣬���û����ע����һ��
 *
 */

#define _HAS_FM_CBX_

/*
 *ϵͳ�Ƿ��о�����Ĥ��Ȳ��������û����ע����һ��
 *
 */

#define _HAS_FM_OILTHK_

/*
 *ϵͳ�Ƿ��д�����Ĥ��Ȳ��������û����ע����һ��
 *
 */

//#define _HAS_R1_OILTHK_

/*
 *ϵͳ�Ƿ����������ն�(���õ������߼���)�����û����ע����һ��
 *
 */
#define _HAS_R1_MODU_

/*
 *ϵͳ�Ƿ���FE�����û����ע����һ��
 *
 */

//#define _HAS_FM_FE_

/*
 *	��������
 */
#define	SHIFT_NUM				2							//0:ҹ�� 1:�װ� 2:�а�
						    	//2							//1:��� 2:���
#define	GROUP_NUM				3							//0:�װ� 1:�Ұ� 2:���� 3:����


/*
 *ϵͳ�Ƿ�߱���������ƣ����û����ע��������
 *
 */
//#define _HAS_CrNi_MODEL_
//#define	 CrNi_INDEX				10							//�Ӳ��ʴ���CrNi_INDEX�����ź�Ϊ���������
//#define	 CrNi_INDEX				30							//�Ӳ��ʴ���CrNi_INDEX�����ź�Ϊ��̼������

/*
 *ϵͳ�Ƿ�߱�������ƣ����û����ע��������
 *
 */
#define _HAS_SiSteel_MODEL_
#define	 SiSteel_INDEX				80						//�Ӳ��ʴ���SiSteel_INDEX�����ź�Ϊ��ָ�����

#define	 HwSteel_INDEX				94						//�Ӳ��ʴ���HwSteel_INDEX�����ź�Ϊ���ư�����


/*
 *ϵͳ�Ƿ��а��ο���ϵͳ�����û����ע����һ��
 *
 */

#define _HAS_FM_SSU_

/*
 *ϵͳ�Ƿ��д����������ǣ����û����ע����һ��
 *
 */
#define _HAS_RM_WIDGAGE_

/*
 *ϵͳ�Ƿ��о�ȡ�������ǣ����û����ע����һ��
 *
 */
//#define _HAS_DC_WIDGAGE_

/*
 *�ֶ��༭����˳�����������û����ע����һ��
 *
 */
//#define _ROLLSEQU_MAN	//�ֶ��༭����˳��������


#endif //_PROJECT_DATA_H_

