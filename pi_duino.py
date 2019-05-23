import serial
from mpd import MPDClient

client = MPDClient()
client.connect("localhost", 6600)
print(client.mpd_version) 
client.add("a2002011001-e02.wav")
client.play()


s1 = serial.Serial('/dev/ttyACM0',9600,timeout=5)
s1.flushInput()



while True:
        if s1.inWaiting()>0:
                inputValue = s1.read(1)
                print(ord(inputValue))
