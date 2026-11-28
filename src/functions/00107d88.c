// FUNCTION: SLPM 0x00107D88  size 48  core 44
// FUN_001b7090(*(int*)(D_00281580 + idx*0x4E280 + 4));
extern char D_00281580[];
extern void FUN_001b7090(int);

void FUN_00107d88(int idx)
{
    FUN_001b7090(*(int *)(D_00281580 + idx * 0x4E280 + 4));
}
