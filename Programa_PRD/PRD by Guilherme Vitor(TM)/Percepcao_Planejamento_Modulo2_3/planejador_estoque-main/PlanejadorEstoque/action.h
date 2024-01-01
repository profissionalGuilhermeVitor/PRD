#ifndef __ACTION__H__
#define __ACTION__H__
#include "varset.h"
#include <string>
namespace planners {
	//-------------------------------------------------------------------------------------
	class action
	{
	protected:
		varset precond, addlst, dellst;
		std::string name;
	public:
		explicit action(std::string n, varlist& vlist) : name(n), precond(vlist), addlst(vlist), dellst(vlist) {};
		const varset& getpreconditions() const { return precond; };
		const varset& getadd() const { return addlst; };
		const varset& getdelete() const { return dellst; };
		std::string getname() const { return name; };
		action& setpreconditions(const std::vector<std::string>& item) { precond.set(item); return *this; };
		action& setadd(const std::vector<std::string>& item);
		action& setdelete(const std::vector<std::string>& item);
		//--
		inline bool canexecute(const varset& state) const { return (state&precond) == precond; };
		inline varset execute(varset state) const { return ((state |= addlst) &= ~dellst); };
		inline varset executerelaxed(varset state) const { return ((state |= addlst)); };
	};
	//-------------------------------------------------------------------------------------
}
#endif