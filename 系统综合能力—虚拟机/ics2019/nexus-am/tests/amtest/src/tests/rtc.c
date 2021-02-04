#include <amtest.h>
#include <amdev.h>

void rtc_test() {
  _DEV_TIMER_DATE_t rtc;
  int sec = 1;
  while (1) {
    while(uptime() < 1000 * sec) ;
    get_timeofday(&rtc);
    printf("%d-%d-%d %02d:%02d:%02d GMT (", rtc.year, rtc.month, rtc.day, rtc.hour, rtc.minute, rtc.second);
    if (sec == 1) {
      printf("%d second).\n", sec);
    } else {
      printf("%d seconds).\n", sec);
    }
    sec ++;
  }
}
