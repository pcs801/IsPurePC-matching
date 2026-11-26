// FUNCTION: SLPM 0x00104E20  size 40  core 40
// sig: lui ; addiu ; daddu ; addiu ; sd ; jal ; addiu ; ld ; j ; addiu

extern char D_1B73FC0[];
extern void FUN_001fbb84(char *, int, int);
extern void FUN_00114a48(void);

void FUN_00104e20(void) {
    FUN_001fbb84(D_1B73FC0, 0, 0x1EC);
    FUN_00114a48();
}
