// FUNCTION: SLPM 0x001BE5A8  size 136  core 132  (MISS 128/132, 16 词)
// 唯一结构性差：ROM 的 jal FUN_001be578 延迟槽是 nop、p=&D_00230568 落在 w19，
// 我们被调度器提前填进延迟槽（少 1 词，后续全体左移 1）。
// 已试 p 赋值放块首/块尾两种顺序，都是 128 → 判延迟槽填充墙。
extern char D_00230568[];
extern int D_002305C8;
extern void FUN_001cae38(void);
extern void FUN_001be578(void);
extern void FUN_001caeb0(void);

char *FUN_001be5a8(void)
{
    char *p = 0;

    FUN_001cae38();
    if (D_00230568[0] == 0) {
        FUN_001be578();
        D_00230568[0] = 1;
        D_00230568[2] = 0;
        D_00230568[3] = -1;
        *(int *)(D_00230568 + 4) = 0;
        D_002305C8 = D_002305C8 + 1;
        p = D_00230568;
    }
    FUN_001caeb0();
    return p;
}
