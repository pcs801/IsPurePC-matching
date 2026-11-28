extern char D_00265D30[];
extern void FUN_001fc2a8(void *buf, char *name, int a2, int a3);
extern void FUN_001b00f0(int a0, void *buf);

void FUN_001b5fa0(int a0, int a1, int a2)
{
    int buf[8];

    FUN_001fc2a8(buf, D_00265D30, a1, (unsigned int)(a2 + 2047) >> 11);
    FUN_001b00f0(a0, buf);
}
