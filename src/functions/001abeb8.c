// FUNCTION: SLPM 0x001ABEB8  size 84  core 84
extern char D_00860FC0[];
extern char D_00861000[];
extern void FUN_001ab4b0(void);
extern void FUN_001fc8c0(void *a0, void *a1);
extern void FUN_001ac540(void *a0, void *a1, int a2);

void FUN_001abeb8(char *p)
{
    char *q;

    FUN_001ab4b0();
    q = D_00861000;
    FUN_001fc8c0(q + 16, p);
    FUN_001ac540(D_00860FC0, q, 7);
}
