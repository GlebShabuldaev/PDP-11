#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"


void do_halt() {
	printf("THE END !!!\n");
	exit(0);
}
void do_move() {
	printf("MOVE\n");
}
void do_add() {
	printf("ADD\n");
}
void do_nothing() {
	printf("NOTHING\n");
}

void run() {
	pc = 01000;
	while(1) {
		word w = w_read(pc);
		printf("%06o %06o\n", pc, w);
		pc += 2;
		if(w == 0){
			printf("halt ");
			do_halt();
		}
		else if((w & 0170000) == 0010000) {
			printf("mov \n");
			do_move();
		}
		else if((w & 0170000) == 0060000) {
			printf("add \n");
			do_add();
		}
		else {
			printf("unknown \n");
			do_nothing();
		}
	}
}