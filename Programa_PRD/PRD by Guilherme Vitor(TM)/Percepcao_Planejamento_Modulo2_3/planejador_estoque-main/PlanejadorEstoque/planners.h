#ifndef __PLANNERS_H__
#define __PLANNERS_H__
#include "problem.h"
#include "varset.h"
#include "pnode.h"
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#define USE_THREADS
#define USE_RELEVANT true
namespace planners {
	//-------------------------------------------------------------------------------------
	class planner
	{
	private:
		planner(const planner& p);
	protected:
		problem* prob;
		pnode *root;
	public:
		explicit planner(problem& p) :prob(&p), root(NULL){};
		virtual ~planner() { if (root) delete root; };
		//--
		pnode* getroot() { return root; };
		problem& getproblem() { return *prob; };
		//--
		virtual pnode* plan() = 0;
	};
	//-------------------------------------------------------------------------------------
	class localsearchplanner : public planner
	{
	private:
		localsearchplanner(const localsearchplanner& p);
	public:
		explicit localsearchplanner(problem& p) :planner(p){};
		//--
		int calcheuristics(varset state);
		pnode* plan();
	};
	//-------------------------------------------------------------------------------------
	class workerthreads
	{
	protected:
		std::vector<std::thread> threads;
		bool *sigfinish;
		bool terminated;
		bool *sigstart;
		std::mutex sm, fm, tm, itm, procm, nextm, outm;
		std::condition_variable cv;
		pnode *node;
		localsearchplanner* planner;
		std::vector<action>::const_iterator _begin, _end;
		std::vector<std::shared_ptr<pnode>> nextnode;
		//--
		workerthreads(const workerthreads& wt) = delete;
		//--
		std::vector<action>::const_iterator end() { return _end; };
		std::vector<action>::const_iterator next();
		//--
		void syncnext(const std::vector<std::shared_ptr<pnode>>& nxt);
	public:
		workerthreads();
		~workerthreads();
		//--
		std::vector<std::shared_ptr<pnode>> process(localsearchplanner *planner, pnode *node, std::vector<action>::const_iterator begin, std::vector<action>::const_iterator end);
		void terminate();
		bool isterminated();
		//--
		friend void workerfunction(int n, workerthreads& wthreads);
	};
	//-------------------------------------------------------------------------------------
}
#endif