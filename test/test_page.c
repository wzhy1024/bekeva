//
// Created by wzhy on 2022/6/12.
//
#include "page.h"

int equalsPage(page_t *a, page_t *b) {
    int equal = 1;
    equal &= a->id == b->id;
    equal &= a->type == b->type;
    equal &= a->keyNum == b->keyNum;
    equal &= a->parent == b->parent;
    if (equal) {
        for (int i = 1; i <= a->keyNum; ++i) {
            equal &= a->key[i] == b->key[i];
        }
        for (int i = 0; i <= a->keyNum; ++i) {
            equal &= a->son[i] == b->son[i];
        }
    }
    return equal;
}

int test_page() {
    int a[] = {0, 7};
    size_t s[] = {1, 10};
    page_t page = {
            .id = 666,
            .type = ROOT,
            .keyNum = 1,
            .parent = 1,
            .key = a,
            .son = s
    };
    char buf[PAGE_SIZE] = {0};
    int used = pageSerialize(&page, buf, PAGE_SIZE);
    printf("%d\n", used);

    page_t recover;
    pageDeserialize(buf, PAGE_SIZE, &recover);
    printf("%d\n", equalsPage(&page, &recover));
    return 1;
}