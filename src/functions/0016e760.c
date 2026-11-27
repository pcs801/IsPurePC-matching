// FUNCTION: SLPM 0x0016E760  size 88  core 84  (g=8)
// Jump-table dispatcher over idx 0..5 (table at 0x00260EA0):
//   idx 2/3 -> case body 0x16E788, idx 0/1/4/5 -> default return.
// Case body: FUN_00179db8(D_00270BF4 + 0x168E00) as a tail call.
// Note: listing all six case labels (four of them empty) is what makes ee-gcc emit
// the dense 6-entry table (sltiu idx,6 + lui/addu/lw/jr); with only "case 2: case 3:"
// it collapses to a compare/branch and the body shrinks to 68 B.
extern int D_00270BF4;
extern void FUN_00179db8(int v);

void FUN_0016e760(int x, int idx)
{
    switch (idx) {
    case 0:
        break;
    case 1:
        break;
    case 2:
    case 3:
        FUN_00179db8(D_00270BF4 + 0x168E00);
        break;
    case 4:
        break;
    case 5:
        break;
    }
}
