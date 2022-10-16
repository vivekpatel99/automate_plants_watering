# automate_plants_watering
## Introduction
This project is measuring moisture via capacitive soil moisture sensor (v1.2) and pump water to the plant. The code is divided into 
two boards.

1. Tiva™ C Series TM4C123G 
   * Moisture Sensor is connected at ADC port 
   * It connected to Raspberry Pi Zero W via SPI communication

2. Raspberry Pi Zero W
   * Sends sensor number to Tiva via SPI and Tiva sends moisture sensor reading in percentage in return
   * Hosts FAST API server to visualize sensor measurement and control pump if needed.

## Pin Connections

| Tiva™ C Series TM4C123G | Capacitive Soil Moisture Sensor |
|:-----------------------:|--------------------------------:|
|          +3.3V          |                        RED Wire |
|           GND           |                      Black Wire |
|           PE3           |                     Yellow Wire |

Raspberry Pi is configured as master and Tiva is configured as slave for SPI communication, as well as
Tiva part is written in C language and Raspberry Pi part is written in python in order to work with API.

| Tiva™ C Series TM4C123G |    Raspberry Pi Zero W    |
|:-----------------------:|:-------------------------:|
|     SSI0Clk 19 PA2      | GPIO 11 (SPI SCLK) PIN:23 |
|     SSI0Fss 20 PA3      | GPIO 7 (SPIO CE1) PIN:26  |
|      SSI0Rx 21 PA4      |   GPIO 10 (MOSI) PIN:19   |
|      SSI0Tx 22 PA5      |   GPIO 9 (MISO) PIN:21    |


## HowTo Setup
### Setup Tiva™ C Series TM4C123G  
   1. Install Code Compose Studio 
   2. Setup Tiva project  https://www.youtube.com/watch?v=RtQYQNF6Jh8
   3. Copy past all the files from Tiva directory

## Setup Raspberry Pi Zero W  
   1. Prepare SD card with Raspberry Pi OS (lite).
   2. Clone the Repo

## HowTo Run the Project
1. Follow HowTo Setup guide
2. Connect moisture sensor and raspberry pi with Tiva 
3. Flash Tiva code into Tiva™ C Series TM4C123G via Code Composer Studio
4. Connect raspberry Pi over SSH 
5. goto to app dir and run following command
    `uvicorn main:app --host 0.0.0.0` 
(for more information about the command please refer to Fast API documentation https://fastapi.tiangolo.com/deployment/manually/)
