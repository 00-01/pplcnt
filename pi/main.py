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
ap = argparse.ArgumentParser()
ap.add_argument("-l", "--loop", default=1, help="run loop")
ap.add_argument("-f", "--frequency", default=10, help="loop frequency")
# ap.add_argument("-scp", "--scp", default=1, help="save to scp")
args = vars(ap.parse_args())

# args
print(f"loop is {args['loop']}")
print(f"frequency is {args['frequency']} seconds")
print("\n")

# # scp
# host = "192.168.0.5"
# port = 22
# username = "z"
# password = "1234qwer"
# local_location = "~/DATA/gappi"

# set rpi serial
ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=None
)

command = "cd ~"
im_dir = "data/"

# HOME_DIR = os.path.expanduser('~')
# with open(f"{HOME_DIR}/device_id.txt") as f:
#     device_id = f.readline().rstrip()

device_id = "65535"

# set gpio
gp = 17
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(gp, GPIO.OUT)
GPIO.output(gp, GPIO.LOW)
camera = PiCamera()

# set inputs
w = 80
h = 80
size = 2
img_size = w * h * size
det_size = 3 + (30 * 12)
threshold = 40

LOOP = 1
while LOOP:
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

    print("[TX] start signal")
    GPIO.output(gp, GPIO.HIGH)
    time.sleep(0.1)
    GPIO.output(gp, GPIO.LOW)

    print("[S] capturing rgb image")
    camera.capture(rgb_file)
    camera.stop_preview()
    # os.system(f"/bin/bash grubFrame.sh {device_id} {dtime}")

    print("[RX] detection")
    rx_det = ser.read()
    while len(rx_det) < (det_size):
        len(rx_det)
        new_det = ser.read()
        rx_det = rx_det + new_det
    if len(rx_det) != (det_size):
        print("[E] incorrect size received. skipping detections!")
        exit()
    # ser.flush()
    # ser.reset_input_buffer()

    print("[RX] image")
    rx_img = ser.read()
    while len(rx_img) < (w * h * size):
        len(rx_img)
        new_img = ser.read()
        rx_img = rx_img + new_img
    if len(rx_img) != (w * h * size):
        print("[E] incorrect size received. skipping image!")
        exit()
    # ser.flush()
    # ser.reset_input_buffer()

    print("[TX] threshold")
    ser.write(threshold.to_bytes(4, byteorder='little'))
    # ser.flush()
    # ser.reset_output_buffer()

    print("[S] saving detection in txt")
    det = []
    det_str = rx_det.decode(encoding='UTF-8', errors='ignore')
    with open(det_file, "w") as file:
        det_str = det_str.split(";")
        for i in det_str:
            if "\00" not in i:
                if i is not None:
                    det.append(i)
                    file.write(f"{i} ")

    print("[S] saving image in bin")
    im_int = struct.unpack('<' + 'B' * w * h * 2, rx_img)
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

    # if args["scp"]:
    #     print("uploading to server")
    #     os.system(f"sudo sshpass -p {password} scp {im_dir}* {username}@{host}:{local_location}")

    LOOP = args["loop"]

    print("-"*24, "FINISH", "-"*6, "\n"*2)

    time.sleep(int(args["frequency"]))
