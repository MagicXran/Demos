#include "ERPOrderStrategyFactory.h"

std::shared_ptr<ERPStrategy> ERPOrderStrategyFactory::createEPRConcreteStrategy()
{
	return std::make_shared<ERPOrderConcreteStrategy>();
}
