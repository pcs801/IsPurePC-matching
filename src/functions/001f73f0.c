extern void FUN_001f7318(char *p);

void FUN_001f73f0(char *p)
{
    if (p[3] == 0) {
        p[3] = 23;
        FUN_001f7318(p);
        return;
    }
    p[3] = p[3] - 1;
}
