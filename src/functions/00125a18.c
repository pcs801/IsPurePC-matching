// FUNCTION: SLPM 0x00125A18  size 64  core 52
// p = D_082A1C0 + idx*4; if (*p == v) return 0; *p = v; *(int*)(D_082A1E0 + idx*4) = 0x14; return 1;
extern char D_082A1C0[];
extern char D_082A1E0[];

int FUN_00125a18(int idx, int v)
{
    int *p;

    p = (int *)(D_082A1C0 + idx * 4);
    if (*p == v)
        return 0;
    *p = v;
    *(int *)(D_082A1E0 + idx * 4) = 0x14;
    return 1;
}
