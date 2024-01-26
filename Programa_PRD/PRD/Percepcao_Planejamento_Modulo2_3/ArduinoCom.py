#-------------------------------------
# Arduino-Python Serial Communication
#-------------------------------------
import os; os.system('cls')
import tkinter as tk
#---------------------------------------------------------------
import serial
arduino = serial.Serial(port='COM4', baudrate=9600, timeout=0.1)
#---------------------------------------------------------------
msW = input("Write: ")
arduino.write(bytes(msW, 'utf-8'))

msrd = arduino.readline()
msrd = msrd.decode('utf-8')
print(f'Read: {msrd}')
print(msrd == '(pickBlock a t3)')

