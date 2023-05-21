#include "fs.h"
#include "font.h"
#include "gcn_c/include/dvd.h"
#include "libtww/m_Do/m_Do_printf.h"

void loadFile(const char* filePath, void* buffer, signed long length, signed long offset) {
    DVDFileInfo fileInfo;
    if (DVDOpen(filePath, &fileInfo)) {
        int bytesRead = DVDReadPrio(&fileInfo, buffer, length, offset, 2);
        if (bytesRead > 0) {
            DVDClose(&fileInfo);
        } else {
            //OSReport("no bytes read!");
            Font::GZ_drawStr("no bytes read!", 20.f, 300.f, 0xFFFFFFFF, false);
        }
    } else {
        //OSReport("failed to open file %s", filePath);
        Font::GZ_drawStr("failed to open file", 20.f, 300.f, 0xFFFFFFFF, false);
    }
}