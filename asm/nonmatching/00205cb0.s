/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205cb0, 0x10

glabel FUN_00205cb0
    /* 106CB0 00205CB0 6F000324 */  addiu      $v1, $zero, 0x6F
    /* 106CB4 00205CB4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106CB8 00205CB8 0800E003 */  jr         $ra
    /* 106CBC 00205CBC 00000000 */   nop
endlabel FUN_00205cb0
