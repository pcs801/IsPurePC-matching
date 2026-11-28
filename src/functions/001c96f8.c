// FUNCTION: SLPM 0x001C96F8  size 128  core 96
// ascending source order -> ee-gcc emits descending (sw 0x2C first), matching the ROM
extern char D_02693C8[];
extern char D_0269358[];
extern char D_02693D8[];
extern char D_0269388[];
extern void FUN_001c92d8(char *, char *);

void FUN_001c96f8(char *p, int a1, int a2)
{
    if (p == 0) {
        FUN_001c92d8(D_02693C8, D_0269358);
        return;
    }
    if (*(signed char *)(p + 4) == 0) {
        FUN_001c92d8(D_02693D8, D_0269388);
        return;
    }
    *(int *)(p + 0x28) = a1;
    *(int *)(p + 0x2C) = a2;
}
