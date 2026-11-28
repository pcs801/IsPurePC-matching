// FUNCTION: SLPM 0x002049C8  size 128  core 128  (MISS 128/128 长度对，11 词)
// 关键：FUN_00204d40 必须声明成 long long 返回、本函数 int —— 尾部 dsll32/dsra32 的
// int->64 符号扩展才对得上（long 在 ee-gcc 是 32 位，不行）。剩下的是调度序 + s1/s2 绑定对调
// （ROM s1=a1/s2=a2，gcc 给我们 s1=a2/s2=a1）。
extern long long FUN_00204d40(int a0, int a1, int a2, int a3);
extern int FUN_00204f10(int a0, int a1, int a2, int a3);

int FUN_002049c8(char *p, int a1, int a2)
{
    if (*(unsigned short *)(p + 0xC) & 0x100)
        FUN_00204f10(*(int *)(p + 0x54), *(short *)(p + 0xE), 0, 2);
    *(unsigned short *)(p + 0xC) &= 0xEFFF;
    return FUN_00204d40(*(int *)(p + 0x54), *(short *)(p + 0xE), a1, a2);
}
