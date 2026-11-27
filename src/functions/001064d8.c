// FUNCTION: SLPM 0x001064D8  size 184
extern char D_00257FC0[];
extern char D_00257FD8[];
extern char D_00258000[];
extern char D_456500[];
extern unsigned int D_00270A80;
extern unsigned int D_00270A84;
extern unsigned int D_00270A88;
extern unsigned int D_00270A8C;
extern unsigned int D_00270A90;
extern unsigned int D_00270A94;
extern void FUN_0010bcf0(void);
extern char *FUN_0010bd80(unsigned int id, void *ptr);
extern void FUN_0010bf68(char *msg, ...);
extern char *FUN_0020dc98(int a, unsigned int size, int c);
extern void FUN_00106268(char *a, char *b);

void FUN_001064d8(void)
{
    char *p;
    char *base;
    char *a;
    char *b;

    FUN_0010bcf0();
    p = FUN_0010bd80(0x8000, (void *)0x1000);
    if (p)
        FUN_0010bf68(D_00257FC0, p);
    D_00270A80 = (unsigned int)FUN_0020dc98(0, 0x12000, 0);
    if (!D_00270A80)
        FUN_0010bf68(D_00257FD8);
    D_00270A94 = (unsigned int)FUN_0010bd80(0x8100, D_456500);
    if (!D_00270A94)
        FUN_0010bf68(D_00258000);
    base = (char *)D_00270A80;
    b = base + 0x10000;
    a = base + 0x2000;
    D_00270A90 = (unsigned int)(base + 0x1000);
    D_00270A84 = (unsigned int)a;
    D_00270A88 = (unsigned int)b;
    D_00270A8C = (unsigned int)base;
    FUN_00106268(a, b);
}
