// FUNCTION: SLPM 0x001D1288  size 72  core 72
void FUN_001d1288(char *p, int *a1, int *a2)
{
    *a1 = 0;
    *a2 = -45;
    if (*(signed char *)(p + 421) != 0) {
        if (*(signed char *)(p + 518) > 0)
            *a1 = *(signed char *)(p + 519);
        if (*(signed char *)(p + 520) > 0)
            *a2 = *(signed char *)(p + 521);
    }
}
