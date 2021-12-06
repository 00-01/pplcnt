import numpy as np
import cv2
from glob import glob


# filename = "IR_MVPC10_0004_20211206-14_07_54.bin"
filename = "IR_MVPC10_0004_20211206-14_13_04.bin"
calibration = "Calibration.bin"

# raw = []
with open(filename, mode='rb') as f:
    raw = np.fromfile(f, dtype=np.int16)
    raw_shaped = np.reshape(raw, (80, 80))
    # cnt = 0
    # byte = f.read(2)
    # while byte:
    #     byte_to_int = int.from_bytes(byte, byteorder="little", signed=False)
    #     raw.append(byte_to_int)
    #     byte = f.read(2)
    #     cnt += 1

# cal = []
with open(calibration, mode='rb') as c:
    cal = np.fromfile(c, dtype=np.int16)
    cal_shaped = np.reshape(cal, (80, 80))
    # cnt = 0
    # byte = c.read(1)
    # while byte:
    #     if cnt%2 == 1:
    #         byte_to_int = int.from_bytes(byte, byteorder="little", signed=False)
    #         cal.append(byte_to_int)
    #     byte = c.read(1)
    #     cnt += 1

calibratedImage = np.subtract(raw, cal)
calibratedImage_to_shape = np.reshape(calibratedImage, (80, 80))

# calibratedImage_to_shape = np.reshape(calibratedImage, (80, 80))


cv2.imwrite(f"{filename}.jpg", calibratedImage_to_shape)
cv2.imshow("asdf", calibratedImage_to_shape)
cv2.waitKey()

