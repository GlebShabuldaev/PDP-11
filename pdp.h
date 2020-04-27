#define pc reg[7]
#define MEMSIZE (64*1024)

#define NO_PARAMS 0
#define HAS_SS 2
#define HAS_DD 1
#define HAS_NN 4
#define HAS_R 8
#define HAS_XX 16

typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;
extern int N, Z, C;


struct Argument {
	word val;		//
	word adr;		//
};


typedef struct {
	word mask;
	word opcode;
	char * name;
	void (*do_func) (struct Argument dd, struct Argument ss, unsigned int nn, unsigned int r, unsigned int xx);
	char params;
} Command;


word reg[8];
byte mem[MEMSIZE];


void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);
void load_file();
void mem_dump(Adress adr, word w);
void do_halt();
void do_mov();
void do_add();
void do_inc();
void do_incb();
void do_add();
void do_movb();
void print_reg();
void do_sub();
void do_clr();