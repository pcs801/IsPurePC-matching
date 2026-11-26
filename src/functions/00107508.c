// FUNCTION: SLPM 0x00107508  size 168
// sig: addiu ; lui ; sd ; lui ; lw ; lui ; addiu ; sd ; ori ; addiu ; addiu ; sd
extern unsigned int D_456490[];
extern unsigned int D_456500[];
extern int D_00270A94;
extern int FUN_0010bd80(unsigned int id, void *ptr);

void FUN_00107508(void)
{
    int r;

    D_456500[1] = D_00270A94;
    D_456500[3] = 0x196000;
    D_456500[2] = 0x40;
    while ((r = FUN_0010bd80(0x90E0, D_456500)) < 0) {
        D_456490[11]++;
        do {
            r = FUN_0010bd80(0x80F0, D_456500);
        } while (r != 1);
    }
    do {
        r = FUN_0010bd80(0x80F0, D_456500);
    } while (r != 1);
}
