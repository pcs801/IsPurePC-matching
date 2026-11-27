/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002058b0, 0x10

glabel FUN_002058b0
    /* 1068B0 002058B0 CFFF0324 */  addiu      $v1, $zero, -0x31
    /* 1068B4 002058B4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1068B8 002058B8 0800E003 */  jr         $ra
    /* 1068BC 002058BC 00000000 */   nop
endlabel FUN_002058b0
