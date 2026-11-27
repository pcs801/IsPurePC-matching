/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205930, 0x50

glabel FUN_00205930
    /* 106930 00205930 39000324 */  addiu      $v1, $zero, 0x39
    /* 106934 00205934 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106938 00205938 0800E003 */  jr         $ra
    /* 10693C 0020593C 00000000 */   nop
    /* 106940 00205940 C6FF0324 */  addiu      $v1, $zero, -0x3A
    /* 106944 00205944 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106948 00205948 0800E003 */  jr         $ra
    /* 10694C 0020594C 00000000 */   nop
    /* 106950 00205950 3B000324 */  addiu      $v1, $zero, 0x3B
    /* 106954 00205954 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106958 00205958 0800E003 */  jr         $ra
    /* 10695C 0020595C 00000000 */   nop
    /* 106960 00205960 3C000324 */  addiu      $v1, $zero, 0x3C
    /* 106964 00205964 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106968 00205968 0800E003 */  jr         $ra
    /* 10696C 0020596C 00000000 */   nop
    /* 106970 00205970 3D000324 */  addiu      $v1, $zero, 0x3D
    /* 106974 00205974 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106978 00205978 0800E003 */  jr         $ra
    /* 10697C 0020597C 00000000 */   nop
endlabel FUN_00205930
