#include <stdint.h>
#include "io.h"
#include "interrupts.h"
#include "rtc.h"

uint8_t read_cmos(uint16_t reg)
{
    outb_wait(CMOS_ADDRESS, reg);
    return inb_wait(CMOS_DATA);
}

uint8_t get_update_in_progress_flag()
{
    outb_wait(CMOS_ADDRESS, 0x0A);
    return inb_wait(CMOS_DATA) & 0x80;
}

void rtc_handler()
{
    outb_wait(CMOS_ADDRESS, 0x0C);
    inb_wait(CMOS_DATA);
}

uint8_t bcd_to_bin(uint8_t val)
{
    return ((val / 16) * 10) + (val & 0x0F);
}

struct Rtc_time get_rtc_time()
{
    struct Rtc_time time;

    while (get_update_in_progress_flag())
        ;

    time.sec = read_cmos(REG_SECONDS);

    time.min = read_cmos(REG_MINUTES);
    time.hour = read_cmos(REG_HOURS);

    time.mday = read_cmos(REG_DAY);
    time.mon = read_cmos(REG_MONTH);
    time.year = read_cmos(REG_YEAR);

    uint8_t registerB = read_cmos(0x0B);

    if (!(registerB & 0x04))
    {
        time.sec = bcd_to_bin(time.sec);
        time.min = bcd_to_bin(time.min);
        time.hour = bcd_to_bin(time.hour);
        time.mday = bcd_to_bin(time.mday);
        time.mon = bcd_to_bin(time.mon);
        time.year = bcd_to_bin(time.year);
    }

    if (time.year < 70)
    {
        time.year += 100;
    }
    else if (time.year >= 100)
    {
        time.year -= 100;
    }

    time.year += 1900;

    return time;
}

void rtc_init()
{
    outb_wait(CMOS_ADDRESS, 0x8A);
    uint8_t prev = inb_wait(CMOS_DATA);
    outb_wait(CMOS_ADDRESS, 0x8A);
    outb_wait(CMOS_DATA, (prev & 0xF0) | 0x0F);

    irq_install_handler(8, rtc_handler);
}