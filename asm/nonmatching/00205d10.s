/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205d10, 0x30

glabel FUN_00205d10
    /* 106D10 00205D10 73000324 */  addiu      $v1, $zero, 0x73
    /* 106D14 00205D14 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106D18 00205D18 0800E003 */  jr         $ra
    /* 106D1C 00205D1C 00000000 */   nop
    /* 106D20 00205D20 74000324 */  addiu      $v1, $zero, 0x74
    /* 106D24 00205D24 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106D28 00205D28 0800E003 */  jr         $ra
    /* 106D2C 00205D2C 00000000 */   nop
    /* 106D30 00205D30 75000324 */  addiu      $v1, $zero, 0x75
    /* 106D34 00205D34 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106D38 00205D38 0800E003 */  jr         $ra
    /* 106D3C 00205D3C 00000000 */   nop
endlabel FUN_00205d10
