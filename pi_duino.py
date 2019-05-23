import serial
s1 = serial.Serial('/dev/ttyACM0',9600,timeout=5)
s1.flushInput()

while True:
        if s1.inWaiting()>0:
                inputValue = s1.read(1)
                print(ord(inputValue))
