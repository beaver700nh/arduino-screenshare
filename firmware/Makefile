export ARDUINO_DIR := /usr/share/arduino/hardware/archlinux-arduino/avr/
export ARDUINO_DIR_3RDPARTY := ~/Arduino/

.PHONY: all
all: build upload

.PHONY: build
build:
	(mkdir -p build; cd build; cmake .. && make -j4)

.PHONY: upload
upload:
	avrdude -c wiring -p atmega2560 -P /dev/ttyACM0 -b 115200 -D -U flash:w:build/bin/arduino-screenshare.hex:i

.PHONY: run
run:
	picocom --quiet --baud=921600 --databits=8 --parity=n --stopbits=1 --flow=n --imap="lfcrlf" /dev/ttyACM0

.PHONY: clean
clean:
	rm -r build
