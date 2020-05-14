from subprocess import Popen, PIPE
import time
import os, msvcrt, sys

#msvcrt.setmode(sys.stdout.fileno(), os.O_BINARY)
#msvcrt.setmode(sys.stdin.fileno(), os.O_BINARY)

p = Popen(['intan0506.exe'], shell=True, stdout=PIPE, stdin=PIPE)
print("read from IntanWrapper")

read_bytes = bytearray()
while True:
    line = p.stdout.read(2)
    read_bytes += line
    #print('a', repr(line))
    if not line:
        break

print(len(read_bytes))