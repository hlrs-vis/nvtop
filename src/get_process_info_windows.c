/*
 *
 * Copyright (C) 2017 Maxime Schmitt <maxime.schmitt91@gmail.com>
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

#include "nvtop/get_process_info.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define pid_path_size 1024
static char pid_path[pid_path_size];

int clock_gettime(int unusedInt, struct timespec* spec)      //C-file part
{
	__int64 wintime; GetSystemTimeAsFileTime((FILETIME*)& wintime);
	wintime -= 116444736000000000i64;  //1jan1601 to 1jan1970
	spec->tv_sec = wintime / 10000000i64;           //seconds
	spec->tv_nsec = wintime % 10000000i64 * 100;      //nano-seconds
	return 0;
}

void get_username_from_pid(pid_t procId, char **buffer) {
	*buffer = NULL;
    return ;

}

#define command_line_increment 32

void get_command_from_pid(pid_t pid, char **buffer) {
	*buffer = NULL;
}



bool get_process_info(pid_t pid, struct process_cpu_usage *usage) {

  return false;
}
