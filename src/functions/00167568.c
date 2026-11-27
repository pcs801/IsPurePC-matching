// FUNCTION: SLPM 0x00167568  size 1872  core 1872  (cumulative draft: skeleton + case idx0 + case idx6/7)
extern int D_00270BF4;
extern char D_00217C30[];
extern char D_00218858[];
extern char D_00260D78[];
extern char D_002705E8[];
extern char D_002705F0[];
extern char D_002705F8[];
extern int FUN_001fc4c0(void *, int);
extern int FUN_001a78f8(int, void *, int);

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
    char *fmt;
    char *dst;
    int n;
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
            int type;

            type = *(int *)(ent + j * 16);
            switch (type) {
            case 0:
                /* 0x1676D0-0x1677F4 */
                *(char *)tag = *(unsigned char *)(hi2 + 0x5D8);
                fmt = *(char **)(D_00217C30 + i * 20 + 4);
                dst = (char *)tag;
                n = 0;
                while (*fmt != 0) {
                    if (*fmt == '%' && fmt[1] == 'N') {
                        *dst++ = *(char *)tag;
                        fmt += 2;
                    } else {
                        *dst++ = *fmt++;
                    }
                    n++;
                    if (n >= j + 1)
                        break;
                }
                *dst = 0;
                FUN_001fc4c0(blk + 0x42BCC, (int)D_002705E8);
                FUN_001fc4c0(blk + 0x42BCC, (int)tag);
                FUN_001a78f8(*(int *)(*(int *)(D_00218858 + i * 28 + 8) + 0x42CCD + 4),
                             (void *)tag, (int)D_002705F0);
                break;
            case 1:
            case 2:
                /* 0x1678F8-0x1679F4: guarded by *(int*)(0x218858+i*28) == j; single
                 * append of the expanded tag string, then the entry loop continues at 0x167B40. */
                if (*(int *)(D_00218858 + i * 28) != j)
                    break;
                *(char *)tag = *(unsigned char *)(hi2 + 0x5D8);
                fmt = *(char **)(D_00217C30 + i * 20 + 4);
                dst = (char *)tag;
                n = 0;
                while (*fmt != 0) {
                    if (*fmt == '%' && fmt[1] == 'N') {
                        *dst++ = *(char *)tag;
                        fmt += 2;
                    } else {
                        *dst++ = *fmt++;
                    }
                    n++;
                    if (n >= j + 1)
                        break;
                }
                *dst = 0;
                FUN_001fc4c0(blk + 0x42BCC, (int)tag);
                break;
            case 6:
            case 7:
                /* 0x1677F8-0x1678F4: same expansion, three appends (0x260D78, tag, 0x2705F8) */
                *(char *)tag = *(unsigned char *)(hi2 + 0x5D8);
                fmt = *(char **)(D_00217C30 + i * 20 + 4);
                dst = (char *)tag;
                n = 0;
                while (*fmt != 0) {
                    if (*fmt == '%' && fmt[1] == 'N') {
                        *dst++ = *(char *)tag;
                        fmt += 2;
                    } else {
                        *dst++ = *fmt++;
                    }
                    n++;
                    if (n >= j + 1)
                        break;
                }
                *dst = 0;
                FUN_001fc4c0(blk + 0x42BCC, (int)D_00260D78);
                FUN_001fc4c0(blk + 0x42BCC, (int)tag);
                FUN_001fc4c0(blk + 0x42BCC, (int)D_002705F8);
                FUN_001a78f8(*(int *)(*(int *)(D_00218858 + i * 28 + 8) + 0x42CCD + 4),
                             (void *)tag, (int)D_002705F0);
                break;
            }
        }
    }
}