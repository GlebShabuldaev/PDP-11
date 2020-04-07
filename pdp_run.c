#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"

struct Argument {
	word val;		//
	word adr;		//
} ss, dd;

void print_reg() {
	printf("------------ halted -------------\n");
	printf("R0:%o R1:%o R2:%o R3:%o \nR4:%o R5:%o R6:%o R7:%o\n", reg[0], reg[1], reg[2], reg[3], reg[4], reg[5], reg[6], reg[7]);
}

void do_halt() {
	print_reg();
	exit(0);
}
void do_move(struct Argument dd, struct Argument ss) {
	//printf("dd = %o ss = %o\n", dd.adr, ss.val);
	reg[dd.adr] = ss.val;
	//mem[dd.adr] = 0;
	//w_write(dd.adr, ss.val);
}
void do_add(struct Argument dd, struct Argument ss) {
	reg[dd.adr] = ss.val + dd.val;
}
void do_nothing() {
}

struct Argument get_mr(word w) {
	struct Argument res;
	unsigned int r = w & 7;  			  //номер регистра
	unsigned int mode = (w >> 3) & 7;     //номер моды
	switch(mode) {
		case 0:		// R3
			res.adr = r;
			res.val = reg[r];
			printf("R%o ", r);
			break;
		case 1:		// (R3)
			res.adr = reg[r];
			if (r != 7 && r != 6 && sizeof(w) != 16)
				res.val = b_read(res.adr); 				
			else
				res.val = w_read(res.adr); 
			printf("(R%o) ", r);
			break;
		case 2:		// (R3)+	#3
			res.adr = reg[r];
			if (r != 7 && r != 6 && sizeof(w) != 16) {
				res.val = b_read(res.adr); 			
				reg[r] += 1;
			}
			else {
				res.val = w_read(res.adr); 
				reg[r] += 2;
				if (r == 7)
					printf("#%o ", res.val);
				else	
					printf("(R%o) ", r);
			}
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		default:
			fprintf(stderr, "Mode %o NOT IMPLEMENTED YET!\n", mode);
			exit(1);
	}
	return res;
}

void run() {
	printf("------------ running ------------\n");
	pc = 01000;
	while(1) {
		word w = w_read(pc);
		printf("%06o: %06o\n", pc, w);
		pc += 2;
		if(w == 0){
			printf("halt \n");
			do_halt();
		}
		else if((w & 0170000) == 0010000) {
			printf("mov ");
			ss = get_mr(w >> 6);
			dd = get_mr(w);
			do_move(dd, ss);
			printf("\n");
		}
		else if((w & 0170000) == 0060000) {
			printf("add ");
			ss = get_mr(w >> 6);
			dd = get_mr(w);
			do_add(dd, ss);
			printf("\n");
		}
		else {
			printf("unknown ");
			do_nothing();
		}
	}
}