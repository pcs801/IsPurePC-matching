// FUNCTION: SLPM 0x001B8108  size 24  core 20
// sig: lui ; lui ; sw ; jr ; sw ; nop
// stores the argument into the two adjacent GsState globals

extern unsigned int D_002304C0;
extern unsigned int D_002304C4;

void FUN_001b8108(unsigned int value)
{
    D_002304C0 = value;
    D_002304C4 = value;
}
