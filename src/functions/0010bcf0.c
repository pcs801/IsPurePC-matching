// FUNCTION: SLPM 0x0010BCF0
extern int FUN_00209658(char *, int, int);
extern char D_47B140[];

int FUN_0010bcf0(void)
{
    int i;

    for (;;) {
        if (FUN_00209658(D_47B140, 0x12346, 0) < 0) {
            for (;;)
                ;
        }
        for (i = 0x270F; i != -1; i -= 4)
            ;
        if (*(int *)(D_47B140 + 0x24) != 0)
            return 1;
    }
}
