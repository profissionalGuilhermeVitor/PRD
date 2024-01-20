import re
import pddl
from pddl.logic import Predicate, constants, variables
from pddl.core import Domain, Problem
from pddl.action import Action
from pddl.formatter import domain_to_string, problem_to_string
from pddl.requirements import Requirements

def excecao_estatica(message):
    for i in message:
        letraA = i[0]
        letraB = i[-3:-1]
        if letraB[1] == " ":
            letraB = letraB[0]

    if(letraA == letraB):
        return True
    else:
        return False


arq = open('D:/Matérias da faculdade/2023-1/TCC/Arquivos/Programa_PRD/PRD by Guilherme Vitor(TM)/Percepcao_Planejamento_Modulo2_3/notes.txt','r')
texto = arq.read()
init = re.findall(":init\(\w on \w+\)",texto)
init = [i[5:] for i in init]
objective = re.findall(":objective-0\(\w on \w+\)",texto)
objective = [i[12:] for i in objective]
print(init)
print(objective)
excecao = [excecao_estatica(init) for i in init]
print(excecao)





