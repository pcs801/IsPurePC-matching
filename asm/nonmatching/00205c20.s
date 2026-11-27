/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205c20, 0x50

glabel FUN_00205c20
    /* 106C20 00205C20 64000324 */  addiu      $v1, $zero, 0x64
    /* 106C24 00205C24 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106C28 00205C28 0800E003 */  jr         $ra
    /* 106C2C 00205C2C 00000000 */   nop
    /* 106C30 00205C30 66000324 */  addiu      $v1, $zero, 0x66
    /* 106C34 00205C34 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106C38 00205C38 0800E003 */  jr         $ra
    /* 106C3C 00205C3C 00000000 */   nop
    /* 106C40 00205C40 99FF0324 */  addiu      $v1, $zero, -0x67
    /* 106C44 00205C44 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106C48 00205C48 0800E003 */  jr         $ra
    /* 106C4C 00205C4C 00000000 */   nop
    /* 106C50 00205C50 98FF0324 */  addiu      $v1, $zero, -0x68
    /* 106C54 00205C54 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106C58 00205C58 0800E003 */  jr         $ra
    /* 106C5C 00205C5C 00000000 */   nop
    /* 106C60 00205C60 96FF0324 */  addiu      $v1, $zero, -0x6A
    /* 106C64 00205C64 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106C68 00205C68 0800E003 */  jr         $ra
    /* 106C6C 00205C6C 00000000 */   nop
endlabel FUN_00205c20
