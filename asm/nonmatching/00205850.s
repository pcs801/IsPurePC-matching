/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205850, 0x40

glabel FUN_00205850
    /* 106850 00205850 2B000324 */  addiu      $v1, $zero, 0x2B
    /* 106854 00205854 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106858 00205858 0800E003 */  jr         $ra
    /* 10685C 0020585C 00000000 */   nop
    /* 106860 00205860 D4FF0324 */  addiu      $v1, $zero, -0x2C
    /* 106864 00205864 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106868 00205868 0800E003 */  jr         $ra
    /* 10686C 0020586C 00000000 */   nop
    /* 106870 00205870 2D000324 */  addiu      $v1, $zero, 0x2D
    /* 106874 00205874 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106878 00205878 0800E003 */  jr         $ra
    /* 10687C 0020587C 00000000 */   nop
    /* 106880 00205880 D2FF0324 */  addiu      $v1, $zero, -0x2E
    /* 106884 00205884 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106888 00205888 0800E003 */  jr         $ra
    /* 10688C 0020588C 00000000 */   nop
endlabel FUN_00205850
