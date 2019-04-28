/*
 *
 * Copyright (C) 2018 Maxime Schmitt <maxime.schmitt91@gmail.com>
 *
 * This file is part of Nvtop.
 *
 * Nvtop is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nvtop is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with nvtop.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef NVTOP_TIME_H_
#define NVTOP_TIME_H_

#include <stdbool.h>
#include <time.h>

#ifdef CLOCK_MONOTONIC_RAW
#define NVTOP_CLOCK CLOCK_MONOTONIC_RAW
#else
#define NVTOP_CLOCK CLOCK_MONOTONIC
#endif
#ifdef WIN32
#include <Windows.h>
#define CLOCK_MONOTONIC 1
//struct timespec { long tv_sec; long tv_nsec; };    //header part
extern int clock_gettime(int unusedInt, struct timespec* spec);
#endif
typedef struct timespec nvtop_time;
#ifdef __GNUC__
inline void nvtop_get_current_time(nvtop_time *time)  __attribute__ ((always_inline));
#endif
inline void nvtop_get_current_time(nvtop_time *time) {

  clock_gettime(NVTOP_CLOCK, time);
}

#ifdef __GNUC__
inline double nvtop_difftime(nvtop_time t0, nvtop_time t1)  __attribute__ ((always_inline));
#endif

inline double nvtop_difftime(nvtop_time t0, nvtop_time t1) {
  double secdiff = difftime(t1.tv_sec, t0.tv_sec);
  if (t1.tv_nsec < t0.tv_nsec) {
    long val = 1000000000l - t0.tv_nsec + t1.tv_nsec;
    secdiff += (double)val / 1e9 - 1.;
  } else {
    long val = t1.tv_nsec - t0.tv_nsec;
    secdiff += (double)val / 1e9;
  }
  return secdiff;
}

inline nvtop_time nvtop_hmns_to_time(unsigned hour, unsigned minutes,
                                     unsigned long nanosec) {
  nvtop_time t = {(long)(hour * 60 * 60 + 60 * minutes + nanosec / 1000000,
                  nanosec % 1000000)};
  return t;
}

inline nvtop_time nvtop_substract_time(nvtop_time t0, nvtop_time t1) {
	  long lv = 
      t0.tv_nsec - t1.tv_nsec < 0
          ? (t0.tv_sec - t1.tv_sec - 1,
                         t0.tv_nsec - t1.tv_nsec + 1000000)
          : (t0.tv_sec - t1.tv_sec, t0.tv_nsec - t1.tv_nsec);

	  nvtop_time t = { lv };
  return t;
}

inline nvtop_time nvtop_add_time(nvtop_time t0, nvtop_time t1) {
	long lv =
      t0.tv_nsec + t1.tv_nsec > 1000000
          ? (t0.tv_sec + t1.tv_sec + 1,
                         t0.tv_nsec + t1.tv_nsec - 1000000)
          : (t0.tv_sec + t1.tv_sec, t0.tv_nsec + t1.tv_nsec);
		  nvtop_time t = { lv };
  return t;
}

#endif // NVTOP_TIME_H_
