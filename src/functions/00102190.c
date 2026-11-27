// FUNCTION: SLPM 0x00102190  size 208  core 208
// GsState raster/alpha block initialiser: 39 byte stores + one short store into
// D_A94700+0x4690..0x46B6 / 0x46CA. The emitted store order is scheduler output; the
// source order below is the one that reproduces it byte-for-byte (found by a
// store-order search against the target word stream).
extern char D_A94700[];

void FUN_00102190(void)
{
    char *p = D_A94700;

    *(char *)(p + 0x469B) = 96;
    *(char *)(p + 0x4693) = -128;
    *(char *)(p + 0x4692) = 45;
    *(char *)(p + 0x4691) = 30;
    *(char *)(p + 0x46AD) = -128;
    *(char *)(p + 0x4695) = 45;
    *(char *)(p + 0x4694) = 45;
    *(char *)(p + 0x4690) = 0;
    *(char *)(p + 0x4696) = 0;
    *(char *)(p + 0x4697) = 0;
    *(char *)(p + 0x4698) = 0;
    *(char *)(p + 0x4699) = 0;
    *(char *)(p + 0x469A) = 0;
    *(char *)(p + 0x46B4) = 45;
    *(char *)(p + 0x469C) = 2;
    *(char *)(p + 0x46B2) = 0;
    *(char *)(p + 0x46B5) = 0;
    *(char *)(p + 0x46B6) = 0;
    *(char *)(p + 0x46A5) = 0;
    *(char *)(p + 0x46B3) = 0;
    *(char *)(p + 0x46A1) = 2;
    *(char *)(p + 0x46A2) = 3;
    *(char *)(p + 0x46AB) = 3;
    *(char *)(p + 0x46AC) = 1;
    *(char *)(p + 0x46AF) = 7;
    *(char *)(p + 0x46A3) = 7;
    *(char *)(p + 0x46A4) = 1;
    *(char *)(p + 0x46B0) = 1;
    *(char *)(p + 0x46A7) = 0;
    *(char *)(p + 0x46A8) = 0;
    *(char *)(p + 0x46A9) = 0;
    *(char *)(p + 0x46AA) = 1;
    *(char *)(p + 0x46A6) = 0;
    *(char *)(p + 0x469D) = 30;
    *(char *)(p + 0x469F) = 0;
    *(char *)(p + 0x469E) = 28;
    *(char *)(p + 0x46B1) = 1;
    *(char *)(p + 0x46A0) = 0;
    *(short *)(p + 0x46CA) = -1;
}
