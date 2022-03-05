#---------------------------------------------------------------------------------------------------------------#
# Sebastian Reel                                                                                                #
# CS 446: Programming Assignment 1                                                                              #
# Purpose: After viewing the contents of the /proc directory, examine specific contents and pull them out,      #
# printing said objects into a file. This should be done through reading the terminal's contents and moving     #
# them into a file you create.                                                                                  #
#---------------------------------------------------------------------------------------------------------------#

import os
import subprocess

# universal file io for every function to write to the file
f = open("sebastianreel_systemDetails.txt", "w")

# defining each variable as what we are locating in the proc directory
# using subprocess to run the terminal commands, and calling encoding to return a list of strings and not bytes
cpu_info = subprocess.run(["cat", "/proc/cpuinfo"], capture_output = True, encoding = 'utf8')
kernel_vers = subprocess.run(["cat", "/proc/version"], capture_output = True, encoding = 'utf8')
uptime = subprocess.run(["cat", "/proc/uptime"], capture_output = True, encoding = 'utf8')
boot = subprocess.run(["stat", "-c", "%z", "/proc/"], capture_output = True, encoding = 'utf8')
disk = subprocess.run(["cat", "/proc/diskstats"], capture_output = True, encoding = 'utf8')
processes = subprocess.run(["cat", "/proc/stat"], capture_output = True, encoding = 'utf8')

def cpu_info_():
    # splits off by new line and returns only certain parts of the list
    # for cpu info, we want both the type and model, so creating two variables for it
    x = cpu_info.stdout.split("\n")
    x = cpu_info.stdout.split()[3:6]
    x2 = cpu_info.stdout.split()[10:13]

    # using list comprehension to convert the list of strings to just string, so that we can write them into a file
    x_string = ' '.join(str(item) for item in x)
    x2_string = ' '.join(str(item) for item in x2)

    f.write("1. " + x_string + "\n")
    f.write("   " + x2_string + "\n")
    print("CPU Type and Model Entered Successfully.")

def kernel_vers_():
    # return the list fo strings of just hte version from the directory
    y = kernel_vers.stdout.split()[0:3]
    # using list comprehension again here
    y_string = ' '.join(str(item) for item in y)
       
    f.write("2. " + y_string + "\n")
    print("Kernel Version Entered Successfully.")

def uptime_():
    # uptime had two items, only returning the first one that prints the uptime in seconds
    z = uptime.stdout.split()[0]
    z_string = ' '.join(str(item) for item in z)

    
    f.write("3. " + z_string + "\n")
    print("Anount of time since last boot (uptime) Entered Successfully.")

def boot_():
    a = boot.stdout.split()[0:2]
    a_string = ' '.join(str(item) for item in a)

    f.write("4. Time Last Booted - " + a_string + "\n")
    print("Time that the system was last booted Entered Successfully.")

def disk_():
    # splitting all of the information about reads and writs happening with the disk statistics
    b = disk.stdout.split("\n")
    # creating a temporary list and variable to return the total added up of all requests done by the disk
    temp = []
    total_diskrequests = 0

    # iterating through the list of disk stats, appending everything but the alpha (characters) to the temporary list 
    for i in b:
        for j in range(len(i)):
            if(i[j].isalpha()):
                temp.append(j)
                break
    
    # iterating through the temp list and adding up all of the numbers in the list, splitting only the numbers into the total and adding them
    for i in range(len(temp)):
        total_diskrequests += sum([int(x) for x in b[i][temp[i]:].split(" ")[1:]])
    
    # writing that created integer variable as a stringb into the variable
    f.write("5. Total Disk Requests - " + str(total_diskrequests) + "\n")
    print("The number of total disk requests made Entered Successfully.")

def processes_():
    # splitting the specifc items in the list that i want to be returned, which are only the items of "proce4ss" and the number of them
    c = processes.stdout.split("\n")

    for i in range(len(c)):
        if ("processes" in c[i]):
            f.write("6. " + c[i])
    f.close()
    print("Number of Processes created since last boot Entered Successfully.")

def main():
    print("--CS 446 Programming Assignment 1--\n")
    cpu_info_()         # 1
    kernel_vers_()      # 2
    uptime_()           # 3
    boot_()             # 4
    disk_()             # 5
    processes_()        # 6
    print("\n--All Done.--")

if __name__ in "__main__":
    main()