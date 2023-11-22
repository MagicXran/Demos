/*
* Copyright (c) 2004, NERCAR
* All rights reserved.
*
* 文件名称：mes_l2_struct
* 摘    要：与宝信MES通信电文的结构体映射
*			 关于详细通信规约，请参考宝信给的iXcom静态规约.pdf
*
* 版本历史：
*     2023-02-03    v1.0     XGZ     创建
*/

#pragma once

#include "project_shared.h"
#include <memory>
//单字节对齐
#pragma pack(1)

namespace model_l2_msg_define
{


	inline int vipStringDecode(char* PvipString, char* Pstring, int* Poffset)
	{
		int status, offset;
		int len;

		status = 1;
		offset = *Poffset;

		//+ 1  If there is valid data in the string, then
		if ((len = strlen((PvipString + offset))) > 0)
		{
			strcpy(Pstring, (PvipString + offset));
			offset = len % 4;
			*Poffset += len;
			if (offset > 0)
				*Poffset += (4 - offset);
		}

		//+ 1  Else (no data)
		else
		{
			//+	2  Increment the
			strcpy(Pstring, "\0");
			*Poffset += 4;
			status = 0;
		}
		//ALARM(AL_WARNING,1024,"Pstring = %s, Poffset= %d",Pstring,*Poffset);
		//+ 1  Return with status
		return status;
	};


	//----------------------------------------------------------------------------
	//+ Encode VIP compressed strings (on 4 byte boundaries)
	//----------------------------------------------------------------------------
	inline int vipStringEncode(char* Pstring, char* PvipString, int* Poffset)
	{
		int status, offset;
		int len;

		status = 1;
		offset = *Poffset;

		//+ 1  If there is valid data in the new string, then
		if ((len = strlen(Pstring)) > 0)
		{
			len++;		// add space for NULL
			strcpy((PvipString + offset), Pstring);
			offset = len % 4;
			*Poffset += len;
			if (offset > 0)
				*Poffset += (4 - offset);
		}

		//+ 1  Else (no data)
		else
		{
			//+	2  Increment the offset and put null character in VIP string
			*Poffset += 4;
			strcpy((PvipString + offset), "\0");
			status = 0;
		}

		//+ 1  Return with status
		return status;
	}


	/// <summary>
	/// ABB L2 => MDS  201
	/// </summary>
	struct MDS_L2_ALIVE
	{
		short int hdrLen;                           //VIP message length,long,4,n/a,0,12,
		short int hdrID;                            //VIP message ID,long,4,n/a,4,201,
		int hbCtr;                                  //heartbeat counter,long,4,counter,8,,
	};



	/// <summary>
	/// ABB L2 => Model 202
	/// </summary>
	struct MDS_CALC_REQ
	{
		short hdrLen;                          //VIP message length,long,4,n/a,0,452,
		short hdrID;                          //VIP message ID,long,4,n/a,4,202,
		int hbCtr;                                  //heartbeat counter,long,4,counter,8,,
		int setupReq;                               //Setup Request,long,4,code,12,"1=test calculations
		int ghostFlag;                              //ghost rolling flag,long,4,boolean,16,"code for area to ghost roll. 
		float slabThk;                              //Slab Thickness,float,4,mm,20,,
		float slabWid;                              //Slab Width,float ,4,mm,24,,
		float slabLen;                              //Slab Length,float,4,m,28,,
		float slabWgt;                              //Slab Weight,float ,4,kg,32,,
		int slabTaperStatus;                        //Slab Taper Status,long,4,boolean,36,"Width taper, changing casting width
		float slabTaperValue;                       //Slab Taper Value,float,4,mm,40,Delta width less than the maximum width,
		int gradeTransCode;                         //Grade Transition Code,long,4,boolean,44,"Slab contaiing mixed grades, normally formed when changing from one grade to another in the caster. The model does not adapt any data for this slab.
		int ferriteRollingFlag;                     //Ferrite Rolling Flag,long,4,boolen,48,1 if ferritic rolling (FM entry temperature critical),,,,,,,,,,
		int useActualChem;                          //Use chemistries below for alloy content,long,4,boolean,52,,,,,,,,,,,
		float Aluminum;                             //% Aluminum,float,4,%,56,Send zeros if the actual analysis is not available. Then the IPSS internal default grade information will be used.,Al,,,,,,,,,
		float Boron;                                //% Boron,float,4,%,60,,B,,,,,,,,,
		float Carbon;                               //% Carbon,float,4,%,64,,C,,,,,,,,,
		float Chromium;                             //% Chromium,float,4,%,68,,Cr,,,,,,,,,
		float Cobalt;                               //% Cobalt,float,4,%,72,,Co,,,,,,,,,
		float Copper;                               //% Copper,float,4,%,76,,Cu,,,,,,,,,
		float Iron;                                 //% Iron,float,4,%,80,Used as check sum for total %,Fe,,,,,,,,,
		float Hydrogen;                             //% Hydrogen,float,4,%,84,,H,,,,,,,,,
		float Magnesium;                            //% Magnesium,float,4,%,88,,Mg,,,,,,,,,
		float Manganese;                            //%Manganese,float,4,%,92,,Mn,,,,,,,,,
		float Molybdenum;                           //% Molybdenum,float,4,%,96,,Mo,,,,,,,,,
		float Nickel;                               //% Nickel,float,4,%,100,,Ni,,,,,,,,,
		float Niobium;                              //% Niobium,float,4,%,104,,Nb,,,,,,,,,
		float Nitrogen;                             //% Nitrogen,float,4,%,108,,N,,,,,,,,,
		float Oxygen;                               //% Oxygen,float,4,%,112,,O,,,,,,,,,
		float Phosphorus;                           //% Phosphorus,float,4,%,116,,P,,,,,,,,,
		float Silicon;                              //% Silicon,float,4,%,120,,Si,,,,,,,,,
		float Sulfer;                               //% Sulfer,float,4,%,124,,S,,,,,,,,,
		float Tin;                                  //% Tin,float,4,%,128,,Sn,,,,,,,,,
		float Tantalum;                             //% Tantalum,float,4,%,132,,Ta,,,,,,,,,
		float Titanium;                             //% Titanium,float,4,%,136,,Ti,,,,,,,,,
		float Tungsten;                             //% Tungsten,float,4,%,140,,W,,,,,,,,,
		float Vanadium;                             //% Vanadium,float,4,%,144,,V,,,,,,,,,
		float Zinc;                                 //% Zinc,float,4,%,148,,Zn,,,,,,,,,
		float Zirconium;                            //% Zirconium,float,4,%,152,,Zr,,,,,,,,,
		int furNum;                                 //Furnace number,long,4,index,156,,,,,,,,,,,
		int rowNum;                                 //Furnace row  number,long,4,index,160,Check if double charging is foreeseen,,,,,,,,,,
		int chargeMode;                             //furnace charge mode,long,4,code,164,"0-cold charge
		int dischTempAim;                           //furnace discharge aim,long,4,oC,168,Discharge temparure aim,,,,,,,,,,
		float rmTmpAim;                             //RM Exit temperature aim,float,4,oC,172,After RM2,,,,,,,,,,
		float rmTmpMax;                             //RM Exit temperature maximum,float,4,oC,176,After RM2,
		float rmTmpMin;                             //RM Exit temperature minimum,float,4,oC,180,After RM2,
		int r1PassNo;                               //desired passes in R1,long,4,count,184,"Desired no of passes.
		int r2PassNo;                               //desired passes in R2,long,4,count,188,"Desired no of passes.
		int plateFlag;                              //Plate Flag,long,4,boolean,192,ordered plate from roughing mill,
		float rmThkAim;                             //RM Exit Thickness Aim,float,4,mm,196,,
		float rmWidAim;                             //RM Exit Width Aim,float,4,mm,200,Used for plate rolling when discharging after RM,
		int noCoilBoxFlag;                          //preferred coil box usage,long,4,boolean,204,"1-no coilbox
		int cutMode;                                //crop shear cut mode,long,4,code,208,"0-cut head and tail
		float csTmpAim;                             //Crop Shear Temperature Aim,float,4,degC,212,"Used for Ferritic Rolling, else zero",
		float csTmpMax;                             //Crop Shear Temperature Maximum,float,4,degC,216,,
		float csTmpMin;                             //Crop Shear Temperature Minimum,float,4,degC,220,,
		int fmDscCode;                              //FM Descaler Practice Code,long,4,code,224,"Codes to be specified (IPSS)
		int fmIscCode;                              //FM InterStand Cooling Practice,long,4,code,228,"Codes to be specified (IPSS)
		float fmThkAim;                             //Fm Thickness Aim,float,4,mm,232,,
		float fmThkMax;                             //FM Thickness Maximum,float,4,mm,236,,
		float fmThkMin;                             //FM Thickness Minimum,float ,4,mm,240,,
		float fmWidAim;                             //FM Width Aim,float,4,mm,244,,
		float fmWidMax;                             //FM Width Maximum,float,4,mm,248,,
		float fmWidMin;                             //FM Width Minimum,float,4,mm,252,,
		float fmTmpAim;                             //Finish Temperature Aim,float,4,oC,256,,
		float fmTmpMax;                             //Finish Temperature Maximum,float,4,oC,260,,
		float fmTmpMin;                             //Finish Temperature Minimum,float,4,oC,264,,
		float fmCrnAim;                             //Crown Aim,float,4,micron,268,,
		float fmCrnMax;                             //Crown Maximum,float,4,micron,272,,
		float fmCrnMin;                             //Crown Minimum,float,4,micron,276,,
		float flatAim;                              //Flatness Aim,float,4,I-units,280,0 is default target,
		float flatMax;                              //Flatness Maximum,float,4,I-units,284,,
		float flatMin;                              //Flatness Minimum,float,4,I-units,288,,
		float ceTmpAim;                             //Coiling Temperature Aim,float,4,oC,292,,
		float ceTmpMax;                             //Coiling Temperature Maximum,float,4,oC,296,,
		float ceTmpMin;                             //Coiling Temperature Minimum,float,4,oC,300,,
		int coolingRateCode;                        //Coiling temperature cooling rate code,long,4,code,304,"For selection of early/late cooling
		float imCoolingTemp;                        //Intermediate cooling temperature on cooling section,float,4,oC,308,"Used for Dual Phase material
		float imRecoveryTime;                       //Intermediate recovery time between first and secondary cooling sections,float,4,s,312,"Used for Dual Phase material
		float fmThkAlt;                             //FM Alternate Thickness target,float,4,mm,316,If the gauge can not be achieved due to for ex temperature problems this gauge is used instead,
		float fmTmpAlt;                             //FM Alternate Temperature target ,float,4,oC,320,If the gauge is changed this finishing temperature is used instead,
		float ctTmpAlt;                             //Coiling Temperature Alternate target,float,4,oC,324,If the gauge is changed this coiling temperature is used instead,
		float ctHheLen;                             //mm   CTC hot head end length
		float ctHheOfs;                             //degC CTC hot head end length
		float ctHteLen;                             //mm   CTC hot tail end length
		float ctHteOfs;                             //degC CTC hot tail end length
		char slabId[16];                            //Slab/Piece designation,char,16,string,328,,
		char steelGrade[12];                        //Steel grade,char,12,string,344,,
		char chargeTime[24];                        //furnace charge time,char,24,string,356,(form: yyyy-mm-dd HH:mm:ss),
		char extractTime[24];                       //furnace extract time,char,24,string,380,(form: yyyy-mm-dd HH:mm:ss),
		char unitName[24];                          //,coil unit name,char,24,string,404,"spare, not needed for IPSS Model",
		char batchName[24];                         // ,slab heat batch ID,char,24,string,428,"spare, not needed for IPSS Model",

		MDS_CALC_REQ() {
			memset(this, 0x00, sizeof(MDS_CALC_REQ));
			hdrID = shared_define::model::MDS_CALC_ID;
			hdrLen = sizeof(MDS_CALC_REQ);
		};

		/// <summary>
		/// 压缩变长字段,保持4 bytes 内存对齐
		/// </summary>
		inline void CompressStr()
		{
			try
			{
				auto pdata = std::make_unique<model_l2_msg_define::MDS_CALC_REQ>();
				auto pdata_row = pdata.get();

				int offset = 0;
				char* PvipString = const_cast<char*>(pdata_row->slabId);

				model_l2_msg_define::vipStringEncode(static_cast<char*>(this->slabId), PvipString, &offset);
				model_l2_msg_define::vipStringEncode(static_cast<char*>(this->steelGrade), PvipString, &offset);
				model_l2_msg_define::vipStringEncode(static_cast<char*>(this->chargeTime), PvipString, &offset);
				model_l2_msg_define::vipStringEncode(static_cast<char*>(this->extractTime), PvipString, &offset);
				model_l2_msg_define::vipStringEncode(static_cast<char*>(this->unitName), PvipString, &offset);
				model_l2_msg_define::vipStringEncode(static_cast<char*>(this->batchName), PvipString, &offset);

				auto total_chars_size = sizeof(this->slabId) + sizeof(this->steelGrade) + sizeof(this->chargeTime) + sizeof(this->extractTime) + sizeof(this->unitName) + sizeof(this->batchName);
				this->hdrLen -= static_cast<short>(total_chars_size - offset);

				//std::cout << offsetof(MDS_CALC_REQ, slabId) << std::endl;
				memcpy(this->slabId, PvipString, offset);
			}
			catch (const std::exception& e)
			{
				throw e;
			}
		}
	}; //460

	/*
	 *	(MDS)MDS_RM1_SUPTYPE --> RM1_CO
	 *	TELID: 111
	 */

	typedef struct {
		float vwrThdEg;                             //"PASS edger peripheral speed reference, thread",float,4,m/s,76,??    Pass  1    ??,Note: Pass Schedules are for R1 only,,
		float frcRfEg;                              //PASS edger force,float,4,MN,80,,,,
		float widRfEg;                              //PASS edger exit width,float,4,mm,84,,,,
		float gapRfEg;                              //PASS edger gap reference,float,4,mm,88,,,,
		float gapOfsHdEg_1;                         //PASS edger gap head short stroke offset,float,4,mm,92,gapOfsHdEg[pass][4],,,
		float gapOfsHdEg_2;                         //,float,4,mm,96,,
		float gapOfsHdEg_3;                         //,float,4,mm,100,,
		float gapOfsHdEg_4;                         //,float,4,mm,104,,
		float gapOfsLenHdEg_1;                      //PASS edger gap head offset length,float,4,mm,108,,
		float gapOfsLenHdEg_2;                      //,float,4,mm,112,,
		float gapOfsLenHdEg_3;                      //,float,4,mm,116,,
		float gapOfsLenHdEg_4;                      //,float,4,mm,120,,
		float gapOfsTlEg_1;                         //PASS edger gap tail short stroke offset,float,4,mm,124,gapOfsTlEg[pass][4],
		float gapOfsTlEg_2;                         //,float,4,mm,128,,
		float gapOfsTlEg_3;                         //,float,4,mm,132,,
		float gapOfsTlEg_4;                         //,float,4,mm,136,,
		float gapOfsLenTlEg_1;                      //PASS edger gap tail offset length,float,4,mm,140,gapOfsLenTlEg[pass],
		float gapOfsLenTlEg_2;                      //,float,4,mm,144,,
		float gapOfsLenTlEg_3;                      //,float,4,mm,148,,
		float gapOfsLenTlEg_4;                      //,float,4,mm,152,,
		float rFactorEg;                            //area in/area out at edger,float,4,mm2/mm2,156,,
		float slpRfFEg;                             //PASS predicted forward slip out of Edger,float,4,%,160,,,,
		float thkRfRm;                              //PASS predicted exit thickness,float,4,mm,164,,,,
		float widRfRm;                              //PASS predicted exit width (hot),float,4,mm,168,,,,
		float tmpRfPyr;                             //PASS strip temperature at exit pyrometer
		float vwrThdRm;                             //"PASS roll peripheral speed reference, thread",float,4,m/s,176,,,,
		float vwrRunRm;                             //"PASS roll peripheral speed reference, run",float,4,m/s,180,,,,
		float vwrTloRm;                             //"PASS roll peripheral speed reference, tailout",float,4,m/s,184,,,,
		float trqRfRm;                              //PASS predicted drive torque,float,4,Nm,188,,,,
		float vssRfRm;                              //PASS predicted strip run speed,float,4,m/s,192,,,,
		float slpRfRm;                              //PASS predicted strip forward slip,float,4,%,196,,,,
		float dPuRfRm;                              //PASS thickness reduction,float,4,%,200,,,,
		float barLenRm;                             //PASS exit strip length,float,4,m,204,,,,
		float gapRfRm;                              //PASS stand gap reference,float,4,mm,208,,,,
		float frcRfRm;                              //PASS predicted roll gap force,float,4,MN,212,,,,
		float frcAGCRm;                             //PASS AGC roll gap force (use for absolute AGC),float,4,MN,216,,,,
		float strWidRm;                             //stretch curve width component,float,4,mm/(mm*MN),220,,,,
		float dHDGapRm;                             //PASS transfer function:delta thickness/delta gap,float,4,mm/mm,224,(may not be used by ABB),,,
		float dFrcDHRm;                             //PASS strip modulus:delta force/delta exit thickness,float,4,kN/mm,228,(may not be used by ABB),,,
		float dFrcDGapRm;                           //PASS modulus:delta force/delta gap,float,4,MN/mm,232,(may not be used by ABB),,,
		float TenRfRg;                              //"strip tension, Edger to RM",float,4,N/mm2,236,,,,
		float AGCModeMinLmt;                        //AGC force limit ,float,4,%,240,% of exit gauge,,,
		float AGCModeMaxLmt;                        //AGC force limit ,float,4,%,244,% of exit gauge,,,
		float dGapDWidEg;                           //Width control sensitivity parameter,float,4,mm/mm,248,,,,
		float rFactorRm;                            //reduction factor (area in/area out) at RM,float,4,mm2/mm2,252,,,,
		float widEntWG;                             //entry width gauge referece (cold),float,4,mm,256,,,,
		float widExtWG;                             //exit width gauge referece (cold),float,4,mm,260,,,,
		float gapOfsRfR;                            //total roll gap offsets applied on this pass,float,4,mm,264,,,,
		float oilFilmOfs;                           //oil film offset applied to gap,float,4,mm,268,,,,
		//04-27 以gblprm.txt
		//int	  spareW1;								//spare word per pass: 1, 2
		//int   spareW2;
		float agcGnRfR;                             //PASS AGC gaugemeter gain,float,4, n/a,272,,
		float widRfEnt;                             //PASS predicted entry width (hot),float,4,mm,
		float spareR1P1;                            //spare
		float spareR1P2;                            //spare
		float spareR1P3;                            //spare
		float spareR1P4;                            //spare
		float spareR1P5;                            //spare

	} MDL_RM1_SUP_PASSTYPE;

	typedef struct {
		short int hdrLen;                           //VIP message length,long,4,n/a,0,2348
		short int hdrID;                            //VIP message ID,long,4,n/a,4,111
		int hbCtr;                                  //heartbeat counter,long,4,counter,8,
		int rmdSOK;                                 //RM Setup setup OK,long,4,boolean,12,
		float rxPyrRef;                             //RM exit pyrometer predicted,float,4,oC,16,
		float widRmx;                               //RM Exit width (hot) predicted,float,4,mm,20,
		int DilatometerCurveId;                     //Dilatometer curve Id for gauge,long,4,index,24,
		int RmAlarmWord;                            //"Alarms bits, reason for setup error",long,4,packed,28,
		int RmEventWord;                            //"Event bits, reason for setup special events",long,4,packed,32,,,,
		float slabThk;                              //slab thickness,float,4,mm,36,,,,
		float slabWid;                              //slab width,float,4,mm,40,,,,
		float slabLen;                              //slab length ,float,4,m,44,,,,
		int lastPassR1;                             //last pass out of R1,long,4,index,48,,,,
		int spareR00;                               //spare word,long,4,n/a,52,,,,
		float skiUpC1;                              //ski-up (turn-up) Upper Zero Point [0-5]
		float skiUpC2;                              //ski-up (turn-up) Upper ratio [0-100]
		float skiUpC3;                              //ski-up (turn-up) Lower Zero Point [0-5]
		float skiUpC4;                              //ski-up (turn-up) Lower ratio [0-100]
		int spareR01;                               //spare word,long,4,n/a,56,,,,
		int spareR02;                               //spare word,long,4,n/a,60,,,,
		int spareR03;                               //spare word,long,4,n/a,64,,,,
		int spareR04;                               //spare word,long,4,n/a,64,,,,
		int spareR05;                               //spare word,long,4,n/a,64,,,,
		int dspSelRm;                               //"PASS descale selected:0=no,1=yes",long,4,packed,68,,,,
		int workingMode;                            //"PASS stand used (active working std):0=no,1=yes",long,4,packed,72,
		MDL_RM1_SUP_PASSTYPE r1Pass;                //Pass 1 data
		MDL_RM1_SUP_PASSTYPE r2Pass;                //Pass 2 data
		MDL_RM1_SUP_PASSTYPE r3Pass;                //Pass 3 data
		MDL_RM1_SUP_PASSTYPE r4Pass;                //Pass 4 data
		MDL_RM1_SUP_PASSTYPE r5Pass;                //Pass 5 data
		MDL_RM1_SUP_PASSTYPE r6Pass;                //Pass 6 data
		MDL_RM1_SUP_PASSTYPE r7Pass;                //Pass 7 data
		MDL_RM1_SUP_PASSTYPE r8Pass;                //Pass 8 data
		MDL_RM1_SUP_PASSTYPE r9Pass;                //Pass 9 data
		MDL_RM1_SUP_PASSTYPE r10Pass;               //Pass 10 data
		MDL_RM1_SUP_PASSTYPE r11Pass;               //Pass 11 data
		//2021-04-27 It was originally [16],[12] but truncation occurred 
		char slabId[16];                            //Slab/Piece designation,char,16,none,1920,
		char steelGrade[12];                        //steel grade,char,12,none,1936,

	} MDS_RM1_SUPTYPE;

	/*
	 *	(MDS)MDS_RM2_SUPTYPE --> MDS
	 *	TELID: 112
	 */
	typedef struct {
		float vwrThdEg;                             //"PASS edger peripheral speed reference, thread",float,4,m/s,76,??    Pass  1    ??,NOTE: Pass schedules are for R2 only,,
		float frcRfEg;                              //PASS edger force,float,4,MN,80,,,,
		float widRfEg;                              //PASS edger exit width,float,4,mm,84,,,,
		float gapRfEg;                              //PASS edger gap reference,float,4,mm,88,,,,
		float gapOfsHdEg_1;                         //PASS edger gap head short stroke offset,float,4,mm,92,gapOfsHdEg[pass][4],,,
		float gapOfsHdEg_2;                         //,float,4,mm,96,,
		float gapOfsHdEg_3;                         //,float,4,mm,100,,
		float gapOfsHdEg_4;                         //,float,4,mm,104,,
		float gapOfsLenHdEg_1;                      //PASS edger gap head offset length,float,4,mm,108,,
		float gapOfsLenHdEg_2;                      //,float,4,mm,112,,
		float gapOfsLenHdEg_3;                      //,float,4,mm,116,,
		float gapOfsLenHdEg_4;                      //,float,4,mm,120,,
		float gapOfsTlEg_1;                         //PASS edger gap tail short stroke offset,float,4,mm,124,gapOfsTlEg[pass][4],
		float gapOfsTlEg_2;                         //,float,4,mm,128,,
		float gapOfsTlEg_3;                         //,float,4,mm,132,,
		float gapOfsTlEg_4;                         //,float,4,mm,136,,
		float gapOfsLenTlEg_1;                      //PASS edger gap tail offset length,float,4,mm,140,gapOfsLenTlEg[pass],
		float gapOfsLenTlEg_2;                      //,float,4,mm,144,,
		float gapOfsLenTlEg_3;                      //,float,4,mm,148,,
		float gapOfsLenTlEg_4;                      //,float,4,mm,152,,
		float rFactorEg;                            //area in/area out at edger,float,4,mm2/mm2,156,,
		float slpRfFEg;                             //PASS predicted forward slip out of Edger,float,4,%,160,,,,
		float thkRfRm;                              //PASS predicted exit thickness,float,4,mm,164,,,,
		float widRfRm;                              //PASS predicted exit width (hot),float,4,mm,168,,,,
		float tmpRfPyr;                             //PASS strip temperature at exit pyrometer
		float vwrThdRm;                             //"PASS roll peripheral speed reference, thread",float,4,m/s,176,,,,
		float vwrRunRm;                             //"PASS roll peripheral speed reference, run",float,4,m/s,180,,,,
		float vwrTloRm;                             //"PASS roll peripheral speed reference, tailout",float,4,m/s,184,,,,
		float trqRfRm;                              //PASS predicted drive torque,float,4,Nm,188,,,,
		float vssRfRm;                              //PASS predicted strip run speed,float,4,m/s,192,,,,
		float slpRfRm;                              //PASS predicted strip forward slip,float,4,%,196,,,,
		float dPuRfRm;                              //PASS thickness reduction,float,4,%,200,,,,
		float barLenRm;                             //PASS exit strip length,float,4,m,204,,,,
		float gapRfRm;                              //PASS stand gap reference,float,4,mm,208,,,,
		float frcRfRm;                              //PASS predicted roll gap force,float,4,MN,212,,,,
		float frcAGCRm;                             //PASS AGC roll gap force (use for absolute AGC),float,4,MN,216,,,,
		float strWidRm;                             //stretch curve width component,float,4,mm/(mm*MN),220,,,,
		float dHDGapRm;                             //PASS transfer function:delta thickness/delta gap,float,4,mm/mm,224,(may not be used by ABB),
		float dFrcDHRm;                             //PASS strip modulus:delta force/delta exit thickness,float,4,kN/mm,228,(may not be used by ABB),
		float dFrcDGapRm;                           //PASS modulus:delta force/delta gap,float,4,MN/mm,232,(may not be used by ABB),
		float TenRfRg;                              //"strip tension, Edger to RM",float,4,N/mm2,236,,
		float AGCModeMinLmt;                        //AGC force limit ,float,4,%,240,% of exit gauge,
		float AGCModeMaxLmt;                        //AGC force limit ,float,4,%,244,% of exit gauge,
		float dGapDWidEg;                           //Width control sensitivity parameter,float,4,mm/mm,248,,
		float rFactorRm;                            //area in/area out at RM,float,4,mm2/mm2,252,,
		float widEntWG;                             //entry width gauge referece (cold),float,4,mm,256,,
		float widExtWG;                             //exit width gauge referece (cold),float,4,mm,260,,
		float gapOfsRfR;                            //total roll gap offsets applied on this pass,float,4,mm,264,,
		float oilFilmOfs;                           //oil film offset applied to gap,float,4,mm,268,,
		//04-27 按照gbxx.txt文件修改.
		//int	  spareW;								//spare word per pass: 1, 2
		float agcGnRfR;                             //PASS AGC gaugemeter gain,float,4, n/a,272,,
		float widRfEnt;                             //PASS predicted entry width (hot),float,4,mm,
		float spareR2P1;                            //spare
		float spareR2P2;                            //spare
		float spareR2P3;                            //spare
		float spareR2P4;                            //spare
		float spareR2P5;                            //spare

	} MDL_RM2_SUP_PASSTYPE;
	typedef struct {
		short int hdrLen;                           //VIP message length,long,4,n/a,0,2348
		short int hdrID;                            //VIP message ID,long,4,n/a,4,112
		int hbCtr;                                  //heartbeat counter,long,4,counter,8,
		int rmdSOK;                                 //RM Setup setup OK,long,4,boolean,12,
		float rxPyrRef;                             //RM exit pyrometer predicted,float,4,oC,16,
		float widRmx;                               //RM Exit width (hot) predicted,float,4,mm,20,
		int DilatometerCurveId;                     //Dilatometer curve Id for gauge,long,4,index,24,
		int RmAlarmWord;                            //"Alarms bits, reason for setup error",long,4,packed,28,
		int RmEventWord;                            //"Event bits, reason for setup special events",long,4,packed,32,,,,
		float slabThk;                              //slab thickness,float,4,mm,36,,,,
		float slabWid;                              //slab width,float,4,mm,40,,,,
		float slabLen;                              //slab length ,float,4,m,44,,,,
		int lastPassR2;                             //last pass out of R2 (R2 Only),long,4,index,48,,,,
		float bFrcCBox;                             //coil box bending force,float,4,MN,52,force (MN) or torque (Nm) ?,,,
		float skiUpC1;                              //ski-up (turn-up) constant 1
		float skiUpC2;                              //ski-up (turn-up) constant 1
		float skiUpC3;                              //ski-up (turn-up) constant 1
		float skiUpC4;                              //ski-up (turn-up) constant 1
		int spareR01;                               //spare word,long,4,n/a,
		int spareR02;                               //spare word,long,4,n/a,
		int spareR03;                               //spare word,long,4,n/a,
		int spareR04;                               //spare word,long,4,n/a,
		int spareR05;                               //spare word,long,4,n/a,
		int dspSelRm;                               //"PASS descale selected:0=no,1=yes",long,4,packed,68,,,,
		int workingMode;                            //"PASS stand used (active working std):0=no,1=yes",long,4,packed,72,
		MDL_RM2_SUP_PASSTYPE r1Pass;                //Pass 1 data
		MDL_RM2_SUP_PASSTYPE r2Pass;                //Pass 2 data
		MDL_RM2_SUP_PASSTYPE r3Pass;                //Pass 3 data
		MDL_RM2_SUP_PASSTYPE r4Pass;                //Pass 4 data
		MDL_RM2_SUP_PASSTYPE r5Pass;                //Pass 5 data
		MDL_RM2_SUP_PASSTYPE r6Pass;                //Pass 6 data
		MDL_RM2_SUP_PASSTYPE r7Pass;                //Pass 7 data
		MDL_RM2_SUP_PASSTYPE r8Pass;                //Pass 8 data
		MDL_RM2_SUP_PASSTYPE r9Pass;                //Pass 9 data
		MDL_RM2_SUP_PASSTYPE r10Pass;               //Pass 10 data
		MDL_RM2_SUP_PASSTYPE r11Pass;               //Pass 11 data
		//原[16] [12]
		char slabId[16];                            //Slab/Piece designation,char,16,none,1920,
		char steelGrade[12];                        //steel grade,char,12,none,1936,

	} MDS_RM2_SUPTYPE;


	/*
	 *	(MDS)MDS_FM_SUPTYPE --> MES
	 *	TELID: 113
	 */
	typedef struct {
		float issRfF;                               //STAND interstand cooling reference (not used on F1),float,4,m3/h,284,??    FM  1    ??,,
		float tmpRfF;                               //STAND strip temperature in roll gap,float,4,oC,288,,,
		float thkRfF;                               //STAND predicted exit thickness,float,4,mm,292,,,
		float dPuRff;                               //STAND thickness reduction,float,4,%,296,,,
		float gapRfF;                               //STAND gap reference,float,4,mm,300,,,
		float gapOfsRfF;                            //"Stand gap offsets including thermal crown, wear, roll shifting & roll bending",float,4,mm,304,oil film not included,,
		float frcRfF;                               //STAND predicted roll gap force,float,4,MN,308,,,
		float frcAGC;                               //STAND AGC roll gap force (use for absolute AGC),float,4,MN,312,,,
		float bndRfF;                               //STAND roll bending reference,float,4,MN,316,,,
		float shftRfF;                              //STAND roll shift position,float,4,mm,320,,,
		float rFactorFm;                            //Reduction factor (area in/area out),float,4,p.u.,324,,units  changed 2009-Feb-10,
		float vlsRfF;                               //STAND lead speed factor,float,4,%,328,(probably not needed by ABB),,
		float dFrcDH;                               //STAND strip modulus:delta force/delta exit thickness,float,4,MN/mm,332,,units  changed 2009-Feb-10,
		float agcGnRfF;                             //STAND AGC gaugemeter gain,float,4,none,336,,,
		float spareL01;                               //spare stand based word,long,4,n/a,340,,,
		float dFrcdCrn;                             //Profile control sensitivity factor (dForce / dCrown),float,4,MN/祄,344,,replaced spare 2009-Feb-10,
		int fmWorkingStand;                         //STAND Stand working request (not dummied),packed,4,boolean,348,bit 0=Active,,
		float torqueRfF;                            //STAND predicted motor torque,float,4,Nm,352,,definition corrected 2009-Feb-10,
		float slpRfF;                               //STAND predicted strip forward slip,float,4,%,356,,,
		float AGCModeMinLmt;                        //AGC mode limit for lock-on (% of stand exit gauge,float,4,%,360,,,
		float AGCModeMaxLmt;                        //AGC mode limit for lock-on (% of stand exit gauge,float,4,%,364,,,
		float dBndDFrc;                             //STAND transfer function:delta roll bending force/delta force,float,4,MN/MN,368,,,
		float dGapDBnd;                             //STAND transfer function:delta gap/delta roll bending force,float,4,mm/MN,372,,,
		float tenRfF;                               //Looper tension reference (not used on F1),float,4,N/mm2,376,,,
		float lprPosRff;                            //Looper angle reference (not used on F1),float,4,deg,380,,,
		float oilFilmOfs;                           //oil film offset applied to gap,float,4,mm,384,,,
		float strWidFm;                             //stretch curve width component,float,4,mm/(mm*MN),388,,,
		float spareFP2;                             //spare
		float spareFP3;                             //spare
		float spareFP4;                             //spare
		float spareFP5;                             //spare

	} MDL_FM_SUP_STDTYPE;


	typedef struct {
		short int hdrLen;                           //VIP message length,long,4,n/a,0,1068,,
		short int hdrID;                            //VIP message ID,long,4,n/a,4,113,,
		int hbCtr;                                  //heartbeat counter,long,4,counter,8,,,
		int fmRelease;                              //"Used to release the transfer bar for rolling in the FM, hold the transfer bar if not set. The aim is to use this bit for ferritic rolling where we have to control the FM entry temperature.",long,4,code,
		int fmdSOK;                                 //FM Setup setup OK,long,4,boolean,16,,,
		int fmAlarmWord;                            //"Alarms to the operator, reason for setup error",long,4,boolean,20,,,
		int fmEventWord;                            //"Event to the operator, reason for setup error (not shown directly to the operator)",long,4,boolean,24,,,
		float fxXryRef;                             //X-ray nominal reference(cold),float,4,mm,28,,,
		float pdi_fmThkMin;                         //FM Exit thickness minimum,float,4,mm,32,,,
		float pdi_fmThkMax;                         //FM Exit thickness maximum,float,4,mm,36,,,
		float pdi_fmTmpAim;                         //PDI FMX temperature target,float,4,oC,40,,,
		float pdi_fmTmpMin;                         //PDI FMX temperature target minimum,float,4,oC,44,,,
		float pdi_fmTmpMax;                         //PDI FMX temperature target maximum,float,4,oC,48,,,
		float pdi_crownAim;                         //Aim crown,float,4,microns,52,,,
		float pdi_crownMin;                         //Minimum crown,float,4,microns,56,,,
		float pdi_crownMax;                         //Maximum crown,float,4,microns,60,,,
		float pdi_flatnessAim;                      //PDI flatness target,float,4,i-units,64,,,
		float pdi_flatnessmin;                      //PDI flatness minimum,float,4,i-units,68,,,
		float pdi_flatnessmax;                      //PDI flatness maximum,float,4,i-units,72,,,
		float pdi_Aluminum;                         //% Aluminum,float,4,%,76,,Al,
		float pdi_Boron;                            //% Boron,float,4,%,80,,B,
		float pdi_Carbon;                           //% Carbon,float,4,%,84,,C,
		float pdi_Chromium;                         //% Chromium,float,4,%,88,,Cr,
		float pdi_Cobalt;                           //% Cobalt,float,4,%,92,,Co,
		float pdi_Copper;                           //% Copper,float,4,%,96,,Cu,
		float pdi_Iron;                             //% Iron,float,4,%,100,Used as check sum for total %,Fe,
		float pdi_Hydrogen;                         //% Hydrogen,float,4,%,104,,H,
		float pdi_Magnesium;                        //% Magnesium,float,4,%,108,,Mg,
		float pdi_Manganese;                        //%Manganese,float,4,%,112,,Mn,
		float pdi_Molybdenum;                       //% Molybdenum,float,4,%,116,,Mo,
		float pdi_Nickel;                           //% Nickel,float,4,%,120,,Ni,
		float pdi_Niobium;                          //% Niobium,float,4,%,124,,Nb,
		float pdi_Nitrogen;                         //% Nitrogen,float,4,%,128,,N,
		float pdi_Oxygen;                           //% Oxygen,float,4,%,132,,O,
		float pdi_Phosphorus;                       //% Phosphorus,float,4,%,136,,P,
		float pdi_Silicon;                          //% Silicon,float,4,%,140,,Si,
		float pdi_Sulfer;                           //% Sulfer,float,4,%,144,,S,
		float pdi_Tin;                              //% Tin,float,4,%,148,,Sn,
		float pdi_Tantalum;                         //% Tantalum,float,4,%,152,,Ta,
		float pdi_Titanium;                         //% Titanium,float,4,%,156,,Ti,
		float pdi_Tungsten;                         //% Tungsten,float,4,%,160,,W,
		float pdi_Vanadium;                         //% Vanadium,float,4,%,164,,V,
		float pdi_Zinc;                             //% Zinc,float,4,%,168,,Zn,
		float pdi_Zirconium;                        //% Zirconium,float,4,%,172,,Zr,
		//2021-04-27 According to gblprm.txt to modify
		//float sparePdi;                             //spare pdi word
		//float spareW00;
		float fmThkAlt;                             //mm FM Alternate Thickness target
		float fmTmpAlt;                             //deg C FM Alternate Temperature target
		int feDspSel;                               //"entry descale selected:0=no,1=yes",long,4,none,184,,,
		float csAimTemp;                            //Crop shear aim temperature,float,4,oC,188,,,
		float tmpRfF0;                              //predicted crop shear temperature,float,4,oC,192,,,
		float vssRfF0;                              //predicted entry strip speed,float,4,m/s,196,,,
		float fxPyrRef;                             //FM exit pyrometer reference(predicted),float,4,oC,200,,,
		float vssFmx;                               //FMX strip speed reference,float,4,m/s,204,,,
		float vssFmxMax;                            //maximum allowable FMX strip speed,float,4,m/s,208,Torque limit/top speed limit - not predicted top speed,,
		float tmpExpFmx;                            //FM exit X-ray and width gauge temperature expansion coefficient,float,4,p.u.,212,,units  changed 2009-Feb-10,
		float barLenFmx;                            //Stand exit strip length,float,4,m,216,,,
		float fmTime;                               //Total FM rolling time,float,4,sec,220,,,
		float widFme;                               //FM Entry strip width(hot),float,4,mm,224,,,
		float widFmx;                               //FM Exit strip width(hot),float,4,mm,228,,,
		float fxWidRef;                             //Width gauge reference (cold),float,4,float,232,,,
		int dilatometerNdx;                         //dilatometer index,long,4,n/a,236,,,
		float pdi_fmWidMin;                         //FM Exit thickness minimum,float,4,mm,240,,,
		float pdi_fmWidMax;                         //FM Exit thickness maximum,float,4,mm,244,,,
		float thkRfF0;                              //Predicted transfer bar thickness,float,4,mm,248,,,
		float MonModeMinLmt;                        //x-ray monitor mode minm limit,float,4,%,252,per cent of exit gauge,,
		float MonModeMaxLmt;                        //x-ray monitor mode max limit,float,4,%,256,per cent of exit gauge,,
		int fmExitStd;                              //FM delivery stand (last active stand),long,4,n/a,260,,,
		float monGnRfF;                             //AGC monitor product gain,float,4,p.u.,264,,units  changed 2009-Feb-10,
		float dFrcDIU;                              //flatness control sensitivity factor for delivery stand,float,4,MN/I,268,,,
		int nStdCrnCorr;                            //latest stand to apply crown correction,long,4,n/a,272,,,
		float fxCrnRfF;                             //FM Exit predicted crown
		float fxWidRefOffset;                       //FM Width Aim offset 
	/*	int spareWFX00;
		int spareWFX01;
		int spareWFX02;
		int spareWFX03; */
		MDL_FM_SUP_STDTYPE f1Data;                  //f1 data
		MDL_FM_SUP_STDTYPE f2Data;                  //f2 data
		MDL_FM_SUP_STDTYPE f3Data;                  //f3 data
		MDL_FM_SUP_STDTYPE f4Data;                  //f4 data
		MDL_FM_SUP_STDTYPE f5Data;                  //f5 data
		MDL_FM_SUP_STDTYPE f6Data;                  //f6 data
		MDL_FM_SUP_STDTYPE f7Data;                  //f7 data
		// 原来 [16] [12]
		char slabId[16];                            //slab ID (strip identifier),char,16,none,1040,,,
		char steelGrade[12];                        //steel grade,char,12,none,1056,,,

	} MDS_FM_SUPTYPE;

	/*
	 *	(MDS)MDS_ROT_SUPTYPE --> MES
	 *	TELID: 114
	 */
	typedef struct {
		short int hdrLen;                           //VIP message length,long,4,n/a,0,132,
		short int hdrID;                            //VIP message ID,long,4,n/a,4,114,
		int hbCtr;                                  //heartbeat counter,long,4,n/a,8,,
		int ctcSOK;                                 //Laminar flow Setup setup OK,long,4,boolean,12,(bit 0 = Ok),
		int ctsAlarmWord;                           //"Alarms bits, reason for setup error",packed,4,bit pattern,16,,
		int ctsEventWord;                           //"Event bits, reason for setup special events",packed,4,bit pattern,20,,
		int rtsSupTop_G1;                           //" top spray on, group 1",long,4,boolean,24,bits 0-31 used for spray 01-32,
		int rtsSupTop_G2;                           //" top spray on, group 2",long,4,boolean,28,bits 0-31 used for spray 33-64,
		int rtsSupTop_G3;                           //" top spray on, group 3",long,4,boolean,32,bits 0-23 used for spray 65-88,
		int rtsSupBtm_G1;                           //" btm spray on, group 1",long,4,boolean,36,bits 0-31 used for spray 01-32,
		int rtsSupBtm_G2;                           //" btm spray on, group 2",long,4,boolean,40,bits 0-31 used for spray 33-64,
		int rtsSupBtm_G3;                           //" btm spray on, group 3",long,4,boolean,44,bits 0-23 used for spray 65-88,
		int rtsSupSwp_G1;                           //" spray sprays on, group 1",long,4,boolean,48,"bits 0-24 used for sweep 1-21, 
		int rtsHheTop_G1;                           //" top spray delayed for hot head, group 1",long,4,boolean,52,bits 0-31 used for spray 01-32,
		int rtsHheTop_G2;                           //" top spray hot head, group 2",long,4,boolean,56,bits 0-31 used for spray 33-64,
		int rtsHheTop_G3;                           //" top spray hot head, group 3",long,4,boolean,60,bits 0-23 used for spray 65-88,
		int rtsHheBtm_G1;                           //" btm spray hot head, group 1",long,4,boolean,64,bits 0-31 used for spray 01-32,
		int rtsHheBtm_G2;                           //" btm spray hot head, group 2",long,4,boolean,68,bits 0-31 used for spray 33-64,
		int rtsHheBtm_G3;                           //" btm spray hot head, group 3",long,4,boolean,72,bits 0-23 used for spray 65-88,
		float ceTmpAim;                             //PDI Coiling temperature target,float,4,oC,76,,
		float ceTmpMin;                             //PDI Coiling temperature target minimum,float,4,oC,80,,
		float ceTmpMax;                             //PDI Coiling temperature target maximum,float,4,oC,84,,
		int rtsSpare1;                              //spare,long,4,n/a,88,,
		int rtsSpare2;                              //spare,long,4,n/a,92,,
		int rtsSpare3;                              //spare,long,4,n/a,96,,
		int rtsSpare4;                              //spare,long,4,n/a,100,,
		char slabId[16];                            //slab ID (strip identifier),char,16,none,104,,
		char steelGrade[12];                        //steel grade,char,12,none,120,,

	} MDS_ROT_SUPTYPE;

	/*
	 *	(MDS)MDS_CLR_SUPTYPE --> MES
	 *	TELID: 115
	 */
	typedef struct {
		short int hdrLen;                           //VIP message length,long,4,n/a,0,128,
		short int hdrID;                            //VIP message ID,long,4,n/a,4,115,
		int hbCtr;                                  //heartbeat counter,long,4,n/a,8,,
		int clrSOK;                                 //Coiler Setup OK,long,4,boolean,12,(bit 0 = Ok),
		int clrAlarmWord;                           //"Alarms to the operator, reason for setup error",long,4,boolean,16,,
		int clrEventWord;                           //"Event to the operator, reason for setup error (not shown directly to the operator)",long,4,boolean,20,,
		float trqBndRfC;                            //coiler bending torque reference,float,4,Nm,24,,
		float tenPrRf;                              //"tension reference, between Mill & Pinch Roll",float,4,N/mm2,28,,
		float tenClrRf;                             //"coiler tension reference, between Pinch Roll & Mandrel",float,4,N/mm2,32,,
		float tensStrClr;                           //predicted tensile strength at clr,float,4,N/mm2,36,,
		float yieldClr;                             //predicted yield stress at coiler,float,4,N/mm2,40,,
		float spWeight;                             //specific weight of steel,float,4,kg/m3,44,,
		float thkCle;                               //thickness at coiling temperature,float,4,mm,48,,
		float thkCold;                              //cold thickness,float,4,mm,52,,
		float widCold;                              //cold width,float,4,mm,56,,
		float widCle;                               //width at coiling temperature,float,4,mm,60,,
		float lenStrip;                             //predicted stip length,float,4,m ,64,,
		int gradeNdx;                               //steel grade index,long,4,n/a,68,,
		int gradeFam;                               //steel grade group,long,4,n/a,72,,
		float vssFmx;                               //FM Exit strip speed on thread,float,4,m/s,76,,
		int clrSpare01A;                            //spare,long,4,n/a,80,,
		int clrSpare01B;                            //spare,long,4,n/a,84,,
		int clrSpare02;                             //spare,long,4,n/a,88,,
		int headInZone;                             //tracking zone of piece at sendout
		float ceTmpAim;                             //PDI Coiling temperature target,float,4,oC,96,,
		char slabId[16];                            //slab ID (strip identifier),char,16,none,100,,
		char steelGrade[12];                        //steel grade,char,12,none,116,,

	} MDS_CLR_SUPTYPE;


	/*
	 *	(MDS)MDS_PDI_REQTYPE --> MES
	 *	TELID: 102
	 */
	typedef struct {
		short int hdrLen;                           //VIP message length,long,4,n/a,0,24,
		short int hdrID;                            //VIP message ID,long,4,n/a,4,102,
		char slabId[16];                            //slab ID (strip identifier),char,16,none,8,,slab ID for requested PDI update

	} MDS_PDI_REQTYPE;

	/*
	 *	(MDS)MDS_RM_RPTTYPE --> MES
	 *	TELID: 121
	 */
	typedef struct {
		short int hdrLen;                           //VIP message length,long,4,n/a,0,100,
		short int hdrID;                            //VIP message ID,long,4,n/a,4,121,
		int hbCtr;                                  //heartbeat counter,long,4,n/a,8,,
		float rgHrdFctL_1;                          //Rougher hardness factor,float,4,unitless,12,,
		float rgHrdFctL_2;                          //Rougher hardness factor,float,4,unitless,16,,
		float rgKsiL_1;                             //Rougher measured ksi,float,4,MN/mm2,20,,
		float rgKsiL_2;                             //Rougher measured ksi,float,4,MN/mm2,24,,
		int rgAutoL_1;                              //Rougher in auto,long,4,Boolean,28,,
		int rgAutoL_2;                              //Rougher in auto,long,4,Boolean,32,,
		int egAutoL_1;                              //Edger in auto,long,4,Boolean,36,,
		int egAutoL_2;                              //Edger in auto,long,4,Boolean,40,,
		int updRmMdl;                               //update rm model,long,4,Boolean,44,,
		int updRmGbl;                               //update rm global,long,4,Boolean,48,,
		int updRmTmp;                               //update rm temperature,long,4,Boolean,52,,
		int updRmWid;                               //update rm width,long,4,Boolean,56,,
		int updRmFrc;                               //update edger calibration,long,4,Boolean,60,,
		int updWsm;                                 //update rm width safety margin,long,4,Boolean,64,,
		float rgKsiRatPm_1;                         //Rougher ksi ratio error,float,4,%,68,,
		float rgKsiRatPm_2;                         //Rougher ksi ratio error,float,4,%,72,,
		float egKsiRatPm_1;                         //edger ksi ratio error,float,4,%,76,,
		float egKsiRatPm_2;                         //edger ksi ratio error,float,4,%,80,,
		char slabId[16];                            //slab ID for desired PDI,char,16,string,84,,

	} MDS_RM_RPTTYPE;

	/*
	 *	(MDS)MDS_FM_RPTTYPE --> MES
	 *	TELID: 122
	 */
	typedef struct {
		short int hdrLen;                           //VIP message length,long,4,n/a,0,432,
		short int hdrID;                            //VIP message ID,long,4,n/a,4,122,
		int hbCtr;                                  //heartbeat counter,long,4,counter,8,,
		float dThkSF_1;                             //FM stand thickness difference,float,4,mm,12,,
		float dThkSF_2;                             //FM stand thickness difference,float,4,mm,16,,
		float dThkSF_3;                             //FM stand thickness difference,float,4,mm,20,,
		float dThkSF_4;                             //FM stand thickness difference,float,4,mm,24,,
		float dThkSF_5;                             //FM stand thickness difference,float,4,mm,28,,
		float dThkSF_6;                             //FM stand thickness difference,float,4,mm,32,,
		float dThkSF_7;                             //FM stand thickness difference,float,4,mm,36,,
		float ksiErF_1;                             //FM yield stress modifier error,float,4,%,40,,
		float ksiErF_2;                             //FM yield stress modifier error,float,4,%,44,,
		float ksiErF_3;                             //FM yield stress modifier error,float,4,%,48,,
		float ksiErF_4;                             //FM yield stress modifier error,float,4,%,52,,
		float ksiErF_5;                             //FM yield stress modifier error,float,4,%,56,,
		float ksiErF_6;                             //FM yield stress modifier error,float,4,%,60,,
		float ksiErF_7;                             //FM yield stress modifier error,float,4,%,64,,
		float rKsiLF_1;                             //FM learning repredicted to measured yield stress ratio,float,4,%,68,,
		float rKsiLF_2;                             //FM learning repredicted to measured yield stress ratio,float,4,%,72,,
		float rKsiLF_3;                             //FM learning repredicted to measured yield stress ratio,float,4,%,76,,
		float rKsiLF_4;                             //FM learning repredicted to measured yield stress ratio,float,4,%,80,,
		float rKsiLF_5;                             //FM learning repredicted to measured yield stress ratio,float,4,%,84,,
		float rKsiLF_6;                             //FM learning repredicted to measured yield stress ratio,float,4,%,88,,
		float rKsiLF_7;                             //FM learning repredicted to measured yield stress ratio,float,4,%,92,,
		float rPwrLF_1;                             //FM learning repredicted to measured power ratio,float,4,%,96,,
		float rPwrLF_2;                             //FM learning repredicted to measured power ratio,float,4,%,100,,
		float rPwrLF_3;                             //FM learning repredicted to measured power ratio,float,4,%,104,,
		float rPwrLF_4;                             //FM learning repredicted to measured power ratio,float,4,%,108,,
		float rPwrLF_5;                             //FM learning repredicted to measured power ratio,float,4,%,112,,
		float rPwrLF_6;                             //FM learning repredicted to measured power ratio,float,4,%,116,,
		float rPwrLF_7;                             //FM learning repredicted to measured power ratio,float,4,%,120,,
		float thkErF;                               //FM exit thickness error,float,4,mm,124,,
		int uTmpOf;                                 //Update FM temperature offset,long,4,boolean,128,,
		int uThkOf;                                 //Update FM thickness offset,long,4,boolean,132,,
		int uGapOf;                                 //Update FM gap offsets,long,4,boolean,136,,
		int uFmMdl;                                 //Update FM force and temperature model (long term),long,4,boolean,140,,
		int uFmMdG;                                 //Update global FM force and temperature model (short term),long,4,boolean,144,,
		int ampSNG;                                 //FM snap shot measured stand amps no good,long,4,boolean,148,,
		int frcPNG;                                 //FM progressive measured stand force no good,long,4,boolean,152,,
		int frcSNG;                                 //FM snap shot measured stand force no good,long,4,boolean,156,,
		int tenPNG;                                 //FM progressive measured looper tension no good,long,4,boolean,160,,
		int gapPNG;                                 //FM progressive measured stand gaps no good,long,4,boolean,164,,
		int gapSNG;                                 //FM snap shot measured stand gaps no good,long,4,boolean,168,,
		int vltSNG;                                 //FM progressive measured stand volts no good,long,4,boolean,172,,
		int vwrPNG;                                 //FM progressive measured stand speed no good,long,4,boolean,176,,
		int vwrSNG;                                 //FM snap shot measured stand speed no good,long,4,boolean,180,,
		int xryPNG;                                 //FM progressive measured exit thickness no good,long,4,boolean,184,,
		int xrySNG;                                 //FM snap shot measured exit thickness no good,long,4,boolean,188,,
		int pyrPNG;                                 //FM progressive measured exit temperature no good,long,4,boolean,192,,
		int widPNG;                                 //FM progressive measured exit width no good,long,4,boolean,196,,
		int widSNG;                                 //FM snap shot measured exit width no good,long,4,boolean,200,,
		int dspPNG;                                 //FM progressive measured descale spray pattern no good,long,4,boolean,204,,
		int iscPNG;                                 //FM progressive measured interstand spray pattern no good,long,4,boolean,208,,
		int oilUNG;                                 //Setup and learning oil use mismatch,long,4,boolean,212,,
		int nSgdNG;                                 //The steel grade index at Learning disagrees with the FMDCLC index,long,4,boolean,216,,
		int nTrdNG;                                 //The thickness range index at Learning disagrees with the FMDCLC index,long,4,boolean,220,,
		int tsaMPF_1;                               //Cascaded looper speed correction and operator offset,long,4,%,224,,
		int tsaMPF_2;                               //Cascaded looper speed correction and operator offset,long,4,%,228,,
		int tsaMPF_3;                               //Cascaded looper speed correction and operator offset,long,4,%,232,,
		int tsaMPF_4;                               //Cascaded looper speed correction and operator offset,long,4,%,236,,
		int tsaMPF_5;                               //Cascaded looper speed correction and operator offset,long,4,%,240,,
		int tsaMPF_6;                               //Cascaded looper speed correction and operator offset,long,4,%,244,,
		int tsaMPF_7;                               //Cascaded looper speed correction and operator offset,long,4,%,248,,
		float ksiMSTLF_1;                           //Ksi steel grade factors used for this bar,float,4,mod.,252,modifer to base value (around 1),
		float ksiMSTLF_2;                           //Ksi steel grade factors used for this bar,float,4,mod.,256,,
		float ksiMSTLF_3;                           //Ksi steel grade factors used for this bar,float,4,mod.,260,,
		float ksiMSTLF_4;                           //Ksi steel grade factors used for this bar,float,4,mod.,264,,
		float ksiMSTLF_5;                           //Ksi steel grade factors used for this bar,float,4,mod.,268,,
		float ksiMSTLF_6;                           //Ksi steel grade factors used for this bar,float,4,mod.,272,,
		float ksiMSTLF_7;                           //Ksi steel grade factors used for this bar,float,4,mod.,276,,
		float ksiMLTLF_1;                           //Ksi stand factors used for this bar,float,4,mod.,280,,
		float ksiMLTLF_2;                           //Ksi stand factors used for this bar,float,4,mod.,284,,
		float ksiMLTLF_3;                           //Ksi stand factors used for this bar,float,4,mod.,288,,
		float ksiMLTLF_4;                           //Ksi stand factors used for this bar,float,4,mod.,292,,
		float ksiMLTLF_5;                           //Ksi stand factors used for this bar,float,4,mod.,296,,
		float ksiMLTLF_6;                           //Ksi stand factors used for this bar,float,4,mod.,300,,
		float ksiMLTLF_7;                           //Ksi stand factors used for this bar,float,4,mod.,304,,
		float ksiMLF_1;                             //FM progressive learned stand yield stress,float,4,MN/mm2,308,,
		float ksiMLF_2;                             //FM progressive learned stand yield stress,float,4,MN/mm2,312,,
		float ksiMLF_3;                             //FM progressive learned stand yield stress,float,4,MN/mm2,316,,
		float ksiMLF_4;                             //FM progressive learned stand yield stress,float,4,MN/mm2,320,,
		float ksiMLF_5;                             //FM progressive learned stand yield stress,float,4,MN/mm2,324,,
		float ksiMLF_6;                             //FM progressive learned stand yield stress,float,4,MN/mm2,328,,
		float ksiMLF_7;                             //FM progressive learned stand yield stress,float,4,MN/mm2,332,,
		float wrCrnLBF_1;                           //Work roll effective crown at FM Crown Learning,float,4,mm,336,,
		float wrCrnLBF_2;                           //Work roll effective crown at FM Crown Learning,float,4,mm,340,,
		float wrCrnLBF_3;                           //Work roll effective crown at FM Crown Learning,float,4,mm,344,,
		float wrCrnLBF_4;                           //Work roll effective crown at FM Crown Learning,float,4,mm,348,,
		float wrCrnLBF_5;                           //Work roll effective crown at FM Crown Learning,float,4,mm,352,,
		float wrCrnLBF_6;                           //Work roll effective crown at FM Crown Learning,float,4,mm,356,,
		float wrCrnLBF_7;                           //Work roll effective crown at FM Crown Learning,float,4,mm,360,,
		int uCrnMdl;                                //Update FM force and temperature model (long term),long,4,n/a,364,,
		float crnMPF;                               //FM progressive measured crown,float,4,boolean,368,,
		float crnMHF;                               //FM head measured crown,float,4,mm,372,,
		float crnMSF;                               //FM snap measured crown,float,4,mm,376,,
		float camberMPF;                            //FM progressive measured camber,float,4,mm,380,,
		float camberMHF;                            //FM head measured camber,float,4,mm,384,,
		float camberMSF;                            //FM snap measured camber,float,4,mm,388,,
		float symIUMHF;                             //FM head measured rhometer symmetrical flatness,float,4,I unit,392,,
		float asymIUMHF;                            //FM head measured rhometer asymmetrical flatness,float,4,I unit,396,,
		float xryDevMHF;                            //F7 xray gauge deviation - head scan,float,4,mm,400,,
		float xryDevMPF;                            //F7 xray gauge deviation - progressive scan,float,4,mm,404,,
		float xryDevMSF;                            //F7 xray gauge deviation - snap shot scan,float,4,mm,408,,
		float crnErF;                               //strip crown error measured - predicted,float,4,mm,412,,
		char slabId[16];                            //slab ID for desired PDI,char,16,string,416,,

	} MDS_FM_RPTTYPE;

	/*
	 *	(MDS)MDS_CTC_RPTTYPE --> MES
	 *	TELID: 123
	 */
	typedef struct {
		short int hdrLen;                           //VIP message length,long,4,n/a,0,500,
		short int hdrID;                            //VIP message ID,long,4,n/a,4,123,
		int hbCtr;                                  //heartbeat counter,long,4,counter,8,,
		float lenFmxCum;                            //Cumulative length at FM Exit pyro,float,4,m,12,,
		float lenRotCum;                            //Cumulative length at Rot pyro,float,4,m,16,,
		float lenCleCum;                            //Cumulative length at Coiler Entry pyro,float,4,m,20,,
		float lenTailCum;                           //Cumulative length of Strip Tail,float,4,m,24,,
		float thkFmxML_1;                           //"Measured FM Exit thickness   at model LRN, THD/RUN",float,4,mm,28,,
		float thkFmxML_2;                           //"Measured FM Exit thickness   at model LRN, THD/RUN",float,4,mm,32,,
		float tmpFmxML_1;                           //"Measured FM Exit temperature at model LRN, THD/RUN",float,4,oC,36,,
		float tmpFmxML_2;                           //"Measured FM Exit temperature at model LRN, THD/RUN",float,4,oC,40,,
		float tmpCzeML_1;                           //"Measured Control Zone Entry temperature at model LRN, THD/RUN",float,4,oC,44,,
		float tmpCzeML_2;                           //"Measured Control Zone Entry temperature at model LRN, THD/RUN",float,4,oC,48,,
		float tmpRotML_1;                           //"Measured Control Zone Exit  temperature at model LRN, THD/RUN",float,4,oC,52,,
		float tmpRotML_2;                           //"Measured Control Zone Exit  temperature at model LRN, THD/RUN",float,4,oC,56,,
		float tmpCzxML_1;                           //"""Measured"" control zone exit temperature (based on measured Cle temp) at learning",float,4,oC,60,,
		float tmpCzxML_2;                           //"""Measured"" control zone exit temperature (based on measured Cle temp) at learning",float,4,oC,64,,
		float tmpCBPML_1;                           //"Measured Coiler Entry bottom temperature at model LRN, THD/RUN",float,4,oC,68,,
		float tmpCBPML_2;                           //"Measured Coiler Entry bottom temperature at model LRN, THD/RUN",float,4,oC,72,,
		float tmpCleML_1;                           //"Measured Coiler Entry temperature at model LRN, THD/RUN",float,4,oC,76,,
		float tmpCleML_2;                           //"Measured Coiler Entry temperature at model LRN, THD/RUN",float,4,oC,80,,
		float sunFwdML_1;                           //"Feed-forward sprays units used at Learning,THD/RUN",float,4,su,84,"spray units, roughly equivalent to one top header",
		float sunFwdML_2;                           //"Feed-forward sprays units used at Learning,THD/RUN",float,4,su,88,,
		float sunFbkML_1;                           //"Feedback sprays units used at Learning,THD/RUN",float,4,su,92,,
		float sunFbkML_2;                           //"Feedback sprays units used at Learning,THD/RUN",float,4,su,96,,
		float sunActML_1;                           //"""Measured"" prays units used at Learning,THD/RUN",float,4,su,100,,
		float sunActML_2;                           //"""Measured"" prays units used at Learning,THD/RUN",float,4,su,104,,
		float sunCtcML_1;                           //"""Measured"" prays units used at Learning,THD/RUN",float,4,su,108,,
		float sunCtcML_2;                           //"""Measured"" prays units used at Learning,THD/RUN",float,4,su,112,,
		float sprOnML_1_1;                          //"Sprays on at Learning, THD/RUN, MAIN/VERN, TOP/BTM",float,4,count,116,,
		float sprOnML_1_2;                          //"Sprays on at Learning, THD/RUN, MAIN/VERN, TOP/BTM",float,4,count,120,,
		float sprOnML_1_3;                          //"Sprays on at Learning, THD/RUN, MAIN/VERN, TOP/BTM",float,4,count,124,,
		float sprOnML_1_4;                          //"Sprays on at Learning, THD/RUN, MAIN/VERN, TOP/BTM",float,4,count,128,,
		float sprOnML_2_1;                          //"Sprays on at Learning, THD/RUN, MAIN/VERN, TOP/BTM",float,4,count,132,,
		float sprOnML_2_2;                          //"Sprays on at Learning, THD/RUN, MAIN/VERN, TOP/BTM",float,4,count,136,,
		float sprOnML_2_3;                          //"Sprays on at Learning, THD/RUN, MAIN/VERN, TOP/BTM",float,4,count,140,,
		float sprOnML_2_4;                          //"Sprays on at Learning, THD/RUN, MAIN/VERN, TOP/BTM",float,4,count,144,,
		float vssFmxML_1;                           //"Measured FM Exit strip speed at model LRN, THD/RUN",float,4,m/s,148,,
		float vssFmxML_2;                           //"Measured FM Exit strip speed at model LRN, THD/RUN",float,4,m/s,152,,
		float vssCzeML_1;                           //"CONTROL ZONE ENTRY VELOCITY AT MOD FDBK, THD/RUN",float,4,m/s,156,,
		float vssCzeML_2;                           //"CONTROL ZONE ENTRY VELOCITY AT MOD FDBK, THD/RUN",float,4,m/s,160,,
		float vavCznML_1;                           //"MOD FDBK SAMPLE PRED CNTRL ZN AVG VELOC, THD/RUN",float,4,m/s,164,,
		float vavCznML_2;                           //"MOD FDBK SAMPLE PRED CNTRL ZN AVG VELOC, THD/RUN",float,4,m/s,168,,
		float vssCzxML_1;                           //"CONTROL ZONE EXIT  VELOCITY AT MOD FDBK, THD/RUN",float,4,m/s,172,,
		float vssCzxML_2;                           //"CONTROL ZONE EXIT  VELOCITY AT MOD FDBK, THD/RUN",float,4,m/s,176,,
		float vssCleML_1;                           //"Measured Coiler Entry strip speed at model LRN, THD/RUN",float,4,m/s,180,,
		float vssCleML_2;                           //"Measured Coiler Entry strip speed at model LRN, THD/RUN",float,4,m/s,184,,
		float vssAvgML_1;                           //"FDBK SAMPLE REPRED VELOC, CTRL ZN - FBK",float,4,m/s,188,,
		float vssAvgML_2;                           //"FDBK SAMPLE REPRED VELOC, CTRL ZN - FBK",float,4,m/s,192,,
		float tmpCzePL_1;                           //Repredicted Control Zone Entry temperature at Learning,float,4,oC,196,,
		float tmpCzePL_2;                           //Repredicted Control Zone Entry temperature at Learning,float,4,oC,200,,
		float tmpCzxPL_1;                           //Repredicted Control Zone Exit  temperature at Learning,float,4,oC,204,,
		float tmpCzxPL_2;                           //Repredicted Control Zone Exit  temperature at Learning,float,4,oC,208,,
		float tmpClePL_1;                           //"Repredicted Coiler Entry temperature at Learning, THD/RUN",float,4,oC,212,,
		float tmpClePL_2;                           //"Repredicted Coiler Entry temperature at Learning, THD/RUN",float,4,oC,216,,
		float terFmxL_1;                            //"Finish exit temp accum error at mdl LRN, THD/RUN",float,4,oC,220,,
		float terFmxL_2;                            //"Finish exit temp accum error at mdl LRN, THD/RUN",float,4,oC,224,,
		float terFmxCtrL_1;                         //"Fmx temperature error, measured - model",float,4,oC,228,,
		float terFmxCtrL_2;                         //"Fmx temperature error, measured - model",float,4,oC,232,,
		float terCleL_1;                            //"Coiler Entry temp error at mdl Learn,THD/RUN",float,4,oC,236,,
		float terCleL_2;                            //"Coiler Entry temp error at mdl Learn,THD/RUN",float,4,oC,240,,
		float terMdlL_1;                            //Model re-predicted temperature error (pred-meas) - LRN,float,4,oC,244,,
		float terMdlL_2;                            //Model re-predicted temperature error (pred-meas) - LRN,float,4,oC,248,,
		float terFwdL_1;                            //Forward loop temperature error (pred-target) - LRN,float,4,oC,252,,
		float terFwdL_2;                            //Forward loop temperature error (pred-target) - LRN,float,4,oC,256,,
		float terTofL_1;                            //Temperature offset error - LRN,float,4,oC,260,,
		float terTofL_2;                            //Temperature offset error - LRN,float,4,oC,264,,
		float thkLrn_1;                             //"FM Exit thickness   at model LRN, THD/RUN",float,4,mm,268,,
		float thkLrn_2;                             //"FM Exit thickness   at model LRN, THD/RUN",float,4,mm,272,,
		float sefLrn_1;                             //Model spray efficiency - LRN,float,4,n/a,276,,
		float sefLrn_2;                             //Model spray efficiency - LRN,float,4,n/a,280,,
		int permMdlLrn_1;                           //"Model Learning permissive, THD/RUN",long,4,boolean,284,,
		int permMdlLrn_2;                           //"Model Learning permissive, THD/RUN",long,4,boolean,288,,
		int permGblLrn_1;                           //"VERNIER FEEDBACK permissive, THD/RUN",long,4,boolean,292,,
		int permGblLrn_2;                           //"VERNIER FEEDBACK permissive, THD/RUN",long,4,boolean,296,,
		float sunEffML_1;                           //"""Measured"" spray efficiency used for model learning THD/RUN",float,4,n/a,300,,
		float sunEffML_2;                           //"""Measured"" spray efficiency used for model learning THD/RUN",float,4,n/a,304,,
		float tcrFbkML_1;                           //"delta temperature FBK correction at model Learning, THD/RUN",float,4,oC,308,,
		float tcrFbkML_2;                           //"delta temperature FBK correction at model Learning, THD/RUN",float,4,oC,312,,
		float sunLrn_1;                             //Spray units on at Learning (SPSFBK),float,4,n/a,316,,
		float sunLrn_2;                             //Spray units on at Learning (SPSFBK),float,4,n/a,320,,
		float sunErrML_1;                           //"Spray units error, measured - predicted - LRN",float,4,n/a,324,,
		float sunErrML_2;                           //"Spray units error, measured - predicted - LRN",float,4,n/a,328,,
		float sprOnLrn_1_1;                         //Total number of sprays at Learning based on spray status,float,4,packed,332,,
		float sprOnLrn_1_2;                         //Total number of sprays at Learning based on spray status,float,4,packed,336,,
		float sprOnLrn_1_3;                         //Total number of sprays at Learning based on spray status,float,4,packed,340,,
		float sprOnLrn_1_4;                         //Total number of sprays at Learning based on spray status,float,4,packed,344,,
		float sprOnLrn_2_1;                         //Total number of sprays at Learning based on spray status,float,4,packed,348,,
		float sprOnLrn_2_2;                         //Total number of sprays at Learning based on spray status,float,4,packed,352,,
		float sprOnLrn_2_3;                         //Total number of sprays at Learning based on spray status,float,4,packed,356,,
		float sprOnLrn_2_4;                         //Total number of sprays at Learning based on spray status,float,4,packed,360,,
		int ctcLrnOk_1;                             //Learning Update accomplished,long,4,boolean,364,,
		int ctcLrnOk_2;                             //Learning Update accomplished,long,4,boolean,368,,
		int impossCtlLrn_1;                         //Temp cold w/o sprays - impossible control condition - LRN,long,4,boolean,372,,
		int impossCtlLrn_2;                         //Temp cold w/o sprays - impossible control condition - LRN,long,4,boolean,376,,
		int badTmpCleLrn_1;                         //Measured Cle temperature unreasonable - LRN,long,4,boolean,380,,
		int badTmpCleLrn_2;                         //Measured Cle temperature unreasonable - LRN,long,4,boolean,384,,
		int badVssCznLrn_1;                         //Avg meas Control Zone strip speed is unreasonable - LRN,long,4,boolean,388,,
		int badVssCznLrn_2;                         //Avg meas Control Zone strip speed is unreasonable - LRN,long,4,boolean,392,,
		int mdlGetErr_1;                            //CTR GET FAILURE AT FEEDBACK,long,4,boolean,396,,
		int mdlGetErr_2;                            //CTR GET FAILURE AT FEEDBACK,long,4,boolean,400,,
		int badDataLrn_1;                           //Bad measured data at Learning,long,4,boolean,404,,
		int badDataLrn_2;                           //Bad measured data at Learning,long,4,boolean,408,,
		int impossLrn_1;                            //IMPOSSIBLE CONTROL CONDITION AT Learning,long,4,boolean,412,,
		int impossLrn_2;                            //IMPOSSIBLE CONTROL CONDITION AT Learning,long,4,boolean,416,,
		int cobbleLrn_1;                            //Cobble flag at Learning,long,4,boolean,420,,
		int cobbleLrn_2;                            //Cobble flag at Learning,long,4,boolean,424,,
		int aclErrLrn_1;                            //Speed-up interference flag at Learning,long,4,boolean,428,,
		int aclErrLrn_2;                            //Speed-up interference flag at Learning,long,4,boolean,432,,
		int insuffSprLrn_1;                         //Insufficent sprays flag at Learning,long,4,boolean,436,,
		int insuffSprLrn_2;                         //Insufficent sprays flag at Learning,long,4,boolean,440,,
		int vssErrLrn_1;                            //Speed error flag at Learning,long,4,boolean,444,,
		int vssErrLrn_2;                            //Speed error flag at Learning,long,4,boolean,448,,
		int loopRot_1;                              //Looping detected on ROT,long,4,boolean,452,,
		int loopRot_2;                              //Looping detected on ROT,long,4,boolean,456,,
		char timLrn_1[12];                          //Time of CTC THD/RUN Learning,char,12,time,460,"""12:34:56"" format",
		char timLrn_2[12];                          //Time of CTC THD/RUN Learning,char,12,time,472,"""12:34:56"" format",
		char slabId[16];                            //slab ID for desired PDI,char,16,n/a,484,,

	} MDS_CTC_RPTTYPE;


	/*
	 *	(MDS)MDS_ALIVETYPE --> MES
	 *	TELID: 101
	 */
	typedef struct {
		short int hdrLen;                           //VIP message length,long,4,n/a,0,12,
		short int hdrID;                            //VIP message ID,long,4,n/a,4,101,
		int hbCtr;                                  //heartbeat counter,long,4,n/a,8,,

	} MDS_ALIVETYPE;

}
#pragma  pack()

