#Piu-Piu

Welcome to Piu-Piu laser tag battle royale development.

Lora module RFM95 setup:
https://learn.adafruit.com/adafruit-rfm69hcw-and-rfm96-rfm95-rfm98-lora-packet-padio-breakouts?view=all

Wiring: https://learn.adafruit.com/adafruit-rfm69hcw-and-rfm96-rfm95-rfm98-lora-packet-padio-breakouts/arduino-wiring

                        Arduino Uno
                        
Vin               -     5V/3.3V

GND               -     GND

EN (Enable pin)   -     Not connected

G0 (GPIO 0 pin)   -     D3 (h/w interrupt pin)

SCK (SPI Clock)   -     D13

MISO              -     D12

MOSI              -     D11

CS                -     D4 (can be any pin)

RST               -     D2 (can be any pin)


CS, RST, G0 can be changed in line 12-14 in Lora_Transmitter.ino
