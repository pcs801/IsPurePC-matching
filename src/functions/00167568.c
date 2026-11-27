// FUNCTION: SLPM 0x00167568  size 1872  core 1872  (skeleton block 1: 0x167568-0x1676D0)
// hi1/hi2 model the target's $s7=0x220000 and $fp=0x270000 base constants.
extern int D_00270BF4;
extern char D_00217C30[];
extern char D_00218858[];
extern int FUN_001fc4c0(void *, int);

void FUN_00167568(void)
{
    int b;
    int i;
    int j;
    int cnt;
    int ent;
    int hi1;
    int hi2;
    char *blk;
    int tag[2];

    hi1 = 0x220000;
    hi2 = 0x270000;
    tag[0] = 0;
    for (i = 0; i < 0x26; i++) {
        b = D_00270BF4;
        blk = (char *)(b + i * 0x202);
        *(int *)(b + i * 0x20 + 0x47818) = (int)(blk + 0x42BCC);
        *(int *)(b + i * 0x20 + 0x47828) = (int)(blk + 0x42CCD);
        blk[0x42BCC] = *(char *)(hi2 + 0x5E0);
        blk[0x42BCD] = *(char *)(hi2 + 0x5E1);
        blk[0x42BCE] = *(char *)(hi2 + 0x5E2);
        FUN_001fc4c0(blk + 0x42BCC, *(int *)(D_00217C30 + i * 20));
        blk[0x42CCD] = *(unsigned char *)(hi2 + 0x5D8);
        cnt = *(int *)(D_00218858 + i * 28 + 4);
        ent = *(int *)(D_00218858 + i * 28 + 8);
        tag[1] = 0;
        for (j = 0; j < cnt; j++) {
        }
    }
}
