#!/usr/bin/env python3
# import io
# import PIL.Image as Image
# import base64
# import re
# import numpy as np
# from picamera import PiCamera
# import paramiko
# import scp
import RPi.GPIO as GPIO
import argparse
import time
import serial
import os
import struct
from datetime import datetime
from ftplib import *


ap = argparse.ArgumentParser()
ap.add_argument("-l", "--loop", required=False, help="run looping or not")
ap.add_argument("-f", "--frequency", required=False, help="loop frequency")
args = vars(ap.parse_args())

print("loop is", args["loop"])
LOOP = True

# set rpi serial
ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=None)

# scp
USE_SCP = True
host = "192.168.0.5"
port = 1111
username = "z"
password = "1234qwer"
command = "cd ~"

# ftp
USE_FTP = False
NODE_NAME = ""
FTP_ADDR = "115.68.41.211"
FTP_USER = "gappocb"
FTP_PASS = "gappocb!"

root = "~/scripts/"
im_dir = "images/"

HOME_DIR = os.path.expanduser('~')
with open(HOME_DIR + "/info.txt") as f:
    NODE_NAME = f.readline().rstrip()

# set gpio
gp = 17
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(gp, GPIO.OUT)
GPIO.output(gp, GPIO.LOW)

# set inputs
w = 80
h = 80
size = 2
img_size = w * h * size
det_size = 3 + (30 * 12)
threshold = 40
# finish = b'\x00\x00\x00\x00'

while LOOP:
    print("\n", "-"*6, "START", "-"*24)
    now = datetime.now()
    dtime = now.strftime("%Y%m%d-%H_%M_%S")

    ser.flush()
    ser.reset_input_buffer()
    ser.reset_output_buffer()

    print("tx start signal")
    GPIO.output(gp, GPIO.HIGH)
    time.sleep(0.1)
    GPIO.output(gp, GPIO.LOW)

    print("rx detection")
    rx_det = ser.read()
    while len(rx_det) < (det_size):
        len(rx_det)
        new_det = ser.read()
        rx_det = rx_det + new_det
    if len(rx_det) != (det_size):
        print("incorrect size received. skipping detections!")
        exit()
    ser.flush()
    ser.reset_input_buffer()

    print("rx image")
    rx_img = ser.read()
    while len(rx_img) < (w * h * size):
        len(rx_img)
        new_img = ser.read()
        rx_img = rx_img + new_img
    if len(rx_img) != (w * h * size):
        print("incorrect size received. skipping image!")
        exit()
    ser.flush()
    ser.reset_input_buffer()

    # tx threshold
    print("tx threshold")
    ser.write(threshold.to_bytes(4, byteorder='little'))
    ser.flush()
    ser.reset_output_buffer()

    # print("capturing picamera image")
    print("/bin/bash grubFrame.sh " + NODE_NAME + " " + dtime)
    os.system("/bin/bash grubFrame.sh " + NODE_NAME + " " + dtime)

    # check image
    # im = Image.frombuffer('I;16', (w,h), rx_img, 'raw', 'L', 0, 1)

    print("saving detection")
    det_name = "CNT_" + NODE_NAME + "_" + dtime + ".txt"
    det_str = rx_det.decode(encoding='UTF-8', errors='ignore')
    with open(im_dir + det_name, "w") as file:
        file.write("%s" % det_str)

    print("saving image")
    img_name = "IR_" + NODE_NAME + "_" + dtime + ".bin"
    im_int = struct.unpack('<' +'B' *w *h *2, rx_img)
    with open(im_dir + img_name, "wb") as file:
        for val in im_int:
            file.write(val.to_bytes(2, byteorder='little', signed=True))

    if USE_FTP == True:
        print("uploading to ftp")
        with FTP(FTP_ADDR, FTP_USER, FTP_PASS) as ftp:
            ftp.cwd(NODE_NAME)
            with open(im_dir + img_name, 'rb') as file:
                ftp.storbinary('STOR ' + img_name, file)
            os.remove(im_dir + img_name)

            with open(im_dir + det_name, 'rb') as file:
                ftp.storbinary('STOR ' + det_name, file)
            os.remove(im_dir + det_name)

    if USE_SCP == True:
        print("uploading to server")
        os.system(f"sudo sshpass -p {password} scp -P {port} images/* {username}@{host}:~/DATA/gappi")
        os.system("rm images/*")

        # transport = paramiko.Transport((host, port))
        # transport.connect(username=username, password=password)
        # sftp = paramiko.SFTPClient.from_transport(transport)

        # # upload det
        # local_det_file = im_dir + det_name
        # target_det_path = "~/" + det_name
        # sftp.put(local_det_file, target_det_path)
        #
        # # upload image
        # local_img_file = im_dir + img_name
        # target_img_path = "~/" + img_name
        # sftp.put(local_img_file, target_img_path)

        # os.remove(local_det_file)
        # os.remove(local_img_file)

        # stdin, stdout, stderr = ssh.exec_command(command)
        # i, o, e = stdin.readlines(), stdout.readlines(), stderr.readlines()
        # print(i, "\n", o, "\n", e)

        # sftp.close()
        # ssh.close()
        # transport.close()

    LOOP = args["loop"]
    if args["loop"] == None:
        LOOP = False

    print("-"*24, "FINISH", "-"*6, "\n"*2)

    time.sleep(int(args["frequency"]))
# camera.stop_preview()
