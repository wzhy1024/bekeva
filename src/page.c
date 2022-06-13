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
    int keyNum = 0;
    memcpy(&keyNum, page->keyNum.content, page->keyNum.length);
    size_t needSpace = page->id.length + page->type.length + page->keyNum.length + page->parent.length +
                       sizeof(unsigned short) * (5 + 2 * keyNum);
    for (int i = 1; i <= keyNum; ++i) {
        needSpace += page->key[i].length;
    }
    for (int i = 0; i <= keyNum; ++i) {
        needSpace += page->son[i].length;
    }
    if (needSpace > pageSize) return 0;
    int offset = 0;
    offset += slotSerialize(&page->id, buf, offset);
    offset += slotSerialize(&page->type, buf, offset);
    offset += slotSerialize(&page->keyNum, buf, offset);
    offset += slotSerialize(&page->parent, buf, offset);
    offset += slotSerialize(page->son + 0, buf, offset);
    for (int i = 1; i <= keyNum; ++i) {
        offset += slotSerialize(page->key + i, buf, offset);
        offset += slotSerialize(page->son + i, buf, offset);
    }
    // assert needSpace == offset
    return offset;
}

int pageDeserialize(char *buf, int pageSize, page_t *page) {
    int offset = 0;
    int sizeOfUnsignedShort = sizeof(unsigned short);

    memcpy(&page->id.length, buf, sizeOfUnsignedShort);
    offset += sizeOfUnsignedShort;
    page->id.content = buf + offset;
    offset += page->id.length;

    memcpy(&page->type.length, buf + offset, sizeOfUnsignedShort);
    offset += sizeOfUnsignedShort;
    page->type.content = buf + offset;
    offset += page->type.length;

    memcpy(&page->keyNum.length, buf + offset, sizeOfUnsignedShort);
    offset += sizeOfUnsignedShort;
    page->keyNum.content = buf + offset;
    offset += page->keyNum.length;

    memcpy(&page->parent.length, buf + offset, sizeOfUnsignedShort);
    offset += sizeOfUnsignedShort;
    page->parent.content = buf + offset;
    offset += page->parent.length;

    int keyNum = 0;
    memcpy(&keyNum, page->keyNum.content, page->keyNum.length);
    page->key = (slot_t *) malloc((keyNum + 1) * sizeof(slot_t));
    page->son = (slot_t *) malloc((keyNum + 1) * sizeof(slot_t));

    memcpy(&page->son[0].length, buf + offset, sizeOfUnsignedShort);
    offset += sizeOfUnsignedShort;
    page->son[0].content = buf + offset;
    offset += page->son[0].length;

    for (int i = 1; i <= keyNum; ++i) {
        memcpy(&page->key[i].length, buf + offset, sizeOfUnsignedShort);
        offset += sizeOfUnsignedShort;
        page->key[i].content = buf + offset;
        offset += page->key[i].length;

        memcpy(&page->son[i].length, buf + offset, sizeOfUnsignedShort);
        offset += sizeOfUnsignedShort;
        page->son[i].content = buf + offset;
        offset += page->son[i].length;
    }

    return 1;   //
}

