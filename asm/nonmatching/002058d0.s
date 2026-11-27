/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002058d0, 0x10

glabel FUN_002058d0
    /* 1068D0 002058D0 33000324 */  addiu      $v1, $zero, 0x33
    /* 1068D4 002058D4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1068D8 002058D8 0800E003 */  jr         $ra
    /* 1068DC 002058DC 00000000 */   nop
endlabel FUN_002058d0
