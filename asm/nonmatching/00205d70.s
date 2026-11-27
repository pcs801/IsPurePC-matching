/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205d70, 0x10

glabel FUN_00205d70
    /* 106D70 00205D70 89FF0324 */  addiu      $v1, $zero, -0x77
    /* 106D74 00205D74 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106D78 00205D78 0800E003 */  jr         $ra
    /* 106D7C 00205D7C 00000000 */   nop
endlabel FUN_00205d70
