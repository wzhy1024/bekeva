//
// Created by wzhy on 2022/6/12.
//
#include "storage.h"
int test_storage() {
    int a1[] = {0, 7};
    size_t s1[] = {1, 10};
    page_t page1 = {
            .id = 0,
            .type = ROOT,
            .keyNum = 1,
            .parent = 1,
            .key = a1,
            .son = s1
    };

    int a2[] = {0, 45, 60};
    size_t s2[] = {1, 50, 999};
    page_t page2 = {
            .id = 1,
            .type = LEAF,
            .keyNum = 2,
            .parent = 666,
            .key = a2,
            .son = s2
    };

    char buf1[PAGE_SIZE] = {0};
    char buf2[PAGE_SIZE] = {0};

    pageSerialize(&page1, buf1, PAGE_SIZE);
    pageSerialize(&page2, buf2, PAGE_SIZE);

    writePage(0, buf1, PAGE_SIZE);
    writePage(1, buf2, PAGE_SIZE);

    char buf11[PAGE_SIZE] = {0};
    char buf22[PAGE_SIZE] = {0};

    readPage(0, buf11, PAGE_SIZE);
    readPage(1, buf22, PAGE_SIZE);

    page_t recover1;
    page_t recover2;

    pageDeserialize(buf11, PAGE_SIZE, &recover1);
    pageDeserialize(buf22, PAGE_SIZE, &recover2);

    printf("%d %d\n", equalsPage(&page1, &recover1), equalsPage(&page2, &recover2));
    return 1;
}