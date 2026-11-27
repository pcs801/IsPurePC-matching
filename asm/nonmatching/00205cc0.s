/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205cc0, 0x20

glabel FUN_00205cc0
    /* 106CC0 00205CC0 70000324 */  addiu      $v1, $zero, 0x70
    /* 106CC4 00205CC4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106CC8 00205CC8 0800E003 */  jr         $ra
    /* 106CCC 00205CCC 00000000 */   nop
    /* 106CD0 00205CD0 90FF0324 */  addiu      $v1, $zero, -0x70
    /* 106CD4 00205CD4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106CD8 00205CD8 0800E003 */  jr         $ra
    /* 106CDC 00205CDC 00000000 */   nop
endlabel FUN_00205cc0
