#!/usr/bin/env python3
import argparse
import os
from datetime import datetime
from glob import glob
import requests
import time

parser = argparse.ArgumentParser()
parser.add_argument("-l", "--loop", default=0, help="run loop")
parser.add_argument("-s", "--sleep", default=0, help="loop sleep")
parser.add_argument("-d", "--delete", default=1, help="delete sent file")
# parser.add_argument("-scp", "--scp", default=0, help="save to scp")
args = parser.parse_args()

# args
print(f"loop is {args.loop}")
print(f"sleep is {args.sleep} seconds")

with open('device_id.txt') as f:
    device_id = f.readline().rstrip()

im_dir = "data/"

url = 'http://115.68.37.86:8180/api/data'


# host = "192.168.0.5"
# username = "z"
# password = ""
# save_dir = "~/DATA/gappi"

def post_data(dir_name, det_data, ir_file, rgb_file):
    data = {"device_id": device_id,
            "predicted": det_data,
            }
    files = {"ir_image": (ir_file, open(ir_file, 'rb'), 'image/png'),
             "rgb_image": (rgb_file, open(rgb_file, 'rb'), 'image/jpeg')
             # "predicted": (det_file, open(det_file, 'rb'), 'text/plain'),
             }
    r = requests.post(url, data=data, files=files)

    if r.status_code == 200:
        if args.delete:
            os.system(f"rm -rf {dir_name}")
    print(r.headers)

    return r.text


LOOP = 1
while LOOP:
    now = datetime.now()
    dtime = now.strftime("%Y%m%d-%H%M%S")
    print([dtime])

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
        #     os.system(f"sshpass -p {password} scp -r {im_dir}* {username}@{host}:{save_dir}")
    LOOP = args.loop
    time.sleep(int(args.sleep))
