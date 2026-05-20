#include "binary_tree.h"

// Функция для создания нового узла
TreeNode* createNode(float value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для добавления узла в дерево
TreeNode* append(TreeNode* root, float value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = append(root->left, value);
    } else {
        root->right = append(root->right, value);
    }
    return root;
}

// Функция для предзаказного обхода (NLR)
void preoder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%f ", root->value);
    preoder(root->left);
    preoder(root->right);
}

// Функция для LNR обхода
void LNR_Traversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    LNR_Traversal(root->left);
    printf("%f ", root->value);
    LNR_Traversal(root->right);
}

// Функция для RNL обхода
void RNL_Traversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    RNL_Traversal(root->right);
    printf("%f ", root->value);
    RNL_Traversal(root->left);
}

// Обход в ширину (уровневый обход)
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) return;

    // Создание очереди для обхода (FIFO)
    TreeNode* queue[100];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        TreeNode* curr = queue[front++]; // Извлекаем узел
        printf("%f ", curr->value);       // Печатаем значение узла

        if (curr->left != NULL) {
            queue[rear++] = curr->left;   // Добавляем левого потомка в очередь
        }
        if (curr->right != NULL) {
            queue[rear++] = curr->right;  // Добавляем правого потомка в очередь
        }
    }
}

// Функция освобождения памяти
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
