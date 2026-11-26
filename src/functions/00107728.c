// FUNCTION: SLPM 0x00107728  size 48
// sig: lui ; sll ; addiu ; sra ; addiu ; lw ; addu ; lbu ; sb ; movn ; jr ; sw

extern unsigned char D_270E80[];
extern int D_00270AA4;

void FUN_00107728(short a0) {
    unsigned char *p;
    unsigned char *q;
    unsigned char c;
    p = D_270E80;
    p = p + 2;
    q = p + a0;
    c = *q;
    *q = 0;
    if (c) {
        D_00270AA4 = a0;
    }
}
