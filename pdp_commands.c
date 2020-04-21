#include <stdio.h>
#include "pdp.h"
#include <stdlib.h>



void do_mov(struct Argument dd, struct Argument ss, unsigned int nn, unsigned int r) {
	if (dd.adr < 8)
		reg[dd.adr] = ss.val;
	else
		w_write(dd.adr, ss.val);
};


void do_movb(struct Argument dd, struct Argument ss, unsigned int nn, unsigned int r) {
	if (dd.adr < 8){
		if (ss.val >> 7 == 1){
			reg[dd.adr] = 0xFF00 | ss.val;
		}
		else
			reg[dd.adr] = 0x0000 | ss.val;
	}
	else
		b_write(dd.adr, ss.val);
};


void do_add(struct Argument dd, struct Argument ss, unsigned int nn, unsigned int r) {
	if (dd.adr < 8 && ss.adr < 8)
		reg[dd.adr] = reg[dd.adr] + reg[ss.adr];
	else
		w_write(dd.adr, w_read(dd.adr) + w_read(ss.adr));
};


void print_reg() {
	printf("R0:%o R1:%o R2:%o R3:%o \nR4:%o R5:%o R6:%o R7:%o\n", reg[0], reg[1], reg[2], reg[3], reg[4], reg[5], reg[6], reg[7]);
};


void do_halt() {
	printf("\n------------ halted -------------\n");
	print_reg();
	exit(0);
};


void do_inc(struct Argument dd, struct Argument ss, unsigned int nn, unsigned int r) {
	w_write(dd.adr, w_read(dd.adr) + 1);
};


void do_incb(struct Argument dd, struct Argument ss, unsigned int nn, unsigned int r) {
	b_write(dd.adr, b_read(dd.adr) + 1);
};

void do_sob(struct Argument dd, struct Argument ss, unsigned int nn, unsigned int r) {
	reg[r] -= 1;
	if (reg[r] != 0)
		pc -= nn;
};

void do_clr(struct Argument dd, struct Argument ss, unsigned int nn, unsigned int r){
	if (dd.adr < 8)
		reg[dd.adr] = 0;
	else
		w_write(dd.adr, 0);
};

Command cmd[] = {
	{0170000, 0010000, "mov", do_mov, 0x03},
	{0170000, 0060000, "add", do_add, 0x03},
	{0xFFFF, 0000000, "halt", do_halt, 0x00},
	{0170000, 0110000, "movb", do_movb, 0x03},
	{0177700, 0015200, "inc", do_inc, 0x01},
	{0177700, 0115200, "incb", do_incb, 0x01},
	{0177000, 0077000, "sob", do_sob, 0x0C},
	{0177700, 0005000, "clr", do_clr, 0x01}
};
