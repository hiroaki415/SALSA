# encoding : utf-8

import spidev

class Sensor:

    spi = spidev.SpiDev()
    msb_flag = 'read'

    def __init__(self, bus, device, mode=0, cshigh=False, msb_flag='read', max_speed_hz=200000, bits_per_word=8, lsbfirst=False):
        
        self.spi.mode = mode
        self.spi.cshigh = cshigh
        self.spi.max_speed_hz = max_speed_hz
        self.spi.bits_per_word = bits_per_word
        self.spi.lsbfirst = lsbfirst

        self.msb_flag = msb_flag
        spi.open(bus,device)

    def read(self, address):
        if msb_flag=='read':
            address |= 0b10000000
        ret =  spi.xfer2([address,0x00])
        return ret[1]

    def write(self, address, data):
        if msb_flag=='write':
            address |= 0b10000000
        ret =  spi.xfer2([address,data])

