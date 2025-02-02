/*
 * rtc.c
 *
 *  Created on: Apr 11, 2024
 *      Author: an nguyen
 */

#include "rtc.h"

extern I2C_HandleTypeDef hi2c1;

uint8_t Decimal2BCD(uint8_t num)
{
  return (num/10)<<4|(num%10);
}

uint8_t BCD2Decimal(uint8_t num)
{
 return (num>>4)*10+(num&0x0F);
}

void RTC_ReadTime (RTC_Typedef *rtc, DateTime *dt)
{
	uint8_t buff[7];
	uint8_t addr_reg = 0;
	HAL_I2C_Master_Transmit(rtc->rtc, RTC_ADDR, &addr_reg, 1, 300);
	HAL_I2C_Master_Receive(rtc->rtc, RTC_ADDR, buff, 7, 300);
	dt->sec = BCD2Decimal(buff[0]);
	dt->min = BCD2Decimal(buff[1]);
	dt->hour = BCD2Decimal(buff[2]);
	dt->day = BCD2Decimal(buff[3]);
	dt->date = BCD2Decimal(buff[4]);
	dt->month = BCD2Decimal(buff[5]);
	dt->year = BCD2Decimal(buff[6]);

}

void RTC_WriteTime(RTC_Typedef *rtc, DateTime *dt)
{
	uint8_t buff[8];
	buff[0] = 0;
	buff[1] = Decimal2BCD(dt->sec);
	buff[2] = Decimal2BCD(dt->min);
	buff[3] = Decimal2BCD(dt->hour);
	buff[4] = Decimal2BCD(dt->day);
	buff[5] = Decimal2BCD(dt->date);
	buff[6] = Decimal2BCD(dt->month);
	buff[7] = Decimal2BCD(dt->year);
	HAL_I2C_Master_Transmit(rtc->rtc,RTC_ADDR,buff,8,100);
}
void RTC_Init (RTC_Typedef *rtc,I2C_HandleTypeDef *i2c, DateTime *dt)
{
	rtc->rtc = i2c;
	rtc->time = dt;
}

