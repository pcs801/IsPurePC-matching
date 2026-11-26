// FUNCTION: SLPM 0x001317F0  size 64  core 64
// sig: sll ; lw ; addu ; addiu ; sll ; addu ; sll ; addu ; daddu ; lui ; addu ; sw

extern int *D_00270CAC;

void *FUN_001317f0(int a0) {
    char *p = (char *)D_00270CAC + a0 * 84;
    *(int *)(p + 0x3F19C) = 1;
    *(int *)(p + 0x3F198) = 1;
    return p;
}
