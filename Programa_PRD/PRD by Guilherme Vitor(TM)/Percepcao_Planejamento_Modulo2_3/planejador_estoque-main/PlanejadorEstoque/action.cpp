#include "action.h"
namespace planners {
	//-------------------------------------------------------------------------------------
	// action
	//-------------------------------------------------------------------------------------
	action& action::setadd(const std::vector<std::string>& item)
	{
		for (std::vector<std::string>::const_iterator it = item.begin(); it != item.end(); it++)
		{
			addlst.set(*it);
			dellst.set("!" + *it);
		}
		return *this;
	};
	//-------------------------------------------------------------------------------------
	action& action::setdelete(const std::vector<std::string>& item)
	{
		for (std::vector<std::string>::const_iterator it = item.begin(); it != item.end(); it++)
		{
			addlst.set("!" + *it);
			dellst.set(*it);
		}
		return *this;
	};
	//-------------------------------------------------------------------------------------
}