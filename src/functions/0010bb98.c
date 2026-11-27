// FUNCTION: SLPM 0x0010BB98
extern int FUN_002059a0(void *);
extern int FUN_00205890(void);
extern int FUN_00205830(int, int);
extern int FUN_002057a0(void *);
extern int FUN_00206ae0(int, int);
extern int FUN_001f47d0(void *, int);
extern int FUN_0010bc40(int);
extern void FUN_0010bcd8(int);
extern char D_479100[];
extern char D_2779F0[];

typedef struct {
    int status;
    int func;
    int stack;
    int stack_size;
    int gp;
    int priority;
    int pad[6];
    int sema_size;
    int sema_init;
    int sema_max;
    int sema_3c;
    int sema_40;
    int sema_attr;
    int pad2[2];
} FRAME;

void FUN_0010bb98(void)
{
    FRAME f;
    int sem;
    int h;

    f.sema_init = 1;
    f.sema_max = 0;
    f.sema_attr = 0;
    sem = FUN_002059a0(&f.sema_size);
    FUN_00205830(FUN_00205890(), 2);
    f.stack_size = 0x2000;
    f.func = (int)FUN_0010bc40;
    f.stack = (int)D_479100;
    f.gp = (int)D_2779F0;
    f.priority = 1;
    h = FUN_002057a0(&f);
    FUN_00206ae0(h, sem);
    FUN_001f47d0((void *)FUN_0010bcd8, sem);
}
