#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bits.h"
#include "control.h"
#include "instruction.h"
#include "x16.h"
#include "trap.h"


// Update condition code based on result
void update_cond(x16_t* machine, reg_t reg) {
    uint16_t result = x16_reg(machine, reg);
    if (result == 0) {
        x16_set(machine, R_COND, FL_ZRO);
    } else if (is_negative(result)) {
        x16_set(machine, R_COND, FL_NEG);
    } else {
        x16_set(machine, R_COND, FL_POS);
    }
}


// Execute a single instruction in the given X16 machine. Update
// memory and registers as required. PC is advanced as appropriate.
// Return 0 on success, or -1 if an error or HALT is encountered.
int execute_instruction(x16_t* machine) {
    // Fetch the instruction and advance the program counter
    uint16_t pc = x16_pc(machine);
    uint16_t instruction = x16_memread(machine, pc);
    x16_set(machine, R_PC, pc + 1);


    // Decode the instruction and execute it
    uint16_t opcode = getopcode(instruction);


    uint16_t DRloc = getbits(instruction, 9, 3);
    uint16_t SR1 = x16_reg(machine, getbits(instruction, 6, 3));
    uint16_t SR2 = x16_reg(machine, getbits(instruction, 0, 3));
    uint16_t IMM = getbits(instruction, 0, 5);


    uint16_t n = getbit(instruction, 11);
    uint16_t z = getbit(instruction, 10);
    uint16_t p = getbit(instruction, 9);
    uint16_t PCoffset9 = getbits(instruction, 0, 9);
    uint16_t PCoffset11 = getbits(instruction, 0, 11);
    uint16_t PCv = x16_reg(machine, R_PC);
    uint16_t BaseRV = x16_reg(machine, getbits(instruction, 6, 3));
    uint16_t offset6 = getbits(instruction, 0, 6);
    uint16_t SR = getbits(instruction, 9, 3);


    switch (opcode) {
        case OP_ADD:
            if (getbit(instruction, 5) == 0){
                x16_set(machine, DRloc, SR1 + SR2);
            } else {
                x16_set(machine, DRloc, SR1 + sign_extend(IMM, 5));
            }
            update_cond(machine, DRloc);
            break;
        case OP_AND:
            if (getbit(instruction, 5) == 0){
                x16_set(machine, DRloc, SR1 & SR2);
            } else {
                x16_set(machine, DRloc, SR1 & sign_extend(IMM, 5));
            }
            update_cond(machine, DRloc);
            break;


        case OP_NOT:
            x16_set(machine, DRloc, ~SR1);
            update_cond(machine, DRloc);
            break;


        case OP_BR:
            if ((n == 1 && (x16_cond(machine) == FL_NEG)) ||
            (z == 1 && (x16_cond(machine) == FL_ZRO)) ||
            (p && (x16_cond(machine) == FL_POS))){
                x16_set(machine, R_PC, PCv++ + sign_extend(PCoffset9, 9));
            }
            break;


        case OP_JMP:
            x16_set(machine, R_PC, BaseRV);
            break;


        case OP_JSR:
            x16_set(machine, R_R7, PCv);
            x16_set(machine, R_PC, PCv);
            if (getbit(instruction, 11) == 0){
                x16_set(machine, R_PC, BaseRV);
            } else {
                x16_set(machine, R_PC, PCv + sign_extend(PCoffset11, 11));
            }
            break;


        case OP_LD:
            x16_set(machine, DRloc, x16_memread(machine, PCv++
            + sign_extend(PCoffset9, 9)));
            update_cond(machine, DRloc);
            break;


        case OP_LDI:
            x16_set(machine, DRloc, x16_memread(machine, x16_memread(machine,
            PCv++ + sign_extend(PCoffset9, 9))));
            update_cond(machine, DRloc);
            break;


        case OP_LDR:
            x16_set(machine, DRloc, x16_memread(machine, BaseRV +
            sign_extend(offset6, 6)));
            update_cond(machine, DRloc);
            break;


        case OP_LEA:
            x16_set(machine, DRloc, PCv + sign_extend(PCoffset9, 9));
            update_cond(machine, DRloc);
            break;


        case OP_ST:
            x16_memwrite(machine, PCv + sign_extend(PCoffset9, 9),
            x16_reg(machine, SR));
            break;


        case OP_STI:
            x16_memwrite(machine, x16_memread(machine, PCv++ +
            sign_extend(PCoffset9, 9)), x16_reg(machine, SR));
            break;


        case OP_STR:
            x16_memwrite(machine, BaseRV + sign_extend(offset6, 6),
            x16_reg(machine, SR));
            break;


        case OP_TRAP:
            // Execute the trap
            return trap(machine, instruction);


        case OP_RES:
        case OP_RTI:
        default:
            // Bad codes, never used
            abort();
    }


    return 0;
}
