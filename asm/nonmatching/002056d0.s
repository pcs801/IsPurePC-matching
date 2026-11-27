/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002056d0, 0x10

glabel FUN_002056d0
    /* 1066D0 002056D0 13000324 */  addiu      $v1, $zero, 0x13
    /* 1066D4 002056D4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1066D8 002056D8 0800E003 */  jr         $ra
    /* 1066DC 002056DC 00000000 */   nop
endlabel FUN_002056d0
