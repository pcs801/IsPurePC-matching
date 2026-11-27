/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002058e0, 0x30

glabel FUN_002058e0
    /* 1068E0 002058E0 CCFF0324 */  addiu      $v1, $zero, -0x34
    /* 1068E4 002058E4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1068E8 002058E8 0800E003 */  jr         $ra
    /* 1068EC 002058EC 00000000 */   nop
    /* 1068F0 002058F0 35000324 */  addiu      $v1, $zero, 0x35
    /* 1068F4 002058F4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1068F8 002058F8 0800E003 */  jr         $ra
    /* 1068FC 002058FC 00000000 */   nop
    /* 106900 00205900 CAFF0324 */  addiu      $v1, $zero, -0x36
    /* 106904 00205904 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106908 00205908 0800E003 */  jr         $ra
    /* 10690C 0020590C 00000000 */   nop
endlabel FUN_002058e0
