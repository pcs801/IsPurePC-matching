// FUNCTION: SLPM 0x0010ED40  size 16
// sig: lui ; addiu ; jr ; lw
// target: return *(int *)((char *)&D_825840 + 0x48);
// note: the duplicated return keeps the base address materialized (lui+addiu)
//       instead of letting gcc fold %lo(sym+0x48) into the load displacement.

extern char D_825840;

int FUN_0010ed40(void) {
    char *p = &D_825840;
    if (p) {
        return *(int *)(p + 0x48);
    }
    return *(int *)(p + 0x48);
}
