#ifndef SPISOK_H
#define SPISOK_H

#include <stdint.h> // Для uint32_t и других стандартных типов
#include <stdio.h>
#include <stdlib.h>

// Определение структуры для записи данных
typedef struct record_t {
    uint32_t timestamp_ms; // Время в миллисекундах
    float lat_rad;         // Широта в радианах
    float lon_rad;         // Долгота в радианах
    float alt_m;          // Высота в метрах
} record_t;

// Определение структуры для узла списка
typedef struct Node {
    record_t data;          // Данные в узле
    struct Node* next;      // Указатель на следующий узел
} Node;

// Определение структуры для самого списка
typedef struct List {
    Node* head;             // Указатель на голову списка
    Node* tail;             // Указатель на хвост списка
    int size;               // Размер списка
} List;

// Прототипы функций
List* create_list(void);
void add_k(List* list, record_t value, float k);
record_t get_k(List* list, float k);
int get_count(List* list);
void destroy_list(List* list);
void print_list(List* list);

#endif // SPISOK_H
