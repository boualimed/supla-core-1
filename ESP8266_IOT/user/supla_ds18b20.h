/*
 ============================================================================
 Name        : supla_ds18b20.h
 Author      : Przemyslaw Zygmunt przemek@supla.org
 Version     : 1.0
 Copyright   : 2016 GPLv2
 ============================================================================
*/

#ifndef SUPLA_DS18B20_H_
#define SUPLA_DS18B20_H_

#include "supla_esp.h"
#include "supla-dev/proto.h"

#ifdef DS18B20
void ICACHE_FLASH_ATTR supla_ds18b20_init(void);
void ICACHE_FLASH_ATTR supla_get_temperature(char value[SUPLA_CHANNELVALUE_SIZE]);
void ICACHE_FLASH_ATTR supla_ds18b20_start(void);
#endif

#endif
