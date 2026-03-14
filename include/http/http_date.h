#ifndef HTTP_DATE_H
#define HTTP_DATE_H

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* time_format_month(struct tm *timeinfo);

char* time_format_weekday(struct tm *timeinfo);

char* time_get_http_format();

#endif