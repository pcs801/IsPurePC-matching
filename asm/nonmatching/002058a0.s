/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002058a0, 0x10

glabel FUN_002058a0
    /* 1068A0 002058A0 30000324 */  addiu      $v1, $zero, 0x30
    /* 1068A4 002058A4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1068A8 002058A8 0800E003 */  jr         $ra
    /* 1068AC 002058AC 00000000 */   nop
endlabel FUN_002058a0
