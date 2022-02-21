#!/usr/bin/env python3
import argparse
import os
from glob import glob
import requests
import time

parser = argparse.ArgumentParser()
parser.add_argument("-l", "--loop", default=1, help="run loop")
parser.add_argument("-s", "--sleep", default=10, help="loop sleep")
parser.add_argument("-d", "--delete", default=1, help="delete sent file")
# parser.add_argument("-scp", "--scp", default=0, help="save to scp")
args = parser.parse_args()

# args
print(f"loop is {args.loop}")
print(f"sleep is {args.sleep} seconds")
print("\n")

with open('device_id.txt') as f:
    device_id = f.readline().rstrip()

im_dir = "data/"

url = 'http://115.68.37.86:8180/api/data'

# # scp
# host = "192.168.0.5"
# port = 22
# username = "z"
# password = "1234qwer"
# local_location = "~/DATA/gappi"

def post_data(dir_name, det_data, ir_file, rgb_file):
    data = {"device_id": device_id,
            "predicted": det_data,
            }
    files = {#"predicted": (det_file, open(det_file, 'rb'), 'text/plain'),
             "ir_image": (ir_file, open(ir_file, 'rb'), 'image/png'),
             "rgb_image": (rgb_file, open(rgb_file, 'rb'), 'image/jpeg')
             }
    r = requests.post(url, data=data, files=files)

    if r.status_code == 200:
        if args.delete:
            os.system(f"rm -rf {dir_name}")

    print(r.headers)

    return r.text

LOOP = 1
while LOOP:
    targets = glob(f'{im_dir}/*')
    if len(targets) < 1:
        break
    for target in targets:
        det = glob(f"{target}/*_DET.txt")
        ir = glob(f"{target}/*_IR.png")
        rgb = glob(f"{target}/*_RGB.jpg")

        try:
            with open(det[0], "r") as file:
                det_data = file.readline().rstrip()
        except IndexError:
            pass

        if len(det) > 0:
            result = post_data(target, det_data, ir[0], rgb[0])
            print(result)

        # if args["scp"]:
        #     print("uploading to server")
        #     os.system(f"sshpass -p {password} scp -r {im_dir}* {username}@{host}:{local_location}")
    LOOP = args.loop
    time.sleep(int(args.sleep))