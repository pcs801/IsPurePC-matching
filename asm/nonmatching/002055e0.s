/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002055e0, 0x10

glabel FUN_002055e0
    /* 1065E0 002055E0 06000324 */  addiu      $v1, $zero, 0x6
    /* 1065E4 002055E4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1065E8 002055E8 0800E003 */  jr         $ra
    /* 1065EC 002055EC 00000000 */   nop
endlabel FUN_002055e0
