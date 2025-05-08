#!/usr/bin/python3

#
# process paper tape hex data and interpret it as PDP-8 BIN format
#
# input format is bytes in two digit hex with 1 to 16 bytes per line
# output format is SIMH deposit format
#
# Andrew Seawright
#
# written to convert the Space Wars tape
#

import sys
import re
import math

#
# process input data into "tape_data" array of byte values
#

#match pattern for line of hexadecimal bytes 
phex = re.compile('\s*([0-9A-Fa-f]{2}\s+){1,16}')

tape_data = []

for line in sys.stdin:
  line = line.rstrip()
  m = phex.match(line)
  if m:
     bytes = re.split('\s+',line)
     for byte in bytes:
       tape_data.append(int(byte,16))


#
# process tape_data
#

pos = 0 # current tape position
L = len(tape_data) # length of tape in bytes
origin = 0
addr = 0
csum = 0
sum = 0

# skip leading 0's
while (pos < L) and (tape_data[pos] == 0x00):
  pos = pos + 1

#skip leader where bit 0x80 is set     
while (pos < L) and (tape_data[pos] & 0x80):
  pos = pos + 1

while (pos < (L-1)):

  if (tape_data[pos] & 0x80):
    # end of the tape
    csum = word
    
    print("#checksum: {0} {1}".format(oct(csum)[2:].zfill(3),oct(sum)[2:].zfill(3)))
    if (csum == sum):
      print("# checksum matches!")
    exit()

  word = ((tape_data[pos] & 0x3f) << 6) | (tape_data[pos+1] & 0x3f); 

  if (tape_data[pos] & 0x40):
    origin = word;
    addr = origin;
    print("#origin: {0}".format(oct(word)[2:].zfill(4)))
    next

  # look ahead
  if (((pos+2) < L) and not (tape_data[pos+2] & 0x80)):
    # not at last word of tape
    # thus this work is not the checksum - ouput data, update sum
    print("d {0} {1}".format(oct(addr)[2:].zfill(4),oct(word)[2:].zfill(4)))
    sum = (sum + tape_data[pos] + tape_data[pos+1]) & 0xfff; 

  addr = addr + 1
  pos = pos + 2
    
