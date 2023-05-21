# arduino-screenshare
Cast your PC's display to an Arduino TFT

## Firmware
Runs on Arduino Mega 2560 with 32K of XRAM and a 3.5" parallel TFTLCD.
Plug the Arduino into your PC, on port `/dev/ttyACM0`.

Arduino libraries required:
- libAdafruit_GFX_Library.a (bundled)
- libMCUFRIEND_kbv.a (bundled)
- libeztft.a (bundled)
- libatmega2560.a (bundled) - the core

Compile:
```shell
$ cd firmware
$ make ARDUINO_DIR=/path/to/arduino ARDUINO_DIR_3RDPARTY=/path/to/arduino-3rdparty
```

## Software
Requires python3, the `mss` module (pip), [img8882565](https://github.com/beaver700nh/img8882565), and ImageMagick.

```shell
$ cd software
$ python src/main.py
```
