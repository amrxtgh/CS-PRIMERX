#include <stdio.h>
#include <assert.h>

/*
 * alloc(n) -> returns a pointer to n consecutive character position.
 * afree(p) -> releases the storage so it can be reused later.
 * alloc -> handout pieces of large character array we call allocbuf
 * allocp -> it is a pointer that points to the next free elements.
 */
#define ALLOCSIZE 10000 
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return 0;
    }
}

void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}
int main() {
    /* Test 1: basic allocation from start */
    char *p1 = alloc(10);
    assert(p1 != NULL);
    assert(p1 == allocbuf);

    /* Test 2: second allocation follows sequentially */
    char *p2 = alloc(20);
    assert(p2 != NULL);
    assert(p2 == allocbuf + 10);

    /* Test 3: zero-byte allocation returns current position without advancing */
    afree(allocbuf);
    char *z1 = alloc(0);
    char *z2 = alloc(0);
    assert(z1 == allocbuf);
    assert(z1 == z2);

    /* Test 4: free and reuse space */
    afree(allocbuf);
    p1 = alloc(10);
    p2 = alloc(20);
    afree(p2);
    char *p3 = alloc(20);
    assert(p3 != NULL);
    assert(p3 == p2);

    /* Test 5: free to buffer start resets allocator */
    afree(allocbuf);
    p1 = alloc(5);
    assert(p1 == allocbuf);

    /* Test 6: allocation of exact full size */
    afree(allocbuf);
    char *full = alloc(ALLOCSIZE);
    assert(full != NULL);
    assert(full == allocbuf);

    /* Test 7: overflow returns NULL */
    afree(allocbuf);
    char *big = alloc(ALLOCSIZE + 1);
    assert(big == NULL);

    /* Test 8: exhaustion after filling to boundary */
    afree(allocbuf);
    char *half1 = alloc(ALLOCSIZE / 2);
    char *half2 = alloc(ALLOCSIZE / 2);
    assert(half1 != NULL);
    assert(half2 != NULL);
    char *over = alloc(1);
    assert(over == NULL);

    /* Test 9: afree with pointer before buffer is ignored */
    afree(allocbuf);
    alloc(100);
    afree(allocbuf - 1);
    char *after_invalid = alloc(10);
    assert(after_invalid == allocbuf + 100);

    /* Test 10: afree with pointer past buffer end is ignored */
    afree(allocbuf);
    alloc(100);
    afree(allocbuf + ALLOCSIZE + 1);
    after_invalid = alloc(10);
    assert(after_invalid == allocbuf + 100);

    /* Test 11: multiple interleaved alloc/afree sequences */
    afree(allocbuf);
    char *a = alloc(100);
    char *b = alloc(200);
    afree(a);
    char *c = alloc(100);
    assert(c == a);
    afree(b);
    char *d = alloc(200);
    assert(d == b);

    /* Test 12: afree at exact buffer end should fail (not < allocbuf + ALLOCSIZE) */
    afree(allocbuf);
    alloc(100);
    afree(allocbuf + ALLOCSIZE);
    char *e = alloc(10);
    assert(e == allocbuf + 100);

    printf("All storage allocator tests passed!\n");
    return 0;
}

