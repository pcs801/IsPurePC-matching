// FUNCTION: SLPM 0x001CACC0  size 96  core 88  (splat merged two functions)
//  0x1CACC0: int buf = *(int*)(p+0x10); FUN_001c01a8(1,&buf,1,0,0); *(char*)p = 0;
//  0x1CAD08: *（u16*)(p+2) += 1 and return it (int return - no truncation)
extern void FUN_001c01a8(int, int *, int, int, int);

void FUN_001cacc0(char *p)
{
    int buf;

    buf = *(int *)(p + 0x10);
    FUN_001c01a8(1, &buf, 1, 0, 0);
    *(char *)p = 0;
}

int FUN_001cad08(char *p)
{
    int v;

    v = *(unsigned short *)(p + 2);
    v = v + 1;
    *(unsigned short *)(p + 2) = v;
    return v;
}
