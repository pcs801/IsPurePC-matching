/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_00205710, 0x30

glabel FUN_00205710
    /* 106710 00205710 17000324 */  addiu      $v1, $zero, 0x17
    /* 106714 00205714 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106718 00205718 0800E003 */  jr         $ra
    /* 10671C 0020571C 00000000 */   nop
    /* 106720 00205720 FC000324 */  addiu      $v1, $zero, 0xFC
    /* 106724 00205724 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106728 00205728 0800E003 */  jr         $ra
    /* 10672C 0020572C 00000000 */   nop
    /* 106730 00205730 FD000324 */  addiu      $v1, $zero, 0xFD
    /* 106734 00205734 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106738 00205738 0800E003 */  jr         $ra
    /* 10673C 0020573C 00000000 */   nop
endlabel FUN_00205710
