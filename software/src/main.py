import mss
import serial
import subprocess
import time

shot = mss.mss()

_magick = "convert shot.png -resize 480x320 -background black -gravity center -extent 480x320 shot.png".split()
_refmt = "img8882565 shot.png shot.bin 3 0".split()

def cap():
    shot.shot(output="shot.png")
    subprocess.call(_magick)
    subprocess.call(_refmt)
    with open("shot.bin", mode="rb") as f:
        return f.read()

ser = serial.Serial(
    port="/dev/ttyACM0",
    baudrate=921600,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=None
)

time.sleep(6)

while True:
    data = cap()
    pixel = 0
    for k in range(10):
        for j in range(64):
            for i in range(15):
                ser.write(data[pixel:pixel+32])
                pixel += 32
        time.sleep(0.2)
