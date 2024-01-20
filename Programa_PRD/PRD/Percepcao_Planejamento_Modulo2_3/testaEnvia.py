import subprocess
from subprocess import check_output
import sys
import requests
import graphlib 
import json
result =subprocess.run(["java", "-jar", r"c:\Users\Home\Desktop\teste\pddl4j\pddl4j-3.8.3.jar","-o", r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\domain.pddl", "-f", r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\problem.pddl"])
print(result)


