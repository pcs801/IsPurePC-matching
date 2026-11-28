// FUNCTION: SLPM 0x001F4ED0  size 112  core 108  (MISS 120/108, 26 words)
// ROM 帧 -0x20：s0@0x0 / ra@0x10，0x8 处有一个未访问的 8 字节槽（同 TU 已中招的
// 0x001F6F38 是 int buf[2]@0 + ra@0x10）→ 原码应有一个 8 字节局部量，本写法没有。
// 另外 ROM 第二路是 jal + 共享尾声（无 sibcall）；加 -fno-optimize-sibling-calls 可把
// 尾部 j 变 jal，长度 116/108，但帧仍是 -0x10。blezl/blez 差异同源。
extern int D_002542D0;
extern char D_0026E0A0[];
extern char D_00255E40[];
extern void FUN_00208450(char *p);
extern int FUN_00209a38(char *p);
extern int FUN_00206a18(int a0);

int FUN_001f4ed0(int a0)
{
    char *p;

    if (a0 == 0) {
        if (D_002542D0 > 0)
            FUN_00208450(D_0026E0A0);
        p = D_00255E40;
        while (FUN_00209a38(p) != 0)
            FUN_00206a18(0xFA0);
        return 0;
    }
    return FUN_00209a38(D_00255E40);
}
