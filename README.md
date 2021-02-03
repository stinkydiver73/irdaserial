# irdaserial

IRDA usb serial adapter firmware at 19200 baud for arduino nano (ATMEGA328 + CH340) and TFDS4500 ir transceiver.
It's mimic the Microchip MCP2120 infrared encoder/decoder with 2 timers.
IRDA rx is a longer negtive pulse on an IR pulse received.
IRDA tx is a half bit delayed short pulse when the serial port is low, repeating while the serial port stays low. 
