extern int D_00270C40;
struct FadeAccumulator { int current; int pad04; int step; };
extern struct FadeAccumulator D_456480;
void FUN_00107eb8(void) { D_456480.current = D_00270C40; D_456480.pad04 = D_456480.step = 0; }
