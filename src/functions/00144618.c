// FUNCTION: SLPM 0x00144618  size 88  core 88  -G8
extern int D_00270BBC;
extern int D_0027033C;
extern int D_00270340;
extern int D_00270344;
extern int D_00270348;
extern int D_0027034C;
extern int D_00270350;
extern void FUN_00144670(void);

void FUN_00144618(void)
{
    if (*(int *)(D_00270BBC + 0x14C) != 0) {
        FUN_00144670();
        return;
    }
    D_00270340 = 0;
    D_00270350 = 0x80;
    D_0027033C = 0;
    D_00270344 = 0x80;
    D_00270348 = 0x80;
    D_0027034C = 0x80;
}
