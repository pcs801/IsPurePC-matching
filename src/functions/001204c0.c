extern void *D_00270CB0;

void FUN_001204c0(int mode)
{
    int i;

    for (i = 0; i <= 0; i++) {
        char *s = (char *)D_00270CB0 + i * 0x5FF8;
        char *e;
        int n, j;

        if (*(signed char *)(s + 0x18) != 1)
            continue;
        n = *(int *)(s + 0x7C);
        if (n <= 0)
            continue;
        for (j = 0, e = s + 0xAC; j < n; j++, e += 0x34) {
            int kind = *(int *)(e + 0x18);
            int v;

            if (kind == 0)
                continue;
            v = *(int *)(e);
            if (v > 0) {
                *(int *)(e) = 0;
                if (mode)
                    v = 0;
                else {
                    v = v - 1;
                    *(int *)(e) = v;
                }
            }
            if (v != 0)
                continue;
            if (*(int *)(e + 4) != 0) {
                if (mode)
                    *(int *)(e + 8) = 0;
                else {
                    v = *(int *)(e + 8) - *(int *)(e + 0xC);
                    if (v <= 0)
                        v = 0;
                    *(int *)(e + 8) = v;
                }
            } else {
                if (mode)
                    *(int *)(e + 8) = 0x80;
                else {
                    v = *(int *)(e + 8) + *(int *)(e + 0xC);
                    if (v >= 0x80)
                        v = 0x80;
                    *(int *)(e + 8) = v;
                }
            }
            switch (kind) {
            case 0:
            case 1:
            case 2:
            case 3:
                break;
            case 4:
            case 5:
                *(int *)(e + 0x1C) = *(int *)(e + 0x1C) + 1;
                break;
            case 6:
            case 7:
                v = *(int *)(e + 0x1C);
                if (v < 0x40)
                    *(int *)(e + 0x1C) = v + 1;
                break;
            case 8:
                break;
            }
        }
    }
}
