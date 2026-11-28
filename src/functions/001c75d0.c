// FUNCTION: SLPM 0x001C75D0  size 72  core 64
// if (D_00237790 == 1) { if (a1 > 0) a1 = 0; if (*(int*)D_00237798 <= 0) return; }
// if (a1 < -999) a1 = -999; *(int*)(p + 0x38) = a1;
extern char D_00237790[];
extern char D_00237798[];

void FUN_001c75d0(char *p, int a1)
{
    if (*(int *)D_00237790 == 1) {
        if (a1 > 0)
            a1 = 0;
        if (*(int *)D_00237798 <= 0)
            return;
    }
    if (a1 < -999)
        a1 = -999;
    *(int *)(p + 0x38) = a1;
}
