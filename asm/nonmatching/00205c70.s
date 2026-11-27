/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205c70, 0x40

glabel FUN_00205c70
    /* 106C70 00205C70 6B000324 */  addiu      $v1, $zero, 0x6B
    /* 106C74 00205C74 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106C78 00205C78 0800E003 */  jr         $ra
    /* 106C7C 00205C7C 00000000 */   nop
    /* 106C80 00205C80 6C000324 */  addiu      $v1, $zero, 0x6C
    /* 106C84 00205C84 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106C88 00205C88 0800E003 */  jr         $ra
    /* 106C8C 00205C8C 00000000 */   nop
    /* 106C90 00205C90 6D000324 */  addiu      $v1, $zero, 0x6D
    /* 106C94 00205C94 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106C98 00205C98 0800E003 */  jr         $ra
    /* 106C9C 00205C9C 00000000 */   nop
    /* 106CA0 00205CA0 6E000324 */  addiu      $v1, $zero, 0x6E
    /* 106CA4 00205CA4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106CA8 00205CA8 0800E003 */  jr         $ra
    /* 106CAC 00205CAC 00000000 */   nop
endlabel FUN_00205c70
