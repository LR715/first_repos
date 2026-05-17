#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла бинарного дерева
typedef struct TreeNode {
    int value;               // Значение узла
    struct TreeNode* left;   // Указатель на левое поддерево
    struct TreeNode* right;  // Указатель на правое поддерево
} TreeNode;

// Прототипы функций
TreeNode* createNode(int value);           // Создание нового узла
TreeNode* append(TreeNode* root, int value); // Добавление узла в дерево
void preoder(TreeNode* root);               // Предзаказ обхода
void LNR_Traversal(TreeNode* root);         // Обход в порядке LNR
void RNL_Traversal(TreeNode* root);         // Обход в порядке RNL
void levelOrderTraversal(TreeNode* root);   // Обход в ширину
void freeTree(TreeNode* root);               // Освобождение памяти

#endif // BINARY_TREE_H
