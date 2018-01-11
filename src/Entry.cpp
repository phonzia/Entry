//
// Created by phonzia on 2017/7/21.
//

#include "Entry.h"
#include <string.h>

using namespace sine;
using namespace cppbase::stringtool;

namespace {
void safe_localtime(struct tm *ptm, const time_t t) {
#if defined(HAVE_LOCALTIME_R)
    // autoconf detected POSIX's localtime_r() on this system
    localtime_r(&t, ptm);
#else
    // No explicitly thread-safe localtime() replacement found.  This
    // may still be thread-safe, as some C libraries take special steps
    // within localtime() to get thread safety, such as TLS.
    memcpy(ptm, localtime(&t), sizeof(tm));
#endif
}
}

Entry::Entry() {
}

bool Entry::parse(const std::string &cron_expr) {
    try {
        std::string expr = trimAll(cron_expr);
        if (expr[0] == '@') {
            if (expr == "@monthly") {
                expr = "0 0 0 1 * *";
            } else if (expr == "@daily") {
                expr = "0 0 0 * * *";
            } else if (expr == "@hourly") {
                expr = "0 0 * * * *";
            } else if (expr == "@minutely") {
                expr = "0 * * * * *";
            } else if (expr == "@weekly") {
                expr = "0 0 0 * * 0";
            } else if (expr == "@secondly") {
                expr = "* * * * * *";
            }
        }

        return second_.parse(stringTok(expr, " ")) &&
               minute_.parse(stringTok(expr, " ")) &&
               hour_.parse(stringTok(expr, " ")) &&
               day_.parse(stringTok(expr, " ")) &&
               month_.parse(stringTok(expr, " ")) &&
               week_.parse(stringTok(expr, " "));
    } catch (std::exception &e) {
        // log error
    }

    return false;
}

bool Entry::check(time_t timestamp) {
    struct tm tm;
    safe_localtime(&tm, timestamp);

    int16_t month = static_cast<int16_t>(tm.tm_mon + 1);
    int16_t day = static_cast<int16_t>(tm.tm_mday);
    int16_t hour = static_cast<int16_t>(tm.tm_hour);
    int16_t minute = static_cast<int16_t>(tm.tm_min);
    int16_t second = static_cast<int16_t>(tm.tm_sec);
    int16_t week = static_cast<int16_t>(tm.tm_wday);

    return month_.check(month) &&
           day_.check(day) &&
           hour_.check(hour) &&
           minute_.check(minute) &&
           second_.check(second) &&
           week_.check(week);
}
