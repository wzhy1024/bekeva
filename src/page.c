//
// Created by wzhy on 2022/6/12.
//

#include "page.h"

int retrieveId(char *pageBuf, void *copyHere) {
    return retrieveContent(pageBuf, 0, copyHere);
}

int retrieveType(char *pageBuf, void *copyHere) {
    return retrieveContent(pageBuf, 1, copyHere);
}

int retrieveKeyNum(char *pageBuf, void *copyHere) {
    return retrieveContent(pageBuf, 2, copyHere);
}

int retrieveParent(char *pageBuf, void *copyHere) {
    return retrieveContent(pageBuf, 3, copyHere);
}

int retrieveSon(char *pageBuf, int i, void *copyHere) {
    return retrieveContent(pageBuf, 4 + 2 * i, copyHere);
}

int retrieveKey(char *pageBuf, int i, void *copyHere) {
    return retrieveContent(pageBuf, 3 + 2 * i, copyHere);
}

int pageSerialize(page_t *page, char *buf, int pageSize) {
    size_t needSpace = 2 * sizeof(size_t) + sizeof(PageType) + sizeof(int) + sizeof(int) * page->keyNum +
                       sizeof(size_t) * (page->keyNum + 1);
    if (needSpace > pageSize) return 0;
    int slotNum = 5 + 2 * page->keyNum;
    slot_t *slot = (slot_t *) malloc(slotNum * sizeof(slot_t));
    makeSlot(slot + 0, &page->id, sizeof(size_t));
    makeSlot(slot + 1, &page->type, sizeof(PageType));
    makeSlot(slot + 2, &page->keyNum, sizeof(int));
    makeSlot(slot + 3, &page->parent, sizeof(size_t));
    for (int i = 1; i <= page->keyNum; ++i) {
        int t = 3 + 2 * i;
        makeSlot(slot + t, page->key + i, sizeof(int));
    }
    for (int i = 0; i <= page->keyNum; ++i) {
        int t = 4 + 2 * i;
        makeSlot(slot + t, page->son + i, sizeof(size_t));
    }
    int offset = 0;
    for (int i = 0; i < slotNum; ++i) {
        slot_t *p = slot + i;
        offset += slotSerialize(p, buf, offset);
    }
    free(slot);
    return offset;
}

int pageDeserialize(char *buf, int pageSize, page_t *page) {
    retrieveId(buf, &page->id);
    retrieveType(buf, &page->type);
    retrieveKeyNum(buf, &page->keyNum);
    retrieveParent(buf, &page->parent);
    page->key = (int *) malloc((page->keyNum + 1) * sizeof(int));
    page->son = (size_t *) malloc((page->keyNum + 1) * sizeof(size_t));
    for (int i = 1; i <= page->keyNum; ++i) {
        retrieveKey(buf, i, page->key + i);
    }
    for (int i = 0; i <= page->keyNum; ++i) {
        retrieveSon(buf, i, page->son + i);
    }
    return 1;   //
}

