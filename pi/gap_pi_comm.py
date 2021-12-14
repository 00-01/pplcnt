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
finish = b'\x00\x00\x00\x00'

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
    # os.system("/bin/bash grubFrame.sh " + NODE_NAME + " " + dtime)

    # check image
    # im = Image.frombuffer('I;16', (w,h), rx_img, 'raw', 'L', 0, 1)

    print("saving detection")
    im_dir = "images/"
    det_name = "CNT_" + NODE_NAME + "_" + dtime + ".txt"
    det_str = rx_det.decode(encoding='UTF-8', errors='ignore')
    with open(im_dir + det_name, "w") as file:
        file.write("%s" % det_str)

    print("saving image")
    im_name = "IR_" + NODE_NAME + "_" + dtime + ".bin"
    im_int = struct.unpack('<' +'B' *w *h *2, rx_img)
    with open(im_dir + im_name, "wb") as file:
        for val in im_int:
            file.write(val.to_bytes(2, byteorder='little', signed=True))

    if USE_FTP == True:
        print("uploading to ftp")
        with FTP(FTP_ADDR, FTP_USER, FTP_PASS) as ftp:
            ftp.cwd(NODE_NAME)
            with open(im_dir + im_name, 'rb') as file:
                ftp.storbinary('STOR ' + im_name, file)
            os.remove(im_dir + im_name)

            with open(im_dir + det_name, 'rb') as file:
                ftp.storbinary('STOR ' + det_name, file)
            os.remove(im_dir + det_name)

    if USE_SCP == True:
        print("uploading to server")
        ssh = paramiko.SSHClient()
        # ssh.load_system_host_keys()
        # ssh.load_host_keys(os.path.expanduser(os.path.join("~", ".ssh", "known_hosts")))
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(host, port, username, password)
        sftp = ssh.open_sftp()

        # upload det
        localPath = im_dir + det_name
        targetPath = '~'
        sftp.put(localPath, targetPath)
        os.remove(im_dir + det_name)

        # upload image
        localPath = im_dir + im_name
        targetPath = '~'
        sftp.put(localPath, targetPath)
        os.remove(im_dir + im_name)

        # stdin, stdout, stderr = ssh.exec_command(command)
        # i, o, e = stdin.readlines(), stdout.readlines(), stderr.readlines()
        # print(i, "\n", o, "\n", e)

        sftp.close()
        ssh.close()

    LOOP = args["loop"]
    if args["loop"] == None:
        LOOP = False

    print("-"*24, "FINISH", "-"*6, "\n"*2)

    time.sleep(int(args["frequency"]))
# camera.stop_preview()
