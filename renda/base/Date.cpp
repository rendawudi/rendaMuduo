//
// Created by rhp on 18-12-4.
//

#include "Date.h"
namespace renda
{
namespace details
{
char require_32_bit_int_at_least[sizeof(int) >= sizeof(int32_t) ? 1 : -1];

int getJulianDayNumber(int year, int month, int day)
{
    (void) require_32_bit_int_at_least;
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
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
} // namespace details

const int Date::kJulianDayof1970_01_01 = details::getJulianDayNumber(1970, 0, 0);

} // namespace renda

using namespace renda;
using namespace renda::details;

Date::Date(int y, int m, int d)
    : julianDayNum_(getJulianDayNumber(y, m, d))
{
}

Date::Date(const tm &t)
    : julianDayNum_(getJulianDayNumber(
          t.tm_year + 1900,
          t.tm_mon + 1,
          t.tm_mday))
{
}

string Date::toIsoString() const
{
    char buf[32];
    YearMonthDay ymd(yearMonthDay());
    snprintf(buf, sizeof(buf) - 1, "%4d-%2d-%2d",
        ymd.year, ymd.month, ymd.day);
    return buf;
}

Date::YearMonthDay Date::yearMonthDay() const
{
    return getYearMonthDay(julianDayNum_);
}