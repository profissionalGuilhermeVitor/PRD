from CheckException import CheckException
import re 
import serial
flag = True
txt = CheckException(r"C:\Users\Home\GitHub_Files\SISTEMAS_PRD_PNRD_iPNRD\Programa_PRD\PRD\Percepcao_Planejamento_Modulo2_3\TestesExemplo\arquivo3_Exc1_Ex1_O.txt").tratarArquivo()
excs = re.findall(":init",txt)
print(excs)


