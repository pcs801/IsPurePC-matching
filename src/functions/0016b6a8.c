// FUNCTION: SLPM 0x0016B6A8
extern unsigned char D_00A98D91[];
extern int FUN_00107990(int a0);
extern int FUN_00107b90(int a0, int a1);
extern int func_00107C98(int a0);
extern int FUN_00107758(int a0);

int FUN_0016b6a8(int a0, int a1)
{
    int c;

    c = a1;
    switch (a0) {
    case 2:
        D_00A98D91[0] = c;
        FUN_00107990(-1);
        FUN_00107b90(1, -1);
        FUN_00107b90(2, -1);
        FUN_00107b90(3, -1);
        return FUN_00107b90(4, -1);
    case 0:
        D_00A98D91[2] = c;
        return FUN_00107b90(0, -1);
    case 1:
        D_00A98D91[1] = c;
        FUN_00107b90(1, -1);
        FUN_00107b90(2, -1);
        FUN_00107b90(3, -1);
        return FUN_00107b90(4, (short)func_00107C98(1));
    case 3:
        D_00A98D91[4] = c;
        return;
    case 4:
        D_00A98D91[3] = c;
        return FUN_00107758(-1);
    }
    return;
}
