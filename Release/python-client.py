from subprocess import Popen, PIPE
import time
import os, msvcrt, sys

p = Popen(['intan.exe'], shell=True, stdout=PIPE, stdin=PIPE)
print("read from IntanWrapper")

read_bytes = bytearray()

time.sleep(3)

while True:
    line = p.stdout.read(2)
    read_bytes += line
    #print('a', repr(line))
    if not line:
        break

print(len(read_bytes))