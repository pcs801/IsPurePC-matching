/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002056f0, 0x10

glabel FUN_002056f0
    /* 1066F0 002056F0 15000324 */  addiu      $v1, $zero, 0x15
    /* 1066F4 002056F4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1066F8 002056F8 0800E003 */  jr         $ra
    /* 1066FC 002056FC 00000000 */   nop
endlabel FUN_002056f0
