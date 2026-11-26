// FUNCTION: SLPM 0x00101A00
extern char D_1B75484[];

unsigned int FUN_00101a00(int idx)
{
    int end;
    unsigned int n;

    if (idx != -1) { end = idx + 1; }
    else { idx = 0; end = 10; }
    n = 0;
    for (; idx < end; idx++) {
        char *p = D_1B75484 + idx * 0x16C;
        if (*(int *)(p + 0x10C) != 0) {
            if (*(short *)(p + 0x11E) == 0) { n++; }
            else { *(char *)(p + 0x119) = 0; }
        }
    }
    return n < 1;
}
