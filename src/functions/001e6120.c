// FUNCTION: SLPM 0x001E6120  size 176  core 172
// symbol covers two functions: 0x001E6120 (A, 120B) + 0x001E6198 (B, 52B, 无符号的本地函数)
// A: 三维槽表查询（0x70/0x1C 步长 → mult1/mult；D_866190 基址；+0x10 哨兵）
// B: 状态读取（idx<8 → 尾调 FUN_001fc8c0(out, D_00253EF0[idx])，否则 *out = D_0026D7F0）
// 当前 A 30 词（120B，与目标同长）但寄存器/地址折叠仍差；B 68B（目标 52B）：本 ee-gcc 对 B
// 的 sibcall 形态一律发 16B 栈帧 + 死 sd/ld ra（b1..b12 八种写法实测），而原码 B 是 frameless（13 词）。
extern char D_866190[];
extern char D_0026D7F0;
extern int D_00253EF0[];
extern void FUN_001e5ef8(int, int, void *);
extern int FUN_001fc8c0(void *, int);

int FUN_001e6120(int slot, int chan)
{
    char buf[0x80];
    int k1 = 0x70;
    int k2 = 0x1C;
    int a = slot * k1;
    int b = chan * k2;
    char *e = D_866190 + a + b;

    if (*(int *)(e + 0x10) == 0)
        return 0x63;
    FUN_001e5ef8(slot, chan, buf);
    if (buf[0x70] == 6 && buf[0x71] == 2)
        return 5;
    return buf[0x70];
}

int FUN_001e6198(unsigned int idx, char *out)
{
    if (idx < 8)
        return FUN_001fc8c0(out, D_00253EF0[idx]);
    *out = D_0026D7F0;
}
