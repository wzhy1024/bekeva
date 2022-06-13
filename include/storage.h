//
// Created by wzhy on 2022/6/12.
//

#ifndef BEKEVA_STORAGE_H
#define BEKEVA_STORAGE_H

#include <fcntl.h>
#include <unistd.h>
#include "page.h"

static int fd = -1;

void openFile(const char *filePath);

void readPage(size_t pageId, char *pageBuf, size_t pageSize);

void writePage(size_t pageId, char *pageBuf, size_t pageSize);

#endif //BEKEVA_STORAGE_H
