// FUNCTION: SLPM 0x001BB560  size 152  core 152  (g=0)
// Jump-table dispatcher over ctx->f2 (signed char, 5-entry table at 0x00266730):
//   idx 0/1 -> 0x1BB5B8, idx 2 -> 0x1BB5E0, idx 3/4 -> 0x1BB5E8 (fall straight to the epilogue).
// Guards: ctx->f8 == 0 -> return; FUN_001b7090(ctx) == 0 -> return.
// NOTE: the guard call passes the ctx POINTER (a0 is untouched at the call site, delay
// slot is a nop); passing ctx->f8 instead makes gcc load a0 = f8 and leaves a 2-word diff.
// All five case labels must be listed (3/4 empty) or ee-gcc collapses the table.
extern int FUN_001b7090(void *ctx);
extern int FUN_001b4828(int v);
extern void FUN_001b2cc8(int v);

struct Ctx {
    char pad0;
    char f1;
    signed char f2;
    int f4;
    int f8;
};

void FUN_001bb560(struct Ctx *c)
{
    if (c->f8 == 0)
        return;
    if (FUN_001b7090(c) == 0)
        return;
    switch (c->f2) {
    case 0:
    case 1:
        if (FUN_001b4828(c->f8) == 3)
            FUN_001b2cc8(c->f4);
        break;
    case 2:
        FUN_001b2cc8(c->f4);
        break;
    case 3:
        break;
    case 4:
        break;
    }
}
