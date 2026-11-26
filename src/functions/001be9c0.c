// FUNCTION: SLPM 0x001BE9C0  size 32  core 32
// sig: lui ; addiu ; jr ; sw ; lui ; addiu ; jr ; lw
// two-function pair over the GsState word at 0x002305E0:
//   FUN_001be9c0 = setter (sw $a0,0(addr)), FUN_001be9d0 = getter (lw $v0,0(addr))
// Status: MISS (volatile-class). Plain -O2 C always folds %lo into the store/load
// offset (lui + sw %lo) and never materialises the full address with addiu.

extern int D_002305E0;

void FUN_001be9c0(int v) { D_002305E0 = v; }
int FUN_001be9d0(void) { return D_002305E0; }
