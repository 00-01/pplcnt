#!/usr/bin/env python3
import argparse
import time

import RPi.GPIO as GPIO
import serial

ap = argparse.ArgumentParser()
ap.add_argument("-f", "--frequency", default=10, help="loop frequency")
args = vars(ap.parse_args())

# set rpi serial
ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=None
)

# set gpio
gp = 17
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(gp, GPIO.OUT)
GPIO.output(gp, GPIO.LOW)

threshold = 40
LOOP = 1
while LOOP:
    ser.flush()
    ser.reset_input_buffer()
    ser.reset_output_buffer()

    print("TX: threshold")
    ser.write(threshold.to_bytes(4, byteorder='little'))
    ser.flush()
    ser.reset_output_buffer()

    time.sleep(int(args["frequency"]))
