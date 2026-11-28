// FUNCTION: SLPM 0x0012B490  size 128  core 124  (MISS 124/124 长度对，4 词)
// 唯一差：两条"总是执行"的调度位序 —— ROM 把 ld s0 放 beq 延迟槽、daddu v0,zero 放 b 延迟槽
// （尾部也是先 ld s0 后 v0=0），我们正好对调。已试 4 种写法（嵌套 if / 局部 short v / 提前合并
// 判定 / 单 else-if）+ ee29（更差 120/124、28 词，已撤 override）→ 判调度墙。
extern void FUN_0012ad30(void);
extern void FUN_00128b78(void);
extern void FUN_00128c50(void);
extern void FUN_00128f00(void);
extern void FUN_0012b340(void);
extern void FUN_0012a1c0(void);

int FUN_0012b490(short *p)
{
    if (p[8] != 0) {
        if (p[8] != 1)
            return 0;
    } else {
        FUN_0012ad30();
        p[8] = 1;
    }
    FUN_00128b78();
    FUN_00128c50();
    FUN_00128f00();
    FUN_0012b340();
    FUN_0012a1c0();
    return 0;
}
