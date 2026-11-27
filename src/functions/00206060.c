// FUNCTION: SLPM 0x00206060  size 40  core 40
extern int *FUN_00212988(void);

int FUN_00206060(void)
{
    *(int *)FUN_00212988() = 5;
    return -1;
}
