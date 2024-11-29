#include <assert.h>
#include "mivm.h"


Trap exec_loop(MIVM *vm, Inst *insts, size_t n)
{
	Trap trap;
	for (int i = 0; i < n; i++) {
		if ((trap = exec_inst(vm, insts[i])) != TRAP_NONE) {
			return trap;
		}
	}
	return TRAP_NONE;
}

Trap exec_inst(MIVM *vm, Inst inst) 
{
	switch (inst.type) {
		case MIPUSH:
			inst_push(vm, inst.op);
			break;
		case MIADD:
			inst_add(vm);
			break;
		case MISUB:
			inst_sub(vm);
			break;
		default:
			return TRAP_UNK_INST;
	};
	
	return TRAP_NONE;
}

Trap inst_push(MIVM *vm, int op)
{
	assert(vm->s_size < STACK_SIZE);
	vm->stack[vm->s_size++] = op;
	return TRAP_NONE;
}

Trap inst_add(MIVM *vm) 
{
	assert(vm->s_size > 1);
	vm->stack[vm->s_size-2] += vm->stack[vm->s_size-1];
	vm->s_size--;

	return TRAP_NONE;
}

Trap inst_sub(MIVM *vm)
{
	assert(vm->s_size > 1);
	vm->stack[vm->s_size-2] -= vm->stack[vm->s_size-1];
	vm->s_size--;

	return TRAP_NONE;

	return TRAP_NONE;
}

void dump_vm(MIVM *vm)
{
	printf("VM STACK:\n");
	for (int i = vm->s_size-1; i >= 0; i--) {
		printf("%d\n", vm->stack[i]);
	}
}
