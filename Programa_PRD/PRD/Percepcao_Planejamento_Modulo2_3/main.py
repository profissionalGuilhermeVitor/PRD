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
import timeit
import ReWrite
stringBlc =""
def transfString():
    stringBlc=""
    for str in exEstatica.exception1()[4]:
        stringBlc += str
    
    return stringBlc



serialP = SerialApp()
serialP.serialPort.port = 'COM5'
print(serialP.updatePort()[0])


serialP.serialPort.baudrate = 9600
print(serialP.connectSerial())


def escritaDeArquivo():
    serialP.closePort() 
    d=""
    serialP.connectSerial()
    c=""
    ti = time.time()
    tf = time.time()
    while tf-ti<370.46:
        tf = time.time()
        print(tf-ti)
        c += serialP.receiveData()

    return c

def planejamento(e):
    try:
        editor = PddlEditor()
        editor.editar_problema(e)
        actionsList = plan()
    except:
        print("PLANO NÃO PODE SER REALIZADO")
    for c in actionsList:
        time.sleep(15)
        serialP.serialPort.write(c.encode())
        time.sleep(15)
        d=""
        ti = timeit.default_timer()
        tf = timeit.default_timer()
        while tf-ti<15.7:
            tf = timeit.default_timer()
            print(tf-ti)
            d += serialP.receiveData()
        with open('testando.txt','w') as writer:
            writer.write(d)
        if("ERRO!!!! BLOCO NAO IDENTIFICADO-REALIZAR NOVA VARREDURA!!" in d):
            print(f"ERRO DE PLANEJAMENTO-NOVA VARREDURA SERÁ REALIZADA- BLOCO {c[1]} NÃO IDENTIFICADO")
            return False
        else:
            continue

with open('testando.txt','w') as writer:
   writer.write(escritaDeArquivo())

    

#Tratamento de Exceções-A fazer no Arduino
exEstatica = CheckException('testando.txt')# Cria objeto de Verificador de exceção
ExcDin = '0'
print(exEstatica.exception1())
if(exEstatica.exception1() is not None):
    stringBlc = exEstatica.exception1()[0]
else:
    while(ExcDin == '0'):
        if(planejamento('testando.txt') == False):
            ExcDin = '0'
            with open('testando.txt','w') as writer:
                writer.write(escritaDeArquivo())
        else:
            ExcDin == '1'


print(exEstatica.exception1())
time.sleep(8)
if(exEstatica.exception1() is not None):
    serialP.serialPort.write((stringBlc+transfString()).encode())


serialP.connectSerial()
while (exEstatica.exception1() is not None):

    print(exEstatica.exception1())
    time.sleep(10)
    print(ReWrite.writeNewInfo(exEstatica.exception1()))
    for c in ReWrite.writeNewInfo(exEstatica.exception1()):
        print(c)
        serialP.serialPort.write(c.encode())
        time.sleep(40)
    serialP.closePort()

    serialP.connectSerial()
    with open('testando.txt','w') as writer:
        writer.write(c)

    #2 - criar programa para filtrar planejamento
    #3 -Criar os códigos que vão no Arduino- Feito
    #4 - Testar em montagem simples -Feito
    #5- Criar lógica para mensagens que vão ser reescritas-Feito


#Chamar Planejador e Editor de PDDL

if planejamento('testando.txt')== False:
    while(ExcDin == '0'):
        if(planejamento('testando.txt') == False):
            ExcDin = '0'
            with open('testando.txt','w') as writer:
                writer.write(escritaDeArquivo())
        else:
            ExcDin == '1'
    
    
    #if actionsList ==[]:
    #    ExcDin = '0'
    #ExcDin = 1