#-------------------------------------
# Arduino-Python Serial Communication
#-------------------------------------
import os; os.system('cls')
import tkinter as tk
#---------------------------------------------------------------
import serial
arduino = serial.Serial(port='COM5', baudrate=9600, timeout=1)
#---------------------------------------------------------------
msW = input("Write: ")
arduino.reset_output_buffer()

dataRead = arduino.readline().decode('utf-8')
print(f'Read: {dataRead}')


