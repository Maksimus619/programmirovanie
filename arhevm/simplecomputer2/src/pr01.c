#include <stdio.h>
#include "mySimpleComputer.h"

/* Функции для вывода информации на экран */
void printCell(int address) {
    int value;
    if (sc_memoryGet(address, &value) == 0) {
        printf("%+05d ", value);
    } else {
        printf("------ ");
    }
}

void printFlags() {
    int value;
    for (int i = 2; i >= 0; i--) {
        if (sc_regGet(i, &value) == 0) {
            printf("%c", value == 1 ? '1' : '_');
        }
    }
    printf(" ");
}

void printDecodedCommand(int value) {
    int sign, command, operand;
    if (sc_commandDecode(value, &sign, &command, &operand) == 0) {
        printf("Decoded command: %+05d (octal: %05o, hex: %04X, binary: ", value, value, value);
        for (int i = 14; i >= 0; i--) {
            printf("%d", (value >> i) & 1);
        }
        printf(")\n");
    } else {
        printf("Cannot decode command\n");
    }
}

void printAccumulator() {
    int value;
    if (sc_accumulatorGet(&value) == 0) {
        printf("Accumulator: %+05d\n", value);
    } else {
        printf("Cannot get accumulator value\n");
    }
}

void printCounters() {
    int value;
    if (sc_icounterGet(&value) == 0) {
        printf("Instruction Counter: %+05d\n", value);
    } else {
        printf("Cannot get instruction counter value\n");
    }
}

int main() {
    /* Инициализация оперативной памяти, аккумулятора, счетчика команд и регистра флагов */
    sc_memoryInit();
    sc_accumulatorInit();
    sc_icounterInit();
    sc_regInit();

    /* Установка значений ячеек оперативной памяти */
    for (int i = 0; i < 20; i++) {
        sc_memorySet(i, i * 10);
    }

    /* Вывод содержимого оперативной памяти */
    printf("Memory content:\n");
    for (int i = 0; i < 20; i++) {
        printCell(i);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }

    /* Попытка задать недопустимое значение ячейке оперативной памяти */
    printf("\nSetting invalid value to memory cell 50: %d\n", sc_memorySet(50, 10000));

    /* Установка значений флагов и их вывод */
    sc_regSet(0, 1);
    sc_regSet(1, 0);
    sc_regSet(2, 1);
    printf("\nFlags content: ");
    printFlags();
    printf("\n");

    /* Попытка установить некорректное значение флага */
    printf("Setting invalid value to flag 3: %d\n", sc_regSet(3, 1));

    /* Установка значения аккумулятора и его вывод */
    sc_accumulatorSet(12345);
    printf("\n");
    printAccumulator();

    /* Попытка задать недопустимое значение аккумулятору */
    printf("Setting invalid value to accumulator: %d\n", sc_accumulatorSet(100000));

    /* Установка значения счетчика команд и его вывод */
    sc_icounterSet(50);
    printf("\n");
    printCounters();

    /* Попытка задать недопустимое значение счетчику команд */
    printf("Setting invalid value to instruction counter: %d\n", sc_icounterSet(-1));

    /* Декодирование значения произвольной ячейки памяти и значения аккумулятора */
    printf("\nDecoding memory cell 5:\n");
    printDecodedCommand(sc_memoryGet(5, NULL));
    printf("\nDecoding accumulator value:\n");
    printDecodedCommand(sc_accumulatorGet(NULL));

    /* Кодирование команды и вывод в разных системах счисления */
    int encoded_command;
    sc_commandEncode(0, 70, 15, &encoded_command);
    printf("\nEncoded command: %d (octal: %o, hex: %X, binary: ", encoded_command, encoded_command, encoded_command);
    for (int i = 14; i >= 0; i--) {
        printf("%d", (encoded_command >> i) & 1);
    }
    printf(")\n");

    return 0;
}
