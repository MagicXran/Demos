#pragma once
#include "project_shared.h"

class StateUtility
{
public:

	/// <summary>
	/// ×´Ì¬ÇÐ»»
	/// </summary>
	/// <param name="instate"></param>
	/// <returns></returns>
	inline static bool StateChange(std::string& stateName, int& instate)
	{
		if (stateName == shared_define::OrderStateTypes::OrderIsDraft)
		{
			stateName = shared_define::OrderStateTypes::OrderIsReleased;
			instate = (int)shared_define::OrderStatesEnum::OrderIsReleased;
			return true;
		}
		if (stateName == shared_define::OrderStateTypes::OrderIsReleased)
		{
			//instate = (int)shared_define::OrderStateTypes::OrderIsReleased + 1;
			return false;
		}
		if (stateName == shared_define::OrderStateTypes::OrderIsDispatched)
		{
			return false;
		}
		if (stateName == shared_define::OrderStateTypes::OrderInProduction)
		{
			//instate = (int)shared_define::OrderStateTypes::OrderInProduction + 1;
			return false;
		}
		if (stateName == shared_define::OrderStateTypes::OrderIsFinished)
		{
			stateName = shared_define::OrderStateTypes::OrderIsFinished;
			instate = (int)shared_define::OrderStatesEnum::OrderIsFinished;
			return true;
		}
		if (stateName == shared_define::OrderStateTypes::OrderIsStopped)
		{
			return false;
		}
		else
		{
			throw std::invalid_argument("error state");
		}
	}

};
