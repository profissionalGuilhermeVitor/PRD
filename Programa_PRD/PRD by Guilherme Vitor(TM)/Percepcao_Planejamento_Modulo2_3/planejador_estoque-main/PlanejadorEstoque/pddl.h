#ifndef __PDDL_H__
#define __PDDL_H__
#include <vector>
#include <istream>
#include "problem.h"
#pragma warning( disable : 4290 )
//-------------------------------------------------------------------------------------
namespace pddl {
	//-------------------------------------------------------------------------------------
	struct type {
		std::string name;
		std::string parent; // "" para nenhum
		type(std::string _name, std::string _parent) : name(_name), parent(_parent) {};
	};
	//-------------------------------------------------------------------------------------
	struct predicate {
		std::string name;
		std::vector<std::string> parnames, partypes;
		bool invariant;
		bool irreversible; // uma vez estabelecido, o fato não é removido
		std::vector<bool> excluive; // uma vez estabelecido um fato deste predicado, nenhum outro com os mesmos parâmetros onde exclusive = true podem ser estabelecidos
	};
	//-------------------------------------------------------------------------------------
	class expression {
	private:
		bool _hasoperator(const std::string& op, std::vector<bool>& signal, bool &s);
		bool _hasoperator(const std::string& op, std::vector<bool>& signal, std::vector<std::string>& pars, bool &s);
	public:
		std::string oper;
		std::vector<std::string> parnames;
		std::vector<expression> children;
		//--
		expression() = default;
		explicit expression(std::string exp);
		//--
		bool hasoperator(const std::string& op);
		bool hasoperator(const std::string& op, std::vector<bool>& signal);
		bool hasoperator(const std::string& op, std::vector<bool>& signal, std::vector<std::string>& pars);
	};
	//-------------------------------------------------------------------------------------
	struct action {
		std::string name;
		std::vector<std::string> parnames, partypes;
		std::vector<long> indexes;
		expression preconditions, effects;
		//--
		std::vector<bool> excluive;
	};
	//-------------------------------------------------------------------------------------
	class domain {
	private:
	public:
		std::vector<type> types;
		std::vector<predicate> predicates;
		std::vector<action> actions;
		std::string name;
		void readstream(std::istream& in) throw (std::exception);
	};
	//-------------------------------------------------------------------------------------
	struct problem {
		std::string name, dmname;
		expression init;
		expression goal;
		std::vector<std::string> objnames, objtypes;
		void readstream(std::istream& in) throw (std::exception);
	};
	//-------------------------------------------------------------------------------------
	class pddlparser {
	protected:
		domain dm;
		problem pb;
		bool falha;
		std::vector<std::string> invariants;
		//--
		struct actioninvariant
		{
			std::string oper;
			std::vector<int> pars;
			int maxpar;
			bool neg;
		};
		//--
		std::vector<std::string> enumvarsoftype(std::string type);
		void parseexpression(const expression& e, std::vector<std::string> &inv, std::vector<std::string> &facts, bool& neg);
		void parseactionexpression(const action& action, const std::vector<std::string>& pars, const expression& e, std::vector<std::string> &inv, std::vector<std::string> &facts, bool& neg);
		void parseactioninvariants(action& action, const expression& e, std::vector<actioninvariant> &invs, bool& neg);
		void getfact(const predicate& pred, std::vector<std::string>& pars, planners::varlist& out, std::vector<std::vector<std::string>>& pvars);
		void convaction(const action& act, std::vector<std::string>& pars, planners::problem& out, std::vector<actioninvariant> &invs, std::vector<std::vector<std::string>>& pvars);
		planners::varlist getfacts();
		void convactions(planners::problem& out);
	public:
		pddlparser(std::string dfname, std::string pfname);
		planners::problem generateproblem(planners::varlist& vlist);
		bool operator!() { return falha; }
	};
};
#endif