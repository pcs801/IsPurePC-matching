/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_0020f860, 0x10

glabel FUN_0020f860
    /* 110860 0020F860 74000324 */  addiu      $v1, $zero, 0x74
    /* 110864 0020F864 0C000000 */  syscall    0 /* handwritten instruction */
    /* 110868 0020F868 0800E003 */  jr         $ra
    /* 11086C 0020F86C 00000000 */   nop
endlabel FUN_0020f860
