#include <iostream>
#include "varset.h"
#include "action.h"
#include "problem.h"
#include "planners.h"
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <cstdarg>
#include <cstdio>
#include <fstream>
#include "pddl.h"

using namespace planners;

std::string strformat(const char* fmtstr, ...)
{
	std::string a_string;
	va_list vl;
	va_start(vl, fmtstr);
	int size = _vscprintf(fmtstr, vl);
	a_string.resize(size++);
	vsnprintf_s((char*)a_string.data(), size, _TRUNCATE, fmtstr, vl);
	va_end(vl);
	return a_string;
}

varlist declareVars(int cx, int cy, int cz, int nbloco1, int nbloco2 = 0, int nbloco3 = 0)
{
	//varlist vars;// (/*(nbloco1 + nbloco2 + nbloco3)*(1 + cx*cy*cz)*/);
	std::vector<std::string> vars;
	vars.reserve((nbloco1 + nbloco2 + nbloco3)*(1 + cx*cy*cz));
	int i;
	for (i = 1; i <= nbloco1; i++)
	{
		vars.push_back(strformat("peca_c1n%d_livre", i));
	}
	for (i = 1; i <= nbloco2; i++)
	{
		vars.push_back(strformat("peca_c2n%d_livre", i));
	}
	for (i = 1; i <= nbloco3; i++)
	{
		vars.push_back(strformat("peca_c3n%d_livre", i));
	}
    for (int x=1;x<=cx;x++)
	{
        for (int y=1; y<=cy; y++)
		{
            for (int z=1; z<=cz; z++)
			{
				vars.push_back(strformat("lugar_x%dy%dz%d_livre", x, y, z));
				for (i = 1; i <= nbloco1; i++)
					vars.push_back(strformat("peca_c1n%d_x%dy%dz%d", i, x, y, z));
				for (i = 1; i <= nbloco2; i++)
					vars.push_back(strformat("peca_c2n%d_x%dy%dz%d", i, x, y, z));
				for (i = 1; i <= nbloco3; i++)
					vars.push_back(strformat("peca_c3n%d_x%dy%dz%d", i, x, y, z));
            }
        }
    }
	varlist vlist;
	vlist.add(vars);
	return vlist;
}

void declareActions(problem& prob, int Cx, int Cy, int Cz, int nbloco1, int nbloco2 = 0, int nbloco3 = 0) {
    for (int x=1;x<=Cx;x++) {
        for (int y=1; y<=Cy; y++) {            
            for (int z=1; z<=Cz; z++) {
				for (int i = 1; i <= nbloco1; i++) {
					action act(strformat("move_pc1n%d_x%dy%dz%d", i, x, y, z),prob.getvarlist());
					if (z == 1)
						act.setpreconditions({ strformat("peca_c1n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z) });
					else
						act.setpreconditions({ strformat("peca_c1n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("!lugar_x%dy%dz%d_livre", x, y, z - 1) });
					act.setadd({ strformat("peca_c1n%d_x%dy%dz%d", i, x, y, z) });
					act.setdelete({ strformat("peca_c1n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z) });
					prob.addaction(act);
                }
				// 2x1x1
				for (int i = 1; i <= nbloco2; i++) {
					if (x<Cx) {
						action act(strformat("move_r1_pc2n%d_x%dy%dz%d", i, x, y, z),prob.getvarlist());
						if (z == 1)
							act.setpreconditions({ strformat("peca_c2n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z) });
						else
							act.setpreconditions({ strformat("peca_c2n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z), strformat("!lugar_x%dy%dz%d_livre", x, y, z - 1), strformat("!lugar_x%dy%dz%d_livre", x + 1, y, z - 1) });
						act.setadd({ strformat("peca_c2n%d_x%dy%dz%d", i, x, y, z), strformat("peca_c2n%d_x%dy%dz%d", i, x + 1, y, z) });
						act.setdelete({ strformat("peca_c2n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z) });
						prob.addaction(act);
					}
					if (y<Cy) {
						action act(strformat("move_r2_pc2n%d_x%dy%dz%d", i, x, y, z), prob.getvarlist());
						if (z == 1)
							act.setpreconditions({ strformat("peca_c2n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z) });
						else
							act.setpreconditions({ strformat("peca_c2n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z), strformat("!lugar_x%dy%dz%d_livre", x, y, z - 1), strformat("!lugar_x%dy%dz%d_livre", x, y + 1, z - 1) });
						act.setadd({ strformat("peca_c2n%d_x%dy%dz%d", i, x, y, z), strformat("peca_c2n%d_x%dy%dz%d", i, x, y + 1, z) });
						act.setdelete({ strformat("peca_c2n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z) });
						prob.addaction(act);
					}
					if (z<Cz) {
						action act(strformat("move_r3_pc2n%d_x%dy%dz%d", i, x, y, z), prob.getvarlist());
						if (z == 1)
							act.setpreconditions({ strformat("peca_c2n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y, z + 1) });
						else
							act.setpreconditions({ strformat("peca_c2n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y, z + 1), strformat("!lugar_x%dy%dz%d_livre", x, y, z - 1) });
						act.setadd({ strformat("peca_c2n%d_x%dy%dz%d", i, x, y, z), strformat("peca_c2n%d_x%dy%dz%d", i, x, y, z + 1) });
						act.setdelete({ strformat("peca_c2n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y, z + 1) });
						prob.addaction(act);
					}
				}
				// Peça 2x2x1
				for (int i = 1; i <= nbloco3; i++) {
					if (x<Cx && y<Cy) {
						action act(strformat("move_r1_pc3n%d_x%dy%dz%d", i, x, y, z), prob.getvarlist());
						if (z == 1)
							act.setpreconditions({ strformat("peca_c3n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y + 1, z) });
						else
							act.setpreconditions({ strformat("peca_c3n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y + 1, z), strformat("!lugar_x%dy%dz%d_livre", x, y, z - 1), strformat("!lugar_x%dy%dz%d_livre", x + 1, y, z - 1), strformat("!lugar_x%dy%dz%d_livre", x, y + 1, z - 1), strformat("!lugar_x%dy%dz%d_livre", x + 1, y + 1, z - 1) });
						act.setadd({ strformat("peca_c3n%d_x%dy%dz%d", i, x, y, z), strformat("peca_c3n%d_x%dy%dz%d", i, x + 1, y, z), strformat("peca_c3n%d_x%dy%dz%d", i, x, y + 1, z), strformat("peca_c3n%d_x%dy%dz%d", i, x + 1, y + 1, z) });
						act.setdelete({ strformat("peca_c3n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y + 1, z) });
						prob.addaction(act);
					}
					if (z<Cz && x<Cx) {
						action act(strformat("move_r2_pc3n%d_x%dy%dz%d", i, x, y, z), prob.getvarlist());
						if (z == 1)
							act.setpreconditions({ strformat("peca_c3n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y, z + 1), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z + 1) });
						else
							act.setpreconditions({ strformat("peca_c3n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y, z + 1), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z + 1), strformat("!lugar_x%dy%dz%d_livre", x, y, z - 1), strformat("!lugar_x%dy%dz%d_livre", x + 1, y, z - 1) });
						act.setadd({ strformat("peca_c3n%d_x%dy%dz%d", i, x, y, z), strformat("peca_c3n%d_x%dy%dz%d", i, x, y, z + 1), strformat("peca_c3n%d_x%dy%dz%d", i, x + 1, y, z), strformat("peca_c3n%d_x%dy%dz%d", i, x + 1, y, z + 1) });
						act.setdelete({ strformat("peca_c3n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y, z + 1), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z), strformat("lugar_x%dy%dz%d_livre", x + 1, y, z + 1) });
						prob.addaction(act);
					}
					if (z<Cz && y<Cy) {
						action act(strformat("move_r3_pc3n%d_x%dy%dz%d", i, x, y, z), prob.getvarlist());
						if (z == 1)
							act.setpreconditions({ strformat("peca_c3n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y, z + 1), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z + 1) });
						else
							act.setpreconditions({ strformat("peca_c3n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y, z + 1), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z + 1), strformat("!lugar_x%dy%dz%d_livre", x, y, z - 1), strformat("!lugar_x%dy%dz%d_livre", x, y + 1, z - 1) });
						act.setadd({ strformat("peca_c3n%d_x%dy%dz%d", i, x, y, z), strformat("peca_c3n%d_x%dy%dz%d", i, x, y, z + 1), strformat("peca_c3n%d_x%dy%dz%d", i, x, y + 1, z), strformat("peca_c3n%d_x%dy%dz%d", i, x, y + 1, z + 1) });
						act.setdelete({ strformat("peca_c3n%d_livre", i), strformat("lugar_x%dy%dz%d_livre", x, y, z), strformat("lugar_x%dy%dz%d_livre", x, y, z + 1), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z), strformat("lugar_x%dy%dz%d_livre", x, y + 1, z + 1) });
						prob.addaction(act);
					}
				}
            }
        }
    }
    
}

void declareStartAndGoal(problem& prob, int Cx, int Cy, int Cz, int nbloco1, int nbloco2, int nbloco3) {
	std::vector<std::string> vars;
	for (int i = 1; i <= nbloco1; i++) {
		vars.push_back(strformat("peca_c1n%d_livre", i));
	}
	for (int i = 1; i <= nbloco2; i++) {
		vars.push_back(strformat("peca_c2n%d_livre", i));
	}
	for (int i = 1; i <= nbloco3; i++) {
		vars.push_back(strformat("peca_c3n%d_livre", i));
	}
	for (int x = 1; x <= Cx; x++) {
		for (int y = 1; y <= Cy; y++) {
			for (int z = 1; z <= Cz; z++) {
				vars.push_back(strformat("lugar_x%dy%dz%d_livre", x, y, z));
			}
		}
	}
	prob.setinit(vars);

	std::vector<std::string> vars2;
#if (__PROBLEM__ == 1)
	vars2.push_back(strformat("peca_c1n1_x1y1z1"));
	vars2.push_back(strformat("peca_c1n2_x2y1z1"));
	vars2.push_back(strformat("peca_c1n3_x1y2z1"));
	vars2.push_back(strformat("peca_c1n4_x2y2z1"));
	vars2.push_back(strformat("peca_c1n5_x1y1z2"));
	vars2.push_back(strformat("peca_c1n6_x2y1z2"));
	vars2.push_back(strformat("peca_c1n7_x1y2z2"));
	vars2.push_back(strformat("peca_c1n8_x2y2z2"));
#elif (__PROBLEM__ == 2)
	vars2.push_back(strformat("peca_c2n1_x1y1z1"));
	vars2.push_back(strformat("peca_c2n1_x2y1z1"));
	vars2.push_back(strformat("peca_c2n2_x1y2z1"));
	vars2.push_back(strformat("peca_c2n2_x2y2z1"));
	vars2.push_back(strformat("peca_c2n3_x1y3z1"));
	vars2.push_back(strformat("peca_c2n3_x2y3z1"));
#elif (__PROBLEM__ == 3)
	vars2.push_back(strformat("peca_c1n1_x5y1z1"));
	vars2.push_back(strformat("peca_c1n2_x1y2z1"));
	vars2.push_back(strformat("peca_c1n3_x2y2z1"));
	vars2.push_back(strformat("peca_c1n4_x3y2z1"));
	vars2.push_back(strformat("peca_c1n5_x4y2z1"));    
	vars2.push_back(strformat("peca_c2n1_x1y1z1"));
	vars2.push_back(strformat("peca_c2n1_x2y1z1"));
	vars2.push_back(strformat("peca_c2n2_x3y1z1"));
	vars2.push_back(strformat("peca_c2n2_x4y1z1"));
	vars2.push_back(strformat("peca_c2n3_x4y3z1"));
	vars2.push_back(strformat("peca_c2n3_x5y3z1"));
	vars2.push_back(strformat("peca_c2n4_x3y5z1"));
	vars2.push_back(strformat("peca_c2n4_x4y5z1"));    
	vars2.push_back(strformat("peca_c2n5_x2y3z1"));
	vars2.push_back(strformat("peca_c2n5_x2y3z2"));
#elif (__PROBLEM__ == 4)
	vars2.push_back(strformat("peca_c2n1_x2y3z1"));
	vars2.push_back(strformat("peca_c2n1_x3y3z1"));
	vars2.push_back(strformat("peca_c2n2_x1y1z3"));
	vars2.push_back(strformat("peca_c2n2_x2y1z3"));
	vars2.push_back(strformat("peca_c2n3_x3y1z3"));
	vars2.push_back(strformat("peca_c2n3_x3y2z3"));
	vars2.push_back(strformat("peca_c2n4_x1y2z3"));
	vars2.push_back(strformat("peca_c2n4_x1y3z3"));
	vars2.push_back(strformat("peca_c2n5_x1y1z1"));
	vars2.push_back(strformat("peca_c2n5_x1y1z2"));
	vars2.push_back(strformat("peca_c2n6_x2y1z1"));
	vars2.push_back(strformat("peca_c2n6_x2y1z2"));
	vars2.push_back(strformat("peca_c2n7_x3y1z1"));
	vars2.push_back(strformat("peca_c2n7_x3y1z2"));
	vars2.push_back(strformat("peca_c2n8_x1y2z1"));
	vars2.push_back(strformat("peca_c2n8_x1y2z2"));
	vars2.push_back(strformat("peca_c2n9_x2y2z1"));
	vars2.push_back(strformat("peca_c2n9_x2y2z2"));
	vars2.push_back(strformat("peca_c2n10_x3y2z1"));
	vars2.push_back(strformat("peca_c2n10_x3y2z2"));
	vars2.push_back(strformat("peca_c2n11_x1y3z1"));
	vars2.push_back(strformat("peca_c2n11_x1y3z2"));
	vars2.push_back(strformat("peca_c2n12_x2y3z2"));
	vars2.push_back(strformat("peca_c2n12_x2y3z3"));
	vars2.push_back(strformat("peca_c2n13_x3y3z2"));
	vars2.push_back(strformat("peca_c2n13_x3y3z3"));
#elif (__PROBLEM__ == 5)
	vars2.push_back(strformat("peca_c1n1_x4y1z5"));
	vars2.push_back(strformat("peca_c1n2_x2y2z5"));
	vars2.push_back(strformat("peca_c1n3_x7y5z5"));
	vars2.push_back(strformat("peca_c1n4_x10y5z5"));
	vars2.push_back(strformat("peca_c2n1_x2y1z5")); vars2.push_back(strformat("peca_c2n1_x3y1z5"));
	vars2.push_back(strformat("peca_c2n2_x1y3z5")); vars2.push_back(strformat("peca_c2n2_x2y3z5"));
	vars2.push_back(strformat("peca_c2n3_x5y5z5")); vars2.push_back(strformat("peca_c2n3_x6y5z5"));
	vars2.push_back(strformat("peca_c2n4_x8y5z5")); vars2.push_back(strformat("peca_c2n4_x9y5z5"));
	vars2.push_back(strformat("peca_c2n5_x1y1z5")); vars2.push_back(strformat("peca_c2n5_x1y2z5"));
	vars2.push_back(strformat("peca_c2n6_x4y1z1")); vars2.push_back(strformat("peca_c2n6_x4y1z2"));
	vars2.push_back(strformat("peca_c2n7_x2y2z1")); vars2.push_back(strformat("peca_c2n7_x2y2z2"));
	vars2.push_back(strformat("peca_c2n8_x7y5z1")); vars2.push_back(strformat("peca_c2n8_x7y5z2"));
	vars2.push_back(strformat("peca_c2n9_x10y5z1")); vars2.push_back(strformat("peca_c2n9_x10y5z2"));
	vars2.push_back(strformat("peca_c2n10_x8y1z2")); vars2.push_back(strformat("peca_c2n10_x8y1z3"));
	vars2.push_back(strformat("peca_c2n11_x10y2z2")); vars2.push_back(strformat("peca_c2n11_x10y2z3"));
	vars2.push_back(strformat("peca_c2n12_x4y1z3")); vars2.push_back(strformat("peca_c2n12_x4y1z4"));
	vars2.push_back(strformat("peca_c2n13_x2y2z3")); vars2.push_back(strformat("peca_c2n13_x2y2z4"));
	vars2.push_back(strformat("peca_c2n14_x7y5z3")); vars2.push_back(strformat("peca_c2n14_x7y5z4"));
	vars2.push_back(strformat("peca_c2n15_x10y5z3")); vars2.push_back(strformat("peca_c2n15_x10y5z4"));
	vars2.push_back(strformat("peca_c3n1_x7y1z1")); vars2.push_back(strformat("peca_c3n1_x7y2z1")); vars2.push_back(strformat("peca_c3n1_x8y1z1")); vars2.push_back(strformat("peca_c3n1_x8y2z1"));
	vars2.push_back(strformat("peca_c3n2_x9y1z1")); vars2.push_back(strformat("peca_c3n2_x9y2z1")); vars2.push_back(strformat("peca_c3n2_x10y1z1")); vars2.push_back(strformat("peca_c3n2_x10y2z1")); // x2y2z1
	vars2.push_back(strformat("peca_c3n3_x3y2z1")); vars2.push_back(strformat("peca_c3n3_x3y3z1")); vars2.push_back(strformat("peca_c3n3_x4y2z1")); vars2.push_back(strformat("peca_c3n3_x4y3z1"));
	vars2.push_back(strformat("peca_c3n4_x3y4z3")); vars2.push_back(strformat("peca_c3n4_x3y5z3")); vars2.push_back(strformat("peca_c3n4_x4y4z3")); vars2.push_back(strformat("peca_c3n4_x4y5z3"));
	vars2.push_back(strformat("peca_c3n5_x3y4z4")); vars2.push_back(strformat("peca_c3n5_x3y5z4")); vars2.push_back(strformat("peca_c3n5_x4y4z4")); vars2.push_back(strformat("peca_c3n5_x4y5z4"));
	vars2.push_back(strformat("peca_c3n6_x5y1z5")); vars2.push_back(strformat("peca_c3n6_x5y2z5")); vars2.push_back(strformat("peca_c3n6_x6y1z5")); vars2.push_back(strformat("peca_c3n6_x6y2z5"));
	vars2.push_back(strformat("peca_c3n7_x5y3z5")); vars2.push_back(strformat("peca_c3n7_x5y4z5")); vars2.push_back(strformat("peca_c3n7_x6y3z5")); vars2.push_back(strformat("peca_c3n7_x6y4z5"));
	vars2.push_back(strformat("peca_c3n8_x7y3z5")); vars2.push_back(strformat("peca_c3n8_x7y4z5")); vars2.push_back(strformat("peca_c3n8_x8y3z5")); vars2.push_back(strformat("peca_c3n8_x8y4z5"));
	vars2.push_back(strformat("peca_c3n9_x9y3z5")); vars2.push_back(strformat("peca_c3n9_x9y4z5")); vars2.push_back(strformat("peca_c3n9_x10y3z5")); vars2.push_back(strformat("peca_c3n9_x10y4z5"));
	vars2.push_back(strformat("peca_c3n10_x1y4z5")); vars2.push_back(strformat("peca_c3n10_x1y5z5")); vars2.push_back(strformat("peca_c3n10_x2y4z5")); vars2.push_back(strformat("peca_c3n10_x2y5z5"));
	vars2.push_back(strformat("peca_c3n11_x3y4z5")); vars2.push_back(strformat("peca_c3n11_x3y5z5")); vars2.push_back(strformat("peca_c3n11_x4y4z5")); vars2.push_back(strformat("peca_c3n11_x4y5z5"));

	vars2.push_back(strformat("peca_c3n12_x1y1z1")); vars2.push_back(strformat("peca_c3n12_x1y2z1")); vars2.push_back(strformat("peca_c3n12_x1y1z2")); vars2.push_back(strformat("peca_c3n12_x1y2z2")); // x1y2z2
	vars2.push_back(strformat("peca_c3n13_x5y2z1")); vars2.push_back(strformat("peca_c3n13_x5y2z2")); vars2.push_back(strformat("peca_c3n13_x5y3z1")); vars2.push_back(strformat("peca_c3n13_x5y3z2"));
	vars2.push_back(strformat("peca_c3n14_x6y2z1")); vars2.push_back(strformat("peca_c3n14_x6y3z1")); vars2.push_back(strformat("peca_c3n14_x6y2z2")); vars2.push_back(strformat("peca_c3n14_x6y3z2"));
	vars2.push_back(strformat("peca_c3n15_x3y4z1")); vars2.push_back(strformat("peca_c3n15_x3y5z1")); vars2.push_back(strformat("peca_c3n15_x3y4z2")); vars2.push_back(strformat("peca_c3n15_x3y5z2"));
	vars2.push_back(strformat("peca_c3n16_x4y4z1")); vars2.push_back(strformat("peca_c3n16_x4y5z1")); vars2.push_back(strformat("peca_c3n16_x4y4z2")); vars2.push_back(strformat("peca_c3n16_x4y5z2"));
	vars2.push_back(strformat("peca_c3n17_x7y1z2")); vars2.push_back(strformat("peca_c3n17_x7y2z2")); vars2.push_back(strformat("peca_c3n17_x7y1z3")); vars2.push_back(strformat("peca_c3n17_x7y2z3"));
	vars2.push_back(strformat("peca_c3n18_x3y2z2")); vars2.push_back(strformat("peca_c3n18_x3y3z2")); vars2.push_back(strformat("peca_c3n18_x3y2z3")); vars2.push_back(strformat("peca_c3n18_x3y3z3"));
	vars2.push_back(strformat("peca_c3n19_x4y2z2")); vars2.push_back(strformat("peca_c3n19_x4y3z2")); vars2.push_back(strformat("peca_c3n19_x4y2z3")); vars2.push_back(strformat("peca_c3n19_x4y3z3"));
	vars2.push_back(strformat("peca_c3n20_x1y1z3")); vars2.push_back(strformat("peca_c3n20_x1y2z3")); vars2.push_back(strformat("peca_c3n20_x1y1z4")); vars2.push_back(strformat("peca_c3n20_x1y2z4"));
	vars2.push_back(strformat("peca_c3n21_x5y1z3")); vars2.push_back(strformat("peca_c3n21_x5y2z3")); vars2.push_back(strformat("peca_c3n21_x5y1z4")); vars2.push_back(strformat("peca_c3n21_x5y2z4"));
	vars2.push_back(strformat("peca_c3n22_x6y1z3")); vars2.push_back(strformat("peca_c3n22_x6y2z3")); vars2.push_back(strformat("peca_c3n22_x6y1z4")); vars2.push_back(strformat("peca_c3n22_x6y2z4"));
	vars2.push_back(strformat("peca_c3n23_x5y3z3")); vars2.push_back(strformat("peca_c3n23_x5y4z3")); vars2.push_back(strformat("peca_c3n23_x5y3z4")); vars2.push_back(strformat("peca_c3n23_x5y4z4"));
	vars2.push_back(strformat("peca_c3n24_x6y3z3")); vars2.push_back(strformat("peca_c3n24_x6y4z3")); vars2.push_back(strformat("peca_c3n24_x6y3z4")); vars2.push_back(strformat("peca_c3n24_x6y4z4"));
	vars2.push_back(strformat("peca_c3n25_x9y1z4")); vars2.push_back(strformat("peca_c3n25_x9y2z4")); vars2.push_back(strformat("peca_c3n25_x9y1z5")); vars2.push_back(strformat("peca_c3n25_x9y2z5"));
	vars2.push_back(strformat("peca_c3n26_x10y1z4")); vars2.push_back(strformat("peca_c3n26_x10y2z4")); vars2.push_back(strformat("peca_c3n26_x10y1z5")); vars2.push_back(strformat("peca_c3n26_x10y2z5"));
	vars2.push_back(strformat("peca_c3n27_x3y2z4")); vars2.push_back(strformat("peca_c3n27_x3y3z4")); vars2.push_back(strformat("peca_c3n27_x3y2z5")); vars2.push_back(strformat("peca_c3n27_x3y3z5"));
	vars2.push_back(strformat("peca_c3n28_x4y2z4")); vars2.push_back(strformat("peca_c3n28_x4y3z4")); vars2.push_back(strformat("peca_c3n28_x4y2z5")); vars2.push_back(strformat("peca_c3n28_x4y3z5"));

	vars2.push_back(strformat("peca_c3n29_x2y1z1")); vars2.push_back(strformat("peca_c3n29_x3y1z1")); vars2.push_back(strformat("peca_c3n29_x2y1z2")); vars2.push_back(strformat("peca_c3n29_x3y1z2")); // x2y1z2
	vars2.push_back(strformat("peca_c3n30_x5y1z1")); vars2.push_back(strformat("peca_c3n30_x6y1z1")); vars2.push_back(strformat("peca_c3n30_x5y1z2")); vars2.push_back(strformat("peca_c3n30_x6y1z2"));
	vars2.push_back(strformat("peca_c3n31_x1y3z1")); vars2.push_back(strformat("peca_c3n31_x2y3z1")); vars2.push_back(strformat("peca_c3n31_x1y3z2")); vars2.push_back(strformat("peca_c3n31_x2y3z2"));
	vars2.push_back(strformat("peca_c3n32_x7y3z1")); vars2.push_back(strformat("peca_c3n32_x8y3z1")); vars2.push_back(strformat("peca_c3n32_x7y3z2")); vars2.push_back(strformat("peca_c3n32_x8y3z2"));
	vars2.push_back(strformat("peca_c3n33_x9y3z1")); vars2.push_back(strformat("peca_c3n33_x10y3z1")); vars2.push_back(strformat("peca_c3n33_x9y3z2")); vars2.push_back(strformat("peca_c3n33_x10y3z2"));
	vars2.push_back(strformat("peca_c3n34_x1y4z1")); vars2.push_back(strformat("peca_c3n34_x2y4z1")); vars2.push_back(strformat("peca_c3n34_x1y4z2")); vars2.push_back(strformat("peca_c3n34_x2y4z2"));
	vars2.push_back(strformat("peca_c3n35_x5y4z1")); vars2.push_back(strformat("peca_c3n35_x6y4z1")); vars2.push_back(strformat("peca_c3n35_x5y4z2")); vars2.push_back(strformat("peca_c3n35_x6y4z2"));
	vars2.push_back(strformat("peca_c3n36_x7y4z1")); vars2.push_back(strformat("peca_c3n36_x8y4z1")); vars2.push_back(strformat("peca_c3n36_x7y4z2")); vars2.push_back(strformat("peca_c3n36_x8y4z2"));
	vars2.push_back(strformat("peca_c3n37_x9y4z1")); vars2.push_back(strformat("peca_c3n37_x10y4z1")); vars2.push_back(strformat("peca_c3n37_x9y4z2")); vars2.push_back(strformat("peca_c3n37_x10y4z2"));
	vars2.push_back(strformat("peca_c3n38_x1y5z1")); vars2.push_back(strformat("peca_c3n38_x2y5z1")); vars2.push_back(strformat("peca_c3n38_x1y5z2")); vars2.push_back(strformat("peca_c3n38_x2y5z2"));
	vars2.push_back(strformat("peca_c3n39_x5y5z1")); vars2.push_back(strformat("peca_c3n39_x6y5z1")); vars2.push_back(strformat("peca_c3n39_x5y5z2")); vars2.push_back(strformat("peca_c3n39_x6y5z2"));
	vars2.push_back(strformat("peca_c3n40_x8y5z1")); vars2.push_back(strformat("peca_c3n40_x9y5z1")); vars2.push_back(strformat("peca_c3n40_x8y5z2")); vars2.push_back(strformat("peca_c3n40_x9y5z2"));
	vars2.push_back(strformat("peca_c3n41_x9y1z2")); vars2.push_back(strformat("peca_c3n41_x10y1z2")); vars2.push_back(strformat("peca_c3n41_x9y1z3")); vars2.push_back(strformat("peca_c3n41_x10y1z3"));
	vars2.push_back(strformat("peca_c3n42_x8y2z2")); vars2.push_back(strformat("peca_c3n42_x9y2z2")); vars2.push_back(strformat("peca_c3n42_x8y2z3")); vars2.push_back(strformat("peca_c3n42_x9y2z3"));
	vars2.push_back(strformat("peca_c3n43_x2y1z3")); vars2.push_back(strformat("peca_c3n43_x3y1z3")); vars2.push_back(strformat("peca_c3n43_x2y1z4")); vars2.push_back(strformat("peca_c3n43_x3y1z4"));
	vars2.push_back(strformat("peca_c3n44_x1y3z3")); vars2.push_back(strformat("peca_c3n44_x2y3z3")); vars2.push_back(strformat("peca_c3n44_x1y3z4")); vars2.push_back(strformat("peca_c3n44_x2y3z4"));
	vars2.push_back(strformat("peca_c3n45_x7y3z3")); vars2.push_back(strformat("peca_c3n45_x8y3z3")); vars2.push_back(strformat("peca_c3n45_x7y3z4")); vars2.push_back(strformat("peca_c3n45_x8y3z4"));
	vars2.push_back(strformat("peca_c3n46_x9y3z3")); vars2.push_back(strformat("peca_c3n46_x10y3z3")); vars2.push_back(strformat("peca_c3n46_x9y3z4")); vars2.push_back(strformat("peca_c3n46_x10y3z4"));
	vars2.push_back(strformat("peca_c3n47_x1y4z3")); vars2.push_back(strformat("peca_c3n47_x2y4z3")); vars2.push_back(strformat("peca_c3n47_x1y4z4")); vars2.push_back(strformat("peca_c3n47_x2y4z4"));
	vars2.push_back(strformat("peca_c3n48_x7y4z3")); vars2.push_back(strformat("peca_c3n48_x8y4z3")); vars2.push_back(strformat("peca_c3n48_x7y4z4")); vars2.push_back(strformat("peca_c3n48_x8y4z4"));
	vars2.push_back(strformat("peca_c3n49_x9y4z3")); vars2.push_back(strformat("peca_c3n49_x10y4z3")); vars2.push_back(strformat("peca_c3n49_x9y4z4")); vars2.push_back(strformat("peca_c3n49_x10y4z4"));
	vars2.push_back(strformat("peca_c3n50_x1y5z3")); vars2.push_back(strformat("peca_c3n50_x2y5z3")); vars2.push_back(strformat("peca_c3n50_x1y5z4")); vars2.push_back(strformat("peca_c3n50_x2y5z4"));
	vars2.push_back(strformat("peca_c3n51_x5y5z3")); vars2.push_back(strformat("peca_c3n51_x6y5z3")); vars2.push_back(strformat("peca_c3n51_x5y5z4")); vars2.push_back(strformat("peca_c3n51_x6y5z4"));
	vars2.push_back(strformat("peca_c3n52_x8y5z3")); vars2.push_back(strformat("peca_c3n52_x9y5z3")); vars2.push_back(strformat("peca_c3n52_x8y5z4")); vars2.push_back(strformat("peca_c3n52_x9y5z4"));
	vars2.push_back(strformat("peca_c3n53_x7y1z4")); vars2.push_back(strformat("peca_c3n53_x8y1z4")); vars2.push_back(strformat("peca_c3n53_x7y1z5")); vars2.push_back(strformat("peca_c3n53_x8y1z5"));
	vars2.push_back(strformat("peca_c3n54_x7y2z4")); vars2.push_back(strformat("peca_c3n54_x8y2z4")); vars2.push_back(strformat("peca_c3n54_x7y2z5")); vars2.push_back(strformat("peca_c3n54_x8y2z5"));
#endif

	for (int i = 1; i <= nbloco1; i++) {
		vars2.push_back(strformat("!peca_c1n%d_livre", i));
	}
	for (int i = 1; i <= nbloco2; i++) {
		vars2.push_back(strformat("!peca_c2n%d_livre", i));
	}
	for (int i = 1; i <= nbloco3; i++) {
		vars2.push_back(strformat("!peca_c3n%d_livre", i));
	}
	bool found = false;
	for (int x = 1; x <= Cx; x++) {
		for (int y = 1; y <= Cy; y++) {
			for (int z = 1; z <= Cz; z++) {
				found = false;
				for (int i = 1; i <= nbloco1; i++) {
					std::string str = strformat("peca_c1n%d_x%dy%dz%d", i, x, y, z);
					if (std::find(vars2.begin(), vars2.end(), str) == vars2.end()) {
						vars2.push_back('!' + str);
					}
					else {
						if (found) std::cout << "Duplicata em " << str << std::endl;
						found = true;
					}
				}
				for (int i = 1; i <= nbloco2; i++) {
					std::string str = strformat("peca_c2n%d_x%dy%dz%d", i, x, y, z);
					if (std::find(vars2.begin(), vars2.end(), str) == vars2.end()) {
						vars2.push_back('!' + str);
					}
					else {
						if (found) std::cout << "Duplicata em " << str << std::endl;
						found = true;
					}
				}
				for (int i = 1; i <= nbloco3; i++) {
					std::string str = strformat("peca_c3n%d_x%dy%dz%d", i, x, y, z);
					if (std::find(vars2.begin(), vars2.end(), str) == vars2.end()) {
						vars2.push_back('!' + str);
					}
					else {
						if (found) std::cout << "Duplicata em " << str << std::endl;
						found = true;
					}
				}
			}
		}
	}
	prob.setgoal(vars2);
}

void ajuda() {
	std::cout << std::endl
		<< "PlanejadorEstoque interno [1 - 5]" << std::endl
		<< "    Executa os problemas embutidos de 1 a 5." << std::endl
	    << std::endl
		<< "PlanejadorEstoque externo [domínio] [problema]" << std::endl
		<< "    Executa o algorítmo aplicado os problema descrito pelos arquivos PDDL" << std::endl
		<< "    [domínio] e [problema]." << std::endl
	    << std::endl;
}

int prob_interno(int problema, bool use_relevant = USE_RELEVANT);
int prob_externo(std::string dominio, std::string problema);

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cerr << "Comando não informado!" << std::endl;
		ajuda();
		return 1;
	}
	std::string comando = argv[1];
	if (comando == "interno") {
		if (argc != 3) {
			std::cerr << "Número de parâmetros inválido!" << std::endl;
			ajuda();
			return 1;
		}
		std::string problema = argv[2];
		int prob_num = std::stoi(problema);
		return prob_interno(prob_num);
	}
	else if (comando == "externo") {
		if (argc != 4) {
			std::cerr << "Número de parâmetros inválido!" << std::endl;
			ajuda();
			return 1;
		}
		return prob_externo(argv[2], argv[3]);
	} else {
		std::cerr << "Comando não informado!" << std::endl;
		ajuda();
		return 1;
	}
}

int prob_externo(std::string dominio, std::string problema)
{
	long startTime, endTime, pddlTime;
	std::cout << "Interpretando arquivos de domínio e problema..." << std::endl;
	pddl::pddlparser parser(dominio, problema);
	if (!parser) {
		std::cerr << "Erro ao carregar arquivos de domínio e problema!" << std::endl;
		return 2;
	}
	startTime = clock();
	varlist vlist;

	std::cout << "Gerando problema..." << std::endl;
	problem prob(parser.generateproblem(vlist));
	pddlTime = clock();
	planner* plan = new localsearchplanner(prob);
	pnode* tree = plan->plan();
	endTime = clock();

	std::cout << "Numero de estados: " << plan->getroot()->getnumstates() << std::endl << std::endl;
	if (tree != NULL) {
		std::cout << (tree->getplanstring()) << std::endl;
	}

	std::cout << "Tempo total: " << 1000.0*(endTime*1.0 - startTime) / CLOCKS_PER_SEC << " ms" << std::endl;
	std::cout << "Tempo do processamento do PDDL: " << 1000.0*(pddlTime * 1.0 - startTime) / CLOCKS_PER_SEC << " ms" << std::endl;
	std::cout << "Tempo do algoritmo de busca: " << 1000.0*(endTime * 1.0 - pddlTime) / CLOCKS_PER_SEC << " ms" << std::endl;

	std::ofstream log("log.txt");
	if (tree) log << "Estado final    : " << tree->getstate() << std::endl;
	log << "Estado objetivo : " << prob.getgoal() << std::endl;

	log.close();

	std::cin.get();
	delete plan;
	return 0;
}

int prob_interno(int problema, bool use_relevant)
{
	long startTime, endTime, varTime, sgTime, actTime;
    startTime = clock();
	int nbloco1 = 0, nbloco2 = 0, nbloco3 = 0;
	int cX = 0, cY = 0, cZ = 0;

	if (problema == 1) {
		nbloco1 = 8;
		nbloco2 = 0;
		nbloco3 = 0;
		cX = 2;
		cY = 2;
		cZ = 2;
	}
	else if (problema == 2) {
		nbloco1 = 0;
		nbloco2 = 3;
		nbloco3 = 0;
		cX = 4;
		cY = 4;
		cZ = 4;
	}
	else if (problema == 3) {
		nbloco1 = 5;
		nbloco2 = 5;
		nbloco3 = 0;
		cX = 5;
		cY = 5;
		cZ = 2;
	}
	else if (problema == 4) {
		nbloco1 = 0;
		nbloco2 = 13;
		nbloco3 = 0;
		cX = 3;
		cY = 3;
		cZ = 3;
	}
	else if (problema == 5) {
		nbloco1 = 4;
		nbloco2 = 15;
		nbloco3 = 54;
		cX = 10;
		cY = 5;
		cZ = 5;
	}
	else {
		std::cerr << "ERRO: Problema " << problema << " não é válido!" << std::endl;
		return 1;
	}
	varlist vlist = declareVars(cX, cY, cZ, nbloco1, nbloco2, nbloco3);
	varTime = clock();
	problem prob(vlist);
	declareStartAndGoal(prob, cX, cY, cZ, nbloco1, nbloco2, nbloco3);
	sgTime = clock();
	if (use_relevant) {
		prob.setaddrelevant(true);
	}
	declareActions(prob, cX, cY, cZ, nbloco1, nbloco2, nbloco3);
	actTime = clock();

	planner* plan = new localsearchplanner(prob);
	pnode* tree = plan->plan();

	endTime = clock();

	std::cout << "Numero de estados: " << plan->getroot()->getnumstates() << std::endl << std::endl;
	if (tree != NULL) {
		std::cout << (tree->getplanstring()) << std::endl;
	}

    
	std::cout << "Tempo total: " << 1000.0*(endTime*1.0 - startTime)/CLOCKS_PER_SEC << " ms" << std::endl;
	std::cout << "Tempo de declaração de variáveis : " << 1000.0*(varTime * 1.0 - startTime) / CLOCKS_PER_SEC << " ms" << std::endl;
	std::cout << "Tempo de definição dos estados inicial e final: " << 1000.0*(sgTime * 1.0 - varTime) / CLOCKS_PER_SEC << " ms" << std::endl;
	std::cout << "Tempo de declaração das ações: " << 1000.0*(actTime * 1.0 - sgTime) / CLOCKS_PER_SEC << " ms" << std::endl;
	std::cout << "Tempo do algoritmo de busca: " << 1000.0*(endTime * 1.0 - actTime) / CLOCKS_PER_SEC << " ms" << std::endl;

	std::ofstream log("log.txt");
	if (tree) log << "Estado final    : " << tree->getstate() << std::endl;
	log << "Estado objetivo : " << prob.getgoal() << std::endl;

	log.close();

	std::cin.get();
	delete plan;
	return 0;
}