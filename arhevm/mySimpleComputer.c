#include "mySimpleComputer.h"

/* Оперативная память */
static int memory[MEM_SIZE];

/* Регистры */
static int accumulator;
static int instruction_counter;
static int flags_register;

/* Функции операций с памятью */

int sc_memoryInit() {
    for (int i = 0; i < MEM_SIZE; i++) {
        memory[i] = 0;
    }
    return 0;
}

int sc_memorySet(int address, int value) {
    if (address < 0 || address >= MEM_SIZE || value < -9999 || value > 9999) {
        return -1;
    }
    memory[address] = value;
    return 0;
}

int sc_memoryGet(int address, int *value) {
    if (address < 0 || address >= MEM_SIZE || value == NULL) {
        return -1;
    }
    *value = memory[address];
    return 0;
}

int sc_memorySave(char *filename) {
    if (filename == NULL) {
        return -1;
    }
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return -1;
    }
    fwrite(memory, sizeof(int), MEM_SIZE, file);
    fclose(file);
    return 0;
}

int sc_memoryLoad(char *filename) {
    if (filename == NULL) {
        return -1;
    }
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return -1;
    }
    fread(memory, sizeof(int), MEM_SIZE, file);
    fclose(file);
    return 0;
}

/* Функции операций с регистрами */

int sc_regInit() {
    flags_register = 0;
    return 0;
}

int sc_regSet(int reg, int value) {
    if (reg < 0 || reg > 2) {
        return -1;
    }
    if (value != 0 && value != 1) {
        return -1;
    }
    if (value == 1) {
        flags_register |= (1 << reg);
    } else {
        flags_register &= ~(1 << reg);
    }
    return 0;
}

int sc_regGet(int reg, int *value) {
    if (reg < 0 || reg > 2 || value == NULL) {
        return -1;
    }
    *value = (flags_register >> reg) & 1;
    return 0;
}

int sc_accumulatorInit() {
    accumulator = 0;
    return 0;
}

int sc_accumulatorSet(int value) {
    if (value < -9999 || value > 9999) {
        return -1;
    }
    accumulator = value;
    return 0;
}

int sc_accumulatorGet(int *value) {
    if (value == NULL) {
        return -1;
    }
    *value = accumulator;
    return 0;
}

int sc_icounterInit() {
    instruction_counter = 0;
    return 0;
}

int sc_icounterSet(int value) {
    if (value < 0 || value >= MEM_SIZE) {
        return -1;
    }
    instruction_counter = value;
    return 0;
}

int sc_icounterGet(int *value) {
    if (value == NULL) {
        return -1;
    }
    *value = instruction_counter;
    return 0;
}

/* Функции операций с командами */

int sc_commandEncode(int sign, int command, int operand, int *value) {
    if (sign != 0 && sign != 1) {
        return -1;
    }
    if (command < 10 || command > 99) {
        return -1;
    }
    if (operand < 0 || operand > 127) {
        return -1;
    }
    *value = (sign << 14) | (command << 7) | operand;
    return 0;
}

int sc_commandDecode(int value, int *sign, int *command, int *operand) {
    if (value < 0 || value > 0x7FFF) {
        return -1;
    }
    *sign = (value >> 14) & 1;
    *command = (value >> 7) & 0x7F;
    *operand = value & 0x7F;
    return 0;
}

int sc_commandValidate(int command) {
    if (command < 10 || command > 99) {
        return -1;
    }
    return 0;
}
