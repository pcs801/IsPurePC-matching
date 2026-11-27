/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205a40, 0x10

glabel FUN_00205a40
    /* 106A40 00205A40 4A000324 */  addiu      $v1, $zero, 0x4A
    /* 106A44 00205A44 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106A48 00205A48 0800E003 */  jr         $ra
    /* 106A4C 00205A4C 00000000 */   nop
endlabel FUN_00205a40
