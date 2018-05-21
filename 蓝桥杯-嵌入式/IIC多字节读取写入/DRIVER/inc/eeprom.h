#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "stm32f10x.h"


void Eeprom_Init(void);
void Eeprom_Read(u8 addr, u8 *data, u8 length);

void Eeprom_Write(u8 addr, u8 *data, u8 length);


#endif

