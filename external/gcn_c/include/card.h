#ifndef __CARD_H__
#define __CARD_H__

#include <stdint.h>
#include "os.h"
#include "dvd.h"

#define CARD_SLOT_A 0
#define CARD_SLOT_B 1

#define CARD_BLOCK_SIZE (8 * 1024)
#define CARD_WORKAREA_SIZE (5 * 8 * 1024)
#define CARD_MAX_FILE 127

#define CARD_ENCODE_ANSI 0u
#define CARD_ENCODE_SJIS 1u

// longest file name string excluding terminating zero
#define CARD_FILENAME_MAX 32

#define CARD_ICON_MAX 8
#define CARD_ICON_WIDTH 32
#define CARD_ICON_HEIGTH 32
#define CARD_BANNER_WIDTH 96
#define CARD_BANNER_HEIGTH 32

#define CARD_RESULT_UNLOCKED 1
#define CARD_RESULT_READY 0
#define CARD_RESULT_BUSY -1
#define CARD_RESULT_WRONGDEVICE -2
#define CARD_RESULT_NOCARD -3
#define CARD_RESULT_NOFILE -4
#define CARD_RESULT_IOERROR -5
#define CARD_RESULT_BROKEN -6
#define CARD_RESULT_EXIST -7
#define CARD_RESULT_NOENT -8
#define CARD_RESULT_INSSPACE -9
#define CARD_RESULT_NOPERM -10
#define CARD_RESULT_LIMIT -11
#define CARD_RESULT_NAMETOOLONG -12
#define CARD_RESULT_ENCODING -13
#define CARD_RESULT_FATAL_ERROR -128

#define CARD_READ_SIZE 512

// Taken from https://github.com/TakaRikka/dolsdk2004/blob/card/include/dolphin/card.h
#define CARD_NUM_SYSTEM_BLOCK 5

#define SECTOR_SIZE INT32_MAX

#define CARDIsValidBlockNo(card, blockNo) ((blockNo) >= CARD_NUM_SYSTEM_BLOCK && (blockNo) < (card)->cBlock)

typedef void (*CARDCallback)(int32_t chan, int32_t result);

typedef struct CARDFileInfo {
    int32_t chan;
    int32_t fileNo;
    int32_t offset;
    int32_t length;
    uint16_t iBlock;
} CARDFileInfo;

typedef struct CARDStat {
    char fileName[CARD_FILENAME_MAX];
    uint32_t length;
    uint32_t time;  // seconds since midnight 01/01/2000
    uint8_t gameName[4];
    uint8_t company[2];
    uint8_t bannerFormat;
    uint32_t iconAddr;
    uint16_t iconFormat;
    uint16_t iconSpeed;
    uint32_t commentAddr;
    uint32_t offsetBanner;
    uint32_t offsetBannerTlut;
    uint32_t offsetIcon[CARD_ICON_MAX];
    uint32_t offsetIconTlut;
    uint32_t offsetData;
} CARDStat;

// Taken from https://github.com/TakaRikka/dolsdk2004/blob/card/include/dolphin/card.h
typedef struct CARDDir {
    /*0x00*/ uint8_t gameName[4];
    /*0x04*/ uint8_t company[2];
    /*0x06*/ uint8_t _padding0;
    /*0x07*/ uint8_t bannerFormat;
    /*0x08*/ uint8_t fileName[CARD_FILENAME_MAX];
    /*0x28*/ uint32_t time;     // seconds since 01/01/2000 midnight
    /*0x2C*/ uint32_t iconAddr; // 0xffffffff if not used
    /*0x30*/ uint16_t iconFormat;
    /*0x32*/ uint16_t iconSpeed;
    /*0x34*/ uint8_t permission;
    /*0x35*/ uint8_t copyTimes;
    /*0x36*/ uint16_t startBlock;
    /*0x38*/ uint16_t length;
    /*0x3A*/ uint8_t _padding1[2];
    /*0x3C*/ uint32_t commentAddr; // 0xffffffff if not used
} CARDDir;

typedef struct CARDControl {
    /* 0x000 */ int32_t attached;
    /* 0x004 */ int32_t result;
    /* 0x008 */ uint16_t size;
    /* 0x00A */ uint16_t pageSize;
    /* 0x00C */ int32_t sectorSize;
    /* 0x010 */ uint16_t cBlock;
    /* 0x012 */ uint16_t vendorID;
    /* 0x014 */ int32_t latency;
    /* 0x018 */ uint8_t id[12];
    /* 0x024 */ int32_t mountStep;
    /* 0x028 */ int32_t formatStep;
    /* 0x02C */ uint32_t scramble;
    /* 0x030 */ DSPTaskInfo task;
    /* 0x080 */ void* workArea;
    /* 0x084 */ CARDDir* currentDir;
    /* 0x088 */ uint16_t* currentFat;
    /* 0x08C */ OS_ThreadQueue threadQueue;
    /* 0x094 */ uint8_t cmd[9];
    /* 0x09D */ uint8_t padding_9d[3];
    /* 0x0A0 */ int32_t cmdlen;
    /* 0x0A4 */ volatile uint32_t mode;
    /* 0x0A8 */ int32_t retry;
    /* 0x0AC */ int32_t repeat;
    /* 0x0B0 */ uint32_t addr;
    /* 0x0B4 */ void* buffer;
    /* 0x0B8 */ int32_t xferred;
    /* 0x0BC */ uint16_t freeNo;
    /* 0x0BE */ uint16_t startBlock;
    /* 0x0C0 */ CARDFileInfo* fileInfo;
    /* 0x0C4 */ CARDCallback extCallback;
    /* 0x0C8 */ CARDCallback txCallback;
    /* 0x0CC */ CARDCallback exiCallback;
    /* 0x0D0 */ CARDCallback apiCallback;
    /* 0x0D4 */ CARDCallback xferCallback;
    /* 0x0D8 */ CARDCallback eraseCallback;
    /* 0x0DC */ CARDCallback unlockCallback;
    /* 0x0E0 */ OSAlarm alarm;
    /* 0x108 */ uint32_t cid;
    /* 0x10C */ const DVDDiskID* diskID;
} CARDControl;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
int32_t CARDOpen(int32_t channel, char* fileName, CARDFileInfo* fileInfo);
int32_t CARDRead(CARDFileInfo* fileInfo, void* buf, int32_t length, int32_t offset);
int32_t CARDClose(CARDFileInfo* fileInfo);
int32_t CARDCreate(int32_t channel, const char* fileName, uint32_t size, CARDFileInfo* fileInfo);
int32_t CARDProbeEx(int32_t channel, int32_t* memSize, int32_t* sectorSize);
int32_t CARDGetStatus(int32_t channel, int32_t file_number, CARDStat* stat);
int32_t CARDWrite(CARDFileInfo* fileInfo, void* buf, int32_t length, int32_t offset);
int32_t CARDDelete(int32_t chn, const char* fileName);
int32_t CARDDeleteAsync(int32_t chn, const char* fileName, CARDCallback callback);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __CARD_H__