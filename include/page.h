//
// Created by wzhy on 2022/6/12.
//

#ifndef BEKEVA_PAGE_H
#define BEKEVA_PAGE_H

#include "slot.h"
#include <stdlib.h>
#include <stdio.h>

/**
 *                                         Page Layout
 *  ------------------------------------------------------------------------------------------------
 *   Slot0    Slot0    Slot0    Slot0    Slot0    Slot0    Slot0    Slot0    Slot0    ....
 *  ------------------------------------------------------------------------------------------------
 *   Id       Type    KeyNum    Parent   Son0     Key1     Son1     Key2     Son2     ....
 *  ------------------------------------------------------------------------------------------------
 */

#define PAGE_SIZE 4096

int retrieveId(char *pageBuf, void *copyHere);

int retrieveType(char *pageBuf, void *copyHere);

int retrieveKeyNum(char *pageBuf, void *copyHere);

int retrieveParent(char *pageBuf, void *copyHere);

int retrieveSon(char *pageBuf, int i, void *copyHere);

int retrieveKey(char *pageBuf, int i, void *copyHere);

typedef enum {
    ROOT, INTERNAL, LEAF
} PageType;

typedef struct {
    slot_t id;
    slot_t type;
    slot_t keyNum;
    slot_t parent;
    slot_t *key;
    slot_t *son;
} page_t;

int pageSerialize(page_t *page, char *buf, int pageSize);

int pageDeserialize(char *buf, int pageSize, page_t *page);

#endif //BEKEVA_PAGE_H
