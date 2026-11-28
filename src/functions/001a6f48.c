// FUNCTION: SLPM 0x001A6F48  size 88  core 88
extern int FUN_001a5c28(int a0);

void FUN_001a6f48(char *p)
{
    unsigned char *r = *(unsigned char **)(p + 104);
    int v = (r[0] << 8) | r[1];
    int n = FUN_001a5c28(v);

    *(int *)(p + 104) = *(int *)(p + 8) + *(int *)(p + 100) * n;
    ((void (*)(void *))*(int *)(p + 28))(p);
}
