#!/usr/bin/env python3
# import io
# import PIL.Image as Image
# import base64
# import re
# from picamera import PiCamera
# import paramiko
# import scp
import requests
# from pymongo import MongoClient
from google.cloud import storage
from ftplib import *

from cv2 import imwrite
import RPi.GPIO as GPIO
import argparse
import time
import serial
import os
import struct
import numpy as np
from datetime import datetime

# true == 1, false == 0
ap = argparse.ArgumentParser()
ap.add_argument("-l", "--loop", default=1, help="run loop")
ap.add_argument("-f", "--frequency", default=10, help="loop frequency")
ap.add_argument("-s", "--saveAsImage", default=1, help="save as image")
# save location
# ap.add_argument("-gc", "--g_cloud", default=0, help="save to google_cloud")
ap.add_argument("-db", "--dbms", default=0, help="save to dbms")
ap.add_argument("-ls", "--localSave", default=0, help="save to pi")
ap.add_argument("-scp", "--scp", default=1, help="save to scp")
ap.add_argument("-ftp", "--ftp", default=0, help="save to ftp")
args = vars(ap.parse_args())

# args
print("loop is", args["loop"])
print("frequency is", args["frequency"])
print("show file is", args["saveAsImage"])
print("\n")

# # google cloud
# client = storage.Client.from_service_account_json('creds.json')
# bucket = client.get_bucket('mill_pplcnt')
# blob = bucket.blob(blob_name)

# # dbms
# client = MongoClient("mongodb://mill:mill1234@192.168.0.5:27017")
# db = client["mydatabase"]
# col = db["customers"]

# scp
host = "192.168.0.5"
port = 1111
username = "z"
password = "1234qwer"
local_location = "~/DATA/gappi"

# ftp
device_id = ""
FTP_ADDR = "115.68.41.211"
FTP_USER = "gappocb"
FTP_PASS = "gappocb!"

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
root = "~/scripts/"
im_dir = "images/"

HOME_DIR = os.path.expanduser('~')
with open(HOME_DIR + "/info.txt") as f:
    device_id = f.readline().rstrip()

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

LOOP = 1
while LOOP:
    print("-"*6, "START", "-"*24)
    now = datetime.now()
    dtime = now.strftime("%Y%m%d-%H_%M_%S")
    det_name = "CNT_" + device_id + "_" + dtime + ".txt"
    det_file = im_dir + det_name
    img_name = "IR_" + device_id + "_" + dtime + ".bin"
    img_file = im_dir + img_name

    ser.flush()
    ser.reset_input_buffer()
    ser.reset_output_buffer()

    print("TX: start signal")
    GPIO.output(gp, GPIO.HIGH)
    time.sleep(0.1)
    GPIO.output(gp, GPIO.LOW)

    print("RX: detection")
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

    print("RX: image")
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

    print("TX: threshold")
    ser.write(threshold.to_bytes(4, byteorder='little'))
    ser.flush()
    ser.reset_output_buffer()

    # print("capturing picamera image")
    print("/bin/bash grubFrame.sh " + device_id + " " + dtime)
    os.system("/bin/bash grubFrame.sh " + device_id + " " + dtime)

    print("saving detection")
    det_str = rx_det.decode(encoding='UTF-8', errors='ignore')
    with open(det_file, "w") as file:
        det_str = det_str.split(";")
        for i in det_str:
            if "\00" not in i:
                file.write(f"{i} ")
    print("saving image")
    im_int = struct.unpack('<' + 'B' * w * h * 2, rx_img)
    with open(img_file, "wb") as file:
        for val in im_int:
            file.write(val.to_bytes(2, byteorder='little', signed=1))
    # opening image and remving bytes
    raw = np.fromfile(img_file, dtype=np.uint16).astype(np.uint8)
    raw_to_shape = np.reshape(raw[:6400], (80, 80))
    with open(img_file, "wb") as file:
        file.write(raw_to_shape)

    # check image
    # im = Image.frombuffer('I;16', (w,h), rx_img, 'raw', 'L', 0, 1)

#############################  UPLOADING  #############################

    # if args["g_cloud"]:
    #     print("uploading to google cloud")
    #     blob.upload_from_filename(path_to_file)
        # print(buckets = list(storage_client.list_buckets())

        # # Retrieve an existing bucket
        # # https://console.cloud.google.com/storage/browser/[bucket-id]/
        # bucket = client.get_bucket('bucket-id')
        # # Then do other things...
        # blob = bucket.get_blob('remote/path/to/file.txt')
        # print(blob.download_as_bytes())
        # blob.upload_from_string('New contents!')

    if args["saveAsImage"]:
        print("saving image as png")
        imwrite(f"{img_file}.png", raw_to_shape)

    if args["scp"]:
        print("uploading to server")
        os.system(f"sudo sshpass -p {password} scp -P {port} {im_dir}* {username}@{host}:{local_location}")
        os.system(f"export data={img_file}")
        print("transfering remote file to dbms")
        payload = {
            "dtime": dtime,
            "device_id": device_id,
            "ppl": det_file,
            "image": img_file,
        }
        os.system(f"python3 ../insert_to_db.py")

    if args["ftp"]:
        print("uploading to ftp")
        with FTP(FTP_ADDR, FTP_USER, FTP_PASS) as ftp:
            ftp.cwd(device_id)
            with open(img_file, 'rb') as file:
                ftp.storbinary('STOR ' + img_name, file)
            with open(det_file, 'rb') as file:
                ftp.storbinary('STOR ' + det_name, file)

    # if args["dbms"]:
    #     print("inserting to db")
    #     payload = {
    #         "dtime": dtime,
    #         "device_id": device_id,
    #         "ppl": det_file,
    #         "image": img_file,
    #     }
    #     db_insert = col.insert_one(payload)
    #     print(db_insert.inserted_ids)

########################################################################

    if not args["localSave"]:
        os.system("rm images/*")
    LOOP = args["loop"]

    print("-"*24, "FINISH", "-"*6, "\n"*2)

    time.sleep(int(args["frequency"]))
# camera.stop_preview()
