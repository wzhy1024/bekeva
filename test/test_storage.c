//
// Created by wzhy on 2022/6/12.
//
#include "storage.h"

int test_storage() {
    size_t id = 0;
    PageType type = ROOT;
    int keyNum = 2;
    size_t parent = 1;
    char key[3][100] = {
            "PlaceHold",
            "IamKey 1",
            "IamKey 22",
    };
    size_t son[3] = {1, 10, 100};
    slot_t keySlots[3] = {
            {.length=4, .content = 0},
            {.length=8, .content = key + 1},
            {.length=9, .content = key + 2},
    };
    slot_t sonSlots[3] = {
            {.length=sizeof(size_t), .content=son},
            {.length=sizeof(size_t), .content=son + 1},
            {.length=sizeof(size_t), .content=son + 2},
    };
    page_t page = {
            .id = {.length = sizeof(size_t), .content = &id},
            .type = {.length = sizeof(PageType), .content = &type},
            .keyNum = {.length = sizeof(int), .content = &keyNum},
            .parent = {.length = sizeof(size_t), .content = &parent},
            .key = keySlots,
            .son = sonSlots
    };

    char buf[PAGE_SIZE] = {0};
    pageSerialize(&page, buf, PAGE_SIZE);
    writePage(0, buf, PAGE_SIZE);

    char buf1[PAGE_SIZE] = {0};
    readPage(0, buf1, PAGE_SIZE);
    page_t recover;
    pageDeserialize(buf1, PAGE_SIZE, &recover);

    printf("%d\n", equalsPage(&page, &recover));

    return 1;
}