// FUNCTION: SLPM 0x0010A228  size 160  core 128
// loop i < 0x64: fill buf via FUN_001fc2a8(buf, D_002585B0, i), then FUN_001093d0(buf, 0xC56680, 0x280, 0x1C0, 1); stop when it returns 0
extern char D_002585B0[];
extern void FUN_00109568(void);
extern void FUN_001fc2a8(void *, char *, int);
extern int FUN_001093d0(void *, char *, int, int, int);

void FUN_0010a228(void)
{
    char buf[0x100];
    int i;

    i = 0;
    FUN_00109568();
    while (i < 0x64) {
        FUN_001fc2a8(buf, D_002585B0, i);
        if (FUN_001093d0(buf, (char *)0xC56680, 0x280, 0x1C0, 1) == 0)
            return;
        i++;
    }
}
