#include "http/http_date.h"

char* time_format_month(struct tm *timeinfo){
    char* month = calloc(4, sizeof(char));
    switch (timeinfo->tm_mon){
    case 0:
        strcpy(month, "Jan");
        break;
    case 1:
        strcpy(month, "Feb");
        break;
    case 2:
        strcpy(month, "Mar");
        break;
    case 3:
        strcpy(month, "Apr");
        break;
    case 4:
        strcpy(month, "May");
        break;
    case 5:
        strcpy(month, "Jun");
        break;
    case 6:
        strcpy(month, "Jul");
        break;
    case 7:
        strcpy(month, "Aug");
        break;
    case 8:
        strcpy(month, "Sep");
        break;
    case 9:
        strcpy(month, "Oct");
        break;
    case 10:
        strcpy(month, "Nov");
        break;
    case 11:
        strcpy(month, "Dec");
        break;
    default:
        break;
    }
}

char* time_format_weekday(struct tm *timeinfo){
    char* week_day = calloc(4, sizeof(char));
    switch (timeinfo->tm_wday){
    case 0:
        strcpy(week_day, "Mon");
        break;
    case 1:
        strcpy(week_day, "Tue");
        break;
    case 2:
        strcpy(week_day, "Wed");
        break;
    case 3:
        strcpy(week_day, "Thu");
        break;
    case 4:
        strcpy(week_day, "Fri");
        break;
    case 5:
        strcpy(week_day, "Sat");
        break;
    case 6:
        strcpy(week_day, "Sun");
        break;
    default:
        break;
    }
}

char* time_get_http_format(){
    size_t date_buffer_size = 30;
    char* date = calloc(date_buffer_size, sizeof(char));
    
    time_t time_now = time(NULL);
    struct tm *timeinfo;
    
    timeinfo = localtime(&time_now);
    
    char* month = time_format_month(timeinfo);
    char* week_day = time_format_weekday(timeinfo);

    while(1){
        int sn_return = snprintf(
            date, 
            date_buffer_size,
            " %s, %02d %s %04d %02d:%02d:%02d GMT", 
            week_day, 
            timeinfo->tm_mday, 
            month, 
            timeinfo->tm_year + 1900,
            timeinfo->tm_hour,
            timeinfo->tm_min,
            timeinfo->tm_sec
        );
        if (sn_return < date_buffer_size) break;

        date_buffer_size = sn_return + 1;

        char* aux_pointer = realloc(date, date_buffer_size);
        if(aux_pointer != date){
            date = aux_pointer;
        }
        memset(date, 0, date_buffer_size);

    }
    free(month);
    free(week_day);
    return date;
}