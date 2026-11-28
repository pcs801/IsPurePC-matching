extern void FUN_00208398(char *buf, int n, int a2, int a3);
extern void FUN_001eee70(int a0, char *buf);

void FUN_001eeec8(int a0, int a1, int a2)
{
    char buf[272];

    FUN_00208398(buf, 256, a1, a2);
    FUN_001eee70(a0, buf);
}
