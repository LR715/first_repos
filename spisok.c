#include "spisok.h"

// Функция для создания нового списка
List* create_list(void) {
    List* lst = (List*)malloc(sizeof(List));
    if (lst) {
        lst->head = NULL;
        lst->tail = NULL;
        lst->size = 0;
    }
    return lst;
}

// Функция для добавления элемента в список по индексу
void add_k(List* list, record_t value, float k) {
    if (!list || k < 0 || k > list->size) return;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed\n"); // Сообщение об ошибке
        return;
    }
    new_node->data = value;
    new_node->next = NULL;

    if (k == 0) {
        // Вставка в начало списка
        new_node->next = list->head;
        list->head = new_node;
        if (list->size == 0) list->tail = new_node;
    } else {
        // Вставка в середину или в конец списка
        Node* prev = list->head;
        for (int i = 0; i < k - 1; i++) {
            prev = prev->next;
        }
        new_node->next = prev->next;
        prev->next = new_node;
        if (new_node->next == NULL) list->tail = new_node; // Обновление tail, если добавляется в конец
    }
    list->size++;
}

// Функция для получения записи по индексу
record_t get_k(List* list, float k) {
    static record_t dummy = {0}; // Возврат "пустой" записи в случае ошибки
    if (!list || k < 0 || k >= list->size) return dummy;
    Node* curr = list->head;
    for (int i = 0; i < k; i++) curr = curr->next;
    return curr->data;
}

// Функция для получения количества элементов в списке
int get_count(List* list) {
    if (!list) return 0;
    return list->size;
}

// Функция для освобождения памяти
void destroy_list(List* list) {
    if (!list) return;
    Node* curr = list->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

// Функция для печати списка
void print_list(List* list) {
    if (!list) return;
    Node* curr = list->head;
    while (curr) {
        printf("[time: %u, lat: %.6f, lon: %.6f, alt: %.2f] -> ",
            curr->data.timestamp_ms,
            curr->data.lat_rad,
            curr->data.lon_rad,
            curr->data.alt_m);
        curr = curr->next;
    }
    printf("NULL\n");
}
