//
// Created by wzhy on 2022/6/12.
//

#include "storage.h"

void openFile(const char *filePath) {
    fd = open(filePath, O_RDWR);
}

void readPage(size_t pageId, char *pageBuf, size_t pageSize) {
    if (fd == -1) return;
    size_t offset = pageId * pageSize;
    lseek(fd, (long) offset, SEEK_SET);
    read(fd, pageBuf, pageSize);
}

void writePage(size_t pageId, char *pageBuf, size_t pageSize) {
    if (fd == -1) return;
    size_t offset = pageId * pageSize;
    lseek(fd, (long) offset, SEEK_SET);
    write(fd, pageBuf, pageSize);
}


