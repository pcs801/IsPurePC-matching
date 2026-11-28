// FUNCTION: SLPM 0x001ea528  size 72  core 72
// ROM: frame 16, q = *(int **)(p+0x40); stores 0xC4/0xEC/0xF8/0xF0 + 0xF4 in call delay slot;
// call is a plain jal (this TU region does not sibcall), 5 stores use q in $a3.
extern void FUN_001e9c88(void);

void FUN_001ea528(char *p, unsigned int a1, int a2)
{
    int *q = *(int **)(p + 0x40);

    q[0x31] = 1;
    q[0x3B] = (a1 & 0xFFFFFFF) | 0x20000000;
    q[0x3E] = a2;
    q[0x3D] = 0;
    q[0x3C] = 0;
    FUN_001e9c88();
}
