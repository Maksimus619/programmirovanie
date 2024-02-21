#ifndef MYSIMPLECOMPUTER_H
#define MYSIMPLECOMPUTER_H

#include <stdio.h>

/* Размер оперативной памяти */
#define MEM_SIZE 128

/* Операции с памятью */
int sc_memoryInit();                               // Инициализация оперативной памяти
int sc_memorySet(int address, int value);          // Установка значения ячейки памяти
int sc_memoryGet(int address, int *value);         // Получение значения ячейки памяти
int sc_memorySave(char *filename);                 // Сохранение содержимого памяти в файл
int sc_memoryLoad(char *filename);                 // Загрузка содержимого памяти из файла

/* Операции с регистрами */
int sc_regInit();                                  // Инициализация регистра флагов
int sc_regSet(int reg, int value);                 // Установка значения регистра флагов
int sc_regGet(int reg, int *value);                // Получение значения регистра флагов
int sc_accumulatorInit();                          // Инициализация аккумулятора
int sc_accumulatorSet(int value);                  // Установка значения аккумулятора
int sc_accumulatorGet(int *value);                 // Получение значения аккумулятора
int sc_icounterInit();                             // Инициализация счетчика команд
int sc_icounterSet(int value);                     // Установка значения счетчика команд
int sc_icounterGet(int *value);                    // Получение значения счетчика команд

/* Операции с командами */
int sc_commandEncode(int sign, int command, int operand, int *value);   // Кодирование команды
int sc_commandDecode(int value, int *sign, int *command, int *operand); // Декодирование команды
int sc_commandValidate(int command);               // Проверка корректности команды

#endif /* MYSIMPLECOMPUTER_H */
