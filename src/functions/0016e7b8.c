// FUNCTION: SLPM 0x0016E7B8  size 80  core 76
extern unsigned char D_A98D90[];
extern void FUN_00104f10(int);

void FUN_0016e7b8(int a0, int a1)
{
    switch (a1) {
    case 0:
    case 1:
    case 4:
    case 5:
        break;
    case 2:
    case 3:
        FUN_00104f10(D_A98D90[0]);
        break;
    }
}
