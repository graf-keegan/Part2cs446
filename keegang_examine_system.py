#Author: Keegan Graf
#Date: 3/3/2022

import os
import subprocess


file = open("keegang_systemDetails.txt", "w")

cpu = subprocess.run(["cat", "/proc/cpuinfo"], capture_output = True, encoding = 'utf8')

c1 = cpu.stdout.split("\n")
c1 = cpu.stdout.split()[3:6]
c2 = cpu.stdout.split()[10:13]

c1parse = ' '.join(str(item) for item in c1)
c2parse = ' '.join(str(item) for item in c2)

file.write(c1parse + ", " + c2parse + "\n")

version = subprocess.run(["cat", "/proc/version"], capture_output = True, encoding = 'utf8')

version_parse = version.stdout.split(" ")

for x in range(len(version_parse)):
    if("version" in version_parse[x]):
        file.write(version_parse[x + 1] + "\n")

uptime = subprocess.run(["cat", "/proc/uptime"], capture_output = True, encoding = 'utf8')

uptime_parse = uptime.stdout.split(" ")
file.write(uptime_parse[0] + "\n")

boot = subprocess.run(["stat", "-c", "%z", "/proc"], capture_output = True, encoding = 'utf8')

boot_parse = boot.stdout.split()[0:2]
pboot = ' '.join(str(item) for item in boot_parse)

file.write(pboot + "\n")


disk = subprocess.run(["cat", "/proc/diskstats"], capture_output = True, encoding = 'utf8')

#disk_num = disk.stdout.split("\n")
#disk_snum = disk_num.split(" ")
#isList = ""

#for o in range(len(disk_snum)):
    #if disk_snum[o].isdigit():
        

file.write("Could not find out how to do disk\n")





stat = subprocess.run(["cat", "/proc/stat"], capture_output = True, encoding = 'utf8')

stat_parse = stat.stdout.split("\n")
for y in range(len(stat_parse)):
    if("process" in stat_parse[y]):
        file.write(stat_parse[y] + "\n")




file.close()