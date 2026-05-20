#include "spisok.h"
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <string.h>

//проверка расширения файла
//Функция возвращает 1, если имя файла заканчивается на ".bin", иначе 0.
int is_bin(const char* filename) {
    const char *dot = strrchr(filename, '.');
    return (dot && strcmp(dot, ".bin") == 0);
}

int main() {
    DIR *dir;//указатель на директорию
    struct dirent *entry;//указатель на структуру данных о файле
    char *bin_files[28];//массив строк для имен файлов (до 28 файлов)
    int file_count = 0;//счетчик найденных бинарных файлов

    //Открывается текущая директория для поиска файлов.
    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }
    printf("file in directory:\n");
    while ((entry = readdir(dir)) != NULL) {
//если файл заканчивается на ".bin", его имя запоминается в массиве bin_files (копируется с помощью strdup),
//и выводится на экран с присвоенным номером.
        if (is_bin(entry->d_name)) {
            printf("%d: %s\n", file_count + 1, entry->d_name);
            bin_files[file_count] = strdup(entry->d_name);
            file_count++;
        }
    }
    closedir(dir);

    if (file_count == 0) {
        printf("not found\n");
        return 0;
    }

    // выбор файла
    printf("file number: ");
    int choice = 0;
    scanf("%d", &choice);

    if (choice < 1 || choice > file_count) {
        printf("not found\n");
        for(int i = 0; i < file_count; i++) free(bin_files[i]);
        return 1;
    }

    char* filename = bin_files[choice-1];
    //Выбранное имя файла теперь хранится в filename.

    printf("file: %s\n", filename);

//Открывается этот файл для бинарного чтения ("rb").
//Если не удаётся открыть — выводит ошибку, освобождает память, завершает программу.

    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror(filename);
        for(int i = 0; i < file_count; i++) free(bin_files[i]);
        return 1;
    }

    // =========== ОСНОВНОЙ КОД =============
    List *list = create_list();
    record_t fp; // временная переменная для хранения одной записи

    // Читаем все структуры из файла и добавляем в список
    while (fread(&fp, sizeof(record_t), 1, f) == 1) {
        add_k(list, fp, get_count(list)); // добавляем в конец списка
    }
    fclose(f);

    int point_count = get_count(list); // подсчитываем количество элементов в списке
    if (point_count == 0) {
        printf("ERROR\n");
        destroy_list(list);
        for(int i = 0; i < file_count; i++) free(bin_files[i]);
        return 0;
    }

    // Строим бинарное дерево по высотам
    TreeNode *tree = NULL;
    for (int i = 0; i < point_count; i++) {
        record_t cur = get_k(list, i);
        float h = cur.alt_m;
        if (tree == NULL) {
            tree = createNode(h);
        } else {
            append(tree, h);
        }
    }

    // Находим минимум
    TreeNode *p = tree;
    while (p->left) p = p->left;
    float min_h = p->value;

    // Находим максимум
    p = tree;
    while (p->right) p = p->right;
    float max_h = p->value;

    // Считаем время полёта
    double t0 = get_k(list, 0).timestamp_ms;
    double t1 = get_k(list, point_count - 1).timestamp_ms;
    double flight_time = (t1 - t0) / 1000.0;

    // Вывод
    printf("number of points: %d\n", point_count);
    printf("duration: %.3f s\n", flight_time);
    printf("min height: %.3f m\n", min_h);
    printf("max height: %.3f m\n", max_h);

    // Запись в stats1.txt
    FILE *out = fopen("stats1.txt", "w");
    if (out) {
        fprintf(out, "Количество точек: %d\n", point_count);
        fprintf(out, "Продолжительность: %.3f сек\n", flight_time);
        fprintf(out, "Мин высота: %.3f м\n", min_h);
        fprintf(out, "Макс высота: %.3f м\n", max_h);
        fclose(out);
    }

    destroy_list(list);
    freeTree(tree);
    for(int i = 0; i < file_count; i++) free(bin_files[i]);

    return 0;
}
