// FUNCTION: SLPM 0x001C7BD8  size 48  core 44
// three jal then a tail sibcall: FUN_001c7a90()
extern void FUN_001c7ac0(void);
extern void FUN_001c7c08(void);
extern void FUN_001c7ad8(void);
extern void FUN_001c7a90(void);

void FUN_001c7bd8(void)
{
    FUN_001c7ac0();
    FUN_001c7c08();
    FUN_001c7ad8();
    FUN_001c7a90();
}
