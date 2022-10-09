import spidev
import time

device = 1


# reference
# https://www.youtube.com/watch?v=B9eaMVppW4U


def init_spi():
    spi = spidev.SpiDev()
    spi.open(0, device)
    spi.max_speed_hz = 10000
    spi.mode = 0b11
    time.sleep(0.05)
    return spi


def read_data():
    spi = init_spi()
    try:
        while True:
            received_data = spi.readbytes(1)
            print(received_data)
            time.sleep(1)
            return received_data
    finally:
        spi.close()


if __name__ == '__main__':
    read_data()
# test
