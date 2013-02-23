#!/usr/bin/python
import struct
import serial
import sys

ser = serial.Serial(sys.argv[1],19200)

while True:
    char = struct.unpack('B', ser.read(1))[0]
    #print type(char)
    sys.stdout.write(hex(char))
    sys.stdout.write(" : ")
    sys.stdout.write(str(char))
    sys.stdout.write("\n")
    sys.stdout.flush()
