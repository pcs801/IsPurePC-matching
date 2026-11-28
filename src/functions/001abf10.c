extern char D_00860FC0[];
extern char D_00861000[];
extern int FUN_001ab4b0(int a0);
extern int FUN_001fc1e0(char *a0, int a1);
extern int FUN_001ac540(char *a0, char *a1, int a2);

// frame-wall experiment: a *used* 16-byte local grows the frame 0x20 -> 0x30
void FUN_001abf10(int a0)
{
    char pad[16];

    FUN_001ab4b0(a0);
    pad[0] = D_00861000[0x10];
    FUN_001fc1e0(pad, a0);
    FUN_001ac540(D_00860FC0, D_00861000, 8);
}
