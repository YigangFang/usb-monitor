#!/usr/bin/python

import hid
import psutil
import font
import screen

dev = hid.hid(0x0483, 0x5750)
scr = screen.display(128,32)
data = [0]*128
while True:
    #get sytem info
    bytes_recv = psutil.net_io_counters().bytes_recv
    cpu=int(psutil.cpu_percent(1))
    bytes_recv = psutil.net_io_counters().bytes_recv - bytes_recv
    phymem = psutil.virtual_memory()
    disk = int(psutil.disk_usage('/').percent)
    #calculate 
    mem = int(phymem.used * 100/phymem.total)
    net = int(bytes_recv * 100/(10*1024*1024)) #10MByte 
    #display
    scr.clear()
    scr.write('CPU:              ' + str(cpu) + '\n')
    scr.rectangle(24, 0, cpu*92/100)
    scr.write('MEM:              ' + str(mem) + '\n')
    scr.rectangle(24, 1, mem*92/100)
    scr.write('DSK:              ' + str(disk) + '\n')
    scr.rectangle(24, 2, disk*92/100)
    scr.write('NET:              ' + str(net) + '\n')
    scr.rectangle(24, 3, net*92/100)
    #fresh screen
    dev.write(scr.data())

