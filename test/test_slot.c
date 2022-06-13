//
// Created by wzhy on 2022/6/12.
//
#include "slot.h"
#include <stdio.h>
#include <string.h>

int test_slot() {
    char s[] = "Hello Slot!";
    slot_t slot;
    makeSlot(&slot, s, sizeof(s));
    char buf[1024] = {0};
    slotSerialize(&slot, buf, 0);
    unsigned short a = 0;
    memcpy(&a, buf, 2);
    printf("%d\n", a);
    printf("%s\n", buf + 2);
    slot_t slot1;
    slotDeserialize(buf, 0, &slot1);
    printf("%d\n", slot1.length);
    printf("%s\n", (char *) slot1.content);

    long long id = 1234;
    int type = 1;
    int L = 1;
    long long parent = 6789;
    long long son0 = 1;
    char key1[] = "hello page!";
    long long son1 = 2;

    slot_t slotArray[] = {
            {sizeof(long long), &id},
            {sizeof(int), &type},
            {sizeof(int), &L},
            {sizeof(long long), &parent},
            {sizeof(long long), &son0},
            {sizeof(key1), key1},
            {sizeof(long long), &son1}
    };
    int offset = 0;
    char buffer[4096] = {0};
    offset += slotSerialize(slotArray, buffer, offset);
    offset += slotSerialize(slotArray + 1, buffer, offset);
    offset += slotSerialize(slotArray + 2, buffer, offset);
    offset += slotSerialize(slotArray + 3, buffer, offset);
    offset += slotSerialize(slotArray + 4, buffer, offset);
    offset += slotSerialize(slotArray + 5, buffer, offset);
    offset += slotSerialize(slotArray + 6, buffer, offset);

    slot_t tmp;
    for (int i = 0; i < 7; ++i) {
        slotAt(buffer, i, &tmp);
        //printf("%d %p\n", slotArray[i].length, slotArray[i].content);
        //printf("%d %p\n", tmp.length, tmp.content);
        int contentOk = 0;
        if (i == 0) {
            long long x = 0;
            memcpy(&x, slotArray[i].content, slotArray[i].length);
            contentOk = x == id;
        } else if (i == 1) {
            int x = 0;
            memcpy(&x, slotArray[i].content, slotArray[i].length);
            contentOk = x == type;
        }
        else if (i == 2) {
            int x = 0;
            memcpy(&x, slotArray[i].content, slotArray[i].length);
            contentOk = x == L;
        }
        else if (i == 3) {
            long long x = 0;
            memcpy(&x, slotArray[i].content, slotArray[i].length);
            contentOk = x == parent;
        }
        else if (i == 4) {
            long long x = 0;
            memcpy(&x, slotArray[i].content, slotArray[i].length);
            contentOk = x == son0;
        }
        else if (i == 5) {
            char x[1024] = {0};
            memcpy(&x, slotArray[i].content, slotArray[i].length);
            contentOk = strcmp(x, key1) == 0;
        }
        else if (i == 6) {
            int long long x = 0;
            memcpy(&x, slotArray[i].content, slotArray[i].length);
            contentOk = x == son1;
        }
        printf("slot:%d %d\n",i, tmp.length == slotArray[i].length && contentOk);
    }
    return 1;
}

