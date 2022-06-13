//
// Created by wzhy on 2022/6/12.
//

#include "slot.h"

void makeSlot(slot_t *slot, void *ptrToData, unsigned short len) {
    slot->length = len;
    slot->content = ptrToData;
}

int slotSerialize(slot_t *slot, char *buf, int offset) {
    memcpy(buf + offset, &slot->length, sizeof(short));
    memcpy(buf + offset + sizeof(short), slot->content, slot->length);
    return (int) sizeof(unsigned short) + slot->length;
}

void slotDeserialize(char *buf, int offset, slot_t *slot) {
    memcpy(&slot->length, buf + offset, sizeof(unsigned short));
    slot->content = buf + offset + 2;
}

void slotAt(char *buf, int t, slot_t *slot) {
    char *p = buf;
    unsigned short l = 0;
    while (t-- > 0) {
        memcpy(&l, p, sizeof(unsigned short));
        p = p + sizeof(unsigned short) + l;
    }
    memcpy(&slot->length, p, sizeof(unsigned short));
    slot->content = p + sizeof(unsigned short);
}

int retrieveContent(char *pageBuf, int t, void *copyHere) {
    slot_t slot;
    slotAt(pageBuf, t, &slot);
    memcpy(copyHere, slot.content, slot.length);
    return slot.length;
}

