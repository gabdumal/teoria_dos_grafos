/*
 * util.c
 *
 * By Haroldo Santos
 */

#include "util.h"

#include <sys/timeb.h>
#include <sys/resource.h>

using namespace std;

double wallClock()
{
  struct timeb tp;
  double mili;

  ftime(&tp);
  mili = (double)((tp.time) + ((double)tp.millitm) / 1000);

  return mili;
}

double cpuTime()
{
  static struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  return ((double)usage.ru_utime.tv_sec) + (((double)usage.ru_utime.tv_usec) / ((double)1000000));
}
