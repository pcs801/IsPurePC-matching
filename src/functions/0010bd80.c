// FUNCTION: SLPM 0x0010BD80
extern int D_47B100;
extern char D_47B140[];
extern int FUN_00209838(char *, int, int, void *, int, void *, int, int, int);

int FUN_0010bd80(unsigned int cmd, void *arg)
{
    int mode = 0;

    if (cmd & 0x8000)
        mode = 0x40;
    if (cmd & 0x1000) {
        FUN_00209838(D_47B140, cmd, 0, arg, 0x40, &D_47B100, mode, 0, 0);
    } else {
        D_47B100 = (int)arg;
        FUN_00209838(D_47B140, cmd, 0, &D_47B100, 0x10, &D_47B100, mode, 0, 0);
    }
    return D_47B100;
}
