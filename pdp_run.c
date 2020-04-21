#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"


struct Argument get_mr(word w1, word w) {
	struct Argument res;
	unsigned int r = w1 & 7;  			  //номер регистра
	unsigned int mode = (w1 >> 3) & 7;     //номер моды
	int x;
	switch(mode) {
		case 0:		// R3
			res.adr = r; //dd.adr = 1
			res.val = reg[r]; //dd.val = 
			printf("R%o ", r);
			break;
		case 1:		// (R3)
			res.adr = reg[r];
			if (w >> 15 == 0 || r == 7 || r == 6)
				res.val = w_read(res.adr); 				
			else
				res.val = b_read(res.adr); 
			printf("(R%o) ", r);
			break;
		case 2:		// (R3)+	#3
			res.adr = reg[r];  //ss.adr = 001006
			if (w >> 15 == 0 || r == 7 || r == 6) {
				res.val = w_read(res.adr); 			
				reg[r] += 2;
				if (r == 7)
					printf("#%o ", res.val);
				else	
					printf("(R%o) ", r);
			}
			else {
				res.val = b_read(res.adr); 	//ss.val = 3
				reg[r] += 1;
				printf("(R%o)b ", r);
			}
			break;
		case 3:
			res.adr = w_read(reg[r]);
			res.val = w_read(res.adr);
			reg[r] += 2; 
			if (r == 7)
				printf("@#%o ", reg[r] - 2);
			else
				printf("@(R%o)+ ", r);
			break;
		case 4:
			if (w >> 15 == 0 || r == 6 || r == 7) {
				reg[r] -= 2;
				res.adr = reg[r];
				res.val = w_read(res.adr);
			}
			else {
				reg[r] -= 1;
				res.adr = reg[r];
				res.val = b_read(res.adr);
			}
			printf("-(R%o) ", r);
			break;
		case 5:
			reg[r] -= 2;
			res.adr = w_read(reg[r]);
			res.val = w_read(res.adr);
			printf("@-(R%o) ", r);
			break;
		case 6:
			x = w_read(pc);
			pc += 2;
			res.adr = reg[r] + x;
			res.val = w_read(res.adr);
			if (r == 7)
				printf("%o ", res.adr);
			else
				printf("%o(R%o) ", x, r); 
		case 7:
			x = w_read(pc);
			pc += 2;
			res.adr = reg[r] + x;
			res.adr = w_read(res.adr);
			res.val = w_read(res.adr);
			if (r == 7)
				printf("@%o ", res.adr);
			else
				printf("@%o(R%o) ", x, r);
			break;
	}
	return res;
}


extern Command cmd[];


void run() {
	printf("------------ running ------------\n");
	pc = 01000;
	struct Argument ss, dd;
	unsigned int nn, r;
	while(1) {
		word w = w_read(pc);
		printf("%06o: %06o\n", pc, w);
		pc += 2;
		for (int i = 0; i < 8; i++) {
			if ((w & cmd[i].mask) == cmd[i].opcode){
				printf("%s ", cmd[i].name);
				if (cmd[i].params & HAS_SS)
					ss = get_mr(w >> 6, w);
				if (cmd[i].params & HAS_DD)
					dd = get_mr(w, w);
				if (cmd[i].params & HAS_R){
					r = (w >> 6) & 1;
					printf("R%o ", reg[r]);
				}
				if (cmd[i].params & HAS_NN) {
					nn = (w & 077) << 1;
					printf("LOOP ");
				}
				cmd[i].do_func(dd, ss, nn, r);
				printf("\n");
				print_reg();
				break;
			}
			if (i == 7) 
				printf("nothing");
		}
	}
}