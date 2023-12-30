import serial 
import re
from SerialApp import SerialApp
from CheckException import CheckException
from PddlEditor import PddlEditor


serialP = SerialApp()
serialP.serialPort.port = 'COM4'

serialP.serialPort.baudrate = 9600
print(serialP.connectSerial())

with open('notes1.txt','w') as writer:
    writer.write(serialP.receiveData())
serialP.closePort()
#Tratamento de Exceções-A fazer no Arduino
exEstatica = CheckException('notes.txt')# Cria objeto de Verificador de exceção
if(exEstatica.exception1()!= None):
    print(f'Exceção {exEstatica.exception1()}')
    serialP.sendData(exEstatica.exception1())
#Chamar Planejador e Editor de PDDL
editor = PddlEditor()

editor.editar_problema('arquivo1.txt')












    


