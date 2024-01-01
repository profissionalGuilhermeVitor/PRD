#ifndef __PNODE_H__
#define __PNODE_H__
#include <vector>
#include <memory>
#include "varset.h"
#include <unordered_map>
#include <mutex>
namespace planners {
	//-------------------------------------------------------------------------------------
	class pnode
	{
	protected:
		pnode* parent;
		varset state;
		int cost, heuristics;
		bool ncut;
		std::unordered_map<std::string, std::shared_ptr<pnode>> children;
		int outputdebugaux(std::ostream& out, int level, int state);
		std::recursive_mutex cm;
	public:
		pnode(pnode* parent, const varset& astate, int cost, int heuristics);
		//--
		void cut();
		bool iscut() const { return ncut; };
		void clear();
		//--
		std::shared_ptr<pnode> addchild(const std::string& action, std::shared_ptr<pnode> node);
		std::shared_ptr<pnode> getchild(const std::string& action);
		//--
		const varset& getstate() const { return state; };
		int getcost() const { return cost; };
		int getheuristics() const { return heuristics; };
		pnode* getparent() { return parent; };
		void setcost(int cost) { this->cost = cost; };
		void setheuristics(int heuristics) { this->heuristics = heuristics; };
		//--
		void updateheuristics();
		void trimdups(const varset &state);
		std::vector<pnode*> searchstate(const varset& state);
		pnode* searchancestors(const varset& state);
		pnode* getbestnode();
		//--
		std::string getplanstring();
		void outputdebug(std::ostream& out);
		int getnumstates();
	};
	//-------------------------------------------------------------------------------------
}
#endif