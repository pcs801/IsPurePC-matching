// FUNCTION: SLPM 0x00112550  size 56  core 52

extern void FUN_00114550(void *);
extern void FUN_001ea4e0(int);

int FUN_00112550(int self)
{
    FUN_00114550((char *)self + 0x48);
    FUN_001ea4e0(self);
    return 1;
}
