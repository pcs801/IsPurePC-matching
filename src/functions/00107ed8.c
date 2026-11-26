extern char D_00281584[];
extern int FUN_001b7758(int);

int FUN_00107ed8(int idx)
{
    return FUN_001b7758(*(int *)(D_00281584 + idx * 0x4E280)) * 60 / 100;
}
