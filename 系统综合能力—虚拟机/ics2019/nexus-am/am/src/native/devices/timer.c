#include <am.h>
#include <amdev.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static struct timeval boot_time = {};

size_t __am_timer_read(uintptr_t reg, void *buf, size_t size) {
  switch (reg) {
    case _DEVREG_TIMER_UPTIME: {
      struct timeval now;
      gettimeofday(&now, NULL);
      long seconds = now.tv_sec - boot_time.tv_sec;
      long useconds = now.tv_usec - boot_time.tv_usec;
      _DEV_TIMER_UPTIME_t *uptime = (_DEV_TIMER_UPTIME_t *)buf;
      uptime->hi = 0;
      uptime->lo = seconds * 1000 + (useconds + 500) / 1000;
      return sizeof(_DEV_TIMER_UPTIME_t);
    }
    case _DEVREG_TIMER_DATE: {
      time_t t = time(NULL);
      struct tm *tm = localtime(&t);
      _DEV_TIMER_DATE_t *rtc = (_DEV_TIMER_DATE_t *)buf;
      rtc->second = tm->tm_sec;
      rtc->minute = tm->tm_min;
      rtc->hour   = tm->tm_hour;
      rtc->day    = tm->tm_mday;
      rtc->month  = tm->tm_mon + 1;
      rtc->year   = tm->tm_year + 1900;
      return sizeof(_DEV_TIMER_DATE_t);
    }
  }
  return 0;
}

void __am_timer_init() {
  gettimeofday(&boot_time, NULL);
}
