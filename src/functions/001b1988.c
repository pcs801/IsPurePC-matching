// SLPM 0x001B1988 slice (core 36) contains TWO adjacent functions:
//   0x001B1988 thunk -> tail call FUN_001cae20
//   0x001B19A0 getter -> return D_00227030
extern void FUN_001cae20(void);
extern int D_00227030;

void FUN_001b1988(void)
{
    FUN_001cae20();
}

int FUN_001b19a0(void)
{
    return D_00227030;
}
