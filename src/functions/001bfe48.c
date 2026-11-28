// FUNCTION: SLPM 0x001BFE48  size 160  core 100
extern void FUN_001c02b0(void);
extern void FUN_001bfb90(int);
extern void FUN_001fbb84(char *, int, int);

void FUN_001bfe48(char *p)
{
    int one;

    one = 1;
    *(char *)(p + 2) = 0;
    if (*(signed char *)(p + 1) == one) {
        do {
            FUN_001c02b0();
        } while (*(signed char *)(p + 1) == one);
    }
    FUN_001bfb90(*(int *)(p + 4));
    FUN_001fbb84(p, 0, 0x44);
}
