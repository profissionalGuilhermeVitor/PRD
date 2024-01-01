#include "problem.h"
namespace planners {
	//-------------------------------------------------------------------------------------
	// problem
	//-------------------------------------------------------------------------------------
	problem::problem(varlist& vlist) : init(vlist), goal(vlist), relevant(vlist), reversible(vlist)
	{
		this->vlist = &vlist;
		radirty = false;
		reldirty = false;
		addrelev = false;
	}
	//-------------------------------------------------------------------------------------
	void problem::addaction(const action& act)
	{
		//if (!name.empty())
		//{
		//auto it = actions.find(name);
		//if (it==actions.end())
		//{
		if (addrelev)
		{
			if (reldirty) updaterelevant();
			if (!(((act.getadd() & relevant) & (~reversible)) & (~getgoal())).isempty())
				return;
		}
		actions.push_back(act);
		radirty = true;
		//}
		//}
	}
	//-------------------------------------------------------------------------------------
	void problem::setinit(const std::vector<std::string>& vars)
	{
		init = varset(*vlist);
		init.set(vars);
		init.sanitize();
		reldirty = true;
	}
	//-------------------------------------------------------------------------------------
	void problem::setgoal(const std::vector<std::string>& vars)
	{
		goal = varset(*vlist);
		goal.set(vars);
		reldirty = true;
	}
	//-------------------------------------------------------------------------------------
	const std::vector<action>& problem::getrelevantactions()
	{
		if (radirty) updateraction();
		return raction;
	}
	//-------------------------------------------------------------------------------------
	void problem::updaterelevant()
	{
		auto vlvec = vlist->getvector();
		relevant = varset(*vlist);
		reversible = varset(*vlist);
		for (auto itrel : vlvec)
		{
			if (itrel[0] != '!' && (getgoal().isset(itrel) || getgoal().isset('!' + itrel)))
			{
				relevant.set(itrel);
				relevant.set('!' + itrel);
			}
		}
		for (auto it : actions)
		{
			reversible |= it.getdelete();
		}

		reldirty = false;
	}
	//-------------------------------------------------------------------------------------
	void problem::updateraction()
	{
		raction.clear();
		std::vector<varset> cpre, cdel;
		std::vector<int> cfac;
		for (int i = 1; i <= vlist->size(); i++)
		{
			if (!getgoal().isset(i)) continue;
			varset cp(*vlist), cd(*vlist);
			cp = (~reversible);
			cd = (~reversible);
			bool hasfact = false;
			for (auto& it : actions)
			{
				if (it.getadd().isset(i))
				{
					cp &= it.getpreconditions();
					cd &= it.getdelete();
					hasfact = true;
				}
			}
			if (!hasfact) continue;
			cpre.push_back(cp);
			cdel.push_back(cd);
			cfac.push_back(i);
		}
		for (auto it : actions)
		{
			if ((((it.getadd() & relevant) & (~reversible)) & (~getgoal())).isempty())
			{
				bool blockgoal = false;
				for (std::size_t i = 0; i < cpre.size(); i++)
				{
					if (it.getadd().isset(cfac[i])) continue; // suporta o fato objetivo
					if (!(it.getdelete()&cpre[i]).isempty() && !(it.getpreconditions()&cdel[i]).isempty())
					{
						blockgoal = true;
						break;
					}
				}
				if (!blockgoal) raction.push_back({ it });
			}
		}
		radirty = false;
	}
	//-------------------------------------------------------------------------------------
}