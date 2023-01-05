/*
 * util.h
 * By Haroldo Santos
 */

#ifndef UTIL_H
#define UTIL_H

#include <ctime>
#include <unistd.h>
#include <sys/times.h>

using namespace std;

double wallClock();
double cpuTime();

#endif /* ifndef UTIL_H */
