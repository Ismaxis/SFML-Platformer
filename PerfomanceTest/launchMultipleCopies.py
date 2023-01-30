import subprocess
import random
import time
processes = []
size = (405, 225)
pos = [0, 0]
for i in range(24):
    processes.append(subprocess.Popen(
        ["../x64/Debug/Client.exe",
         str(size[0]), str(size[1]),
         str(size[0] * pos[0]), str(size[1] * pos[1]), "test", str(random.randint(0, 1000))], cwd="../Client"))
    pos[0] += 1
    if (pos[0] > 5):
        pos[0] = 0
        pos[1] += 1
