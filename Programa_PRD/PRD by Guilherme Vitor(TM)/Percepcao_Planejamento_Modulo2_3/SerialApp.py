import serial
import serial.tools.list_ports

class SerialApp ():
    def __init__(self):
        self.serialPort = serial.Serial()
        self.baudrate = [9600,115200]
        self.portlist = []

    def updatePort(self):
        self.portlist =[port.device for port in serial.tools.list_ports.comports() ]
        print(self.portlist)

    #Estabelecer Conexão
    def connectSerial(self):
        try:
            self.serialPort.open()
        except:
            print("ERRO!!!")

    #Receber Dados
    def receiveData(self):
        dataRead = self.serialPort.read(1000).decode('utf-8')
        print(dataRead)
        return dataRead

    #Enviar Dados
    def sendData(self):
        if(self.serialPort.isOpen()):
            dataSend = str(self.data) + '\n'
            self.serialPort.write(dataSend.encode())
            self.serialPort.flushOutput()

    #Fechar a porta

    def closePort(self):
        self.serialPort.close()
