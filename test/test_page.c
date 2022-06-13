//
// Created by wzhy on 2022/6/12.
//
#include "page.h"

int equalsPage(page_t *a, page_t *b) {
    int equal = 1;
    equal &= a->id.length == b->id.length;
    equal &= memcmp(a->id.content, b->id.content, a->id.length) == 0;
    equal &= a->type.length == b->type.length;
    equal &= memcmp(a->type.content, b->type.content, a->type.length) == 0;
    equal &= a->keyNum.length == b->keyNum.length;
    equal &= memcmp(a->keyNum.content, b->keyNum.content, a->keyNum.length) == 0;
    equal &= a->parent.length == b->parent.length;
    equal &= memcmp(a->parent.content, b->parent.content, a->parent.length) == 0;
    equal &= a->son[0].length == b->son[0].length;
    equal &= memcmp(a->son[0].content, b->son[0].content, a->son[0].length) == 0;
    int keyNum = 0;
    memcpy(&keyNum, a->keyNum.content, a->keyNum.length);
    if (equal) {
        for (int i = 1; i <= keyNum; ++i) {
            equal &= a->key[i].length == b->key[i].length;
            equal &= memcmp(a->key[i].content, b->key[i].content, a->key[i].length) == 0;
            equal &= a->son[i].length == b->son[i].length;
            equal &= memcmp(a->son[i].content, b->son[i].content, a->son[i].length) == 0;
        }
    }
    return equal;
}

int test_page() {
    size_t id = 666;
    PageType type = ROOT;
    int keyNum = 1;
    size_t parent = 1;
    char key[2][100] = {
            "PlaceHold",
            "IamKey1"
    };
    size_t son[2] = {1, 10};
    slot_t keySlots[2] = {
            {.length=0, .content = 0},
            {.length=7, .content = key + 1}
    };
    slot_t sonSlots[2] = {
            {.length=sizeof(size_t), .content=son},
            {.length=sizeof(size_t), .content=son + 1},
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
    int used = pageSerialize(&page, buf, PAGE_SIZE);
    printf("%d\n", used);

    page_t recover;
    pageDeserialize(buf, PAGE_SIZE, &recover);
    printf("%d\n", equalsPage(&page, &recover));

    printf("%s\n", recover.key[1].content);
    return 1;
}