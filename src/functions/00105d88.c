// FUNCTION: SLPM 0x00105D88  size 176  core 172
extern char D_00B1EC00[];
extern unsigned char D_00A98D10[];
extern unsigned short FUN_00105818(int i);

void FUN_00105d88(int a) {
    char *st = D_00B1EC00;
    int i;
    for (i = 0; i < *(unsigned int *)(st + 0x6958); i++) {
        if (FUN_00105818(i) == a)
            D_00A98D10[i / 8] |= 1 << (i % 8);
    }
}
