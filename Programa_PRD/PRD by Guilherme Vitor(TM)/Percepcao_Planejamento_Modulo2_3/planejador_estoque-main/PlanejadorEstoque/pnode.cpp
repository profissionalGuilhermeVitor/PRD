#include "pnode.h"
#include <climits>
namespace planners {
	//-------------------------------------------------------------------------------------
	// pnode
	//-------------------------------------------------------------------------------------
	pnode::pnode(pnode* parent, const varset& astate, int cost, int heuristics) :state(astate)
	{
		this->cost = cost;
		this->heuristics = heuristics;
		this->parent = parent;
	}
	//-------------------------------------------------------------------------------------
	void pnode::cut()
	{
		if (!ncut) {
			std::lock_guard<std::recursive_mutex> lk(cm);
			std::unordered_map<std::string, std::shared_ptr<pnode>>::iterator it;
			for (it = children.begin(); it != children.end(); it++)
			{
				if (it->second) it->second->cut();
			}
		}
	}
	//-------------------------------------------------------------------------------------
	void pnode::clear()
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		children.clear();
	}
	//-------------------------------------------------------------------------------------
	std::shared_ptr<pnode> pnode::addchild(const std::string& action, std::shared_ptr<pnode> node)
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		children.insert(std::make_pair(action, node));
		return node;
	}
	//-------------------------------------------------------------------------------------
	std::shared_ptr<pnode> pnode::getchild(const std::string& action)
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		std::unordered_map<std::string, std::shared_ptr<pnode>>::iterator it = children.find(action);
		if (it != children.end()) {
			return it->second;
		}
		return std::shared_ptr<pnode>();
	}
	//-------------------------------------------------------------------------------------
	void pnode::updateheuristics()
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		int h = INT_MAX;
		if (children.empty()) return;
		std::unordered_map<std::string, std::shared_ptr<pnode>>::iterator it;
		for (it = children.begin(); it != children.end(); it++)
		{
			if (it->second->getheuristics()<h)
				h = it->second->getheuristics();
		}
		if (h>getheuristics())
			setheuristics((h == INT_MAX) ? h : h + 1);
	}
	//-------------------------------------------------------------------------------------
	void pnode::trimdups(const varset &state)
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		std::vector<pnode*> dups = searchstate(state);
		std::shared_ptr<pnode> min;
		std::unordered_map<std::string, std::shared_ptr<pnode>>::iterator it;
		for (it = children.begin(); it != children.end(); it++)
		{
			if (min == NULL)
				min = it->second;
			else {
				if (min->getcost() > it->second->getcost()) {
					min->cut();
					min = it->second;
				}
				else {
					it->second->cut();
				}
			}
		}
	}
	//-------------------------------------------------------------------------------------
	std::vector<pnode*> pnode::searchstate(const varset& state)
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		std::vector<pnode*> result;
		std::unordered_map<std::string, std::shared_ptr<pnode>>::iterator it;

		if (this->state == state) result.push_back(this);
		for (it = children.begin(); it != children.end(); it++)
		{
			if (it->second && it->second->state == state) result.push_back(it->second.get());
		}

		return result;
	}
	//-------------------------------------------------------------------------------------
	pnode* pnode::searchancestors(const varset& state)
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		if (this->state == state) return this;
		if (parent) return parent->searchancestors(state);
		return NULL;
	}
	//-------------------------------------------------------------------------------------
	pnode* pnode::getbestnode()
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		if (children.empty()) return this;
		std::unordered_map<std::string, std::shared_ptr<pnode>>::iterator it;
		std::vector<std::shared_ptr<pnode>> items;

		for (it = children.begin(); it != children.end(); it++)
		{
			if (!it->second->iscut()) items.push_back(it->second);
		}

		std::vector<std::shared_ptr<pnode>>::iterator it2;
		pnode* best = NULL;
		for (it2 = items.begin(); it2 != items.end(); it2++)
		{
			if (!best)
			{
				best = it2->get();
			}
			else
			{
				if (best->getcost() + best->getheuristics() > (*it2)->getcost() + (*it2)->getheuristics())
					best = it2->get();
			}
		}
		return best;
	}
	//-------------------------------------------------------------------------------------
	int pnode::getnumstates()
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		int r = children.size();
		std::unordered_map<std::string, std::shared_ptr<pnode>>::const_iterator it;
		for (it = children.begin(); it != children.end(); it++)
		{
			r = r + it->second->getnumstates();
		}
		return r;
	}
	//-------------------------------------------------------------------------------------
	std::string pnode::getplanstring()
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		int cnt = 0;
		pnode* p = this;
		std::string s;

		while (p->parent)
		{
			std::unordered_map<std::string, std::shared_ptr<pnode>>::const_iterator it;
			for (it = p->parent->children.begin(); it != p->parent->children.end(); it++)
			{
				if (p == it->second.get())
				{
					s = it->first + "\r\n" + s;
					cnt++;
					break;
				}
			}
			p = p->parent;
		}
		return "(numereo de acoes: " + std::to_string(cnt) + ")\r\n" + s;
	}
	//-------------------------------------------------------------------------------------
	static void outputspace(std::ostream& out, int level)
	{
		for (; level > 0; level--)
			out << "  ";
	}
	//-------------------------------------------------------------------------------------
	int pnode::outputdebugaux(std::ostream& out, int level, int state)
	{
		std::lock_guard<std::recursive_mutex> lk(cm);
		out << "S" << state++ << " (h=" << getheuristics() << "): " << getstate() << std::endl;
		level++;
		std::unordered_map<std::string, std::shared_ptr<pnode>>::const_iterator it;
		for (it = children.begin(); it != children.end(); it++)
		{
			outputspace(out, level);
			out << "+--(" << it->first << ")--> ";
			state = it->second->outputdebugaux(out, level, state);
		}
		return state;
	}
	//-------------------------------------------------------------------------------------
	void pnode::outputdebug(std::ostream& out)
	{
		outputdebugaux(out, 0, 0);
	}
	//-------------------------------------------------------------------------------------
}