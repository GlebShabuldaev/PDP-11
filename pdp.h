#define pc reg[7]
#define MEMSIZE (64*1024)

typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;
typedef struct {
	word mask;
	word opcode;
	char * name;
	void (*do_func) (void);
	char params;
} Command;

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);
void load_file();
void mem_dump(Adress adr, word w);
void do_halt();
void do_move();
void do_add();
void do_nothing();

word reg[8];
byte mem[MEMSIZE];
/*Command cmd[] = {
	{0170000, 0010000, "mov", do_move},
	{0170000, 0060000, "add", do_add},
	{0170000, 0010000, "halt", do_halt},//
//	{0170000, 0010000, "nothing", do_nothing},
};*/
/*
for(int i; cmd[i][]; i++); //найти программу
*/
