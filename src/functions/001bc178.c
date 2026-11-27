// SLPM 0x001BC178 slice (core 88) holds NINE tiny accessors in a row:
//   0x1BC178 p[19]=a2, p[18]=a1   0x1BC188 p[17]=a2, p[16]=a1
//   0x1BC198 p[12]=a1             0x1BC1A0 return p[12]
//   0x1BC1A8 p[13]=a1             0x1BC1B0 return p[13]
//   0x1BC1B8 p[14]=a1             0x1BC1C0 return p[14]
//   0x1BC1C8 return 0
// NOTE: the two-store setters must be written in ASCENDING field order (p[18] before p[19]).
void FUN_001bc178(int *p, int a1, int a2)
{
    p[18] = a1;
    p[19] = a2;
}

void FUN_001bc188(int *p, int a1, int a2)
{
    p[16] = a1;
    p[17] = a2;
}

void FUN_001bc198(int *p, int a1) { p[12] = a1; }
int FUN_001bc1a0(int *p) { return p[12]; }
void FUN_001bc1a8(int *p, int a1) { p[13] = a1; }
int FUN_001bc1b0(int *p) { return p[13]; }
void FUN_001bc1b8(int *p, int a1) { p[14] = a1; }
int FUN_001bc1c0(int *p) { return p[14]; }
int FUN_001bc1c8(int *p) { (void)p; return 0; }
