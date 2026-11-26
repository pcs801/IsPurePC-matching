// FUNCTION: SLPM 0x001C2A98
extern int FUN_001c29d8(void);
extern int FUN_001c29f8(void);
extern int FUN_001c2a28(void);
extern int FUN_001c2a48(void);
extern int FUN_001c2a78(void);
extern int FUN_001c2a88(void);

int FUN_001c2a98(void *p, int op)
{
    int r = 0;
    if (!p) return 0;
    switch (op) {
    case 0xC8: r = FUN_001c29d8(); break;
    case 0xC9: r = FUN_001c29f8(); break;
    case 0xCA:
    case 0xCC: r = FUN_001c2a28(); break;
    case 0xCB:
    case 0xCD: r = FUN_001c2a48(); break;
    case 0x12D: r = FUN_001c2a78(); break;
    case 0x12E: r = FUN_001c2a88(); break;
    case 0x12B: r = 1; break;
    }
    return r;
}
