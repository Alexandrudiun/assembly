#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 4096
#define REGISTER_COUNT 8

unsigned char memory[MEMORY_SIZE];
unsigned int registers[REGISTER_COUNT];

enum {
    ADD,
    SUB,
    MUL,
    DIV,
    MOV,
    JMP,
    CMP,
    HLT
};

void execute_instruction(unsigned int instruction) {
    unsigned char opcode = instruction >> 24;
    unsigned char reg1 = (instruction >> 16) & 0xFF;
    unsigned char reg2 = (instruction >> 8) & 0xFF;
    unsigned int value = instruction & 0xFF;
    switch (opcode) {
        case ADD:
            registers[reg1] += registers[reg2];
            break;
        case SUB:
            registers[reg1] -= registers[reg2];
            break;
        case MUL:
            registers[reg1] *= registers[reg2];
            break;
        case DIV:
            if (registers[reg2] == 0) {
                printf("Error: Division by zero.\n");
                exit(1);
            }
            registers[reg1] /= registers[reg2];
            break;
        case MOV:
            registers[reg1] = value;
            break;
        case JMP:
            registers[0] = value;
            break;
        case CMP:
            if (registers[reg1] == registers[reg2]) {
                registers[REGISTER_COUNT - 1] = 0;
            } else if (registers[reg1] > registers[reg2]) {
                registers[REGISTER_COUNT - 1] = 1;
            } else {
                registers[REGISTER_COUNT - 1] = -1;
            }
            break;
        case HLT:
            exit(0);
            break;
    }
}

void disassemble_instruction(unsigned int instruction) {
    unsigned char opcode = instruction >> 24;
    unsigned char reg1 = (instruction >> 16) & 0xFF;
    unsigned char reg2 = (instruction >> 8) & 0xFF;
    unsigned int value = instruction & 0xFF;
    switch (opcode) {
        case ADD:
            printf("ADD R%d, R%d\n", reg1, reg2);
            break;
        case SUB:
            printf("SUB R%d, R%d\n", reg1, reg2);
            break;
        case MUL:
            printf("MUL R%d, R%d\n", reg1, reg2);
            break;
        case DIV:
            printf("DIV R%d, R%d\n", reg1, reg2);
            break;
        case MOV:
            printf("MOV R%d, %d\n", reg1, value);
            break;
        case JMP:
            printf("JMP %d\n", value);
            break;
        case CMP: printf("CMP R%d, R%d);
          break;
        case HLT:
            printf("HLT\n");
            break;
    }
  }

int main() {
    // initialize all registers to zero
    for (int i = 0; i < REGISTER_COUNT; i++) {
        registers[i] = 0;
    }

    FILE* file = fopen("program.bin", "rb");
    if (file == NULL) {
        printf("Error: Unable to open program file.\n");
        exit(1);
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Read the file into memory
    if (fread(memory, 1, file_size, file) != file_size) {
        printf("Error: Unable to read program file.\n");
        exit(1);
    }

    fclose(file);

    // Execute the instructions
    unsigned int instruction_pointer = 0;
    while (1) {
        unsigned int instruction = *(unsigned int*)(memory + instruction_pointer);
        execute_instruction(instruction);
        instruction_pointer += sizeof(unsigned int);
    }

    return 0;
}
