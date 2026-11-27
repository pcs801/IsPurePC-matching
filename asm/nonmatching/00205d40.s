/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205d40, 0x20

glabel FUN_00205d40
    /* 106D40 00205D40 76000324 */  addiu      $v1, $zero, 0x76
    /* 106D44 00205D44 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106D48 00205D48 0800E003 */  jr         $ra
    /* 106D4C 00205D4C 00000000 */   nop
    /* 106D50 00205D50 8AFF0324 */  addiu      $v1, $zero, -0x76
    /* 106D54 00205D54 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106D58 00205D58 0800E003 */  jr         $ra
    /* 106D5C 00205D5C 00000000 */   nop
endlabel FUN_00205d40
