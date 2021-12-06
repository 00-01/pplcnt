#!/usr/bin/env python3
import RPi.GPIO as GPIO
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

# set rpi serial
ser = serial.Serial(
	port = '/dev/ttyS0',
	baudrate = 115200,
	parity = serial.PARITY_NONE,
	stopbits = serial.STOPBITS_ONE,
	bytesize = serial.EIGHTBITS,
	timeout = 0)

# set inputs
w = 80
h = 80
size = 2 #shorts
#size = 1
DET_SIZE = 3 + (30*12)
threshold = 40

# scp
USE_SCP = False
host = "192.168.0.5"
port = 1111
username = "z"
password = "1234qwer"

# ftp
USE_FTP = True
NODE_NAME=""
FTP_ADDR="115.68.41.211"
FTP_USER="gappocb"
FTP_PASS="gappocb!"

HOME_DIR= os.path.expanduser('~')
with open(HOME_DIR + "/info.txt") as f:
	NODE_NAME = f.readline().rstrip()

gp = 17
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(gp, GPIO.OUT)
GPIO.output(gp, GPIO.LOW)

now = datetime.now()
dt_string = now.strftime("%Y%m%d-%H_%M_%S")
ser.flush()

# send interrupt signal to gap
print("sending interrupt signal")
GPIO.output(gp, GPIO.HIGH)
time.sleep(0.1)
GPIO.output(gp, GPIO.LOW)

# capture picamera image
print("capturing picamera image")
os.system("/bin/bash grubFrame.sh "+ NODE_NAME + " " + dt_string)

# rx serial
print("serial read begin")
if ser.in_waiting > 0:
	print ("serial read waiting")
	rx = ser.read(w * h * size)
	while len(rx) < (w * h * size):
		b = ser.read(w * h * size-len(rx))
		rx = rx+b
	if len(rx) != (w * h * size):
		print("incorrect size received. skipping image!")
		exit()
	ser.flush()

# reading detections
	det = ser.read(DET_SIZE)
	while len(det) < (DET_SIZE):
		tmp_det = ser.read((DET_SIZE) - len(det))
		det = det+tmp_det
	if len(det) != (DET_SIZE):
		print("incorrect size received. skipping detections!")
		exit()

# tx threshold
	ser.write(threshold.to_bytes(4, byteorder='little'))

# save bin
	im_int = struct.unpack('<' + 'h' *w*h, rx)
	# im = Image.frombuffer('I;16',(w, h),rx,'raw','L',0,1)
	im_dir = "images/"
	im_name = "IR_" + NODE_NAME + "_" + dt_string + ".bin"
	with open(im_dir+im_name, "wb") as file:
		for val in im_int:
			file.write(val.to_bytes(2, byteorder='little', signed=True))

# save txt
	det_str = det.decode()
	det_name = "CNT_" + NODE_NAME + "_" + dt_string + ".txt"
	with open (im_dir+det_name,"w") as file:
		file.write("%s" % det_str)

# upload to ftp
	if USE_FTP == True:
		with FTP(FTP_ADDR, FTP_USER, FTP_PASS) as ftp:
			ftp.cwd(NODE_NAME)
			with open (im_dir + im_name, 'rb') as file:
				ftp.storbinary('STOR ' + im_name, file)
			os.remove(im_dir + im_name)
			with open (im_dir + det_name, 'rb') as file:
				ftp.storbinary('STOR ' + det_name, file)
			os.remove(im_dir + det_name)
		print("saved to ftp")
# upload to server
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
		print("saved to server")
else:
	print("SERIAL READ FAIL")
# camera.stop_preview()
