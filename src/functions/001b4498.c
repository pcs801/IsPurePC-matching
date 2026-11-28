// FUNCTION: SLPM 0x001B4498  size 72  core 72
extern void FUN_001b4288(int a0, int a1, int a2, int a3);
extern void FUN_001b4370(int a0, int a1, int a2, int a3);

void FUN_001b4498(int a0, int a1)
{
    if (a1 < 256) {
        FUN_001b4288(0, 0, 0, a0);
        return;
    }
    FUN_001b4370(0, 0, 0, a0);
}
