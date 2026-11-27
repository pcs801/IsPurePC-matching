// FUNCTION: SLPM 0x002082C0  size 40  (MISS 40/40, 1 word)
// ROM: addiu sp ; daddu a0,a2 ; beq a0,zero,L ; sd ra ; jal FUN_00207200 ; ...
// ee-gcc branches on a2 directly (`beq a2,zero`) instead of testing the copied a0.

extern int FUN_00207200(int a0);

int FUN_002082c0(int a0, int a1, int a2)
{
    int t;

    t = a2;
    if (t != 0) {
        do {
            FUN_00207200(t);
        } while (0);
    }
    return 1;
}
