import subprocess
from subprocess import check_output
import sys
import requests
import graphlib 
import json
result =subprocess.run(["java", "-jar", r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\planejador\pddl4j\pddl4j-3.8.3.jar","-o",r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\TestesExemplo\domain.pddl", "-f", r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\TestesExemplo\problem.pddl","-p","0"])

#out = check_output(["java", "-jar", r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\planejador\pddl4j\pddl4j-3.8.3.jar","-o",r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\TestesExemplo\domain.pddl", "-f", r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\TestesExemplo\problem.pddl","-p","0"])
#print()


