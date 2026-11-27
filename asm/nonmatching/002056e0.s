/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002056e0, 0x10

glabel FUN_002056e0
    /* 1066E0 002056E0 14000324 */  addiu      $v1, $zero, 0x14
    /* 1066E4 002056E4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1066E8 002056E8 0800E003 */  jr         $ra
    /* 1066EC 002056EC 00000000 */   nop
endlabel FUN_002056e0
