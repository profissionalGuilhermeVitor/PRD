import serial 
import re
from SerialApp import SerialApp

txt = open('notes.txt', 'r')

serialP = SerialApp()
serialP.serialPort.port = 'COM4'

serialP.serialPort.baudrate = 9600
serialP.connectSerial()
f = open('notes.txt', 'r')

with open('notes.txt', 'w') as writer:
    writer.writelines(serialP.receiveData())
    print(f.readline(1))

str = txt.readlines(10000)
print(str[4])


    


