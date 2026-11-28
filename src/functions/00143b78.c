extern char *D_00270BBC;
extern void FUN_001436e0(int a0, int a1, int *a2);
extern void FUN_001a8260(void *p);
extern int FUN_001a8250(void *p);

void FUN_00143b78(void)
{
    int args[8];

    switch (*(int *)D_00270BBC) {
    case 3:
    case 4:
    case 6:
    case 7:
    case 10:
        args[0] = 0;
        args[1] = 0;
        FUN_001436e0(*(int *)(D_00270BBC + 280), *(signed char *)(D_00270BBC + 296), args);
        break;
    case 5:
        FUN_001a8260(D_00270BBC + 300);
        if (*(int *)(D_00270BBC + 292) == 0) {
            args[0] = 640 - FUN_001a8250(D_00270BBC + 300);
            args[1] = 0;
            FUN_001436e0(*(int *)(D_00270BBC + 280), *(signed char *)(D_00270BBC + 296), args);
            args[0] -= 640;
            args[1] = 0;
            FUN_001436e0(*(int *)(D_00270BBC + 288), !(*(signed char *)(D_00270BBC + 296)), args);
        } else {
            args[0] = FUN_001a8250(D_00270BBC + 300) - 640;
            args[1] = 0;
            FUN_001436e0(*(int *)(D_00270BBC + 280), *(signed char *)(D_00270BBC + 296), args);
            args[0] += 640;
            args[1] = 0;
            FUN_001436e0(*(int *)(D_00270BBC + 288), !(*(signed char *)(D_00270BBC + 296)), args);
        }
        break;
    case 8:
    case 9:
        break;
    default:
        break;
    }
}