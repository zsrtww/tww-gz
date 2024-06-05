#ifndef __OS_H__
#define __OS_H__

#include <stdint.h>

typedef int64_t OSTime;

typedef void (*DSPCallback)(void *task);

typedef struct STRUCT_DSP_TASK
{                                   
    /*0x00*/ volatile uint32_t state;
    /*0x04*/ volatile uint32_t priority;                  
    /*0x08*/ volatile uint32_t flags;                     
    /*0x0C*/ uint16_t *iram_mmem_addr;          
    /*0x10*/ uint32_t iram_length;             
    /*0x14*/ uint32_t iram_addr;                               
    /*0x18*/ uint16_t *dram_mmem_addr;          
    /*0x1C*/ uint32_t dram_length;
    /*0x20*/ uint32_t dram_addr;
    /*0x24*/ uint16_t dsp_init_vector;
    /*0x26*/ uint16_t dsp_resume_vector;
    /*0x28*/ DSPCallback init_cb;          
    /*0x2C*/ DSPCallback res_cb;           
    /*0x30*/ DSPCallback done_cb;          
    /*0x34*/ DSPCallback req_cb;                              
    /*0x38*/ struct STRUCT_DSP_TASK *next; 
    /*0x3C*/ struct STRUCT_DSP_TASK *prev; 
    OSTime t_context;
    OSTime t_task;
} DSPTaskInfo;

typedef struct OSAlarm OSAlarm;
typedef struct OSContext OSContext;
typedef void (*OSAlarmHandler)(OSAlarm *alarm, OSContext *context);

struct OSAlarm {
    OSAlarmHandler handler;
    uint32_t tag;
    OSTime fire;
    OSAlarm *prev;
    OSAlarm *next;
    OSTime period;
    OSTime start;
};

typedef int32_t OSPriority;

struct OSThread;
struct OSMutex;
struct OSMutexQueue;

typedef struct OSThread OSThread;

typedef struct OS_ThreadQueue {
    struct OSThread *head;
    struct OSThread *tail;
} OS_ThreadQueue;

#endif  // __OS_H__