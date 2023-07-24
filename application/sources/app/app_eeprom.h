#ifndef __APP_EEPROM_H__
#define __APP_EEPROM_H__

#include <stdint.h>
#include "app.h"

/**
  *****************************************************************************
  * EEPROM define address.
  *
  *****************************************************************************
  */
#define EEPROM_START_ADDR						(0X0000)
#define EEPROM_END_ADDR							(0X1000)

#define EEPROM_SCORE_ADDR           (10)
#define EEPROM_SETTING_ADDR         (110)

#define EEPROM_SCORE_START_ADDR     (0X0010)
#define EEPROM_SCORE_PLAY_ADDR      (0X0014)
#define EEPROM_SCORE_1ST_ADDR       (0X0018)
#define EEPROM_SCORE_2ND_ADDR       (0X001C)
#define EEPROM_SCORE_3RD_ADDR       (0X0020)
#define EEPROM_SCORE_END_ADDR       (0X00FF)

#define EEPROM_SETTING_START_ADDR   (0X0100)
#define EEPROM_SETTING_1_ADDR       (0X0101)
#define EEPROM_SETTING_2_ADDR       (0X0102)
#define EEPROM_SETTING_3_ADDR       (0X0103)
#define EEPROM_SETTING_END_ADDR     (0X01FF)

/******************************************************************************/
/* Archey game */
/******************************************************************************/
typedef struct {
	/* score data */
  uint32_t score_now;
  uint32_t score_1st;
  uint32_t score_2nd;
  uint32_t score_3rd;
} ar_game_score_t;

typedef struct {
  /* setting data */
  uint8_t num_arrow;
  uint8_t arrow_speed;
  uint8_t meteoroid_speed;
} ar_game_setting_t;

typedef struct {
  uint8_t data;
  uint8_t* pbuf = (uint8_t*)&data;
  uint8_t len = sizeof(data);
} ar_game_score;

typedef struct {
  uint8_t data;
  uint8_t* pbuf = (uint8_t*)&data;
  uint8_t len = sizeof(data);
} ar_game_setting;

#endif //__APP_EEPROM_H__
