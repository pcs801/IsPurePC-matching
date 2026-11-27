/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00211738, 0x10

glabel FUN_00211738
    /* 112738 00211738 74000324 */  addiu      $v1, $zero, 0x74
    /* 11273C 0021173C 0C000000 */  syscall    0 /* handwritten instruction */
    /* 112740 00211740 0800E003 */  jr         $ra
    /* 112744 00211744 00000000 */   nop
endlabel FUN_00211738
