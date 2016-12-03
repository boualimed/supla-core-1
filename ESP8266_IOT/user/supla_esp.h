/*
 ============================================================================
 Name        : supla_esp.h
 Author      : Przemyslaw Zygmunt przemek@supla.org
 Version     : 1.3
 Copyright   : GPLv2
 ============================================================================
*/

#ifndef SUPLA_ESP_H_
#define SUPLA_ESP_H_

#include "supla-dev/proto.h"

#define LO_VALUE  0
#define HI_VALUE  1

#define RELAY_INIT_VALUE LO_VALUE
#define SAVE_STATE_DELAY  1000


#define GPIO_PORT_INIT \
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4); \
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5); \
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); \
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13); \
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14)

#define GPIO_PORT_POST_INIT
#define RELAY_BEFORE_CHANGE_STATE
#define RELAY_AFTER_CHANGE_STATE


#ifdef __BOARD_gate_module_mem
	#define __BOARD_gate_module
	#define RELAY1_ELLOCK_MEM
#endif

#ifdef __BOARD_gate_module_wroom_mem
	#define __BOARD_gate_module_wroom
	#define RELAY1_ELLOCK_MEM
#endif

#ifdef __BOARD_gate_module2_wroom_mem
	#define __BOARD_gate_module2_wroom
	#define RELAY1_ELLOCK_MEM
#endif

#if defined(__BOARD_dht11_esp01)

	#define DEVICE_NAME "SUPLA-DHT11-ESP01"
	#define SENSOR_DHT11
	#define TEMPERATURE_CHANNEL 0
	#define CFG_PORT         0

#elif defined(__BOARD_dht22_esp01)

	#define DEVICE_NAME "SUPLA-DHT22-ESP01"
	#define SENSOR_DHT22
	#define TEMPERATURE_CHANNEL 0
	#define CFG_PORT         0

#elif defined(__BOARD_am2302_esp01)

	#define DEVICE_NAME "SUPLA-AM2302-ESP01"
	#define SENSOR_DHT22
	#define TEMPERATURE_CHANNEL 0
	#define CFG_PORT         0


#elif defined(__BOARD_thermometer_esp01)

	#define DEVICE_NAME "SUPLA-THERMOMETER-ESP01"
	#define DS18B20
	#define TEMPERATURE_CHANNEL 0
	#define CFG_PORT         0

#elif defined(__BOARD_thermometer_esp01_ds_gpio0)

	#define DEVICE_NAME "SUPLA-THERMOMETER-ESP01"
	#define DS18B20
	#define W1_GPIO0
	#define TEMPERATURE_CHANNEL 0
	#define CFG_PORT         2

#elif defined(__BOARD_wifisocket) || defined(__BOARD_wifisocket_54)

	#define DS18B20
	#define CFGBTN_TYPE_SELECTION
	#define DEVICE_NAME "SUPLA-SOCKET"
	#define TEMPERATURE_CHANNEL 1
	#define LED_RED_PORT    13
	#define LED_GREEN_PORT  12
	#define LED_BLUE_PORT   14
	#define RELAY_STATE_RESTORE

	#ifdef __BOARD_wifisocket_54
		#define RELAY1_PORT      5
		#define CFG_PORT         4
	#else
		#define RELAY1_PORT      4
		#define CFG_PORT         5
	#endif


#elif defined(__BOARD_wifisocket_esp01)

	#define DEVICE_NAME "SUPLA-SOCKET"
	#define RELAY1_PORT      0
	#define CFG_PORT         2

#elif defined(__BOARD_gate_module_esp01)

	#define DEVICE_NAME "SUPLA-GATE-MODULE-ESP01"
	#define RELAY1_PORT      0
	#define CFG_PORT         2

#elif defined(__BOARD_gate_module_esp01_ds)

	#define DEVICE_NAME "SUPLA-GATE-MODULE-ESP01"
	#define RELAY1_PORT      3
	#define CFG_PORT         0
	#define TEMPERATURE_CHANNEL 1
	#define USE_GPIO3
	#define DS18B20

#elif defined(__BOARD_gate_module) \
	|| defined(__BOARD_gate_module_dht11) \
	|| defined(__BOARD_gate_module_dht22)

	#define DEVICE_NAME "SUPLA-GATE-MODULE"

	#if defined(__BOARD_gate_module_dht11)
		#define SENSOR_DHT11
	#elif defined(__BOARD_gate_module_dht22)
		#define SENSOR_DHT22
	#else
		#define DS18B20
	#endif

	#define RESET_RELAY_PORT
	#define TEMPERATURE_CHANNEL 4

	#define LED_GREEN_PORT  12
	#define LED_BLUE_PORT   14

	#define CFG_PORT         5

	#define RELAY1_PORT      4
	#define RELAY2_PORT      13

	#define INPUT_PORT1      12
	#define INPUT_PORT2      14


#elif defined(__BOARD_gate_module_wroom)

	#define DEVICE_NAME "SUPLA-GATE-MODULE"
	#define RESET_RELAY_PORT
	#define DS18B20
	#define TEMPERATURE_CHANNEL 4

	#define LED_GREEN_PORT  5
	#define LED_BLUE_PORT   12

	#define CFG_PORT         13

	#define RELAY1_PORT      4
	#define RELAY2_PORT      14

	#define INPUT_PORT1      5
	#define INPUT_PORT2      12


#elif defined(__BOARD_gate_module2_wroom)

	#define DEVICE_NAME "SUPLA-GATE-MODULE"
	#define RESET_RELAY_PORT
	#define DS18B20
	#define TEMPERATURE_CHANNEL 4

	#define LED_GREEN_PORT  12
	#define LED_BLUE_PORT   14

	#define CFG_PORT         13
	#define RELAY1_PORT      4
	#define RELAY2_PORT      5

	#define INPUT_PORT1      12
	#define INPUT_PORT2      14


#elif defined(__BOARD_rs_module)

	#define DEVICE_NAME "SUPLA-RS-MODULE"
	#define RESET_RELAY_PORT
	#define DS18B20
	#define TEMPERATURE_CHANNEL 2

	#define LED_GREEN_PORT  12
	#define LED_BLUE_PORT   14

	#define CFG_PORT         5

	#define RELAY1_PORT      4
	#define RELAY2_PORT      13

	#define INPUT_PORT1      12

#elif defined(__BOARD_rs_module_wroom)

	#define DEVICE_NAME "SUPLA-RS-MODULE"
	#define RESET_RELAY_PORT
	#define DS18B20

	#define TEMPERATURE_CHANNEL 2

	#define LED_GREEN_PORT  5
	#define LED_BLUE_PORT   12

	#define CFG_PORT         13
	#define RELAY1_PORT      4
	#define RELAY2_PORT      14

	#define INPUT_PORT1      5

#elif defined(__BOARD_starter1_module_wroom)

	#define DS18B20
	#define BTN_PULLUP
	#define W1_GPIO5
	#define DEVICE_NAME "SUPLA-STARTER1-MODULE"

	#define TEMPERATURE_CHANNEL 2

	#define LED_RED_PORT  14

	#define CFG_PORT         12
	#define RELAY1_PORT      4
	#define RELAY2_PORT      13

#elif defined(__BOARD_jangoe_rs)

	#define DEVICE_NAME "JANGOE-RS-MODULE"
	#define RESET_RELAY_PORT

	#define INPUT_PORT1      4

	#define CFG_PORT         5

	#define RELAY1_PORT      14
	#define RELAY2_PORT      2


	#undef GPIO_PORT_INIT

	#define GPIO_PORT_INIT \
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2); \
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4); \
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5); \
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); \
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13); \
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14)

	#undef LO_VALUE
	#undef HI_VALUE

	#define LO_VALUE  1
	#define HI_VALUE  0

#elif defined(__BOARD_jangoe_wifisocket)

	#define DEVICE_NAME "JANGOE-WIFISOCKET"

	#define CFG_PORT         5

	#define RELAY1_PORT      14
	#define RELAY2_PORT      2

	#define BUTTON1_PORT      13
	#define BUTTON2_PORT      12

	#undef GPIO_PORT_INIT

	#define GPIO_PORT_INIT \
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2); \
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4); \
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5); \
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); \
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13); \
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14)

	#undef LO_VALUE
	#undef HI_VALUE

	#define LO_VALUE  1
	#define HI_VALUE  0

#elif defined(__BOARD_sonoff)

	#define DEVICE_NAME "SONOFF"
	#define RELAY1_PORT      12
	#define CFG_PORT         0
	#define LED_RED_PORT     13
	#define RELAY_STATE_RESTORE

#elif defined(__BOARD_sonoff_ds18b20)

	#define DS18B20
	#define DEVICE_NAME "SONOFF-DS18B20"
	#define RELAY1_PORT      12
	#define CFG_PORT         0
	#define LED_RED_PORT     13
	#define TEMPERATURE_CHANNEL 1
	#define W1_GPIO3
	#define RELAY_STATE_RESTORE

#elif defined(__BOARD_dimmer)

	#define DEVICE_NAME "DIMMER"
	#define CFG_PORT         0
	#define DIMMER_CHANNEL   0
	#define SUPLA_PWM_COUNT  1

#elif defined(__BOARD_EgyIOT)

	#define DEVICE_NAME "EgyIOT"

	#define USE_GPIO16_OUTPUT
	#define RELAY1_PORT      4
	#define RELAY2_PORT      13
	#define RELAY3_PORT      16

	#define CFG_PORT                 0
	#define RGB_CONTROLLER_CHANNEL   3
	#define SUPLA_PWM_COUNT          3


	#define PWM_0_OUT_IO_MUX PERIPHS_IO_MUX_MTMS_U
	#define PWM_0_OUT_IO_NUM 14
	#define PWM_0_OUT_IO_FUNC  FUNC_GPIO14

	#define PWM_1_OUT_IO_MUX PERIPHS_IO_MUX_MTDI_U
	#define PWM_1_OUT_IO_NUM 12
	#define PWM_1_OUT_IO_FUNC  FUNC_GPIO12

	#define PWM_2_OUT_IO_MUX PERIPHS_IO_MUX_GPIO5_U
	#define PWM_2_OUT_IO_NUM 5
	#define PWM_2_OUT_IO_FUNC  FUNC_GPIO5



#elif defined(__BOARD_zam_row_01)

#include "com/zam/supla_esp.h"

#elif defined(__BOARD_rgbw) || defined(__BOARD_rgbw_wroom)

	#define DEVICE_NAME "RGBW-CONTROLLER"

	#define CFG_PORT         0
	#define SUPLA_PWM_COUNT  5
	#define RGBW_CONTROLLER_CHANNEL  0
	#define COLOR_BRIGHTNESS_PWM

#elif defined(__BOARD_rgb_aqua)

	#define DEVICE_NAME "RGB-CONTROLLER-AQUA"

	#define CFG_PORT         4
	#define LED_RED_PORT     5
	#define SUPLA_PWM_COUNT  3
	#define RGB_CONTROLLER_CHANNEL  0

	#define PWM_0_OUT_IO_MUX PERIPHS_IO_MUX_MTMS_U
	#define PWM_0_OUT_IO_NUM 13
	#define PWM_0_OUT_IO_FUNC  FUNC_GPIO13

	#define PWM_1_OUT_IO_MUX PERIPHS_IO_MUX_MTCK_U
	#define PWM_1_OUT_IO_NUM 12
	#define PWM_1_OUT_IO_FUNC  FUNC_GPIO12

	#define PWM_2_OUT_IO_MUX PERIPHS_IO_MUX_MTDI_U
	#define PWM_2_OUT_IO_NUM 14
	#define PWM_2_OUT_IO_FUNC  FUNC_GPIO14


#elif defined(__BOARD_h801)

	#define DEVICE_NAME "H801-RGBWW"

	#define CFG_PORT         0
	#define LED_RED_PORT  5
	#define SUPLA_PWM_COUNT  5
	#define RGBWW_CONTROLLER_CHANNEL  0

	#define PWM_0_OUT_IO_MUX PERIPHS_IO_MUX_MTDO_U
	#define PWM_0_OUT_IO_NUM 15
	#define PWM_0_OUT_IO_FUNC  FUNC_GPIO15

	#define PWM_1_OUT_IO_MUX PERIPHS_IO_MUX_MTCK_U
	#define PWM_1_OUT_IO_NUM 13
	#define PWM_1_OUT_IO_FUNC  FUNC_GPIO13

	#define PWM_2_OUT_IO_MUX PERIPHS_IO_MUX_MTDI_U
	#define PWM_2_OUT_IO_NUM 12
	#define PWM_2_OUT_IO_FUNC  FUNC_GPIO12

	#define PWM_3_OUT_IO_MUX PERIPHS_IO_MUX_MTMS_U
	#define PWM_3_OUT_IO_NUM 14
	#define PWM_3_OUT_IO_FUNC  FUNC_GPIO14

	#define PWM_4_OUT_IO_MUX PERIPHS_IO_MUX_GPIO4_U
	#define PWM_4_OUT_IO_NUM 4
	#define PWM_4_OUT_IO_FUNC  FUNC_GPIO4
#endif


// PWM ----------------------------------

#ifndef PWM_0_OUT_IO_MUX
	#define PWM_0_OUT_IO_MUX PERIPHS_IO_MUX_GPIO4_U
	#define PWM_0_OUT_IO_NUM 4
	#define PWM_0_OUT_IO_FUNC  FUNC_GPIO4
#endif

#ifndef PWM_1_OUT_IO_MUX
	#define PWM_1_OUT_IO_MUX PERIPHS_IO_MUX_GPIO5_U
	#define PWM_1_OUT_IO_NUM 5
	#define PWM_1_OUT_IO_FUNC  FUNC_GPIO5
#endif

#ifndef PWM_2_OUT_IO_MUX
	#define PWM_2_OUT_IO_MUX PERIPHS_IO_MUX_MTDI_U
	#define PWM_2_OUT_IO_NUM 12
	#define PWM_2_OUT_IO_FUNC  FUNC_GPIO12
#endif

#ifndef PWM_3_OUT_IO_MUX
	#define PWM_3_OUT_IO_MUX PERIPHS_IO_MUX_MTCK_U
	#define PWM_3_OUT_IO_NUM 13
	#define PWM_3_OUT_IO_FUNC  FUNC_GPIO13
#endif

#ifndef PWM_4_OUT_IO_MUX
	#define PWM_4_OUT_IO_MUX PERIPHS_IO_MUX_MTMS_U
	#define PWM_4_OUT_IO_NUM 14
	#define PWM_4_OUT_IO_FUNC  FUNC_GPIO14
#endif

#ifndef PWM_PERIOD
	#define PWM_PERIOD 1000
#endif

// --------------------------------------

#define AP_SSID "SUPLA-ESP8266"

#define SPI_FLASH_SEC_SIZE  4096
#define SERVER_MAXSIZE      100
#define WIFI_SSID_MAXSIZE   32
#define WIFI_PWD_MAXSIZE    64

#define STATE_MAXSIZE       200

#define RECVBUFF_MAXSIZE  1024

#define ACTIVITY_TIMEOUT 10

#if defined(SENSOR_DHT11) || defined(SENSOR_DHT22) || defined(SENSOR_AM2302)
#define DHTSENSOR
#endif



#endif /* SUPLA_ESP_H_ */
