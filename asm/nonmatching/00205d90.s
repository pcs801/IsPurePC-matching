/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205d90, 0x10

glabel FUN_00205d90
    /* 106D90 00205D90 88FF0324 */  addiu      $v1, $zero, -0x78
    /* 106D94 00205D94 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106D98 00205D98 0800E003 */  jr         $ra
    /* 106D9C 00205D9C 00000000 */   nop
endlabel FUN_00205d90
