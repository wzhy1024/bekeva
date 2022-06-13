#include <stdio.h>
#include <stdlib.h>
#include "../test/test_slot.c"
#include "../test/test_page.c"
#include "../test/test_storage.c"
#include <fcntl.h>

typedef struct {
    int exist;
    int index;
} result_t;

result_t binarySearch(const int a[], int lo, int hi, int e) {
    int p = lo, q = hi;
    int mid;
    result_t r;
    while (p <= q) {
        mid = (p + q) / 2;
        if (a[mid] < e)
            p = mid + 1;
        else if (a[mid] > e)
            q = mid - 1;
        else {
            r.exist = 1;
            r.index = mid;
            return r;
        }
    }
    r.exist = 0;
    r.index = q == hi ? hi - 1 : q;
    return r;
}

#define LEN 500000

void test(int times) {
    int a[LEN] = {0};
    for (int i = 0; i < LEN; ++i) {
        a[i] = rand() + 1 + (i == 0 ? 0 : a[i - 1]);
    }
    for (int i = 0; i < times; ++i) {
        int lo = rand() % LEN;
        if (lo == LEN - 1) lo--;
        int hi = lo + 1 + rand() % (LEN - lo);
        int e = rand();
        result_t r_real;
        if (e < a[lo]) {
            r_real.exist = 0;
            r_real.index = lo - 1;
        } else {
            for (int j = lo; j < hi; ++j) {
                if (a[j] == e) {
                    r_real.exist = 1;
                    r_real.index = j;
                    break;
                }
                if (a[j] < e && (j == hi - 1 || e < a[j + 1])) {
                    r_real.exist = 0;
                    r_real.index = j;
                    break;
                }
            }
        }
        result_t r_test = binarySearch(a, lo, hi, e);
        printf("%d: %d\n", i, r_real.exist == r_test.exist && r_real.index == r_test.index);
    }
}

int main() {
    openFile("D:/tmp/a.txt");
    test_storage();
    return 0;
}
