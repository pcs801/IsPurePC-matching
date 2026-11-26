// FUNCTION: SLPM 0x00105838  size 64  core 60
// sig: lui ; sll ; addu ; lw ; sll ; sll ; addu ; bnez ; lw ; jr ; lw ; nop

extern int *D_00B25554;

int FUN_00105838(int a, int b) {
    int *p = (int *)D_00B25554[3 * a];
    if (b == 0)
        return *p;
    return *(int *)((char *)p + (b << 2));
}
