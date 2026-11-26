extern void FUN_001e9090(int, int, int, int);

struct Conf {
    int pad;
    int a;
    short b;
    short c;
    int d;
    int e;
    int pad14[3];
};

void FUN_00106268(void)
{
    struct Conf s[2];

    FUN_001e9090(1, 0x8010, 0x980, 0);
    FUN_001e9090(1, 0x8010, 0xA80, 0);
    FUN_001e9090(1, 0x8010, 0x981, 0);
    FUN_001e9090(1, 0x8010, 0xA81, 0);
    FUN_001e9090(1, 0x8010, 0xB80, 0);
    FUN_001e9090(1, 0x8010, 0xC80, 0);
    FUN_001e9090(1, 0x8010, 0xB81, 0);
    FUN_001e9090(1, 0x8010, 0xC81, 0);
    FUN_001e9090(1, 0x8050, 0x1D00, 0x1DFFFF);
    FUN_001e9090(1, 0x8050, 0x1D01, 0x1FFFFF);

    s[0].b = 0x2C;
    s[0].c = 0x2C;
    s[0].a = 4;
    s[0].d = 0x23;
    s[0].e = 0x2D;
    s[1].b = 0x32;
    s[1].c = 0x32;
    s[1].d = 0x32;
    s[1].e = 0x32;
    s[1].a = 8;

    FUN_001e9090(1, 0x8130, 0, (int)s);
    FUN_001e9090(1, 0x8150, 0, 0);
    FUN_001e9090(1, 0x8130, 1, (int)(s + 1));
    FUN_001e9090(1, 0x8150, 1, 0);
    FUN_001e9090(1, 0x8070, 2, 1);
    FUN_001e9090(1, 0x8070, 3, 1);
    FUN_001e9090(1, 0x8010, 0x800, 0xFC0);
    FUN_001e9090(1, 0x8010, 0x801, 0xFCC);
    FUN_001e9090(1, 0x8010, 0x980, 0x3FFF);
    FUN_001e9090(1, 0x8010, 0xA80, 0x3FFF);
    FUN_001e9090(1, 0x8010, 0x981, 0x3FFF);
    FUN_001e9090(1, 0x8010, 0xA81, 0x3FFF);
    FUN_001e9090(1, 0x8010, 0xB80, 0x3FFF);
    FUN_001e9090(1, 0x8010, 0xC80, 0x3FFF);
    FUN_001e9090(1, 0x8010, 0xB81, 0x3FFF);
    FUN_001e9090(1, 0x8010, 0xC81, 0x3FFF);
}
