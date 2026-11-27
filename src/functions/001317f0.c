// FUNCTION: SLPM 0x001317F0  size 64  core 64
// sig: sll ; lw ; addu ; addiu ; sll ; addu ; sll ; addu ; daddu ; lui ; addu ; sw
// near-miss: 64/64 bytes, 10 words. got base in $v1, want $a1 (lw $a1,-0x6D44($gp));
// inline-expression form DOES get $a1 but re-loads the global for the 2nd store (76B).
// Remaining: 需 p 只算一次且基址落 $a1、v0 = p 供返回，源级未找到同时满足的写法。

extern int *D_00270CAC;

void *FUN_001317f0(int a0) {
    char *p = (char *)D_00270CAC + a0 * 84;
    *(int *)(p + 0x3F198) = 1;
    *(int *)(p + 0x3F19C) = 1;
    return p;
}
