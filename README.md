# assembly
This code is an implementation of a simple virtual machine (VM) that can execute a set of basic instructions. The VM has a memory of 4096 bytes and 8 registers.

## The following instructions are supported:

ADD: Add the contents of two registers and store the result in the first register
SUB: Subtract the contents of one register from another and store the result in the first register
MUL: Multiply the contents of two registers and store the result in the first register
DIV: Divide the contents of one register by another and store the result in the first register
MOV: Move a value into a register
JMP: Jump to a specific memory location
CMP: Compare the contents of two registers and store the result in the last register
HLT: Exit the program
The program reads a binary file named "program.bin" and stores it in memory. It then executes the instructions in memory one by one, starting at the beginning.

The execute_instruction function takes an instruction as an argument and performs the appropriate operation based on the instruction's opcode. The disassemble_instruction function takes an instruction as an argument and prints out the corresponding assembly code for that instruction.

In the main function, all registers are initialized to 0. Then the program opens the "program.bin" file, reads it into memory and execute the instructions.
It also includes some error handling, such as checking if the program file can be opened and read, and exiting the program if division by zero occurs.
