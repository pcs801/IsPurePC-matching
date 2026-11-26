// FUNCTION: SLPM 0x0010C230  size 240  core 240
// sig: addiu ; daddu ; sd ; daddu ; sd ; sd ; jal ; daddu ; daddu ; jal ; addiu ; lh
// fall-through state machine on FadeAccumulator::phase (int16 at 0x10)
// matched: ee-gcc -O2 -mips3 -G0, worker m26b10-tu-0010c230

extern void FUN_00155b68(void *, int);
extern void FUN_00155b78(void *, int);
extern void FUN_0017efa0(int, int);
extern int FUN_0017efe8(void);
extern int D_00C56508;

typedef struct {
    char pad[0x10];
    short phase;
} FadeAccumulator;

int FUN_0010c230(FadeAccumulator *o) {
    int tmp[4];

    FUN_00155b68(tmp, 0);
    FUN_00155b78(tmp, 1);

    switch (o->phase) {
    case 0:
        FUN_0017efa0(2, 10);
        o->phase = 1;
    case 1:
        if (FUN_0017efe8() != 1)
            break;
        o->phase = 2;
        break;
    case 2:
        if (D_00C56508 != 0) {
            FUN_0017efa0(3, 10);
            o->phase = 3;
        }
        break;
    case 3:
        if (FUN_0017efe8() == 1)
            return 1;
        break;
    }
    return 0;
}
