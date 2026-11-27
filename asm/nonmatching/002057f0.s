/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002057f0, 0x40

glabel FUN_002057f0
    /* 1067F0 002057F0 25000324 */  addiu      $v1, $zero, 0x25
    /* 1067F4 002057F4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1067F8 002057F8 0800E003 */  jr         $ra
    /* 1067FC 002057FC 00000000 */   nop
    /* 106800 00205800 DAFF0324 */  addiu      $v1, $zero, -0x26
    /* 106804 00205804 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106808 00205808 0800E003 */  jr         $ra
    /* 10680C 0020580C 00000000 */   nop
    /* 106810 00205810 27000324 */  addiu      $v1, $zero, 0x27
    /* 106814 00205814 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106818 00205818 0800E003 */  jr         $ra
    /* 10681C 0020581C 00000000 */   nop
    /* 106820 00205820 28000324 */  addiu      $v1, $zero, 0x28
    /* 106824 00205824 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106828 00205828 0800E003 */  jr         $ra
    /* 10682C 0020582C 00000000 */   nop
endlabel FUN_002057f0
