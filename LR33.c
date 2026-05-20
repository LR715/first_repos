#include "spisok.h"
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {

    FILE *in_file = fopen("flight_data9.bin", "rb");
    if (!in_file) {
        perror("flight_data9.bin");
        return 1;
    }
// создаЄм пустой односв€зный список
    List *list = create_list();
    record_t fp; // временна€ переменна€ дл€ хранени€ одной записи

    while (fread(&fp, sizeof(record_t), 1, in_file) == 1) {
// пока удаЄтс€ прочесть структуру record_t из файла

        add_k(list, fp, get_count(list)); // добавл€ем в конец списка
    }
    fclose(in_file);

    int count = get_count(list); // подсчитываем количество элементов в списке
    if (count == 0) {
        printf("ERROR\n");
        destroy_list(list);
        return 0;
    }

    // —троим бинарное дерево  по высотам
    TreeNode *tree = NULL;
    for (int i = 0; i < count; i++) {
        record_t cur = get_k(list, i);// получаем i-ю структуру из списка
        float h = cur.alt_m;
        if (tree == NULL) {
            tree = createNode(h);// если дерево пусто Ч создаЄм корень
        } else {
            append(tree, h); // иначе добавл€ем узел в дерево
        }
    }

    // находим минимум Ч спускаемс€ влево
    TreeNode *p = tree;
    while (p->left) p = p->left; // доходим до самого левого элемента
    float min_h = p->value;  // это минимальна€ высота

    // находим максимум Ч спускаемс€ вправо
    p = tree;
    while (p->right) p = p->right;
    float max_h = p->value;

    // считаем врем€ полЄта
    double t0 = get_k(list, 0).timestamp_ms;
    double t1 = get_k(list, count - 1).timestamp_ms;
    double flight_time = (t1 - t0) / 1000.0;

    // вывод
    printf("number of points: %d\n", count);
    printf("duration: %.3f s\n", flight_time);
    printf("min height: %.3f m\n", min_h);
    printf("max height: %.3f m\n", max_h);

    // в файл
    FILE *out = fopen("stats.txt", "w");
    if (out) {
        fprintf(out, " оличество точек: %d\n", count);
        fprintf(out, "ѕродолжительность: %.3f сек\n", flight_time);
        fprintf(out, "ћин высота: %.3f м\n", min_h);
        fprintf(out, "ћакс высота: %.3f м\n", max_h);
        fclose(out);
    }

    //
    destroy_list(list);
    freeTree(tree);

    return 0;
}
