//
// Created by rhp on 18-12-4.
//

#ifndef RENDA_DATE_H
#define RENDA_DATE_H

#include "copyable.h"
#include "types.h"
namespace renda
{

class Date : public copyable
{
  public:
    struct YearMonthDay
    {
        int year;
        int month;
        int day;
    };

    static const int kDaysPerWeek = 7;
    static const int kJulianDayof1970_01_01;

    Date()
        : julianDayNum_(0)
    {
    }

    Date(int year, int month, int day);

    explicit Date(int julianDay)
        : julianDayNum_(julianDay)
    {
    }

    explicit Date(const tm &);

    void swap(Date &that)
    {
        std::swap(julianDayNum_, that.julianDayNum_);
    }

    bool valid()
    {
        return julianDayNum_ > 0;
    }

    string toIsoString() const;

    YearMonthDay yearMonthDay() const;

    int year() const
    {
        return yearMonthDay().year;
    }

    int month() const
    {
        return yearMonthDay().month;
    }

    int day() const
    {
        return yearMonthDay().day;
    }

    int weekDay() const
    {
        return (julianDayNum_ + 1) % kDaysPerWeek;
    }

    int julianDayNumber() const
    {
        return julianDayNum_;
    }

  private:
    int julianDayNum_;
};

inline bool operator<(Date &x, Date &y)
{
    return x.julianDayNumber() < y.julianDayNumber();
}

inline bool operator==(Date &x, Date &y)
{
    return x.julianDayNumber() == y.julianDayNumber();
}

} // namespace renda

#endif //RENDA_DATE_H
