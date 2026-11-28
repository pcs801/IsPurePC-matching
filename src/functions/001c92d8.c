// FUNCTION: SLPM 0x001C92D8  size 96  core 80
// char buf[0x40]; FUN_001fc8c0(buf, a0); FUN_001fc4c0(buf, a1); FUN_001d3398(buf);
extern void FUN_001fc8c0(char *, char *);
extern void FUN_001fc4c0(char *, char *);
extern void FUN_001d3398(char *);

void FUN_001c92d8(char *a0, char *a1)
{
    char buf[0x40];

    FUN_001fc8c0(buf, a0);
    FUN_001fc4c0(buf, a1);
    FUN_001d3398(buf);
}
