// FUNCTION: SLPM 0x001AB738  size 96  core 88
// FUN_001ab4b0(a0); FUN_001fc8c0(D_0861010, a0); *(int*)(D_0861000+8) = a1;
// FUN_001ac540(D_0860FC0, D_0861000, 0);
extern char D_0861010[];
extern char D_0861000[];
extern char D_0860FC0[];
extern void FUN_001ab4b0(char *);
extern void FUN_001fc8c0(char *, char *);
extern void FUN_001ac540(char *, char *, int);

void FUN_001ab738(char *a0, int a1)
{
    FUN_001ab4b0(a0);
    FUN_001fc8c0(D_0861010, a0);
    *(int *)(D_0861000 + 8) = a1;
    FUN_001ac540(D_0860FC0, D_0861000, 0);
}
