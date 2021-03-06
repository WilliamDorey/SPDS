#
# Python script to send and receive serial communications
# to control the embedded circuit
#
# Located in the scripts section of the webserver

import	serial
import	sys
from	time	import	sleep

port = serial.Serial("/dev/ttyS0", baudrate=2400)
argument = sys.argv[1]

port.write(argument)
port.read()
port.write("1")
port.read()
port.write("1")

# If the argument is an 'S' send 6 numbers out
if argument == 'S' :
  code = list(sys.argv[2])
  i = 0
  while i < 6 :
    port.write(code[i])
    port.read()
    i = i + 1
  print("Passcode Updated Successful!")

# If the arguement is 'W' recieve 2 Hexadecimal characters
elif argument == 'W' :
  val = ''
  i = 0
  while i < 2 :
    port.write("1")
    val += port.read()
    i += 1
  print(val)
