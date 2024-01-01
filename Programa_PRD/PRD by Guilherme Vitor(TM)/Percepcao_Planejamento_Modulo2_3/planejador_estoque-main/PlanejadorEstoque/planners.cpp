#include "planners.h"
#include <ctime>
#include <random>
#include <vector>
#include <iostream>
namespace planners {
	//-------------------------------------------------------------------------------------
	// localsearchplanner
	//-------------------------------------------------------------------------------------
	int localsearchplanner::calcheuristics(varset state)
	{
		varlist& vlist = prob->getvarlist();
		const std::vector<action>& actions = prob->getrelevantactions();
		int* gs = new int[vlist.size()];
		int i;
		for (i = 1; i <= vlist.size(); i++)
		{
			gs[i - 1] = (state.isset(i)) ? 0 : INT_MAX;
		}

		for (;;)
		{
			varset next = state;
			bool changed = false;
			std::vector<action>::const_iterator it;
			//std::cout << "Estado: " << state << std::endl;
			for (it = actions.begin(); it != actions.end(); it++)
			{
				//std::cout << "Acao: (" << it->second.getpreconditions() << "," << it->second.getadd() << "," << it->second.getdelete() << std::endl;
				if (!it->canexecute(state)) continue;
				next = it->executerelaxed(next);
				int gf2 = 0;
				for (i = 1; i <= vlist.size(); i++)
				{
					if (it->getpreconditions().isset(i))
					{
						if (gs[i - 1] == INT_MAX)
						{
							gf2 = INT_MAX;
							break;
						}
						else
						{
							gf2 += gs[i - 1];
						}
					}
				}
				for (i = 1; i <= vlist.size(); i++)
				{
					if (it->getadd().isset(i))
					{
						int newgf = (gf2 == INT_MAX) ? gf2 : gf2 + 1;
						if (newgf < gs[i - 1])
						{
							changed = true;
							gs[i - 1] = newgf;
						}
					}
				}
			}
			state = next;
			if (!changed) break;
		}

		int h = 0;
		//std::cout << getproblem().getgoal() << std::endl;
		for (i = 1; i <= vlist.size(); i++)
		{
			if (getproblem().getgoal().isset(i))
			{
				if (gs[i - 1] == INT_MAX)
				{
					h = INT_MAX;
					break;
				}
				else
				{
					h += gs[i - 1];
				}
			}
		}

		return h;
	}
	//-------------------------------------------------------------------------------------
	pnode* localsearchplanner::plan()
	{
		if (root) delete root;
		root = new pnode(NULL, getproblem().getinit(), 0, calcheuristics(getproblem().getinit()));
#ifdef USE_RELEVANT
		const std::vector<action>& actions = prob->getrelevantactions();
#else
		const std::vector<action>& actions = prob->getactions();
#endif
		unsigned long seed = clock();
		std::mt19937 rnd(seed);
		pnode *node = root;
		int pcount = 0, rcount = 0;
		const int maxp = 5, maxr = 5;
		workerthreads wt;

		while (node != NULL)
		{
			int heur = node->getheuristics();
			if (heur == 0) return node;
			std::vector<std::shared_ptr<pnode>> next;
#ifndef USE_THREADS
			for (auto it=actions.begin();it!=actions.end();it++)
			{
				if (!it->canexecute(node->getstate()))
					continue;
				std::shared_ptr<pnode> chnode = node->getchild(it->getname());
				if (chnode && chnode->iscut())
					continue;
				varset child( (chnode)?chnode->getstate():it->execute(node->getstate()) );
				if (node->searchancestors(child)!=NULL)
					continue;
				if (!chnode)
					chnode = std::shared_ptr<pnode>(new pnode(node,child,node->getcost()+1,calcheuristics(child)));
				if (next.empty())
				{
					next.push_back(chnode);
				}
				else if (next[0]->getheuristics()>chnode->getheuristics())
				{
					next.clear();
					next.push_back(chnode);
				}
				else if (next[0]->getheuristics()==chnode->getheuristics())
				{
					next.push_back(chnode);
				}
				node->addchild(it->getname(),chnode);
			}
#else
			next = wt.process(this, node, actions.begin(), actions.end());
#endif
			node->updateheuristics();
			if (!next.empty())
			{
				if (node->getheuristics() == next[0]->getheuristics())
					pcount++;
				if (pcount > maxp)
				{
					rcount++;
					if (rcount > maxr)
						node = NULL;
					else
					{
						pcount = 0;
						node = root;
					}
				}
				else
				{
					if (next.size() == 1)
						node = next[rnd() % next.size()].get();
					else
						node = next[0].get();
				}
			}
			else
				node = NULL;

		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------
	// workerthreads
	//-------------------------------------------------------------------------------------
	std::vector<action>::const_iterator workerthreads::next()
	{
		std::lock_guard<std::mutex> lk(itm);
		return (_begin != _end) ? _begin++ : _end;
	}
	//-------------------------------------------------------------------------------------
	workerthreads::workerthreads() : sigfinish(NULL), sigstart(false), node(NULL), terminated(false)
	{
		unsigned int n = std::thread::hardware_concurrency();
		if (n < 1) n = 1;
		std::cout << "Usando " << n << " threads." << std::endl;
		sigfinish = new bool[n];
		sigstart = new bool[n];
		for (std::size_t i = 0; i < n; i++) {
			sigfinish[i] = false;
			sigstart[i] = false;
		}
		for (unsigned int i = 0; i < n; i++)
		{
			threads.emplace_back(workerfunction, i, std::ref(*this));
		}
	}
	//-------------------------------------------------------------------------------------
	workerthreads::~workerthreads()
	{
		terminate();
		if (sigfinish)
		{
			delete[] sigfinish;
			sigfinish = NULL;
		}
		if (sigstart)
		{
			delete[] sigstart;
			sigstart = NULL;
		}
	}
	//-------------------------------------------------------------------------------------
	std::vector<std::shared_ptr<pnode>> workerthreads::process(localsearchplanner *planner, pnode *node, std::vector<action>::const_iterator begin, std::vector<action>::const_iterator end)
	{
		std::lock_guard<std::mutex> proclock(procm);
		if (isterminated()) return std::vector<std::shared_ptr<pnode>>();
		this->node = node;
		this->_begin = begin;
		this->_end = end;
		this->planner = planner;
		int n = threads.size();
		{
			std::lock_guard<std::mutex> lk(fm);
			for (int i = 0; i < n; i++)
				sigfinish[i] = false;
		}
		{
			std::unique_lock<std::mutex> lk(sm);
			for (int i = 0; i < n; i++)
				sigstart[i] = true;
		}
		cv.notify_all();
		{
			std::unique_lock<std::mutex> lk(fm);
			cv.wait(lk, [n, this]{ for (int i = 0; i < n; i++) { if (!sigfinish[i]) return false; } return true; });
		}
		return nextnode;
	}
	//-------------------------------------------------------------------------------------
	void workerthreads::terminate()
	{
		std::unique_lock<std::mutex> lk(tm);
		if (!terminated)
		{
			terminated = true;
			lk.unlock();
			cv.notify_all();
			for (auto& th : threads)
				th.join();
		}
	}
	//-------------------------------------------------------------------------------------
	bool workerthreads::isterminated()
	{
		std::lock_guard<std::mutex> lk(tm);
		return terminated;
	}
	//-------------------------------------------------------------------------------------
	void workerthreads::syncnext(const std::vector<std::shared_ptr<pnode>>& nxt)
	{
		std::lock_guard<std::mutex> lk(nextm);
		if (nxt.empty()) return;
		if (nextnode.empty())
		{
			nextnode.insert(nextnode.end(), nxt.begin(), nxt.end());
		}
		else if (nextnode[0]->getheuristics() > nxt[0]->getheuristics())
		{
			nextnode.clear();
			nextnode.insert(nextnode.end(), nxt.begin(), nxt.end());
		}
		else if (nextnode[0]->getheuristics() == nxt[0]->getheuristics())
		{
			nextnode.insert(nextnode.end(), nxt.begin(), nxt.end());
		}
	}
	//-------------------------------------------------------------------------------------
	void workerfunction(int n, workerthreads& wthreads)
	{
		bool run = true;
		while (run)
		{
#ifdef DEBUG_PLANNING_THREADS
			{
				std::lock_guard<std::mutex> lk(wthreads.outm);
				std::cout << "Thread " << n << ": Início do loop (1)" << std::endl;
			}
#endif
			{
				std::unique_lock<std::mutex> lk(wthreads.sm);
				bool b = wthreads.sigstart[n];
				wthreads.cv.wait(lk, [n, &wthreads]{ return wthreads.sigstart[n] || wthreads.isterminated(); });
				b = wthreads.sigstart[n];
				wthreads.sigstart[n] = false;
			}
#ifdef DEBUG_PLANNING_THREADS
			{
				std::lock_guard<std::mutex> lk(wthreads.outm);
				std::cout << "Thread " << n << ": Iniciando tarefa (2)" << std::endl;
			}
#endif
			if (wthreads.isterminated())
				run = false;
			else
			{
#ifdef DEBUG_PLANNING_THREADS
				{
					std::lock_guard<std::mutex> lk(wthreads.outm);
					std::cout << "Thread " << n << ": Processando tarefa (3)" << std::endl;
				}
#endif
				std::vector<std::shared_ptr<pnode>> next;
				for (auto it = wthreads.next(); it != wthreads.end(); it = wthreads.next())
				{
					if (!it->canexecute(wthreads.node->getstate()))
						continue;
					std::shared_ptr<pnode> chnode = wthreads.node->getchild(it->getname());
					if (chnode && chnode->iscut())
						continue;
					varset child((chnode) ? chnode->getstate() : it->execute(wthreads.node->getstate()));
					if (wthreads.node->searchancestors(child) != NULL)
						continue;
					if (!chnode)
						chnode = std::shared_ptr<pnode>(new pnode(wthreads.node, child, wthreads.node->getcost() + 1, wthreads.planner->calcheuristics(child)));
					if (next.empty())
					{
						next.push_back(chnode);
					}
					else if (next[0]->getheuristics() > chnode->getheuristics())
					{
						next.clear();
						next.push_back(chnode);
					}
					else if (next[0]->getheuristics() == chnode->getheuristics())
					{
						next.push_back(chnode);
					}
					wthreads.node->addchild(it->getname(), chnode);
				}
				wthreads.syncnext(next);
#ifdef DEBUG_PLANNING_THREADS
				{
					std::lock_guard<std::mutex> lk(wthreads.outm);
					std::cout << "Thread " << n << ": Finalizando tarefa (4)" << std::endl;
				}
#endif

			}
			{
				std::lock_guard<std::mutex> lk(wthreads.fm);
				wthreads.sigfinish[n] = true;
			}
#ifdef DEBUG_PLANNING_THREADS
			{
				std::lock_guard<std::mutex> lk(wthreads.outm);
				std::cout << "Thread " << n << ": Notificando fim (5)" << std::endl;
			}
#endif
			wthreads.cv.notify_all();
		}
	}
	//-------------------------------------------------------------------------------------
}