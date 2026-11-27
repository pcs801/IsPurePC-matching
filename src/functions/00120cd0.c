// FUNCTION: SLPM 0x00120CD0  size 448  core 448
// Dispatch on *(signed char *)(obj+1) via jtbl_00259F00 (10 entries; ASCII "0123" follows).
// Each body builds a 2-int block on the stack, passes &block + obj + arg (+ one extra value
// for cases 0/5/6) and returns the callee result. D_A94700 is accessed through a struct so
// ee-gcc keeps the symbol base and uses the 0x4698/0x4699 displacements.

struct Adj {
    char pad[0x4698];
    signed char dx;
    signed char dy;
};

extern char D_A94700[];
extern int FUN_00124200(int *p, void *obj, int arg, int a);
extern int FUN_00124620(int *p, void *obj, int arg);
extern int FUN_00124848(int *p, void *obj, int arg);
extern int FUN_00124978(int *p, void *obj, int arg);
extern int FUN_00125098(int *p, void *obj, int arg);
extern int FUN_00125170(int *p, void *obj, int arg, int a);
extern int FUN_00125a70(int *p, void *obj, int arg, int a);
extern int FUN_00126028(int *p, void *obj, int arg);

int FUN_00120cd0(void *obj, int arg)
{
    int v[2];
    struct Adj *p;

    switch (*(signed char *)((char *)obj + 1)) {
    case 0:
        v[0] = *(int *)((char *)obj + 0x4C) + ((struct Adj *)D_A94700)->dx;
        v[1] = *(int *)((char *)obj + 0x50) - ((struct Adj *)D_A94700)->dy;
        return FUN_00124200(v, obj, arg, v[0]);
    case 1:
        v[0] = 0x22;
        v[1] = 0x28;
        return FUN_00124620(v, obj, arg);
    case 2:
        v[0] = *(int *)((char *)obj + 0x4C);
        v[1] = *(int *)((char *)obj + 0x50);
        return FUN_00124848(v, obj, arg);
    case 3:
        v[0] = *(int *)((char *)obj + 0x4C);
        v[1] = *(int *)((char *)obj + 0x50) + 0x27;
        return FUN_00124978(v, obj, arg);
    case 4:
        v[0] = *(int *)((char *)obj + 0x4C);
        v[1] = *(int *)((char *)obj + 0x50);
        return FUN_00125098(v, obj, arg);
    case 5:
        v[0] = *(int *)((char *)obj + 0x4C) + ((struct Adj *)D_A94700)->dx;
        v[1] = *(int *)((char *)obj + 0x50) - ((struct Adj *)D_A94700)->dy;
        return FUN_00125170(v, obj, arg, v[0]);
    case 6:
        v[0] = *(int *)((char *)obj + 0x4C) + ((struct Adj *)D_A94700)->dx;
        v[1] = *(int *)((char *)obj + 0x50) - ((struct Adj *)D_A94700)->dy;
        return FUN_00125a70(v, obj, arg, v[0]);
    case 7:
    case 8:
    case 9:
        v[0] = *(int *)((char *)obj + 0x4C);
        v[1] = *(int *)((char *)obj + 0x50);
        return FUN_00126028(v, obj, arg);
    }
}