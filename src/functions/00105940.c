// FUNCTION: SLPM 0x00105940  size 232  core 228
// sig: lui ; lui ; addiu ; addiu ; addiu ; addiu ; addiu ; daddu ; sd ; sd ; daddu ; sd

extern unsigned int D_00212D70[];
extern unsigned int D_873F00[];
extern unsigned int D_D72980[];
extern unsigned int *D_01BA0D50;
extern void FUN_00100fc8(int, int, void *, void *);
extern void FUN_0019e328(void *, int, int, void *);

void FUN_00105940(void) {
    unsigned int i;
    FUN_00100fc8(7, 0x15, D_873F00, D_D72980);
    for (i = 0; i < 26; i++) {
        unsigned int idx = D_00212D70[i * 2];
        unsigned int sel = D_00212D70[i * 2 + 1];
        unsigned int off = ((D_873F00[0] * 4 + 0x13) >> 4) + (&D_873F00[1])[sel];
        FUN_0019e328((void *)(*D_01BA0D50 + idx * 44), 0x2BC0, 0x3D40,
                     (void *)((char *)D_873F00 + (off << 4)));
    }
}
