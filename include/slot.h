//
// Created by wzhy on 2022/6/12.
//

#ifndef BEKEVA_SLOT_H
#define BEKEVA_SLOT_H

#include <memory.h>

typedef struct {
    unsigned short length;
    void *content;
} slot_t;

void makeSlot(slot_t *slot, void *ptrToData, unsigned short len);

int slotSerialize(slot_t *slot, char *buf, int offset);

void slotDeserialize(char *buf, int offset, slot_t *slot);

void slotAt(char *buf, int t, slot_t *slot);

int retrieveContent(char *pageBuf, int t, void *copyHere);

#endif //BEKEVA_SLOT_H
