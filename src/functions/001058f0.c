// FUNCTION: SLPM 0x001058F0  size 80  core 76
// Near-miss (2 words, pure register): target keeps the constant address in $v1
// (lui v1,0xB2 / lw v0,-0x13FC(v1) / addiu v1,v0,0x10); every plain-C form tried
// coalesces address+value into $v0 (literal) or puts value in $v1 (symbol form).

extern unsigned char D_A969D0[];

void FUN_001058f0(int n, unsigned short idx, int val)
{
    int sum = idx;
    if (n > 0) {
        int base = *(int *)0x00B1EC04;
        int *p = (int *)((char *)base + 0x10);
        do {
            sum += *p;
            p = (int *)((char *)p + 0x14);
        } while (--n);
    }
    D_A969D0[sum] = (unsigned char)(val + 1);
}
