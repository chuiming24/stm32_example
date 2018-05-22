#include <i2c.h>
#include <eeprom.h>
#include "stm32f10x.h"



void Eeprom_Init(void){
	i2c_init();
}

void Eeprom_Read(u8 addr, u8 *data, u8 length){
	unsigned char i;
	
	I2CStart(); 
	I2CSendByte(0xa0);
	I2CWaitAck(); 
	
	I2CSendByte(addr);
	I2CWaitAck(); 
	
	I2CStart();
	I2CSendByte(0xa1); 
	I2CWaitAck();
	
	for(i = 0; i < length; i++){
		*data = I2CReceiveByte(); 
		I2CSendAck(); 
		data++;
	}
	I2CStop();
}

void Eeprom_Write(u8 addr, u8 *data, u8 length){
	unsigned char i;
	
	I2CStart(); 
	I2CSendByte(0xa0); 
	I2CWaitAck(); 
	
	I2CSendByte(addr);	
	I2CWaitAck(); 
	
	for(i = 0; i < length; i++){
		I2CSendByte(*data);
		I2CWaitAck(); 
		data++;
	}
	I2CStop();		
}
