// FUNCTION: SLPM 0x00114550  size 160 (core 156)
// MISS: 116/156 bytes. Semantics recovered: GS/VIF register poke then semaphore delete.
//   FUN_0020f130(); *(int*)0x1000F590 = *(int*)0x1000F520 | 0x10000;
//   *(int*)0x1000B400 = 5; *(int*)0x1000F590 = *(int*)0x1000F520 & ~0x10000;
//   FUN_0020f180(); *(int*)0x1000B420 = 0; *(int*)0x1000B410 = 0; *(int*)0x1000B430 = 0;
//   FUN_002059b0(obj->f40); return 1;
// Remaining gap is codegen shape only: the target materialises every literal address into
// a register (lui+ori) and uses 0-displacement accesses - an unoptimised-looking build of
// the same source - while ee-gcc -O2 always folds them (lui v1,0x1001 / lw v1,-2784(v1)).
// Tried pointer locals, int-typed address locals, explicit load temporaries and -G8:
// all give the same 116-byte -O2 form.
extern void FUN_0020f130(void);
extern void FUN_0020f180(void);
extern void FUN_002059b0(int sema);

int FUN_00114550(int *p)
{
    FUN_0020f130();
    *(int *)0x1000F590 = *(int *)0x1000F520 | 0x10000;
    *(int *)0x1000B400 = 5;
    *(int *)0x1000F590 = *(int *)0x1000F520 & 0xFFFEFFFF;
    FUN_0020f180();
    *(int *)0x1000B420 = 0;
    *(int *)0x1000B410 = 0;
    *(int *)0x1000B430 = 0;
    FUN_002059b0(p[0x10]);
    return 1;
}
