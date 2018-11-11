#!/usr/bin/python

import hid
import psutil
import font
import screen
import style

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
    #render
    style.display_percent_bar(scr, 0 , 'CPU:', cpu)
    style.display_percent_bar(scr, 1 , 'MEM:', mem)
    style.display_percent_bar(scr, 2 , 'DSK:', disk)
    style.display_percent_bar(scr, 3 , 'NET:', net)
    #display
    dev.write(scr.data())

