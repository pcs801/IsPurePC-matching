// FUNCTION: SLPM 0x00112598 (getter + setter pair, core 20 of 24)

int FUN_00112598(char *p) {
    return *(int *)(p + 0xA8);
}

int FUN_0011259c(char *p, int v) {
    int old = *(int *)(p + 0xA8);
    *(int *)(p + 0xA8) = v;
    return old;
}
