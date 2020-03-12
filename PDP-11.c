#include <stdio.h>
#include <assert.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void test_mem() {
	byte b0 = 0x0a;
	b_write(2, b0);
	byte bres = b_read(2);
	assert(b0 == bres);
	Adress a = 4;
	byte b1 = 0x0b;
	b0 = 0x0a;
	word w = 0x0b0a;
	b_write(a, b0);
	b_write(a+1, b1);
	word wres = w_read(a);
	assert(w == wres);
	w_write(a, w);
}

int main(int argc, char * argv[]) {
	test_mem();
	printf("%s", argv[argc]);
	return 0; 
}

void b_write(Adress adr, byte b) { 
	mem[adr] = b;
}

byte b_read(Adress adr) {
	return mem[adr];
}

void w_write(Adress adr, word w){
	mem[adr] = w;
	mem[adr + 1] = w >> 8;
}

word w_read(Adress adr){
	word w = ((word)mem[adr+1]) << 8;
	w = w | mem[adr];
	return w;
}
