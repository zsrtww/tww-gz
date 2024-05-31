#ifndef M_DO_M_DO_PRINTF_H
#define M_DO_M_DO_PRINTF_H

extern "C" {
typedef void (*OSReport)(const char* string, ...);
#define OSReport ((OSReport)tww_os_report_addr)
}

#endif