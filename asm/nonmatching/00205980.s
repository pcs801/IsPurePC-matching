/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205980, 0x20

glabel FUN_00205980
    /* 106980 00205980 3E000324 */  addiu      $v1, $zero, 0x3E
    /* 106984 00205984 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106988 00205988 0800E003 */  jr         $ra
    /* 10698C 0020598C 00000000 */   nop
    /* 106990 00205990 3F000324 */  addiu      $v1, $zero, 0x3F
    /* 106994 00205994 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106998 00205998 0800E003 */  jr         $ra
    /* 10699C 0020599C 00000000 */   nop
endlabel FUN_00205980
