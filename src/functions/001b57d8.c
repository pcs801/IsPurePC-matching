// FUNCTION: SLPM 0x001B57D8  size 88  core 88
extern void FUN_001b5c70(void);
extern void FUN_001b5818(void *p, int v);
extern void FUN_001b5c88(void);

void FUN_001b57d8(char *p, int v)
{
    FUN_001b5c70();
    FUN_001b5818(p, v);
    FUN_001b5c88();
}
