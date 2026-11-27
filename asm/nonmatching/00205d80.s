/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205d80, 0x10

glabel FUN_00205d80
    /* 106D80 00205D80 78000324 */  addiu      $v1, $zero, 0x78
    /* 106D84 00205D84 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106D88 00205D88 0800E003 */  jr         $ra
    /* 106D8C 00205D8C 00000000 */   nop
endlabel FUN_00205d80
