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
void load_file();

void test_mem() {
	byte b0 = 0x0a;
	b_write(2, b0);
	byte bres = b_read(2);
	assert(b0 == bres);
	Adress a = 4;
	byte b1 = 0xcb;
	b0 = 0x0a;
	word w = 0xcb0a;
	b_write(a, b0);
	b_write(a+1, b1);
	word wres = w_read(a);
	assert(w == wres);
	w = 0x0a0b;
	w_write(a, w);
	wres = w_read(a);
	assert(w == wres);
}

int main(int argc, char * argv[]) {
	test_mem();
	load_file();
	return 0; 
}

void b_write(Adress adr, byte b) { 
	mem[adr] = b;
}

byte b_read(Adress adr) {
	return mem[adr];
}

void w_write(Adress adr, word w) {
	mem[adr] = w;
	mem[adr + 1] = w >> 8;
}

word w_read(Adress adr) {
	word w = ((word)mem[adr+1]) << 8;
	w = w | mem[adr];
	return w;
}

void load_file() {
	unsigned int adr_1;
	unsigned int N;
	while(scanf("%x%x", &adr_1, &N) == 2) {
		for(unsigned i = 0; i < N; i++) {
			unsigned int k;
			scanf("%x", &k);
			b_write(adr_1 + i, k);
			printf("%x\n", b_read(adr_1 + i));
		}
	}
}


/*
void load_file(int argc, char  * argv[]) {
	FILE * fin =  fopen(argv[1], "r");
	int adr_1;
	char N;
	scanf("%d %hhx", &adr_1, &N);
	for(unsigned i = 0; i < N; i++) {
		byte k;
		scanf("%hhx", &k);
		b_write(adr_1 + i, k);
	}
}
*/