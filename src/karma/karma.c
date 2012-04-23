#define _GNU_SOURCE
#include <stdio.h>

#include "common.h"
#include "includes.h"
#include "trace.h"                                                                                                                                                       

#include "karma/karma.h"

/* Karma Mode: Log data related to MSCHAPv2 challenge/response authentication attempts */
extern void karma_logger(int type, char *message)
{
    FILE *logfd;
    time_t cur_time;
    struct tm *tm_ptr;
    char time_buf[256];                                                                                                                                                     
    /* General: probe requests, username requests */
    logfd = fopen("./hostapd-karma.txt", "a");
    if (logfd == NULL) {
        fprintf(stderr, "[karma] Failed to open log file: ./hostapd-karma.txt\n");
        logfd = stderr;
    }

    cur_time = time(NULL);
    (void) time(&cur_time);
    tm_ptr = localtime(&cur_time);
    strftime(time_buf, 256, "%Y-%m-%d %H:%M:%S", tm_ptr);
    fprintf(logfd, "%s:%s\n", time_buf, message);
    fprintf(stderr, "[karma] %s:%s\n", time_buf, message);
    fclose(logfd);
    
    /* MSCHAPv2 Challenge/Response */
    if (type == 1)
    {
        logfd = fopen("./hostapd-karma.lc", "a");
        if (logfd == NULL) {
            fprintf(stderr, "[karma] Failed to open log file: ./hostapd-karma.lc\n");
            logfd = stderr;
        }
        fprintf(logfd, "%s\n", message);
        fclose(logfd);
    }
}
