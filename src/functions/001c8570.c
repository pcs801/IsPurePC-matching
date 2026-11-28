// FUNCTION: SLPM 0x001C8570  size 48  core 44
// three jal then a tail sibcall: FUN_001c7ad8()
extern void FUN_001c7a58(void);
extern void FUN_001c7ac0(void);
extern void FUN_001c85a0(void);
extern void FUN_001c7ad8(void);

void FUN_001c8570(void)
{
    FUN_001c7a58();
    FUN_001c7ac0();
    FUN_001c85a0();
    FUN_001c7ad8();
}
