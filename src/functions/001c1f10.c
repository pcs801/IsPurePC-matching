// FUNCTION: SLPM 0x001C1F10  size 196  (core 196, g=0)
// Near-miss fix: the fast path (*(int*)(self+0x2C) == 0) must NOT materialise a return
// value - the target falls straight into the epilogue with no "move v0,zero". Writing
// "return 0;" adds exactly one word (daddu v0,zero) and shifts the whole tail, so the
// function relies on the implicit fall-through (or a bare "return;").
extern int FUN_001cae38(int a0);
extern int FUN_001be870(int a0);
extern void FUN_001be630(int a0);
extern int FUN_001caeb0(void);

int FUN_001c1f10(int self)
{
    int v;

    if (*(int *)(self + 0x2C)) {
        FUN_001cae38(self);
        v = FUN_001be870(*(int *)(self + 0x2C));
        switch (v) {
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            break;
        case 9:
            *(char *)(self + 2) = 3;
            FUN_001be630(*(int *)(self + 0x2C));
            *(int *)(self + 0x2C) = 0;
            break;
        case 3:
            *(int *)(self + 0x28) = *(int *)(self + 0x24);
            *(int *)(self + 0x1C) = *(int *)(self + 0x1C) + *(int *)(self + 0x24);
            *(char *)(self + 2) = 1;
            FUN_001be630(*(int *)(self + 0x2C));
            *(int *)(self + 0x2C) = 0;
            break;
        case 0:
            *(char *)(self + 2) = 0;
            FUN_001be630(*(int *)(self + 0x2C));
            *(int *)(self + 0x2C) = 0;
            break;
        }
        return FUN_001caeb0();
    }
}
