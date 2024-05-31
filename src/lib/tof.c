#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void init_tof(void) {
    // Internal pullup on SCL and SDA
	PORTD |= (1 << PD0) | (1 << PD1);

	// Set bus speed to 100kHz
	TWBR = 32;

	// Enable TWI
	TWCR |= (1 << TWEN);

}

void i2cWaitForComplete(void) {
    while(!(TWCR & (1 << TWINT)));
}

void i2cSendStart(void) {
    TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);
    i2cWaitForComplete();
}

void i2cSendStop(void){
    TWCR = (1<<TWINT)|(1<<TWSTO)| (1<<TWEN);
}

void i2cSend(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    i2cWaitForComplete();
}

uint8_t i2cReadAck(void) {
    TWCR = (1<<TWINT)|(1<<TWEA) | (1<<TWEN);
    i2cWaitForComplete();
    return (TWDR);
}

uint8_t i2cReadNoAck() {
    TWCR = (1<<TWINT)| (1<<TWEN);
    i2cWaitForComplete();
    return (TWDR);
}

void i2cSendData(uint8_t tof_addr, uint8_t addr1, uint8_t addr2, uint8_t data) {
    i2cSendStart();
    i2cSend(tof_addr);
    i2cSend(addr1);
    i2cSend(addr2);
    i2cSend(data);
    i2cSendStop();
}
uint8_t i2cRecieveData(uint8_t tof_addr_w, uint8_t tof_addr_r, uint8_t addr1, uint8_t addr2){
        i2cSendStart();
        i2cSend(tof_addr_w);
        i2cSend(addr1);
        i2cSend(addr2);
        i2cSendStart();
        i2cSend(tof_addr_r);
        uint8_t firstByte = i2cReadNoAck();
        i2cSendStop();

        return firstByte;
}

void loadSettings(uint8_t tof_addr_w){
    i2cSendData(tof_addr_w, 0x02, 0x07, 0x01);
    i2cSendData(tof_addr_w, 0x02, 0x08, 0x01);
    i2cSendData(tof_addr_w, 0x00, 0x96, 0x00);
    i2cSendData(tof_addr_w, 0x00, 0x97, 0xfd);
    i2cSendData(tof_addr_w, 0x00, 0xe3, 0x00);
    i2cSendData(tof_addr_w, 0x00, 0xe4, 0x04);
    i2cSendData(tof_addr_w, 0x00, 0xe5, 0x02);
    i2cSendData(tof_addr_w, 0x00, 0xe6, 0x01);
    i2cSendData(tof_addr_w, 0x00, 0xe7, 0x03);
    i2cSendData(tof_addr_w, 0x00, 0xf5, 0x02);
    i2cSendData(tof_addr_w, 0x00, 0xd9, 0x05);
    i2cSendData(tof_addr_w, 0x00, 0xdb, 0xce);
    i2cSendData(tof_addr_w, 0x00, 0xdc, 0x03);
    i2cSendData(tof_addr_w, 0x00, 0xdd, 0xf8);
    i2cSendData(tof_addr_w, 0x00, 0x9f, 0x00);
    i2cSendData(tof_addr_w, 0x00, 0xa3, 0x3c);
    i2cSendData(tof_addr_w, 0x00, 0xb7, 0x00);
    i2cSendData(tof_addr_w, 0x00, 0xbb, 0x3c);
    i2cSendData(tof_addr_w, 0x00, 0xb2, 0x09);
    i2cSendData(tof_addr_w, 0x00, 0xca, 0x09);
    i2cSendData(tof_addr_w, 0x01, 0x98, 0x01);
    i2cSendData(tof_addr_w, 0x01, 0xb0, 0x17);
    i2cSendData(tof_addr_w, 0x01, 0xad, 0x00);
    i2cSendData(tof_addr_w, 0x00, 0xff, 0x05);
    i2cSendData(tof_addr_w, 0x01, 0x00, 0x05);
    i2cSendData(tof_addr_w, 0x01, 0x99, 0x05);
    i2cSendData(tof_addr_w, 0x01, 0xa6, 0x1b);
    i2cSendData(tof_addr_w, 0x01, 0xac, 0x3e);
    i2cSendData(tof_addr_w, 0x01, 0xa7, 0x1f);
    i2cSendData(tof_addr_w, 0x00, 0x30, 0x00);



    i2cSendData(tof_addr_w, 0x00, 0x11, 0x10);
    i2cSendData(tof_addr_w, 0x01, 0x0A, 0x30);
    i2cSendData(tof_addr_w, 0x00, 0x3F, 0x46);
    i2cSendData(tof_addr_w, 0x00, 0x31, 0xFF);
    i2cSendData(tof_addr_w, 0x00, 0x41, 0x63);
    i2cSendData(tof_addr_w, 0x00, 0x2E, 0x01);
    i2cSendData(tof_addr_w, 0x00, 0x1B, 0x09);
    i2cSendData(tof_addr_w, 0x00, 0x3e, 0x31);
    i2cSendData(tof_addr_w, 0x00, 0x14, 0x04);
    // Reset fist boot
    i2cSendData(tof_addr_w, 0x00, 0x16, 0x00);
}

uint8_t get_tof_distance_in_mm(uint8_t tof_addr_w, uint8_t tof_addr_r){
    uint8_t interuptResult = 0;
    while (!(i2cRecieveData(tof_addr_w, tof_addr_r, 0x00, 0x4D) & 0x01));
    i2cSendData(tof_addr_w, 0x00, 0x18, 0x01);
    while (!(interuptResult & 0x04)){
            interuptResult = i2cRecieveData(tof_addr_w, tof_addr_r, 0x00, 0x4F);
    }

    uint8_t result = i2cRecieveData(tof_addr_w, tof_addr_r, 0x00, 0x62);
    i2cSendData(tof_addr_w, 0x00, 0x15, 0x07);
    return result;
}


