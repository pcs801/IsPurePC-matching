// FUNCTION: SLPM 0x00101960  size 160  core 160
// sig: addiu ; addiu ; sd ; sd ; sd ; bne ; sd ; daddu ; b ; addiu ; addiu ; daddu
// verified byte-exact (matched by TU worker, attempt 6 on this structure)

extern char D_1B75484[];

void FUN_00101960(int idx)
{
    int end;
    int i;

    if (idx == -1) {
        idx = 0;
        end = 10;
    } else {
        end = idx + 1;
    }

    for (i = idx; i < end; i++) {
        char *p = D_1B75484 + i * 0x16C;
        if (*(int *)(p + 0x10C) != 0) {
            int r = ((int (*)(char *))*(void **)(p + 0x10C))(p + 0x10C);
            *(short *)(p + 0x11E) = r;
            if ((short)r != 0) {
                *(int *)(p + 0x10C) = 0;
            }
        }
    }
}
