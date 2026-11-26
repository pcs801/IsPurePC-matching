extern int FUN_001aa830(char *, char *, int, int);
extern int FUN_0010be90();

extern int D_477C40[];
extern int D_46CC40[];
extern char D_002589D0[];
extern char D_002589F0[];

int FUN_0010bb18(char *p)
{
    int r = FUN_001aa830((char *)D_477C40, (char *)D_46CC40, *(int *)(p + 0x7E78), -1);

    if (r < 0)
        FUN_0010be90(D_002589D0, r);
    else
        FUN_0010be90(D_002589F0);
    return r;
}
