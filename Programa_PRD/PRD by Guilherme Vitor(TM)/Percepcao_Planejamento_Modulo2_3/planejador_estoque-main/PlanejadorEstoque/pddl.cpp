#include "pddl.h"
#include <cctype>
#include <string>
#include <fstream>
#include <algorithm>
namespace pddl {
	//-------------------------------------------------------------------------------------
	// funções auxiliares
	//-------------------------------------------------------------------------------------
	static std::string next_parameter(const std::string& buffer, int& pos)
	{
		if (pos == 0) pos++;
		while (pos < (int)buffer.length() && isspace(buffer[pos])) pos++;
		int p = pos;
		while (p < (int)buffer.length() && !isspace(buffer[p]) && buffer[p] != '(' && buffer[p] != ')') p++;
		if (p == pos) { return ""; }
		std::string result = buffer.substr(pos, p - pos);
		pos = p;
		return result;
	}
	//-------------------------------------------------------------------------------------
	static std::string next_section(const std::string& buffer, int& pos)
	{
		if (pos == 0) pos++;
		int p = buffer.find('(',pos);
		if (p == -1)
		{
			pos = -1;
			return std::string();
		}
		pos = p;
		int lvl = 1;
		while (lvl>0)
		{
			p++;
			if (p >= (int)buffer.length()) break;
			if (buffer[p] == '(') lvl++;
			else if (buffer[p] == ')') lvl--;
		}
		
		if (p >= (int)buffer.length())
		{
			pos = -1;
			return std::string();
		}

		std::string result = buffer.substr(pos, p - pos + 1);
		pos = p + 1;
		return result;
	}
	//-------------------------------------------------------------------------------------
	// expression
	//-------------------------------------------------------------------------------------
	expression::expression(std::string exp)
	{
		int pos = 0;
		oper = next_parameter(exp, pos);
		for (std::string par = next_parameter(exp, pos); par.length() > 0; par = next_parameter(exp, pos))
		{
			parnames.push_back(par);
		}
		for (std::string child = next_section(exp, pos); child.length() > 0; child = next_section(exp, pos))
		{
			children.push_back(expression(child));
		}
	}
	//-------------------------------------------------------------------------------------
	bool expression::hasoperator(const std::string& op)
	{
		if (_stricmp(op.c_str(), oper.c_str()) == 0)
			return true;
		for (auto& ch : children)
		{
			if (ch.hasoperator(op)) return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------------
	bool expression::_hasoperator(const std::string& op, std::vector<bool>& signal, bool& s)
	{
		bool result = false;
		if (_stricmp(op.c_str(), oper.c_str()) == 0)
		{
			signal.push_back(s);
			return true;
		}
		if (_stricmp(op.c_str(), "not") == 0)
			s = !s;
		for (auto& ch : children)
		{
			if (ch.hasoperator(op, signal)) result = true;
		}
		if (_stricmp(op.c_str(), "not") == 0)
			s = !s;
		return result;
	}
	//-------------------------------------------------------------------------------------
	bool expression::_hasoperator(const std::string& op, std::vector<bool>& signal, std::vector<std::string>& pars, bool& s)
	{
		bool result = false;
		if (_stricmp(op.c_str(), oper.c_str()) == 0)
		{
			signal.push_back(s);
			std::string tmp = "";
			for (auto&t : parnames) tmp += t + " ";
			if (tmp.length() > 0) tmp.erase(tmp.length() - 1);
			pars.push_back(tmp);
			return true;
		}
		if (_stricmp(op.c_str(), "not") == 0)
			s = !s;
		for (auto& ch : children)
		{
			if (ch.hasoperator(op, signal)) result = true;
		}
		if (_stricmp(op.c_str(), "not") == 0)
			s = !s;
		return result;
	}
	//-------------------------------------------------------------------------------------
	bool expression::hasoperator(const std::string& op, std::vector<bool>& signal)
	{
		bool s;
		return _hasoperator(op, signal, s);
	}
	//-------------------------------------------------------------------------------------
	bool expression::hasoperator(const std::string& op, std::vector<bool>& signal, std::vector<std::string>& pars)
	{
		bool s;
		return _hasoperator(op, signal, pars, s);
	}
	//-------------------------------------------------------------------------------------
	// domain
	//-------------------------------------------------------------------------------------
	void domain::readstream(std::istream& in) throw (std::exception)
	{
		std::string buffer;
		{ // Lê todo o documento pddl em um buffer
			int npar = 0;
			while (isspace(in.peek())) in.get();
			if (in.peek() != '(') throw std::exception("Arquivo de entrada inválido");
			buffer += (char)in.get();
			npar++;
			while (npar) {
				char c = (char)in.get();

				if (c == ';') { while (c != '\n' && c != '\r') { c = (char)in.get(); } } // Suporte a comentários

				if (c == '(') npar++;
				else if (c == ')') npar--;

				if (isspace(c) && isspace(in.peek())) continue;
				else if (isspace(c)) buffer += ' ';
				else buffer += c;
			}
		}
		int pos = 0;
		if (_stricmp(next_parameter(buffer, pos).c_str(), "define") != 0) throw std::exception("Arquivo de entrada inválido");
		for (std::string sec = next_section(buffer, pos); sec.length() > 0; sec = next_section(buffer, pos))
		{
			int p = 0;
			std::string secname = next_parameter(sec, p);
			if (_stricmp(secname.c_str(), "domain") == 0)
			{
				name = next_parameter(sec, p);
			}
			else if (_stricmp(secname.c_str(), ":requirements") == 0)
			{
				for (std::string req = next_parameter(sec, p); req.length() > 0; req = next_parameter(sec, p))
				{
					if (_stricmp(req.c_str(), ":strips") == 0) continue;
					throw std::exception(("Requerimento \""+req+"\" não é suportado").c_str());
				}
			}
			else if (_stricmp(secname.c_str(), ":types") == 0)
			{
				for (;;)
				{
					std::string tname = next_parameter(sec, p);
					if (tname.length() < 1) break;
					if (next_parameter(sec, p) != "-") throw std::exception("Arquivo de entrada inválido");
					std::string tparent = next_parameter(sec, p);
					if (tparent.length() < 1) throw std::exception("Arquivo de entrada inválido");
					if (tparent == "object") tparent = "";
					types.push_back(type(tname,tparent));
				}
			}
			else if (_stricmp(secname.c_str(), ":predicates") == 0)
			{
				for (std::string pred = next_section(sec, p); pred.length() > 0; pred = next_section(sec, p))
				{
					predicate pr;
					int idx = 0;
					pr.invariant = true;
					pr.name = next_parameter(pred, idx);
					if (pr.name.length()<1) throw std::exception("Arquivo de entrada inválido");
					for (;;)
					{
						std::string parname = next_parameter(pred, idx);
						if (parname.length() < 1) break;
						if (next_parameter(pred, idx) != "-") throw std::exception("Arquivo de entrada inválido");
						std::string partype = next_parameter(pred, idx);
						if (parname.length() < 1) throw std::exception("Arquivo de entrada inválido");
						pr.parnames.push_back(parname);
						pr.partypes.push_back(partype);
					}
					predicates.push_back(pr);
				}
			}
			else if (_stricmp(secname.c_str(), ":action") == 0)
			{
				action act;
				act.name = next_parameter(sec, p);
				if (act.name.length()<1) throw std::exception("Arquivo de entrada inválido");
				for (std::string field = next_parameter(sec, p); field.length() > 0; field = next_parameter(sec, p))
				{
					if (_stricmp(field.c_str(), ":parameters") == 0)
					{
						std::string pars = next_section(sec, p);
						if (pars.length()<1) throw std::exception("Arquivo de entrada inválido");
						int idx = 0;
						for (;;)
						{
							std::string parname = next_parameter(pars, idx);
							if (parname.length() < 1) break;
							if (next_parameter(pars, idx) != "-") throw std::exception("Arquivo de entrada inválido");
							std::string partype = next_parameter(pars, idx);
							if (parname.length() < 1) throw std::exception("Arquivo de entrada inválido");
							act.parnames.push_back(parname);
							act.partypes.push_back(partype);
						}
					}
					else if (_stricmp(field.c_str(), ":precondition") == 0)
					{
						std::string prec = next_section(sec, p);
						if (prec.length()<1) throw std::exception("Arquivo de entrada inválido");
						act.preconditions = expression(prec);
					}
					else if (_stricmp(field.c_str(), ":effect") == 0)
					{
						std::string eff = next_section(sec, p);
						if (eff.length()<1) throw std::exception("Arquivo de entrada inválido");
						act.effects = expression(eff);
					}
				}
				actions.push_back(act);
			}
		}
		for (auto& pred : predicates)
		{
			pred.invariant = true;
			int pos = 0, neg = 0;
			pred.excluive = std::vector<bool>(pred.parnames.size(), true);
			for (auto& act : actions)
			{
				std::vector<bool> signal, signal2; 
				bool hasef = false, haspc = false;
				if (act.effects.hasoperator(pred.name, signal))
				{
					pred.invariant = false;
					hasef = true;
					for (auto s : signal)
					{
						if (s)
							neg++;
						else
							pos++;
					}
				}
				if (pred.parnames.size() == 1)
				{
					if (act.preconditions.hasoperator(pred.name, signal2))
					{
						haspc = true;
					}
					if (haspc != hasef || signal2 == signal)
						pred.excluive[0] = false;
				}
			}
			if (pos > 0 && neg > 0)
				pred.irreversible = false;
			else
				pred.irreversible = true;
		}
		for (auto& act : actions)
		{
			act.excluive = std::vector<bool>(act.parnames.size(), false);
			for (auto& pred : predicates)
			{
				if (pred.invariant || !pred.irreversible || pred.parnames.size() > 1 || !pred.excluive[0]) continue;
				std::vector<bool> signal;
				std::vector<std::string> pars;
				if (!act.effects.hasoperator(pred.name, signal, pars)) continue;
				for (auto& par : pars)
				{
					for (std::size_t i = 0; i < act.parnames.size(); i++)
					{
						if (_stricmp(act.parnames[i].c_str(), par.c_str()) == 0)
							act.excluive[i] = true;
					}
				}
			}
		}
	}
	//-------------------------------------------------------------------------------------
	// problem
	//-------------------------------------------------------------------------------------
	void problem::readstream(std::istream& in) throw (std::exception)
	{
		std::string buffer;
		{ // Lê todo o documento pddl em um buffer
			int npar = 0;
			while (isspace(in.peek())) in.get();
			if (in.peek() != '(') throw std::exception("Arquivo de entrada inválido");
			buffer += (char)in.get();
			npar++;
			while (npar) {
				char c = (char)in.get();

				if (c == ';') { while (c != '\n' && c != '\r') { c = (char)in.get(); } } // Suporte a comentários

				if (c == '(') npar++;
				else if (c == ')') npar--;

				if (isspace(c) && isspace(in.peek())) continue;
				else if (isspace(c)) buffer += ' ';
				else buffer += c;
			}
		}
		int pos = 0;
		if (_stricmp(next_parameter(buffer, pos).c_str(), "define") != 0) throw std::exception("Arquivo de entrada inválido");
		for (std::string sec = next_section(buffer, pos); sec.length() > 0; sec = next_section(buffer, pos))
		{
			int p = 0;
			std::string secname = next_parameter(sec, p);
			if (_stricmp(secname.c_str(), "problem") == 0)
			{
				name = next_parameter(sec, p);
			}
			else if (_stricmp(secname.c_str(), ":domain") == 0)
			{
				dmname = next_parameter(sec, p);
			}
			else if (_stricmp(secname.c_str(), ":objects") == 0)
			{
				for (;;)
				{
					std::string objname = next_parameter(sec, p);
					if (objname.length() < 1) break;
					if (next_parameter(sec, p) != "-") throw std::exception("Arquivo de entrada inválido");
					std::string objtype = next_parameter(sec, p);
					if (objtype.length() < 1) throw std::exception("Arquivo de entrada inválido");
					objnames.push_back(objname);
					objtypes.push_back(objtype);
				}
			}
			else if (_stricmp(secname.c_str(), ":init") == 0)
			{
				init.oper = "and";
				int p = 0;
				for (std::string exp = next_section(sec, p); exp.length() > 0; exp = next_section(sec, p))
				{
					expression e(exp);
					init.children.push_back(e);
				}
			}
			else if (_stricmp(secname.c_str(), ":goal") == 0)
			{
				int p = 0;
				std::string gstr = next_section(sec, p);
				goal = expression(gstr);
			}
		}
	}
	//-------------------------------------------------------------------------------------
	// pddlparser
	//-------------------------------------------------------------------------------------
	std::vector<std::string> pddlparser::enumvarsoftype(std::string type)
	{
		std::vector<std::string> t;
		t.push_back(type);
		bool added = false;
		do
		{
			added = false;
			for (auto& tobj : dm.types)
			{
				for (auto& at : t)
				{
					if (_stricmp(tobj.parent.c_str(), at.c_str()) == 0)
					{
						added = true;
						t.push_back(tobj.name);
						break;
					}
				}
			}
		} while (added);
		std::vector<std::string> vars;
		for (std::size_t i = 0; i < pb.objtypes.size(); i++)
		{
			for (auto& at : t)
			{
				if (_stricmp(pb.objtypes[i].c_str(), at.c_str()) == 0)
				{
					vars.push_back(pb.objnames[i]);
				}
			}
		}
		return vars;
	}
	//-------------------------------------------------------------------------------------
	void pddlparser::parseactioninvariants(action& action, const expression& e, std::vector<pddlparser::actioninvariant> &invs, bool& neg)
	{
		if (action.indexes.empty())
		{
			action.indexes.reserve(action.parnames.size());
			for (std::size_t i = 0; i < action.parnames.size(); i++) action.indexes.push_back(i);
		}
		if (_stricmp(e.oper.c_str(), "not") == 0)
		{
			neg = !neg;
			if (e.children.size() > 0)
			{
				parseactioninvariants(action, e.children[0], invs, neg);
			}
			neg = !neg;
		}
		else if (_stricmp(e.oper.c_str(), "and") == 0)
		{
			for (auto& ch : e.children)
			{
				parseactioninvariants(action, ch, invs, neg);
			}
		}
		else
		{
			actioninvariant ainv;
			ainv.oper = e.oper;
			ainv.neg = neg;
			ainv.maxpar = -1;
			bool isinv = false;
			for (auto& pred : dm.predicates)
			{
				if (_stricmp(pred.name.c_str(), e.oper.c_str()) == 0)
				{
					isinv = pred.invariant;
					break;
				}
			}
			if (!isinv) return;
			for (auto& par : e.parnames)
			{
				bool foundpar = false;
				for (std::size_t i = 0; i < action.parnames.size(); i++)
				{
					if (_stricmp(action.parnames[i].c_str(), par.c_str()) == 0)
					{
						ainv.pars.push_back(i);
						if ((int)i>ainv.maxpar) ainv.maxpar = i;
						foundpar = true;
						if (action.indexes[i] > 0) action.indexes[i] = -action.indexes[i]; // marca parâmetro para reordenação
						break;
					}
				}
				if (!foundpar) return;
			}
			invs.push_back(std::move(ainv));
		}
	}
	//-------------------------------------------------------------------------------------
	void pddlparser::parseactionexpression(const action& action, const std::vector<std::string>& pars, const expression& e, std::vector<std::string> &inv, std::vector<std::string> &facts, bool& neg)
	{
		if (_stricmp(e.oper.c_str(), "not") == 0)
		{
			neg = !neg;
			if (e.children.size() > 0)
			{
				parseactionexpression(action, pars, e.children[0], inv, facts, neg);
			}
			neg = !neg;
		}
		else if (_stricmp(e.oper.c_str(), "and") == 0)
		{
			for (auto& ch : e.children)
			{
				parseactionexpression(action, pars, ch, inv, facts, neg);
			}
		}
		else
		{
			std::string fact;
			if (neg) fact = "!";
			fact += e.oper;
			for (auto& par : e.parnames)
			{
				bool foundpar = false;
				for (std::size_t i = 0; i < /*action.parnames.size()*/pars.size(); i++)
				{
					if (_stricmp(action.parnames[i].c_str(), par.c_str()) == 0)
					{
						fact += " ";
						fact += pars[i];
						foundpar = true;
					}
				}
				if (!foundpar) return;
			}
			bool isinv = false;
			for (auto& pred : dm.predicates)
			{
				if (_stricmp(pred.name.c_str(), e.oper.c_str()) == 0)
				{
					isinv = pred.invariant;
					break;
				}
			}
			if (isinv)
				inv.push_back(std::move(fact));
			else
				facts.push_back(std::move(fact));
		}
	}
	//-------------------------------------------------------------------------------------
	void pddlparser::parseexpression(const expression& e, std::vector<std::string> &inv, std::vector<std::string> &facts, bool& neg)
	{
		if (_stricmp(e.oper.c_str(), "not") == 0)
		{
			neg = !neg;
			if (e.children.size() > 0)
			{
				parseexpression(e.children[0], inv, facts, neg);
			}
			neg = !neg;
		}
		else if (_stricmp(e.oper.c_str(), "and") == 0)
		{
			for (auto& ch : e.children)
			{
				parseexpression(ch, inv, facts, neg);
			}
		}
		else
		{
			std::string fact;
			if (neg) fact = "!";
			fact += e.oper;
			for (auto& par : e.parnames)
			{
				fact += " ";
				fact += par;
			}
			bool isinv = false;
			for (auto& pred : dm.predicates)
			{
				if (_stricmp(pred.name.c_str(), e.oper.c_str()) == 0)
				{
					isinv = pred.invariant;
					break;
				}
			}
			if (isinv)
				inv.push_back(std::move(fact));
			else
				facts.push_back(std::move(fact));
		}
	}
	//-------------------------------------------------------------------------------------
	void pddlparser::getfact(const predicate& pred, std::vector<std::string>& pars, planners::varlist& out, std::vector<std::vector<std::string>>& pvars)
	{
		if (pvars.size() != pred.parnames.size())
		{
			for (auto& t : pred.partypes)
				pvars.push_back(enumvarsoftype(t));
		}
		if (pars.empty()) pars.reserve(pred.parnames.size());
		if (pars.size() < pred.parnames.size())
		{
			for (auto& npar : pvars[pars.size()])
			{
				pars.push_back(npar);
				getfact(pred, pars, out, pvars);
				pars.pop_back();
			}
		}
		else
		{
			std::string s = pred.name;
			for (auto& par : pars)
			{
				s += " ";
				s += par;
			}
			out.add(std::move(s));
		}
	}
	//-------------------------------------------------------------------------------------
	planners::varlist pddlparser::getfacts()
	{
		planners::varlist out;
		std::vector<std::string> pars;
		std::vector<std::vector<std::string>> pvars;
		for (auto&pred : dm.predicates)
		{
			if (pred.invariant) continue;
			pars.clear();
			pvars.clear();
			getfact(pred, pars, out, pvars);
		}
		return out;
	}
	//-------------------------------------------------------------------------------------
	void pddlparser::convaction(const action& act, std::vector<std::string>& pars, planners::problem& out, std::vector<actioninvariant> &invs, std::vector<std::vector<std::string>>& pvars)
	{
		static long int actcnt = 0;
		if (pvars.size() <= pars.size() && pvars.size() < act.parnames.size())
		{
			/*int m = (pars.size() < act.parnames.size()) ? pars.size() + 1 : act.parnames.size();
			for (int i = pvars.size(); i<m; i++)*/
			pvars.push_back(enumvarsoftype(act.partypes[pvars.size()]));
			/*for (auto& t : act.partypes)
				pvars.push_back(enumvarsoftype(t));*/
		}
		if (pars.size() < act.parnames.size())
		{
			if (pars.empty())
				pars.reserve(act.parnames.size());
			else
			{
				for (auto& inv : invs)
				{
					if ((int)pars.size() != inv.maxpar + 1) continue;
					std::string f = inv.oper;
					for (auto i : inv.pars)
					{
						f += " ";
						f += pars[i];
					}
					if (!std::binary_search(invariants.begin(), invariants.end(), f, [](const std::string&a, const std::string&b){return _stricmp(a.c_str(), b.c_str()) < 0; }))
						return;
				}
			}
			for (auto& npar : pvars[pars.size()])
			{
				pars.push_back(npar);
				convaction(act, pars, out, invs, pvars);
				pars.pop_back();
			}
		}
		else
		{
			for (auto& inv : invs)
			{
				if ((int)pars.size() != inv.maxpar + 1) continue;
				std::string f = inv.oper;
				for (auto i : inv.pars)
					f += " " + pars[i];
				if (!std::binary_search(invariants.begin(), invariants.end(), f, [](const std::string&a, const std::string&b){return _stricmp(a.c_str(), b.c_str()) < 0; }))
					return;
			}
			std::string aname = act.name;
			for (std::size_t i = 0; i < act.indexes.size(); ++i)
			{
				for (std::size_t i2 = 0; i2 < act.indexes.size(); ++i2)
				{
					if (act.indexes[i2] == (long)i)
					{
						aname += " ";
						aname += pars[i2];
						break;
					}
				}
			}
			std::vector<std::string> inv, facts;
			bool neg = false;
			parseactionexpression(act, pars, act.preconditions, inv, facts, neg);
			/*for (auto& f : inv)
			{
				if (!std::binary_search(invariants.begin(), invariants.end(), f, [](const std::string&a, const std::string&b){return _stricmp(a.c_str(), b.c_str()) < 0; }))
					return;
			}*/
			planners::action pl_action(aname, out.getvarlist());
			pl_action.setpreconditions(facts);

			inv.clear(); facts.clear(); neg = false;
			parseactionexpression(act, pars, act.effects, inv, facts, neg);
			// inv será reutilizado para conter a lista de exclusão
			inv.clear(); // desnecessário, mas feito como garantia
			for (auto iter = facts.begin(); iter != facts.end();){
				if ((*iter)[0] == '!')
				{
					(*iter).erase(0, 1);
					inv.push_back(std::move(*iter));
					iter = facts.erase(iter);
				}
				else
					++iter;
			}
			pl_action.setdelete(inv);
			pl_action.setadd(facts);
			out.addaction(pl_action);
			//std::cout << "\r" << ++actcnt;
		}
	}
	//-------------------------------------------------------------------------------------
	void pddlparser::convactions(planners::problem& out)
	{
		for (auto&act : dm.actions)
		{
			std::vector<actioninvariant> invs;
			std::vector<std::string> pars;
			std::vector<std::vector<std::string>> pvars;
			bool neg;
			parseactioninvariants(act, act.preconditions, invs, neg);
			//-- reordena para que parâmetros de invariantes sejam analisados primeiro
			std::size_t newpos = 0;
			for (std::size_t i = 0; i < act.parnames.size(); ++i)
			{
				if (act.indexes[i] < 0)
				{
					act.indexes[i] = -act.indexes[i];
					if (i != newpos)
					{
						std::swap(act.parnames[i], act.parnames[newpos]);
						std::swap(act.partypes[i], act.partypes[newpos]);
						std::swap(act.indexes[i], act.indexes[newpos]);
					}
					newpos++;
				}
			}
			for (auto& o : invs)
			{
				o.maxpar = -1;
				for (std::size_t i = 0; i < o.pars.size(); i++)
				{
					for (std::size_t i2 = 0; i2 < act.indexes.size(); i2++)
					{
						if (o.pars[i] == act.indexes[i2])
						{
							o.pars[i] = i2;
							if (o.maxpar < (long)i2) o.maxpar = i2;
							break;
						}
					}
				}
			}
			//--
			convaction(act, pars, out, invs, pvars);
		}
	}
	//-------------------------------------------------------------------------------------
	pddlparser::pddlparser(std::string dfname, std::string pfname)
	{
		falha = false;
		{
			std::ifstream fin(dfname, std::ios::in);
			if (!fin) {
				falha = true;
			}
			else {
				dm.readstream(fin);
			}
		}
		{
			std::ifstream fin(pfname, std::ios::in);
			if (!fin) {
				falha = true;
			}
			else {
				pb.readstream(fin);
			}
		}
	}
	//-------------------------------------------------------------------------------------
	planners::problem pddlparser::generateproblem(planners::varlist& vlist)
	{
		vlist = getfacts();
		planners::problem prob(vlist);

		std::vector<std::string> inv, facts;
		bool neg = false;
		parseexpression(pb.init, inv, facts, neg);

		invariants = std::move(inv);
		std::sort(invariants.begin(), invariants.end(), [](const std::string&a, const std::string&b){return _stricmp(a.c_str(), b.c_str()) < 0; });
		prob.setinit(facts);
		neg = false; inv.clear(); facts.clear();
		parseexpression(pb.goal, inv, facts, neg);
		prob.setgoal(facts);

		prob.setaddrelevant(true);

		convactions(prob);

		return prob;
	}
	//-------------------------------------------------------------------------------------
};