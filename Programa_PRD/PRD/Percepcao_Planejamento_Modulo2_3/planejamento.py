import subprocess
from subprocess import check_output
import re
from CheckException import CheckException

def plan():
    out = check_output(["java", "-jar", r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\planejador\pddl4j\pddl4j-3.8.3.jar","-o",r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\TestesExemplo\domain.pddl", "-f", r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\TestesExemplo\problem.pddl","-p","0"])
    with open('plan.txt','w') as writer:
        writer.write(str(out))

    planfile = open('plan.txt','r').read()

    if (("the problem to encode is not ADL" in planfile) or ( "no plan found" in planfile)):
        return "ERRO"

    plansList = CheckException('plan.txt').tratarArquivo()
    c = re.findall("pickblock \w \w+",plansList)
    return c



