#!/usr/bin/env python3
# from cv2 import imwrite
import argparse
import os
import struct
import time
from datetime import datetime

import RPi.GPIO as GPIO
import numpy as np
import serial
from PIL import Image
from picamera import PiCamera

parser = argparse.ArgumentParser()
parser.add_argument("-l", "--loop", default=1, help="run loop")
parser.add_argument("-s", "--sleep", default=1, help="loop sleep")
args = parser.parse_args()

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

# po = 27  # power
# GPIO.setup(po, GPIO.OUT)
# GPIO.output(po, GPIO.LOW)

tr = 17  # trigger ir
GPIO.setup(tr, GPIO.OUT)
GPIO.output(tr, GPIO.LOW)

camera = PiCamera()

ser = serial.Serial(port='/dev/ttyS0',
                    baudrate=115200,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    timeout=10, )

w, h = 80, 80
size = 1
img_size = w * h * size
det_size = 3 + (30 * 12)
threshold = 40

with open('device_id.txt') as f:
    device_id = f.readline().rstrip()

LOOP = 1
while LOOP:
    start = time.time()
    now = datetime.now()
    dt = now.strftime("%Y-%m-%d  %H:%M:%S")
    dtime = now.strftime("%Y%m%d-%H%M%S")

    print([dt])
    print("-" * 6, "START", "-" * 24)

    print(f"[I] loop is {args.loop}")
    print(f"[I] sleep is {args.sleep} seconds")


    camera.start_preview()

    base_dir = f"data/{dtime}/"
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
    GPIO.output(tr, GPIO.HIGH)
    time.sleep(0.1)
    GPIO.output(tr, GPIO.LOW)

    print("[S] capturing rgb image")
    camera.capture(rgb_file)
    camera.stop_preview()
    # os.system(f"/bin/bash grubFrame.sh {device_id} {dtime}")

    print("[RX] detection")
    rx_det = ser.read()
    while len(rx_det) < (det_size):
        new_det = ser.read()
        rx_det += new_det

    print("[RX] image")
    # prev_len = -1
    rx_img = ser.readline()
    while len(rx_img) < (img_size):
        new_img = ser.read()
        rx_img += new_img
        # current_len = len(rx_img)
        # if current_len == prev_len:    # data checker
        #     break
        # prev_len = current_len

    print("[TX] threshold")
    ser.write(threshold.to_bytes(4, byteorder='little'))

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
    ir_image = np.reshape(ir_raw[:6400], (w, h))

    print("[S] saving image in png")
    im = Image.fromarray(ir_image)
    im.save(f"{ir_img_file}")
    # imwrite(f"{ir_file}.png", ir_image) #cv2

    # check image
    # im = Image.frombuffer('I;16', (w,h), rx_img, 'raw', 'L', 0, 1)


    end = time.time() - start
    print(f"[I] runtime : {round(end, 2)} sec")
    print("-" * 24, "FINISH", "-" * 6, "\n" * 2)

    time.sleep(int(args.sleep))
    LOOP = args.loop
