#pragma once
#include "messagedef.h"
#include "l1vip_sstruct.h"

namespace msg
{
	class L1VipMessage :public Message
	{
	public:
		explicit L1VipMessage() = default;
		virtual ~L1VipMessage() = default;

	private:
		inline virtual void ParseMessage() override {};

	public:
		inline virtual  void  HandleL1VipData() {};
		inline void initDatas(void* data) {
			try
			{
				if (!data)
				{
					throw std::logic_error("data of receive is nullptr in L1VipMessage(data)~");
				}


				livip_struct::VipNetHeader header;
				header.ConvertBigEndian2LittleEndian(data);

				m_len = header.hdrLen;
				m_id = header.hdrID;

				if (header.hdrLen > shared_define::MAX_BUFFER_SIZE)
				{
					throw std::logic_error("data of receive is too long than shared_define::MAX_BUFFER_SIZE~");
				}
				memcpy(m_buffer, data, m_len);
			}
			catch (...)
			{
				throw  "data of parsing is error in initDatas()";
			}
		}

	};
}
