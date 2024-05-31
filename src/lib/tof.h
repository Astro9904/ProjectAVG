void init_tof();

void i2cWaitForComplete(void);
void i2cSendStart(void);

void i2cSendStop(void);

void i2cSend(uint8_t tof_addr_w, uint8_t data);

uint8_t i2cReadAck(uint8_t tof_addr_w, uint8_t tof_addr_r);

uint8_t i2cReadNoAck(uint8_t tof_addr_w, uint8_t tof_addr_r);

void i2cSendData(uint8_t tof_addr_w, uint8_t addr1, uint8_t addr2, uint8_t data);
uint8_t i2cRecieveData(uint8_t tof_addr_w, uint8_t tof_addr_r, uint8_t addr1, uint8_t addr2);

void loadSettings(uint8_t tof_addr_w);

uint8_t get_tof_distance_in_mm(uint8_t tof_addr_w, uint8_t tof_addr_r);



