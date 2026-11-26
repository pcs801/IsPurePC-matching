extern unsigned char D_281580[];
extern int D_270C40;
extern int D_456480[3];
extern int FUN_001b7090(int);
extern void FUN_001b7da8(int, int);

int FUN_001071b0(int idx)
{
    unsigned char *base = D_281580 + idx * 0x4E280;
    int chunk[10];
    int i, j, n, per, sum, total, avg, dev, lvl, val;
    short *smp;

    if (base[3] == 0 || FUN_001b7090(*(int *)(base + 4)) != 3) {
        D_456480[0] = D_270C40;
        D_456480[2] = 0;
        return 0;
    }
    if (D_456480[0] >= D_270C40)
        return D_456480[1];
    sum = 0;
    n = *(int *)(*(int *)(base + 4) + 0x34);
    smp = *(short **)(*(int *)(base + 4) + 0x2C);
    for (i = n; i > 0; i--) {
        int v = *smp++;
        if (v < 0)
            v = -v;
        sum += v;
    }
    per = *(int *)(*(int *)(base + 4) + 0x34) / 10;
    smp = *(short **)(*(int *)(base + 4) + 0x2C);
    total = 0;
    for (i = 0; i < 10; i++) {
        chunk[i] = 0;
        if (per > 0) {
            for (j = per; j != 0; j--) {
                int v = *smp++;
                if (v < 0)
                    v = -v;
                if (chunk[i] < v)
                    chunk[i] = v;
            }
        }
        total += chunk[i];
    }
    avg = total / 10;
    dev = 0;
    for (i = 0; i < 10; i++) {
        int d = chunk[i] - avg;
        dev += d < 0 ? -d : d;
    }
    dev /= 10;
    n = sum / *(int *)(*(int *)(base + 4) + 0x34);
    lvl = 0;
    if (n >= 1000)
        lvl = n < 5000 ? 2 : 1;
    if (lvl == 0) {
        if (dev >= 301)
            lvl = 1;
    } else if (lvl == 1) {
        if (dev >= 701)
            lvl = dev / 400 % 3;
        else if (dev >= 301)
            lvl = dev / 50 % 3;
    } else {
        if (dev >= 701)
            lvl = dev / 400 % 2 + 1;
        else if (dev >= 301)
            lvl = dev / 50 % 2 + 1;
    }
    val = 1000 - dev;
    if (val < 0)
        val = 0;
    D_456480[0] = val;
    D_456480[0] = D_456480[0] / 40;
    if (D_456480[0] < 5)
        D_456480[0] = 5;
    D_456480[0] = D_456480[0] + D_270C40;
    if (D_456480[2] == 0) {
        if (lvl != 0)
            D_456480[2] = 1;
        else
            D_456480[0] = D_270C40;
    }
    D_456480[1] = lvl;
    return lvl;
}
