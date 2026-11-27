// FUNCTION: SLPM 0x0016E808  size 280  core 280
extern char *D_00270BF4;
extern char D_00217BC8[];
extern unsigned char D_00A98D9D[16];
extern void FUN_00123568(char *);
extern void FUN_00123a78(void);
extern void FUN_00123830(int);
extern void FUN_00123d28(int, int);
extern void FUN_00123e70(int);
extern void FUN_001204c0(int);
extern void FUN_00120cd0();
extern int FUN_001237a8(int);
extern void FUN_00120fd0(char *, int, int, int, int, int, int, int, int);

int FUN_0016e808(int a0, int idx)
{
    switch (idx) {
    case 0:
    case 3:
        FUN_00123568(D_00270BF4 + 0x21380);
        FUN_00123a78();
        FUN_00123830(0);
        FUN_00123d28(6, 2);
        FUN_00120fd0(D_00217BC8, 1, 0, 0, 0, 0, 0, D_00A98D9D[0], 1);
        return FUN_001237a8(2);
    case 5:
        FUN_00123568(D_00270BF4 + 0x21380);
        FUN_00123d28(6, 2);
        FUN_00123e70(0);
        FUN_001204c0(0);
        FUN_00120cd0(D_00270BF4 + 0x21398 + *(int *)(D_00270BF4 + 0x21380) * 0x5FF8, 10);
        break;
    case 1:
    case 2:
    case 4:
    default:
        break;
    }
}
