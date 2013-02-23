from serial import Serial

s = Serial('/dev/ttyUSB0')
while True:
    s.write(chr(0) + chr(29) + "\n")
    print s.read(4)
