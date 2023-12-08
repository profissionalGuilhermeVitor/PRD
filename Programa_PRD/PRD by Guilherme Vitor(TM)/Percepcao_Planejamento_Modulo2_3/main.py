import serial 
import re
from SerialApp import SerialApp
#======================Função Que pega os dados da Serial do Arduino================================
def WriteSerialFile():#Arrumar a questão do arquivo

    serialP = SerialApp()
    serialP.serialPort.port = 'COM4'

    serialP.serialPort.baudrate = 9600
    serialP.connectSerial()
    f = open('notes.txt', 'r')

    with open('notes.txt', 'w') as writer:
        writer.writelines(serialP.receiveData())
        
    file = f.read
    f.close()
    serialP.closePort()
    return file    

#======================================================================================================
#================Selecionar arquivo com regex e entregar lista inicial===================================
def FileRegex(regfile):
    i=0
    txt = re.split('\s',WriteSerialFile())
    

if(__name__ == '__main__'):
    FileRegex('notes.txt')



    


