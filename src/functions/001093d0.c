// FUNCTION: SLPM 0x001093D0  size 408  (best effort: 17/101 words differ)
extern char D_002585A0[];

extern void FUN_001fbb84(void *p, int v, int n);
extern void FUN_001fc2a8(void *p, void *fmt, int v);
extern int FUN_0020ac78(void *p, int flags);
extern int FUN_0020b530(int fd, void *p, int n);
extern void FUN_0020af08(int fd);

struct Tim2Hdr {
    char magic[4];
    unsigned char version;
    unsigned char format;
    unsigned short count;
    unsigned int pad0;
    unsigned int pad1;
};

struct Tim2Img {
    unsigned int totalSize;
    unsigned int clutSize;
    unsigned int imageSize;
    unsigned short headerSize;
    unsigned short clutColors;
    unsigned char imageType;
    unsigned char imageFormat;
    unsigned char zero12;
    unsigned char depth;
    unsigned short width;
    unsigned short height;
    unsigned long long tex0;
    unsigned long long tex1;
    unsigned int regs0;
    unsigned int regs1;
};

int FUN_001093d0(int id, void *data, int width, int height, int flag) {
    char path[256];
    struct Tim2Hdr hdr;
    struct Tim2Img img;
    int fd;

    FUN_001fbb84(&hdr, 0, 16);
    FUN_001fbb84(&img, 0, 0x30);
    hdr.magic[0] = 'T';
    hdr.count = 1;
    img.headerSize = 0x30;
    hdr.magic[1] = 'I';
    hdr.magic[2] = 'M';
    hdr.magic[3] = '2';
    hdr.version = 4;
    img.totalSize = width * height * 4 + 0x30;
    img.imageSize = width * height * 4;
    img.imageFormat = 1;
    img.depth = 3;
    hdr.format = 0;
    img.clutSize = 0;
    img.clutColors = 0;
    img.imageType = 0;
    img.zero12 = 0;
    img.width = width;
    img.height = height;
    img.tex0 = 0;
    img.tex1 = 0;
    img.regs0 = 0;
    img.regs1 = 0;
    FUN_001fc2a8(path, D_002585A0, id);
    if (flag == 0) {
        fd = FUN_0020ac78(path, 0x602);
    } else {
        fd = FUN_0020ac78(path, 0xA02);
        if (fd < 0)
            return 0;
    }
    FUN_0020b530(fd, &hdr, 0x10);
    FUN_0020b530(fd, &img, 0x30);
    FUN_0020b530(fd, data, width * height * 4);
    FUN_0020af08(fd);
    return 1;
}
