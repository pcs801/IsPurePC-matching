extern int D_00270AAC;
extern int D_00270AA8;

struct GsState { char pad[0xB8]; unsigned int flags; };

void FUN_00107f30(void);
void FUN_001080a0(void);
void FUN_001081f8(void);

void FUN_001084e0(void)
{
    struct GsState *gs = *(struct GsState **)0x01B9F900;
    int mode;

    if (gs->flags & 8) {
        D_00270AAC = (D_00270AAC + 1) % 3;
    }
    mode = D_00270AAC;
    switch (mode) {
    case 0:
        FUN_00107f30();
        break;
    case 1:
        FUN_001080a0();
        break;
    case 2:
        break;
    case 0x63:
        FUN_001081f8();
        break;
    }
    D_00270AA8 = 0;
}
