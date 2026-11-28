extern char *D_00270CAC;

void FUN_00131578(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        char *e = D_00270CAC + i * 84 + 0x3F18C;

        *(int *)(e + 0xC) = 0;
        *(int *)(e) = 0;
        *(char *)(e + 0x2C) = 0;
        *(int *)(e + 0x28) = 0;
    }
}
