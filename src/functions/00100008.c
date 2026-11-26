// FUNCTION: SLPM 0x00100008  (ELF entry / crt0 region, size 1104)
// 说明：该地址段不是编译器生成的函数体，而是手写启动代码：
//   32 x padduw GPR 清零、mthi/mtlo/mtsah、mtc1 $zero,$f0-$f31、adda.s、sync.p、
//   ctc1 $zero,$31、两段对齐 memset 循环、syscall 0x3C/0x3D、FlushCache、
//   以及 0x00100258 起的另一个正常函数（帧 0x60）。
// 这些指令（padduw/mthi/mtc1/sync.p/ctc1/syscall/ei）无法由普通 C 生成，
// 因此本函数在纯 C 约束下不可能字节匹配；此处保留最小占位实现。
void FUN_00100008(void)
{
}
