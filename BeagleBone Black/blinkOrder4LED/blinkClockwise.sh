#!/bin/sh 
LED0=/sys/class/leds/beaglebone:green:usr0/brightness
LED1=/sys/class/leds/beaglebone:green:usr1/brightness
LED2=/sys/class/leds/beaglebone:green:usr2/brightness
LED3=/sys/class/leds/beaglebone:green:usr3/brightness

while true; 
do	echo "1" > $LED0
    sleep 1
    echo "0" > $LED0
    sleep 1
	
	echo "1" > $LED1
    sleep 1
    echo "0" > $LED1
    sleep 1 
	
	echo "1" > $LED2
    sleep 1
    echo "0" > $LED2
    sleep 1 
	
	echo "1" > $LED3
    sleep 1
    echo "0" > $LED3
    sleep 1 
done