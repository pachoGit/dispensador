#ifndef UTIL_H_
#define UTIL_H_

#include <TimeLib.h>

struct Detail
{
    int hour;

    int minute;

    int amount;

    int type;
};

bool isSameDetail(Detail &d1, Detail &d2)
{
    return (d1.hour == d2.hour && d1.minute == d2.minute);
}

Detail parseInput(String &input)
{
    int hour, minute, amount, type;
    int ikey = 0;
    while (input.length() > 1)
    {
        String output = input.substring(0, input.indexOf(","));
        input = input.substring(input.indexOf(output) + output.length() + 1);
        if (ikey == 0) // Parse la hora
        {
            String shour = output.substring(0, output.indexOf(":"));
            String sminute = output.substring(output.indexOf(":")+1, 5);
            hour = shour.toInt();
            minute = sminute.toInt();
        }
        if (ikey == 1)
        {
            amount = output.toInt();
        }
        if (ikey == 2)
        {
            type = output.toInt();
        }
        ikey++;
    }
    return {hour, minute, amount, type};
}


#endif // UTIL_H_
