import spidev
import time

device = 1


# reference
# https://www.youtube.com/watch?v=B9eaMVppW4U


def init_spi():
    spi = spidev.SpiDev()
    spi.open(0, device)
    spi.max_speed_hz = 2_50_000  # 10000
    spi.mode = 0b11
    time.sleep(0.05)
    return spi


def read_data():
    spi = init_spi()
    try:
        received_data = spi.readbytes(1)[0]
        return received_data
    finally:
        spi.close()


def send_data(sensor_number: int):
    spi = init_spi()
    try:
        spi.writebytes([sensor_number])
        print(f'data sent {sensor_number}')
    finally:
        spi.close()


if __name__ == '__main__':
    #    while True:
    # data = input();
    send_data(0)
    print(read_data())
