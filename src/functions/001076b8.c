// FUNCTION: SLPM 0x001076B8
extern unsigned char D_281580[];
extern void FUN_001bb940(int h);
extern void FUN_001b6960(int h);

void FUN_001076b8(void) {
    unsigned char *p = D_281580;
    unsigned char *end = D_281580 + 0x1D4F00;
    do {
        if (*(int *)(p + 4)) {
            FUN_001bb940(*(int *)(p + 4));
            FUN_001b6960(*(int *)(p + 4));
            *(int *)(p + 4) = 0;
        }
        p += 0x4E280;
    } while ((int)p < (int)end);
}
