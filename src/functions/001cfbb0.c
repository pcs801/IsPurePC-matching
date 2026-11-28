// FUNCTION: SLPM 0x001CFBB0  size 96  core 88
// eight void calls then return 0
extern void FUN_001cb878(void);
extern void FUN_001cb890(void);
extern void FUN_001cb8a8(void);
extern void FUN_001cb8c0(void);
extern void FUN_001cb8d8(void);
extern void FUN_001cb8f0(void);
extern void FUN_001cb908(void);
extern void FUN_001cb920(void);

int FUN_001cfbb0(void)
{
    FUN_001cb878();
    FUN_001cb890();
    FUN_001cb8a8();
    FUN_001cb8c0();
    FUN_001cb8d8();
    FUN_001cb8f0();
    FUN_001cb908();
    FUN_001cb920();
    return 0;
}
