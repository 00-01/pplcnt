#!/usr/bin/env python3
import RPi.GPIO as GPIO
import argparse
import time
import serial
import os
import io
import PIL.Image as Image
import base64
import re
import numpy as np
from picamera import PiCamera
import struct
from datetime import datetime
from ftplib import *
import paramiko
import scp

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
    timeout=0)

# scp
USE_SCP = False
host = "192.168.0.5"
port = 1111
username = "z"
password = "1234qwer"

# ftp
USE_FTP = True
NODE_NAME = ""
FTP_ADDR = "115.68.41.211"
FTP_USER = "gappocb"
FTP_PASS = "gappocb!"

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
DET_SIZE = 3 + (30 * 12)
threshold = 40

while LOOP:
    print("="*12, "STARTING", "="*12)
    now = datetime.now()
    dt_string = now.strftime("%Y%m%d-%H_%M_%S")

    ser.flush()
    ser.reset_input_buffer()
    ser.reset_output_buffer()

    # tx threshold
    print("tx threshold")
    ser.write(threshold.to_bytes(4, byteorder='little'))

    print("tx start signal")
    GPIO.output(gp, GPIO.HIGH)
    time.sleep(0.1)
    GPIO.output(gp, GPIO.LOW)

    print("rx read begin")
    if ser.in_waiting > 0:
        print("reading image")
        rx_img = ser.read(w * h * size)
        while len(rx_img) < (w * h * size):
            new_img = ser.read(w * h * size - len(rx_img))
            rx_img = rx_img + new_img
        if len(rx_img) != (w * h * size):
            print("incorrect size received. skipping image!")
            exit()
        ser.flush()

        print("capturing picamera image")
        os.system("/bin/bash grubFrame.sh " + NODE_NAME + " " + dt_string)


        # import cv2
        # print(len(rx_img))
        #
        # dt = np.dtype(np.uint8)
        # dt = dt.newbyteorder('>')
        # t = np.frombuffer(rx_img, dtype=dt)
        # # p = Image.fromarray(t)
        # # p.save('orogin.png')

        # print(len(t))
        # t2 = (t[:6400]).reshape(80, 80)
        # t1 = (t[6400:]).reshape(80, 80)
        # print(t2)
        # print(t1)
        # im = Image.fromarray(t2)
        # im.save("aaa2.png")
        # im1 = Image.fromarray(t1)
        # im1.save('aaa1.png')
        # cv2.imwrite('aaa22.png', t2)
        # cv2.imwrite('aaa11.png', t1)
        # exit()


        print("rx detection")
        rx_det = ser.read(DET_SIZE)
        while len(rx_det) < (DET_SIZE):
            new_det = ser.read(DET_SIZE - len(rx_det))
            rx_det = rx_det + new_det
        if len(rx_det) != (DET_SIZE):
            print("incorrect size received. skipping detections!")
            exit()
        ser.flush()

        # check image
        # im = Image.frombuffer('I;16', (w,h), rx_img, 'raw', 'L', 0, 1)
        # im.save(f"a.jpg")

        print("saving image")
        im_dir = "images/"
        im_name = "IR_" + NODE_NAME + "_" + dt_string + ".bin"
        im_int = struct.unpack('<' +'B' *w *h *2, rx_img)
        with open(im_dir + im_name, "wb") as file:
            for val in im_int:
                file.write(val.to_bytes(2, byteorder='little', signed=True))

        print("saving detection")
        det_str = rx_det.decode()
        det_name = "CNT_" + NODE_NAME + "_" + dt_string + ".txt"
        with open(im_dir + det_name, "w") as file:
            file.write("%s" % det_str)

        print("uploading to ftp")
        if USE_FTP == True:
            with FTP(FTP_ADDR, FTP_USER, FTP_PASS) as ftp:
                ftp.cwd(NODE_NAME)
                with open(im_dir + im_name, 'rb') as file:
                    ftp.storbinary('STOR ' + im_name, file)
                os.remove(im_dir + im_name)
                with open(im_dir + det_name, 'rb') as file:
                    ftp.storbinary('STOR ' + det_name, file)
                os.remove(im_dir + det_name)

        print("uploading to server")
        if USE_SCP == True:
            ssh = paramiko.SSHClient()
            # ssh.load_system_host_keys()
            ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            ssh.connect(host, port, username, password)
            sftp = ssh.open_sftp()

            # localPath = im_dir + im_name
            # targetPath = '~/' + im_dir + im_name
            # sftp.put(localPath, targetPath)
            # os.remove(im_dir + im_name)
            #
            # localPath = im_dir + det_name
            # targetPath = '~/' + im_dir + det_name
            # sftp.put(localPath, targetPath)
            # os.remove(im_dir + det_name)

            sftp.close()
            ssh.close()
        print("-"*12, "COMPLETE", "-"*12, "\n")
    else:
        print("%"*12, "FAILED", "%"*12, "\n")

    LOOP = args["loop"]
    if args["loop"] == None:
        LOOP = False

    time.sleep(int(args["frequency"]))
# camera.stop_preview()
