/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002059d0, 0x10

glabel FUN_002059d0
    /* 1069D0 002059D0 BDFF0324 */  addiu      $v1, $zero, -0x43
    /* 1069D4 002059D4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1069D8 002059D8 0800E003 */  jr         $ra
    /* 1069DC 002059DC 00000000 */   nop
endlabel FUN_002059d0
