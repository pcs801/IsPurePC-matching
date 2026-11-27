/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_0020f600, 0x10

glabel FUN_0020f600
    /* 110600 0020F600 74000324 */  addiu      $v1, $zero, 0x74
    /* 110604 0020F604 0C000000 */  syscall    0 /* handwritten instruction */
    /* 110608 0020F608 0800E003 */  jr         $ra
    /* 11060C 0020F60C 00000000 */   nop
endlabel FUN_0020f600
