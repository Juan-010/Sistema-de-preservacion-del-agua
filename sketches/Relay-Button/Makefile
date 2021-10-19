PORT = /dev/ttyACM0
BOARD = arduino:avr:uno

compile:
	arduino-cli compile -b $(BOARD)
upload:
	arduino-cli upload -b $(BOARD) -p $(PORT)
