#ifndef MIVM_H__
#define MIVM_H__

#include <stdio.h>

#define STACK_SIZE 1000

typedef struct {
	int stack[STACK_SIZE];
	size_t s_size;
} MIVM;

typedef enum {
	MIPUSH,
	MIADD,
	MISUB
} InstType;

typedef struct {
	InstType type;
	int op;
} Inst;

typedef enum {
	TRAP_STACKOVERFLOW,
	TRAP_STACKUNDERFLOW,
	TRAP_UNK_INST,
	TRAP_NONE=-1
} Trap;

Trap exec_loop(MIVM *vm, Inst *insts, size_t n);
Trap exec_inst(MIVM *vm, Inst inst);
Trap inst_push(MIVM *vm, int op);
Trap inst_add(MIVM *vm);
Trap inst_sub(MIVM *vm);
void dump_vm(MIVM *vm);

#endif
