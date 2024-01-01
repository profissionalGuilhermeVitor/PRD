#ifndef __PROBLEM__H__
#define __PROBLEM__H__
#include "varset.h"
#include "action.h"
#include <map>
namespace planners {
	//-------------------------------------------------------------------------------------
	class problem
	{
	protected:
		varlist*vlist;
		std::vector<action> actions;
		varset init, goal;
		bool radirty, reldirty;
		bool addrelev;
		varset relevant, reversible; // Fatos relevantes e reversíveis
		std::vector<action> raction;
		void updateraction();
		void updaterelevant();
	public:
		explicit problem(varlist& vlist);
		//--
		void addaction(const action& act);
		const std::vector<action>& getactions() const { return actions; };
		const std::vector<action>& getrelevantactions();
		//--
		void setinit(const std::vector<std::string>& vars);
		void setgoal(const std::vector<std::string>& vars);
		void setaddrelevant(bool b) { addrelev = b; };
		const varset & getinit() const { return init; };
		const varset & getgoal() const { return goal; };
		const bool getaddrelevant() const { return addrelev; };
		varlist& getvarlist() { return *vlist; };
		bool matchgoal(varset state) const { return (state&goal) == goal; };
	};
	//-------------------------------------------------------------------------------------
}
#endif