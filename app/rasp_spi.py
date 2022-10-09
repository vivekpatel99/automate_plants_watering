import spidev
import time

device = 1


def init_spi():
	spi= spidev.SpiDev()
	spi.open(0,device)
	spi.max_speed_hz = 10000 #16_000_000
	spi.mode = 0b11;
	time.sleep(0.05)	
	return spi

def read_data():
	spi = init_spi()
	try:	
		while(True):
			#resp =  spi.xfer([0])
			#print(resp)
			print(spi.readbytes(1))
			time.sleep(1)
	finally:
		spi.close()
			

if __name__ == '__main__':
	read_data()
