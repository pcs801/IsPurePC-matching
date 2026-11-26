// FUNCTION: SLPM 0x00105B90  size 144  core 144
extern unsigned char D_A98D91;
extern unsigned char D_A98D92;
extern unsigned char D_A98D93;
extern unsigned char D_A98D94;
extern unsigned char D_A98D95;

int FUN_00105b90(int idx)
{
    switch (idx) {
    case 0: return D_A98D91;
    case 1: return D_A98D92;
    case 2: return D_A98D93;
    case 3: return D_A98D94;
    case 4: return D_A98D95;
    case 5: return 0x80;
    case 6: return 0;
    }
    return 0x80;
}
