/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205da0, 0x10

glabel FUN_00205da0
    /* 106DA0 00205DA0 79000324 */  addiu      $v1, $zero, 0x79
    /* 106DA4 00205DA4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106DA8 00205DA8 0800E003 */  jr         $ra
    /* 106DAC 00205DAC 00000000 */   nop
endlabel FUN_00205da0
