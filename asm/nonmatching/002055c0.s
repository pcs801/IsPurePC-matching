/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002055c0, 0x20

glabel FUN_002055c0
    /* 1065C0 002055C0 04000324 */  addiu      $v1, $zero, 0x4
    /* 1065C4 002055C4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1065C8 002055C8 0800E003 */  jr         $ra
    /* 1065CC 002055CC 00000000 */   nop
    /* 1065D0 002055D0 05000324 */  addiu      $v1, $zero, 0x5
    /* 1065D4 002055D4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1065D8 002055D8 0800E003 */  jr         $ra
    /* 1065DC 002055DC 00000000 */   nop
endlabel FUN_002055c0
