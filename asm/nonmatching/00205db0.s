/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205db0, 0x10

glabel FUN_00205db0
    /* 106DB0 00205DB0 7A000324 */  addiu      $v1, $zero, 0x7A
    /* 106DB4 00205DB4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106DB8 00205DB8 0800E003 */  jr         $ra
    /* 106DBC 00205DBC 00000000 */   nop
endlabel FUN_00205db0
