// FUNCTION: SLPM 0x0016EA80  size 48  core 44
// D_00270BF4 = *(int*)(p+0x44) ; if (FUN_0016cf88(p)) D_00270C54 = 3;
extern int D_00270BF4;
extern int D_00270C54;
extern int FUN_0016cf88(char *);

void FUN_0016ea80(char *p)
{
    D_00270BF4 = *(int *)(p + 0x44);
    if (FUN_0016cf88(p))
        D_00270C54 = 3;
}
