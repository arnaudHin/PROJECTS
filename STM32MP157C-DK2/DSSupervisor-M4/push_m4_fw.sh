
#!/bin/bash

echo -n /lib/firmware/DAVIDSON_PROJECT_CM4.elf > /sys/module/firmware_class/parameters/path

echo -n DAVIDSON_PROJECT_CM4.elf > /sys/class/remoteproc/remoteproc0/firmware

echo start > /sys/class/remoteproc/remoteproc0/state




