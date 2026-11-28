// FUNCTION: SLPM 0x0019B5E8  size 160  core 156  (MISS 156/156 长度对，15 词)
// 结构已对（六参转发 + step*2 步进），差在 prologue 调度序：ROM 在 beqz 之后才算
// s5 = a0+0x18 / s4 = step<<1，我们被提前到参数保存之间；且守卫写法（if(n==0) return 与
// for 自守）都试过，前者 164/156、后者 156/156 仍差 15 词 → 调度墙。
extern void FUN_0019ac28(int a0, char *a1, int a2, int a3, int a4, int a5);

void FUN_0019b5e8(int *p, int a1)
{
    int n = p[1];
    int step = p[0];
    int cur = p[2];
    char *q = (char *)p + 0x18;
    int i;

    for (i = 0; i < n; i++) {
        FUN_0019ac28(a1, q, 0, i, cur, step);
        cur += step * 2;
    }
}
