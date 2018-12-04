//
// Created by rhp on 18-12-4.
//

#include <stdint-gcc.h>
#include "Date.h"
namespace renda
{
namespace details
{
char require_32_bit_int_at_least[sizeof(int) >= sizeof(int32_t) ? 1:-1];

int getJulianDayNumber(int year, int month, int day)
{
    (void) require_32_bit_int_at_least;
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    return day + (153*m + 2) / 5 + 365*y + y/4 - y/100 + y/400 - 32045;
}

Date::YearMonthDay getYearMonthDay(int julianDayNum)
{
    int a = julianDayNum + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - ((b * 146097) / 4);
    int d = (4 * c + 3) / 1461;
    int e = c - ((1461 * d) / 4);
    int m = (5 * e + 2) / 153;
    Date::YearMonthDay ymd;
    ymd.day = e - ((153 * m + 2) / 5) + 1;
    ymd.month = m + 3 - 12 * (m / 10);
    ymd.year = b * 100 + d - 4800 + (m / 10);
    return ymd;
}
}

static const int Date::kJulianDayof1970_01_01 = details::getJulianDayNumber(1970, 1, 1);

YearMonthDay Date::yearMonthDay() const
{

}
}
}
