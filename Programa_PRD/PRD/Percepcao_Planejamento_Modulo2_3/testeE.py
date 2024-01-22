import serial 
import re
from SerialApp import SerialApp
import SerialApp as sp

from PddlEditor import PddlEditor


ports = [f'COM{i}' for i in range(0,15)]
serialP = SerialApp()
for i in ports:
    if sp.SerialApp.portIsUsable(i):
        serialP.serialPort.port = i
        break
    else:
        continue

serialP.serialPort.baudrate = 9600
serialP.connectSerial()
serialP.sendData(int('1'))
serialP.receiveData()
