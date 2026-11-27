/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205ce0, 0x30

glabel FUN_00205ce0
    /* 106CE0 00205CE0 71000324 */  addiu      $v1, $zero, 0x71
    /* 106CE4 00205CE4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106CE8 00205CE8 0800E003 */  jr         $ra
    /* 106CEC 00205CEC 00000000 */   nop
    /* 106CF0 00205CF0 8FFF0324 */  addiu      $v1, $zero, -0x71
    /* 106CF4 00205CF4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106CF8 00205CF8 0800E003 */  jr         $ra
    /* 106CFC 00205CFC 00000000 */   nop
    /* 106D00 00205D00 72000324 */  addiu      $v1, $zero, 0x72
    /* 106D04 00205D04 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106D08 00205D08 0800E003 */  jr         $ra
    /* 106D0C 00205D0C 00000000 */   nop
endlabel FUN_00205ce0
