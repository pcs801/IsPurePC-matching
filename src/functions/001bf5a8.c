// FUNCTION: SLPM 0x001BF5A8  size 48  core 48
// Region is two adjacent accessor bodies over the state words at 0x002305D0/0x002305D4:
//   0x001BF5A8 setter (32 B): D0 = D4; D4 = a0
//   0x001BF5C8 getter (16 B): return D4
// Status: MISS (vol-class). The original materialises both absolute addresses
// (lui + addiu + 0(reg)); plain -O2 C always folds %lo into the load/store offset
// (lui + lw/sw %lo(reg)). Only a vol-qualified access reproduces the exact bytes,
// and that qualifier is rejected by the candidate sanitizer.
extern int D_002305D0;
extern int D_002305D4;

void FUN_001bf5a8(int a0) {
    D_002305D0 = D_002305D4;
    D_002305D4 = a0;
}

int FUN_001bf5c8(void) {
    return D_002305D4;
}
