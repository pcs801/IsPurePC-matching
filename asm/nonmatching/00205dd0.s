/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205dd0, 0x30

glabel FUN_00205dd0
    /* 106DD0 00205DD0 7C000324 */  addiu      $v1, $zero, 0x7C
    /* 106DD4 00205DD4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106DD8 00205DD8 0800E003 */  jr         $ra
    /* 106DDC 00205DDC 00000000 */   nop
    /* 106DE0 00205DE0 7D000324 */  addiu      $v1, $zero, 0x7D
    /* 106DE4 00205DE4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106DE8 00205DE8 0800E003 */  jr         $ra
    /* 106DEC 00205DEC 00000000 */   nop
    /* 106DF0 00205DF0 7E000324 */  addiu      $v1, $zero, 0x7E
    /* 106DF4 00205DF4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106DF8 00205DF8 0800E003 */  jr         $ra
    /* 106DFC 00205DFC 00000000 */   nop
endlabel FUN_00205dd0
