// FUNCTION: SLPM 0x001F3A68  size 80  core 80
extern void FUN_001f38c8(int a0);
extern void FUN_001f3900(int a0);

void FUN_001f3a68(int a0)
{
    int v;

    FUN_001f38c8(a0);
    v = *(int *)0x10002020;
    if (((-(v & 7)) & 7) == 0)
        return;
    FUN_001f3900(a0);
}
