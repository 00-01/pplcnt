#!/usr/bin/env python3
# from cv2 import imwrite
import argparse
import os
import struct
import time
from datetime import datetime
from glob import glob
from PIL import Image

import RPi.GPIO as GPIO
import numpy as np
import serial
from picamera import PiCamera
from time import sleep

# true == 1, false == 0
parser = argparse.ArgumentParser()
parser.add_argument("-l", "--loop", default=1, help="run loop")
parser.add_argument("-s", "--sleep", default=10, help="loop sleep")
args = parser.parse_args()

print(f"loop is {args.loop}")
print(f"sleep is {args.sleep} seconds")
print("\n")

with open('device_id.txt') as f:
    device_id = f.readline().rstrip()

im_dir = "data/"

# set rpi
ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=None
)
gp = 17
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(gp, GPIO.OUT)
GPIO.output(gp, GPIO.LOW)
camera = PiCamera()

# set inputs
w, h = 80, 80
size = 1
img_size = w * h * size
det_size = 3 + (30 * 12)
threshold = 40

LOOP = 1
while LOOP > 0:
    print("-"*6, "START", "-"*24)
    camera.start_preview()

    now = datetime.now()
    dtime = now.strftime("%Y%m%d-%H%M%S")
    base_dir = f"{im_dir}{dtime}/"
    det_file = f"{base_dir}{dtime}_{device_id}_DET.txt"
    ir_file = f"{base_dir}{dtime}_{device_id}_IR.bin"
    ir_img_file = f"{base_dir}{dtime}_{device_id}_IR.png"
    rgb_file = f"{base_dir}{dtime}_{device_id}_RGB.jpg"

    if not os.path.exists(base_dir):
        os.makedirs(base_dir)

    ser.flush()
    ser.reset_input_buffer()
    ser.reset_output_buffer()

    wait_time = 8
    wait = 1
    retry = 4
    while retry > 0:
        print("[TX] start signal")
        GPIO.output(gp, GPIO.HIGH)
        time.sleep(0.1)
        GPIO.output(gp, GPIO.LOW)

        print("[S] capturing rgb image")
        camera.capture(rgb_file)
        camera.stop_preview()
        # os.system(f"/bin/bash grubFrame.sh {device_id} {dtime}")

        print("[TX] threshold")
        ser.write(threshold.to_bytes(4, byteorder='little'))

        FLAG = 0
        start = time.time()
        print("[RX] detection")
        # rx_det = ser.read(det_size)
        rx_det = ser.read()
        while len(rx_det) < (det_size):
            if wait < wait_time:
                new_det = ser.read()
                rx_det += new_det
                wait = time.time() - start
                print("w0", wait)
            else:
                print("[!] det time error")
                time.sleep(2)
                FLAG = 1
                break
        if FLAG == 1: continue

        print("[RX] image")
        # rx_img = ser.read(img_size)
        rx_img = ser.read()
        while len(rx_img) < (w * h * size):
            if wait < wait_time:
                new_img = ser.read()
                rx_img += new_img
                wait = time.time() - start
                print("w1", wait)
            else:
                print("[!] image time error")
                time.sleep(2)
                FLAG = 1
                break
        print("r")
        retry -= 1
        if FLAG == 1: continue

        print("[S] saving detection in txt")
        det = []
        det_str = rx_det.decode(encoding='UTF-8', errors='ignore')
        with open(det_file, "w") as file:
            det_str = det_str.split(";")
            st = 0
            for i in det_str:
                if "\00" not in i:
                    if i is not None:
                        det.append(i)
                        if st != 0:
                            file.write(f",")
                        file.write(f"{i}")
                        st = 1

        print("[S] saving image in bin")
        im_int = struct.unpack('<' + 'B' * img_size, rx_img)
        with open(ir_file, "wb") as file:
            for val in im_int:
                file.write(val.to_bytes(2, byteorder='little', signed=1))
        # opening image and remove bytes
        ir_raw = np.fromfile(ir_file, dtype=np.uint16).astype(np.uint8)
        ir_image = np.reshape(ir_raw[:6400], (80, 80))

        print("[S] saving image in png")
        im = Image.fromarray(ir_image)
        im.save(f"{ir_img_file}")
        # imwrite(f"{ir_file}.png", ir_image) #cv2

        # check image
        # im = Image.frombuffer('I;16', (w,h), rx_img, 'raw', 'L', 0, 1)

        LOOP = args.loop

        print("-"*24, "FINISH", "-"*6, "\n"*2)

        time.sleep(int(args.sleep))