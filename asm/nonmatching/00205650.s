/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205650, 0x30

glabel FUN_00205650
    /* 106650 00205650 0D000324 */  addiu      $v1, $zero, 0xD
    /* 106654 00205654 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106658 00205658 0800E003 */  jr         $ra
    /* 10665C 0020565C 00000000 */   nop
    /* 106660 00205660 0E000324 */  addiu      $v1, $zero, 0xE
    /* 106664 00205664 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106668 00205668 0800E003 */  jr         $ra
    /* 10666C 0020566C 00000000 */   nop
    /* 106670 00205670 0F000324 */  addiu      $v1, $zero, 0xF
    /* 106674 00205674 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106678 00205678 0800E003 */  jr         $ra
    /* 10667C 0020567C 00000000 */   nop
endlabel FUN_00205650
