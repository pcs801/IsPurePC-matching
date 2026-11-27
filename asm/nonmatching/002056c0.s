/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002056c0, 0x10

glabel FUN_002056c0
    /* 1066C0 002056C0 12000324 */  addiu      $v1, $zero, 0x12
    /* 1066C4 002056C4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1066C8 002056C8 0800E003 */  jr         $ra
    /* 1066CC 002056CC 00000000 */   nop
endlabel FUN_002056c0
