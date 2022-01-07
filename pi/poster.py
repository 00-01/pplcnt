#!/usr/bin/env python3
import argparse
import os
from glob import glob
import requests

ap = argparse.ArgumentParser()
ap.add_argument("-l", "--loop", default=1, help="run loop")
ap.add_argument("-f", "--frequency", default=10, help="loop frequency")
ap.add_argument("-scp", "--scp", default=1, help="save to scp")
args = vars(ap.parse_args())

# args
print(f"loop is {args['loop']}")
print(f"frequency is {args['frequency']} seconds")
print("\n")

# HOME_DIR = os.path.expanduser('~')
# with open(f"{HOME_DIR}/info.txt") as f:
#     device_id = f.readline().rstrip()

device_id = 'MVPC10_0004'

url = 'http://115.68.37.86:8180/api/data'

# scp
host = "192.168.0.5"
port = 22
username = "z"
password = "1234qwer"
local_location = "~/DATA/gappi"

im_dir = "data/"


def post_data(dir_name, det_file, ir_file, rgb_file):
    # data = {
    #     "predicted": det_file
    # }
    files = {
        "predicted": (det_file, open(det_file, 'rb'), 'text/plain'),
        "ir_image": (ir_file, open(ir_file, 'rb'), 'image/png'),
        "rgb_image": (rgb_file, open(rgb_file, 'rb'), 'image/jpeg'),
    }
    r = requests.post(url, files=files) #, data=data)

    if r.status_code == 200:
        os.system(f"rm -rf {dir_name}")

    print(r.headers)
    print(r.url)
    print(r.text)

    return r.text

LOOP = 1
while LOOP:
    targets = glob('/home/z/data/*')
    if len(targets) < 1:
        break
    for target in targets:
        det = glob(f"{target}/*_DET.txt")
        ir = glob(f"{target}/*_IR.png")
        rgb = glob(f"{target}/*_RGB.jpg")
        # det = []
        # with open(det, "r") as file:
        #     det_str = det_str.split(" ")
        #     for i in det_str:
        #         det.append(i)
        if len(det) > 0:
            result = post_data(target, det[0], ir[0], rgb[0])
            print(result)

        if args["scp"]:
            print("uploading to server")
            os.system(f"sudo sshpass -p {password} scp {im_dir}* {username}@{host}:{local_location}")

    LOOP = args["loop"]
