// FUNCTION: SLPM 0x001D2338  size 120  core 116  (MISS 116/116 长度对，12 词全是调度序)
// ROM 序：lui 0x86 / addiu sp / lw 0x865E7C / li v0,-1 / sd s1 / s1=a0 / sd s2 / s2=a1 / sd s0 / beqz / sd ra
// 我们序：addiu sp / li v0,-1 / sd s1 / s1=a0 / sd s2 / sd s0 / sd ra / lui / lw / beqz / s2=a1
// 尾部：ROM 先 li v0,0 再 sw s2,0xC(s0)，我们相反。
// 已试 3 变体（int 局部承接全局读 / ((int*)p)[3]），编译结果完全一致 → 判调度墙。
extern int FUN_001d2250(void);
extern void FUN_001fcfa0(int a0, int a1, int a2);

int FUN_001d2338(int a0, int a1)
{
    int p;

    if (*(int *)0x00865E7C == 0)
        return -1;
    p = FUN_001d2250();
    if (p == 0)
        return -2;
    FUN_001fcfa0(p, a0, 0xC);
    *(int *)(p + 0xC) = a1;
    return 0;
}
