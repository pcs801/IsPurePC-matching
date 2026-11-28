// FUNCTION: SLPM 0x001eee70  size 88  core 84
extern int FUN_001ea720(void *a0, int *a1);
extern int FUN_001eecf8(int a0);

int FUN_001eee70(char *p, int a1)
{
    int buf[2];

    if (*(int *)(p + 0x868) != 0 && p != 0 && *(int *)(p + 0xC) != 0) {
        buf[0] = 0;
        buf[1] = a1;
        return FUN_001ea720(*(void **)(p + 0x868), buf);
    }
    return FUN_001eecf8(a1);
}
