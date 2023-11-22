#pragma once

#include "universal_toolbox.hpp"
#pragma pack(1)

/// <summary>
///  只接受数据；
///  只给L1发送心跳，除此外，都不给L1下发任何设定
/// </summary>
namespace  livip_struct
{

	/// <summary>
	/// 通用电文头 4 bytes
	/// </summary>
	struct VipNetHeader
	{
		short int hdrLen;
		short int hdrID;

		/// <summary>
		/// 大端转小端,不会改变输入的原数据字节序
		/// </summary>
		/// <param name="data"></param>
		inline void ConvertBigEndian2LittleEndian(const void* data)
		{
			const uint8_t* bytes = static_cast<const uint8_t*>(data);

			// 手动指定每个成员的偏移量，并进行赋值和字节序转换
			std::memcpy(&this->hdrLen, bytes + 0, sizeof(this->hdrLen));
			this->hdrLen = uni_box::net::ConvertBigEndianToLittle<short int>(&this->hdrLen);

			std::memcpy(&this->hdrID, bytes + FIELD_OFFSET(VipNetHeader, hdrID), sizeof(this->hdrID));
			this->hdrID = uni_box::net::ConvertBigEndianToLittle<short int>(&this->hdrID);
		}


		/// <summary>
		/// 根据指定字节序，转换
		/// </summary>
		/// <param name="endian">0:小端，1:大端字节序</param>
		inline void convert2OrderBytes(int endian = 0)
		{

			// 小端
			if (endian == 0)
			{
				uni_box::net::to_little_endian(this->hdrLen);
				uni_box::net::to_little_endian(this->hdrID);
			}
			else
			{
				uni_box::net::to_big_endian(this->hdrLen);
				uni_box::net::to_big_endian(this->hdrID);
			}
		}

	};

	namespace fce
	{
		/// <summary>
		/// id:1801
		/// L1_FCE_CONSUMABLES - L1FCE Consumables (once per minute)
		/// </summary>
		struct L1_FCE_CONSUMABLES
		{
			VipNetHeader header;
			int   COMM_DATA;
			int	SPARE1;
			float BLAST_FURNACE_GAS;
			float CONVERTER_GAS;
			float COKE_OVEN_GAS;
			float NATURAL_GAS;
			float OXYGEN;
			float NITROGEN;
			float COMPRESSED_AIR;
			float STEAM;
			float INDUSTR_SUPPL_WATER;
			float TAP_WATER;
			float SPARE2;
			float SPARE3;

			inline void convert2OrderBytes(int endian = 0)
			{
				if (endian == 0)
				{
					uni_box::net::to_little_endian(this->header.hdrLen);
					uni_box::net::to_little_endian(this->header.hdrID);
					uni_box::net::to_little_endian(this->COMM_DATA);
					uni_box::net::to_little_endian(this->SPARE1);
					uni_box::net::to_little_endian(this->BLAST_FURNACE_GAS);
					uni_box::net::to_little_endian(this->CONVERTER_GAS);
					uni_box::net::to_little_endian(this->COKE_OVEN_GAS);
					uni_box::net::to_little_endian(this->NATURAL_GAS);
					uni_box::net::to_little_endian(this->NATURAL_GAS);
					uni_box::net::to_little_endian(this->OXYGEN);
					uni_box::net::to_little_endian(this->NITROGEN);
					uni_box::net::to_little_endian(this->COMPRESSED_AIR);
					uni_box::net::to_little_endian(this->STEAM);
					uni_box::net::to_little_endian(this->INDUSTR_SUPPL_WATER);
					uni_box::net::to_little_endian(this->TAP_WATER);
					uni_box::net::to_little_endian(this->SPARE2);
					uni_box::net::to_little_endian(this->SPARE3);
				}
				else
				{
					uni_box::net::to_big_endian(this->header.hdrLen);
					uni_box::net::to_big_endian(this->header.hdrID);
					uni_box::net::to_big_endian(this->COMM_DATA);
					uni_box::net::to_big_endian(this->SPARE1);
					uni_box::net::to_big_endian(this->BLAST_FURNACE_GAS);
					uni_box::net::to_big_endian(this->CONVERTER_GAS);
					uni_box::net::to_big_endian(this->COKE_OVEN_GAS);
					uni_box::net::to_big_endian(this->NATURAL_GAS);
					uni_box::net::to_big_endian(this->NATURAL_GAS);
					uni_box::net::to_big_endian(this->OXYGEN);
					uni_box::net::to_big_endian(this->NITROGEN);
					uni_box::net::to_big_endian(this->COMPRESSED_AIR);
					uni_box::net::to_big_endian(this->STEAM);
					uni_box::net::to_big_endian(this->INDUSTR_SUPPL_WATER);
					uni_box::net::to_big_endian(this->TAP_WATER);
					uni_box::net::to_big_endian(this->SPARE2);
					uni_box::net::to_big_endian(this->SPARE3);
				}
			}
		};

		/// <summary>
		/// id:1802
		/// L2_ALIVE_FCE - L2 Alive (response to L1_FCE_CONSUMABLES)
		/// </summary>
		struct L2_ALIVE_FCE
		{
			VipNetHeader header;
			int   COMM_DATA;
			int	SPARE1;
			float	SPARE2;

			/// <summary>
			/// 将数据转为大端字节序
			/// 注意:需要将
			/// </summary>
			inline void ConvertLittleEndian2BigEndian()
			{
				if (uni_box::net::getCurHostEndian() == uni_box::host_endian::BigEndian)
					return;
				uni_box::net::to_big_endian(this->header.hdrID);
				uni_box::net::to_big_endian(this->header.hdrLen);
				uni_box::net::to_big_endian(this->COMM_DATA);
				uni_box::net::to_big_endian(this->SPARE1);
				uni_box::net::to_big_endian(this->SPARE2);
			}
		};
	}

	namespace rm1
	{
		/// <summary>
		/// 接收RM1传来心跳
		/// </summary>
		struct L1_PS21_ALIVE
		{
			VipNetHeader header;
			int hbCtr; //Counter incremented by one for each message sent. Range 1…999999
			int dummy;
		};

		/// <summary>
		/// 心跳，发给RM1
		/// </summary>
		struct L2_ALIVE_PS21
		{
			VipNetHeader header;
			int hbCtr; //Counter incremented by one for each message sent. Range 1…999999

			/// <summary>
			/// 将数据转为大端字节序
			/// 注意:需要将
			/// </summary>
			void ConvertLittleEndian2BigEndian()
			{
				if (uni_box::net::getCurHostEndian() == uni_box::host_endian::BigEndian)
					return;
				uni_box::net::to_big_endian(this->header.hdrID);
				uni_box::net::to_big_endian(this->header.hdrLen);
				uni_box::net::to_big_endian(this->hbCtr);
			}
		};

		/// <summary>
		/// L1 RM1发来模轧信号
		/// 模轧分两类：来自L2画面点击的请求模轧；来自L1请求的模轧
		/// </summary>
		struct START_GHOST_ROLLING
		{
			VipNetHeader header;
			int dummy1;
			int dummy2;

			/// <summary>
			/// 根据指定字节序，转换
			/// </summary>
			/// <param name="endian">0:小端，1:大端字节序</param>
			inline void convert2OrderBytes(int endian = 0)
			{

				// 小端
				if (endian == 0)
				{
					uni_box::net::to_little_endian(this->header.hdrLen);
					uni_box::net::to_little_endian(this->header.hdrID);
					uni_box::net::to_little_endian(this->dummy1);
					uni_box::net::to_little_endian(this->dummy2);
				}
				else if (endian == 1)
				{
					uni_box::net::to_big_endian(this->header.hdrLen);
					uni_box::net::to_big_endian(this->header.hdrID);
					uni_box::net::to_big_endian(this->dummy1);
					uni_box::net::to_big_endian(this->dummy2);
				}
			}
		};


		/// <summary>
		/// RM1发来换新辊信息
		/// </summary>
		struct RM1_ROLL_CHANGE
		{
			VipNetHeader header;
			char ER_OS_ROLL_ID[8];			   //Roll  ID of current operator side edger roll after roll change
			float ER_OS_ROLL_DIAM;			   //mm: Roll  diameter of current operator side edger roll after roll change mm
			char ER_DS_ROLL_ID[8];			   //Roll  ID of current drive side edger roll after roll change
			float ER_DS_ROLL_DIAM;			   //Roll  diameter of current drive side edger roll after roll change
			char WR_TOP_ROLL_ID[8];		   //Roll  ID of current top work roll after roll change
			float WR_TOP_ROLL_DIAM;			   //Roll  diameter of current top work roll after roll change
			char WR_BTM_ROLL_ID[8];		   //Roll  ID of current bottom work roll after roll change
			float WR_BTM_ROLL_DIAM;			   //Roll  diameter of current bottom work roll after roll change
			char ROLL_CHANGE_TIME[20];		   //Roll change time(YYYY - MM - DD HH : MI:SS)

			inline void convert2OrderBytes(int endian = 0)
			{
				if (endian == 0)
				{
					uni_box::net::to_little_endian(this->header.hdrLen);
					uni_box::net::to_little_endian(this->header.hdrID);
					uni_box::net::to_little_endian(this->ER_OS_ROLL_DIAM);
					uni_box::net::to_little_endian(this->ER_DS_ROLL_DIAM);
					uni_box::net::to_little_endian(this->WR_TOP_ROLL_DIAM);
					uni_box::net::to_little_endian(this->WR_BTM_ROLL_DIAM);
				}
				else
				{
					uni_box::net::to_big_endian(this->header.hdrLen);
					uni_box::net::to_big_endian(this->header.hdrID);
					uni_box::net::to_big_endian(this->ER_OS_ROLL_DIAM);
					uni_box::net::to_big_endian(this->ER_DS_ROLL_DIAM);
					uni_box::net::to_big_endian(this->WR_TOP_ROLL_DIAM);
					uni_box::net::to_big_endian(this->WR_BTM_ROLL_DIAM);
				}
			}
		};


		struct RM1_ROLL_WEAR
		{
			VipNetHeader header;
			char ER_OS_ROLL_ID[8];			   // Roll ID of current operator side edger roll
			char ER_DS_ROLL_ID[8];			   //Roll ID of current drive side edger roll
			float ER_ACCUM_WEIGHT;			   //kg: Accumulated rolled weight since last roll change(edger rolls)
			float ER_ACCUM_LENGTH;			   //m: Accumulated rolled length since last roll change(edger rolls)
			char WR_TOP_ROLL_ID[8];		   //Roll ID of current top work roll
			char WR_BTM_ROLL_ID[8];		   //Roll ID of current bottom work roll
			float WR_ACCUM_WEIGHT;			   //Accumulated rolled weight since last roll change(work rolls)
			float WR_ACCUM_LENGTH;			   //Accumulated rolled length since last roll change(work rolls)

			inline void convert2OrderBytes(int endian = 0)
			{
				if (endian == 0)
				{
					uni_box::net::to_little_endian(this->header.hdrLen);
					uni_box::net::to_little_endian(this->header.hdrID);
					uni_box::net::to_little_endian(this->ER_ACCUM_WEIGHT);
					uni_box::net::to_little_endian(this->ER_ACCUM_LENGTH);
					uni_box::net::to_little_endian(this->WR_ACCUM_WEIGHT);
					uni_box::net::to_little_endian(this->WR_ACCUM_LENGTH);
				}
				else
				{
					uni_box::net::to_big_endian(this->header.hdrLen);
					uni_box::net::to_big_endian(this->header.hdrID);
					uni_box::net::to_big_endian(this->ER_ACCUM_WEIGHT);
					uni_box::net::to_big_endian(this->ER_ACCUM_LENGTH);
					uni_box::net::to_big_endian(this->WR_ACCUM_WEIGHT);
					uni_box::net::to_big_endian(this->WR_ACCUM_LENGTH);
				}

			}
		};


		struct FCE_DISCHARGE
		{
			VipNetHeader header;
			char MATERIAL_ID[12]; //TODO: 原文档数据不准确
			char FCE_DISCH_TIME[20];
			int32_t FCE_DISCH_FCENO;
			float FCE_DISCH_TEMP;


			/// <summary>
			/// 根据指定字节序，转换
			/// </summary>
			/// <param name="endian">0:小端，1:大端字节序</param>
			inline void convert2OrderBytes(int endian = 0)
			{

				// 小端
				if (endian == 0)
				{
					uni_box::net::to_little_endian(this->header.hdrLen);
					uni_box::net::to_little_endian(this->header.hdrID);
					uni_box::net::to_little_endian(this->FCE_DISCH_FCENO);
					uni_box::net::to_little_endian(this->FCE_DISCH_TEMP);
				}
				else
				{
					uni_box::net::to_big_endian(this->header.hdrLen);
					uni_box::net::to_big_endian(this->header.hdrID);
					uni_box::net::to_big_endian(this->FCE_DISCH_FCENO);
					uni_box::net::to_big_endian(this->FCE_DISCH_TEMP);
				}
			}
		};

	}

	namespace rm2
	{
		/// <summary>
		/// 接收RM2传来心跳
		/// </summary>
		struct L1_PS31_ALIVE
		{
			VipNetHeader header;
			int hbCtr; //Counter incremented by one for each message sent. Range 1…999999
			int dummy;
		};

		/// <summary>
		/// 心跳，发给RM2
		/// </summary>
		struct L2_ALIVE_PS31
		{
			VipNetHeader header;
			int hbCtr; //Counter incremented by one for each message sent. Range 1…999999
			int dummy;

			void ConvertLittleEndian2BigEndian()
			{
				if (uni_box::net::getCurHostEndian() == uni_box::host_endian::BigEndian)
					return;
				uni_box::net::to_big_endian(this->header.hdrID);
				uni_box::net::to_big_endian(this->header.hdrLen);
				uni_box::net::to_big_endian(this->hbCtr);
				uni_box::net::to_big_endian(this->dummy);
			}
		};

		/// <summary>
		/// RM2发来换新辊信息
		/// </summary>
		struct RM2_ROLL_CHANGE
		{
			VipNetHeader header;
			char ER_OS_ROLL_ID[8];			   //Roll  ID of current operator side edger roll after roll change
			float ER_OS_ROLL_DIAM;			   //Roll  diameter of current operator side edger roll after roll change
			char ER_DS_ROLL_ID[8];			   //Roll  ID of current drive side edger roll after roll change
			float ER_DS_ROLL_DIAM;			   //Roll  diameter of current drive side edger roll after roll change
			char WR_TOP_ROLL_ID[8];		   //Roll  ID of current top work roll after roll change
			float WR_TOP_ROLL_DIAM;			   //Roll  diameter of current top work roll after roll change
			char WR_BTM_ROLL_ID[8];		   //Roll  ID of current bottom work roll after roll change
			float WR_BTM_ROLL_DIAM;			   //Roll  diameter of current bottom work roll after roll change
			char BR_TOP_ROLL_ID[8];
			float BR_TOP_ROLL_DIAM;
			char BR_BTM_ROLL_ID[8];
			float BR_BTM_ROLL_DIAM;
			char ROLL_CHANGE_TIME[20];		   //Roll change time(YYYY - MM - DD HH : MI:SS)


			inline void convert2OrderBytes(int endian = 0)
			{
				if (endian == 0)
				{
					uni_box::net::to_little_endian(this->header.hdrLen);
					uni_box::net::to_little_endian(this->header.hdrID);
					uni_box::net::to_little_endian(this->ER_OS_ROLL_DIAM);
					uni_box::net::to_little_endian(this->ER_DS_ROLL_DIAM);
					uni_box::net::to_little_endian(this->WR_TOP_ROLL_DIAM);
					uni_box::net::to_little_endian(this->WR_BTM_ROLL_DIAM);
					uni_box::net::to_little_endian(this->BR_TOP_ROLL_DIAM);
					uni_box::net::to_little_endian(this->BR_BTM_ROLL_DIAM);
				}
				else
				{
					uni_box::net::to_big_endian(this->header.hdrLen);
					uni_box::net::to_big_endian(this->header.hdrID);
					uni_box::net::to_big_endian(this->ER_OS_ROLL_DIAM);
					uni_box::net::to_big_endian(this->ER_DS_ROLL_DIAM);
					uni_box::net::to_big_endian(this->WR_TOP_ROLL_DIAM);
					uni_box::net::to_big_endian(this->WR_BTM_ROLL_DIAM);
					uni_box::net::to_big_endian(this->BR_TOP_ROLL_DIAM);
					uni_box::net::to_big_endian(this->BR_BTM_ROLL_DIAM);
				}
			}

		};


		struct RM2_ROLL_WEAR
		{
			VipNetHeader header;
			char ER_OS_ROLL_ID[8];			   // Roll ID of current operator side edger roll
			char ER_DS_ROLL_ID[8];			   //Roll ID of current drive side edger roll
			float ER_ACCUM_WEIGHT;			   //Accumulated rolled weight since last roll change(edger rolls)
			float ER_ACCUM_LENGTH;			   //Accumulated rolled length since last roll change(edger rolls)
			char WR_TOP_ROLL_ID[8];		   //Roll ID of current top work roll
			char WR_BTM_ROLL_ID[8];		   //Roll ID of current bottom work roll
			float WR_ACCUM_WEIGHT;			   //Accumulated rolled weight since last roll change(work rolls)
			float WR_ACCUM_LENGTH;			   //Accumulated rolled length since last roll change(work rolls)
			char BR_TOP_ROLL_ID[8];
			char BR_BTM_ROLL_ID[8];
			float BR_ACCUM_WEIGHT;
			float BR_ACCUM_LENGTH;

			inline void convert2OrderBytes(int endian = 0)
			{
				if (endian == 0)
				{
					uni_box::net::to_little_endian(this->header.hdrLen);
					uni_box::net::to_little_endian(this->header.hdrID);
					uni_box::net::to_little_endian(this->ER_ACCUM_WEIGHT);
					uni_box::net::to_little_endian(this->ER_ACCUM_LENGTH);
					uni_box::net::to_little_endian(this->WR_ACCUM_WEIGHT);
					uni_box::net::to_little_endian(this->WR_ACCUM_LENGTH);
					uni_box::net::to_little_endian(this->BR_ACCUM_WEIGHT);
					uni_box::net::to_little_endian(this->BR_ACCUM_LENGTH);
				}
				else
				{
					uni_box::net::to_big_endian(this->header.hdrLen);
					uni_box::net::to_big_endian(this->header.hdrID);
					uni_box::net::to_big_endian(this->ER_ACCUM_WEIGHT);
					uni_box::net::to_big_endian(this->ER_ACCUM_LENGTH);
					uni_box::net::to_big_endian(this->WR_ACCUM_WEIGHT);
					uni_box::net::to_big_endian(this->WR_ACCUM_LENGTH);
					uni_box::net::to_big_endian(this->BR_ACCUM_WEIGHT);
					uni_box::net::to_big_endian(this->BR_ACCUM_LENGTH);
				}

			}
		};


		/// <summary>
		/// 轧线停止时间
		/// </summary>
		struct MILL_STOP
		{
			VipNetHeader header;
			//char START_TIME[20]; //Time when the mill stop occured (YYYY-MM-DD HH:MM:SS)
			//char END_TIME[4]; // Time when mill was restarted (YYYY-MM-DD HH:MM:SS)
			char st$en$timee[24];

			inline void convert2OrderBytes(int endian = 0)
			{
				if (endian == 0)
				{
					uni_box::net::to_little_endian(this->header.hdrLen);
					uni_box::net::to_little_endian(this->header.hdrID);
				}
				else
				{
					uni_box::net::to_big_endian(this->header.hdrLen);
					uni_box::net::to_big_endian(this->header.hdrID);
				}

			}
		};

	}

	namespace fm
	{
		struct L2_ALARMS_PS42
		{
			VipNetHeader header;
			int L2_ALARM_FLAGS; //Packed booleans, each bit one specific alarm for 800xA alarm list. Alarm texts to be set in a NLS_Resource file for MES alarm texts only
			int dummy;
		};

		struct L2_ALIVE_PS42
		{
			VipNetHeader header;
			int hbCtr; //Counter incremented by one for each message sent. Range 1…999999
			int dummy;
			void ConvertLittleEndian2BigEndian()
			{
				if (uni_box::net::getCurHostEndian() == uni_box::host_endian::BigEndian)
					return;
				uni_box::net::to_big_endian(this->header.hdrID);
				uni_box::net::to_big_endian(this->header.hdrLen);
				uni_box::net::to_big_endian(this->hbCtr);
				uni_box::net::to_big_endian(this->dummy);
			}
		};

		struct FM_ROLL_WEAR
		{
			VipNetHeader header;
			int STAND_ID;
			char WR_TOP_ROLL_ID[8];		   //Roll ID of current top work roll
			char WR_BTM_ROLL_ID[8];		   //Roll ID of current bottom work roll
			float WR_ACCUM_WEIGHT;			   //kg
			float WR_ACCUM_LENGTH;			   //m
			char BR_TOP_ROLL_ID[8];
			char BR_BTM_ROLL_ID[8];
			float BR_ACCUM_WEIGHT;
			float BR_ACCUM_LENGTH;

			inline void convert2OrderBytes(int endian = 0)
			{
				if (endian == 0)
				{
					uni_box::net::to_little_endian(this->header.hdrLen);
					uni_box::net::to_little_endian(this->header.hdrID);
					uni_box::net::to_little_endian(this->STAND_ID);
					uni_box::net::to_little_endian(this->WR_ACCUM_WEIGHT);
					uni_box::net::to_little_endian(this->WR_ACCUM_LENGTH);
					uni_box::net::to_little_endian(this->BR_ACCUM_WEIGHT);
					uni_box::net::to_little_endian(this->BR_ACCUM_LENGTH);
				}
				else
				{
					uni_box::net::to_big_endian(this->header.hdrLen);
					uni_box::net::to_big_endian(this->STAND_ID);
					uni_box::net::to_big_endian(this->WR_ACCUM_WEIGHT);
					uni_box::net::to_big_endian(this->WR_ACCUM_LENGTH);
					uni_box::net::to_big_endian(this->BR_ACCUM_WEIGHT);
					uni_box::net::to_big_endian(this->BR_ACCUM_LENGTH);
				}

			}
		};

		struct FM_ROLL_CHANGE
		{
			VipNetHeader header;
			char WR_TOP_ROLL_ID[8];		   //Roll  ID of current top work roll after roll change
			float WR_TOP_ROLL_DIAM;			   //Roll  diameter of current top work roll after roll change
			char WR_BTM_ROLL_ID[8];		   //Roll  ID of current bottom work roll after roll change
			float WR_BTM_ROLL_DIAM;			   //Roll  diameter of current bottom work roll after roll change
			char BR_TOP_ROLL_ID[8];			   //Roll  ID of current operator side edger roll after roll change
			float BR_TOP_ROLL_DIAM;			   //mm: Roll  diameter of current operator side edger roll after roll change mm
			char BR_BTM_ROLL_ID[8];			   //Roll  ID of current drive side edger roll after roll change
			float BR_BTM_ROLL_DIAM;			   //Roll  diameter of current drive side edger roll after roll change
			char ROLL_CHANGE_TIME[20];		   //Roll change time(YYYY - MM - DD HH : MI:SS)

			inline void convert2OrderBytes(int endian = 0)
			{
				if (endian == 0)
				{
					uni_box::net::to_little_endian(this->header.hdrLen);
					uni_box::net::to_little_endian(this->header.hdrID);
					uni_box::net::to_little_endian(this->WR_TOP_ROLL_DIAM);
					uni_box::net::to_little_endian(this->WR_BTM_ROLL_DIAM);
					uni_box::net::to_little_endian(this->BR_TOP_ROLL_DIAM);
					uni_box::net::to_little_endian(this->BR_BTM_ROLL_DIAM);
				}
				else
				{
					uni_box::net::to_big_endian(this->header.hdrLen);
					uni_box::net::to_big_endian(this->header.hdrID);
					uni_box::net::to_big_endian(this->WR_TOP_ROLL_DIAM);
					uni_box::net::to_big_endian(this->WR_BTM_ROLL_DIAM);
					uni_box::net::to_big_endian(this->BR_TOP_ROLL_DIAM);
					uni_box::net::to_big_endian(this->BR_BTM_ROLL_DIAM);
				}
			}

		};
	}

	namespace dc
	{
		struct L2_ALIVE_PS67
		{
			VipNetHeader header;
			int hbCtr; //Counter incremented by one for each message sent. Range 1…999999
			int dummy;

			void ConvertLittleEndian2BigEndian()
			{
				if (uni_box::net::getCurHostEndian() == uni_box::host_endian::BigEndian)
					return;
				uni_box::net::to_big_endian(this->header.hdrID);
				uni_box::net::to_big_endian(this->header.hdrLen);
				uni_box::net::to_big_endian(this->hbCtr);
				uni_box::net::to_big_endian(this->dummy);
			}
		};
	}
}

#pragma  pack()
