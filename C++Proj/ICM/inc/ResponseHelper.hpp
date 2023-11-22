#pragma once

#include "ActualResponseFlyw.h"
#include "CrewMgtHelper.hpp"

class ResponseHelper
{
public:

	/// <summary>
	/// 将propData指定属性值存入ActualResponse中。班组自动根据当前时间判断
	/// </summary>
	/// <param name="pdi_id"></param>
	/// <param name="equipId"></param>
	/// <param name="propData"></param>
	inline static void SaveActualResponse(shared_define::ID_TYPE pdi_id, int equipId, shared_define::ComInfo propData)
	{
		bool newResp = false;
		std::string propName;
		int passNo;
		try
		{
			if (propData._tag.length() == 0)
			{
				throw std::invalid_argument(fmt::format("SaveActualResponse method failed because variable '{0}' had an empty Tag!", propData.name_));
			}

			// Skip this object
			if (propData._tag[0] == '$')
				return;

			//Tag = PropertyName#PassNo
			if (propData._tag.find("#") != std::string::npos)
			{
				int idx = propData._tag.find("#");
				if (idx != std::string::npos)
				{
					propName = propData._tag.substr(0, idx);
					passNo = std::stoi(propData._tag.substr(idx + 1));
				}
			}
			else
			{
				propName = propData._tag;
				passNo = 0;
			}


			//得到属性表id
			auto propId = ActualResponseFlyw::CachePropNameId()[propName];

			// Insert/Update the properties of the ActualResponse
			ActualResponseFlyw actResp(pdi_id, equipId, propId, passNo);
			actResp.setVal(propData._value);
			actResp.Save();
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("Failed to save the ActualResponse for Material {0}, Property: {1}, reason:{2}", pdi_id, propData._tag, e.what()));
		}
	}

};
