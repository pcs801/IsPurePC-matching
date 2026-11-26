// FUNCTION: SLPM 0x001EA668
void FUN_001ea668(void *arg0, int arg1, int arg2, int arg3) {
    char *p = *(char **)((char *)arg0 + 0x40);
    *(int *)(p + 0xA8) = arg1;
    *(int *)(p + 0xAC) = arg2;
    *(int *)(p + 0xB0) = arg3;
}

void FUN_001ea680(void *arg0, int *arg1, int *arg2, int *arg3) {
    char *p = *(char **)((char *)arg0 + 0x40);
    *arg1 = *(int *)(p + 0xA8);
    *arg2 = *(int *)(p + 0xAC);
    *arg3 = *(int *)(p + 0xB0);
}
