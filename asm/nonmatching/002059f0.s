/* asm-native: C cannot emit syscall/sync/ei/cop0/lq/sq.
   Byte-exact by construction - this is the original assembly. */
nonmatching FUN_002059f0, 0x50

glabel FUN_002059f0
    /* 1069F0 002059F0 45000324 */  addiu      $v1, $zero, 0x45
    /* 1069F4 002059F4 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1069F8 002059F8 0800E003 */  jr         $ra
    /* 1069FC 002059FC 00000000 */   nop
    /* 106A00 00205A00 BAFF0324 */  addiu      $v1, $zero, -0x46
    /* 106A04 00205A04 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106A08 00205A08 0800E003 */  jr         $ra
    /* 106A0C 00205A0C 00000000 */   nop
    /* 106A10 00205A10 47000324 */  addiu      $v1, $zero, 0x47
    /* 106A14 00205A14 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106A18 00205A18 0800E003 */  jr         $ra
    /* 106A1C 00205A1C 00000000 */   nop
    /* 106A20 00205A20 B8FF0324 */  addiu      $v1, $zero, -0x48
    /* 106A24 00205A24 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106A28 00205A28 0800E003 */  jr         $ra
    /* 106A2C 00205A2C 00000000 */   nop
    /* 106A30 00205A30 49000324 */  addiu      $v1, $zero, 0x49
    /* 106A34 00205A34 0C000000 */  syscall    0 /* handwritten instruction */
    /* 106A38 00205A38 0800E003 */  jr         $ra
    /* 106A3C 00205A3C 00000000 */   nop
endlabel FUN_002059f0
