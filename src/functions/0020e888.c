// FUNCTION: SLPM 0x0020E888  size 32  core 32
// frame 0x20, jal FUN_0020e2b8 with `daddu a3,sp,zero` in the delay slot (4th arg = a
// 16-byte stack buffer).
extern void FUN_0020e2b8(int, int, int, void *);

void FUN_0020e888(int a0, int a1, int a2)
{
    int buf[4];
    do {
        FUN_0020e2b8(a0, a1, a2, buf);
    } while (0);
}
