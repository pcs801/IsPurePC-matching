// 1-instruction arg shuffle: ROM moves a2->v0, a3->v1, t0->t3, t1->t2 BEFORE the frame,
// then a2=a1, a3=v0, t0=v1, t1=t3, a1=1, then jal.
// ee-gcc reproduces the same 60-byte length but orders the frame first and uses different
// temps (v0/v1/t2), so 14 words remain. Void call form keeps it a jal (no sibcall).

extern void FUN_00208b00(int a0, int a1, int a2, int a3, int a4, int a5, int a6);

void FUN_00208c78(int a0, int a1, int a2, int a3, int a4, int a5)
{
    FUN_00208b00(a0, 1, a1, a2, a3, a4, a5);
}
