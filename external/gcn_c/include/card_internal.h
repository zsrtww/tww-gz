/*!
 *  This file contains the declaration of internal CARD functions and structures.
 */
#ifndef __CARD_INTERNAL_H__
#define __CARD_INTERNAL_H__
#include "card.h"
#include <stddef.h>
#include <stdbool.h>

// Specifically have to use this one and not make a new one
extern CARDControl __CARDBlock[2];  // One for each memory card slot

// Vanilla functions used in main code
void __CARDDefaultApiCallback(int32_t chn, int32_t result);
void __CARDSyncCallback(int32_t chn, int32_t result);
int32_t __CARDGetControlBlock(int32_t chn, CARDControl** card);
int32_t __CARDPutControlBlock(CARDControl* card, int32_t result);
int32_t __CARDSync(int32_t chn);
int32_t __CARDUpdateFatBlock(int32_t chn, uint16_t* fatBlock, CARDCallback callback);
CARDDir* __CARDGetDirBlock(CARDControl* card);
int32_t __CARDUpdateDir(int32_t chn, CARDCallback callback);
int32_t __CARDCompareFileName(CARDDir* dirBlock, const char* fileName);
int32_t __CARDAccess(CARDControl* card, CARDDir* dirBlock);
void *__CARDGetFatBlock(CARDControl *card);

#endif  // __CARD_INTERNAL_H__