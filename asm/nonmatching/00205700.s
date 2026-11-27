/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205700, 0x10

glabel FUN_00205700
    /* 106700 00205700 16000324 */  addiu      $v1, $zero, 0x16
    /* 106704 00205704 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106708 00205708 0800E003 */  jr         $ra
    /* 10670C 0020570C 00000000 */   nop
endlabel FUN_00205700
