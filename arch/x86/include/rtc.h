#ifndef RTC_H
#define RTC_H

#include <stdint.h>

#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

#define REG_SECONDS 0x00
#define REG_MINUTES 0x02
#define REG_HOURS 0x04
#define REG_DAY 0x07
#define REG_MONTH 0x08
#define REG_YEAR 0x09

struct Rtc_time
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t mday;
    uint8_t mon;
    uint16_t year;
};

void rtc_init();
struct Rtc_time get_rtc_time();

#endif