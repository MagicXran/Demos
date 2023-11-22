/*
* Copyright (c) 2011, 北京科技大学高效轧制国家工程研究中心
* All rights reserved.
*
* 文件名称：ProjectData.H

* 摘    要：轧钢过程控制自动化(L2)应用程序
*
* 版本历史：
*     2009-09-27    v1.0     宋勇   创建
*	  2012-05-28    v1.1     荆丰伟 修改
*/

#ifndef	_PROJECT_DATA_H_
#define	_PROJECT_DATA_H_


/*
 *	PDI编码规则
 */

#ifndef PDI_STR_LEN
#define	PDI_STR_LEN											//定义PDI中字符串长度(4*N-1)

#define MATID_LEN_USE			12							//钢卷号实际长度
#define MATID_LEN				15							//钢卷号字符串长度
#define STEEL_GRADE_LEN			23							//材料号字符串长度
#define QUALCODE_LEN			3							//材质代码字符串长度（PXX）
#define BATCHNO_LEN				15							//批号字符串长度
#define SLABNO_LEN				15							//板坯号字符串长度
#define SCHNUMBER_LEN			12							//计划号字符串长度
#define ROLLNO_LEN				12							//轧辊号字符串长度 

#define PRODUCTSTD_LEN			23							//产品标准字符串长度
#define	MATID_FORMAT			"%s%02d0"					//钢卷号格式

#endif



/*
 *	设备数量
 */

#ifndef	FACTORY_NUM
#define	FACTORY_NUM

#define	MAX_FCE_COUNT			3							//最大的加热炉数量
#define	MAX_FCEROW_COUNT		2							//加热炉最大排料数量

#define	FCE_MAXSLABNUM			100							//加热炉每列允许的最大块数
const float SLABLENCRITICAL = 5800.0f;						//长短坯长度分界定义(不用,板坯长短范围为6000-11000mm)[mm]   

#define SLAB_THK			   160
#define MIN_SLAB_WID		   750
#define MIN_SLAB_LEN		   7200
#define MAX_SLAB_WET           33000.0	//kg
#define MIN_SLAB_WET		   (SLAB_THK/1000.0)*(MIN_SLAB_WID/1000.0)*(MIN_SLAB_LEN/1000.0)*7800.0	//kg

#define	RM_STAND_NUM			2							//粗轧机架数
#define	RM_EDGER_STAND_NUM		2							//立辊轧机轧机架数


#define	FM_STAND_NUM			7							//精轧机架数
#define MAX_FM_STAND_NUM 		8							//最大精轧机架数
#define	FECC_STAND_NO			3							//精轧咬钢自适应咬入机架数
#define NFMOILRPM				11							//ABB number of FM oil film model speed points (x)
#define NFMOILFRC				11							//ABB number of FM oil film model force points (y)
//#define ABB_SLIP				 0							//是否使用Abb前滑 改为使用内部变量控制
#define ABB_COILNO_NUM			9							//ABB加热炉到粗轧R2跟踪电文TM分段数目
#define ABB_COILNO_LEN			16							//ABB卷号字符长度


#define	DC_NUM					3							//卷取机数

#define	R1_MIN_PASS				1							//R1最小轧制道次数
#define	R1_MAX_PASS				7							//R1最大轧制道次数

#define	R2_MIN_PASS				1							//R2最小轧制道次数
#define	R2_MAX_PASS				7							//R2最大轧制道次数

#define	RM_MIN_PASS				1							//粗轧总和最小轧制道次数
#define	RM_MAX_PASS				11							//粗轧总和最大轧制道次数

#define	CTC_R_NUM				(16*4)
#define	CTC_F_NUM				(3*8)

#define	PHT_NUM					8

#define	MAT_CLASS_NUM			100							//材质分类数
#define	WID_CLASS_NUM			10							//成品宽度分类数
#define	THK_CLASS_NUM			24							//成品厚度分类数
#define STRAINRATE_CLASS_NUM	20							//变形速率分类数-精轧
#define MATTEMP_CLASS_NUM		20							//轧件温度分类数-精轧
#define	R1THK_CLASS_NUM			14							//R1入口厚度分类数
#define	E1WIDCUT_CLASS_NUM		10							//E1成品减宽分类数
#define R1STRAINRATE_CLASS_NUM	10							//变形速率分类数-粗轧R1
#define R1MATTEMP_CLASS_NUM		10							//轧件温度分类数-粗轧R1
#define R1TORQUE_CLASS_NUM		10							//轧制力矩分类数-粗轧R1
#define	PLAN_CLASS_NUM			50							//轧制工艺分类数


#define MIDTHERMOMETER_NUM		0							//CTC中间温度计的个数
#define MAX_VALVE_NUM          	128							//最大集管个数
#define MAX_WORD_NUM           	8							//最大状态字

#define MAX_SSC_POINT			100							//SSC头尾取点最大个数	- 自学习表使用,SSC模型中另外定义了一个 应该一致,因为北海项目自学习表已经建立好了。			

#define STRETCH_DATA_NUM		2000						//刚度处理曲线数据数量
/*
 *	数据区名称
 */
//公共数据区定义
#define MILLLINE_DATA_AREANAME			"MILL_DATA"
#define STAND_ROLL_AREANAME				"ROLL_DATA"
#define ROLL_STATE_AREANAME				"ROLL_STATE"
#define COM_CON_DATA_AREANAME			"COM_CON_DATA"

//粗轧模型数据区定义
#define RSU_STC_DATA_AREANAME			"RSU_STC_DATA"
#define RSU_CON_DATA_AREANAME			"RSU_CON_DATA"
#define RSU_SCH_DATA_AREANAME			"RSU_SCH_DATA"
#define RSU_BAR_LRN_AREANAME			"RSU_BAR_LRN"
#define RSU_LOT_LRN_AREANAME			"RSU_LOT_LRN"
#define RSU_LRN_BLOCK_AREANAME			"RSU_LRN_BLOCK"
#define RSU_SSC_DATA_AREANAME			"RSU_SSC_DATA"
#define RSU_SSC_DATA_CUT_AREANAME		"RSU_SSC_DATA_CUT"
#define STRETCH_RAW_DATA_AREANAME		"STRETCH_RAW_DATA"

//精轧模型数据区定义
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

// 板形模型数据区定义
#define SSU_CONSTANT_AREANAME			"SSU_CONSTANT"
#define SSU_DATA_AREANAME				"SSU_DATA"
#define SSU_RCT_AREANAME				"SSU_RCT"
#define SSU_HIERARCHY_AREANAME			"SSU_HIERARCHY"
#define SSU_LEARNING_AREANAME			"SSU_LEARNING"
#define SSU_ROLL_TEMP_AREANAME          "ROLL_TEMP_DATA"

//卷取模型数据区定义
#define CSU_STC_DATA_AREANAME			"CSU_STC_DATA"
#define CSU_CON_DATA_AREANAME			"CSU_CON_DATA"
#define CSU_SCH_DATA_AREANAME			"CSU_SCH_DATA"

//CTC模型数据区定义
#define CTC_STC_DATA_AREANAME			"CTC_STC_DATA"
#define CTC_CON_DATA_AREANAME			"CTC_CON_DATA"
#define CTC_SCH_DATA_AREANAME			"CTC_SCH_DATA"
#define CTC_BAR_LRN_AREANAME			"CTC_BAR_LRN"
#define CTC_LOT_LRN_AREANAME			"CTC_LOT_LRN"
#define CTC_GTK_DATA_AREANAME			"CTC_GTK_DATA"

#endif


/*
 *	系统是否安装HTK模块
 *	如果没有请注释下一行
 */

#define _HTK_MDL


/*
 *	加热炉控制系统是否承担炉区跟踪
 *	如果没有请注释下一行（如果有，则还需注释掉_HTK_MDL）
 */

#define _FCE_SYS_TRK

/*
 *系统是否安装层流冷却模块, 如果没有请注释下一行
 *
 */

#define _HAS_CTC_MODULE_

/*
 *系统是否安装层流冷却中间高温计, 如果没有请注释下一行
 *
 */

//#define _HAS_MIDCT_LRN_


/*
 *系统是否安装粗轧前保温罩，如果没有请注释下一行
 *
 */

//#define _HAS_RM_TBX_


/*
 *系统是否安装粗轧后保温罩，如果没有请注释下一行
 *
 */

//#define _HAS_FM_TBX_

/*
 *系统是否安装热卷箱，如果没有请注释下一行
 *
 */

#define _HAS_FM_CBX_

/*
 *系统是否有精轧油膜厚度补偿，如果没有请注释下一行
 *
 */

#define _HAS_FM_OILTHK_

/*
 *系统是否有粗轧油膜厚度补偿，如果没有请注释下一行
 *
 */

//#define _HAS_R1_OILTHK_

/*
 *系统是否已做粗轧刚度(采用弹跳曲线计算)，如果没有请注释下一行
 *
 */
#define _HAS_R1_MODU_

/*
 *系统是否有FE，如果没有请注释下一行
 *
 */

//#define _HAS_FM_FE_

/*
 *	班组设置
 */
#define	SHIFT_NUM				2							//0:夜班 1:白班 2:中班
						    	//2							//1:早班 2:晚班
#define	GROUP_NUM				3							//0:甲班 1:乙班 2:丙班 3:丁班


/*
 *系统是否具备不锈钢轧制，如果没有请注释下两行
 *
 */
//#define _HAS_CrNi_MODEL_
//#define	 CrNi_INDEX				10							//从材质代码CrNi_INDEX索引号后为不锈钢轧制
//#define	 CrNi_INDEX				30							//从材质代码CrNi_INDEX索引号后为普碳钢轧制

/*
 *系统是否具备硅钢轧制，如果没有请注释下两行
 *
 */
#define _HAS_SiSteel_MODEL_
#define	 SiSteel_INDEX				80						//从材质代码SiSteel_INDEX索引号后为硅钢钢轧制

#define	 HwSteel_INDEX				94						//从材质代码HwSteel_INDEX索引号后为花纹板轧制


/*
 *系统是否有板形控制系统，如果没有请注释下一行
 *
 */

#define _HAS_FM_SSU_

/*
 *系统是否有粗轧后面测宽仪，如果没有请注释下一行
 *
 */
#define _HAS_RM_WIDGAGE_

/*
 *系统是否有卷取后面测宽仪，如果没有请注释下一行
 *
 */
//#define _HAS_DC_WIDGAGE_

/*
 *手动编辑轧制顺序表情况，如果没有请注释下一行
 *
 */
//#define _ROLLSEQU_MAN	//手动编辑轧制顺序表情况下


#endif //_PROJECT_DATA_H_

