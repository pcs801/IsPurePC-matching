// FUNCTION: SLPM 0x001C78B0  size 64  core 56
extern char D_00237790[];
extern char D_00237798[];
extern char D_00268F50[];
extern void FUN_001b2390(char *);

int FUN_001c78b0(void)
{
    if (*(int *)D_00237790 == 1) {
        if (*(int *)D_00237798 <= 0)
            return 0;
    }
    FUN_001b2390(D_00268F50);
    return 0;
}
