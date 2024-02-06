import serial 
import re
from SerialApp import SerialApp
from CheckException import CheckException
from PddlEditor import PddlEditor
import SerialApp as sp
import subprocess
from subprocess import check_output
from planejamento import plan
import time
import ReWrite



serialP = SerialApp()
serialP.serialPort.port = 'COM5'
print(serialP.updatePort()[0])


serialP.serialPort.baudrate = 9600
print(serialP.connectSerial())

with open('testando.txt','w') as writer:
    writer.write(serialP.receiveData())

    

#Tratamento de Exceções-A fazer no Arduino
exEstatica = CheckException('testando.txt')# Cria objeto de Verificador de exceção
ExcDin = '0'
if(exEstatica.exception1() is not None):
    stringBlc = exEstatica.exception1()[0]
else:
    editor = PddlEditor()
    editor.editar_problema('testando.txt')
    actionsList = plan()

def transfString():
    stringBlc=""
    for str in exEstatica.exception1()[4]:
        stringBlc += str
    
    return stringBlc

time.sleep(1)

serialP.serialPort.write((stringBlc+transfString()).encode())

time.sleep(15)


serialP.connectSerial()
while (exEstatica.exception1() is not None):
    print(exEstatica.exception1() is None)
    time.sleep(1)
    for c in ReWrite.writeNewInfo():
        serialP.serialPort.write(c.encode())
        time.sleep(30)
    serialP.closePort()
    #1 - Reescrever exceção 1 e 3 para reescrita - Feito
    serialP.connectSerial()
    with open('testando.txt','w') as writer:
        writer.write(serialP.receiveData())
    #2 - criar programa para filtrar planejamento
    #3 -Criar os códigos que vão no Arduino- Feito
    #4 - Testar em montagem simples -Feito
    #5- Criar lógica para mensagens que vão ser reescritas-Feito


    


#Chamar Planejador e Editor de PDDL
#while(ExcDin == '0'):
    #editor = PddlEditor()

    #editor.editar_problema('notes1.txt')

    #actionsList = plan()

    #ExcDin = 1