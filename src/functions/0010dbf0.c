// FUNCTION: SLPM 0x0010DBF0  size 184  core 184
extern int D_D72980[];
extern void FUN_001dcb68(void *, int, int, int, int, int, int, int);
extern void FUN_00205c20(int);
extern void FUN_001dce90(void *, void *);
extern void FUN_001dc850(int, int);

void FUN_0010dbf0(void)
{
    unsigned int i;
    char buf[0x60];

    for (i = 0; i <= 0x37FFFF; i++)
        D_D72980[i] = 0;
    for (i = 0; i < 16; i++) {
        FUN_001dcb68(buf, i << 10, 4, 0, 0, 0, 0x100, 0x100);
        FUN_00205c20(0);
        FUN_001dce90(buf, D_D72980);
        FUN_001dc850(0, 0);
    }
}
