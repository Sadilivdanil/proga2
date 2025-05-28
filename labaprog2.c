#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Структура узла
struct Node {
    int data;
    struct Node *next;
    struct Node *down;
};
typedef struct Node node_t;

// Функция выделяет память под новый элемент списка
node_t *newNode(int data) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = NULL;
    new_node->down = NULL;
    return new_node;
}

// Функция для вставки нового элемента в конец списка
void appendNode(node_t** head, int data) {
    node_t* new_node = newNode(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    node_t* cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = new_node;
}

// Функция создания списка из ввода пользователя
node_t* createList() {
    node_t* head = NULL;
    int data;
    printf("Введите числа (0 для завершения): ");
    while (1) {
        scanf("%d", &data);
        if (data == 0) break;
        appendNode(&head, data);
    }
    return head;
}

// Функция для вывода списка на экран
void printList(node_t *node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Функция связывания двух списков (учитывает разную длину)
void linkLists(node_t* upper, node_t* lower) {
    while (upper && lower) {
        upper->down = lower;
        upper = upper->next;
        lower = lower->next;
    }
}

// Функция навигации по связанным спискам
void navigate(node_t* start) {
    node_t* current = start;
    char command;

    printf("Навигация: W/S - вверх/вниз, A/D - влево/вправо, Q - выход\n");
    while (1) {
        printf("Текущий узел: %d\n", current->data);
        printf("Введите команду: ");
        scanf(" %c", &command);
        command = toupper(command);

        if (command == 'Q') break;
        else if (command == 'D') {
            if (current->next) current = current->next;
            else printf("Движение вправо невозможно!\n");
        }
        else if (command == 'A') {
            printf("Нельзя идти влево!\n");
        }
        else if (command == 'S') {
            if (current->down) current = current->down;
            else printf("Движение вниз невозможно!\n");
        }
        else if (command == 'W') {
            printf("Нельзя идти вверх!\n");
        }
        else {
            printf("Неизвестная команда!\n");
        }
    }
}

// Основная функция
int main() {
    printf("Создание первого списка:\n");
    node_t* upperList = createList();
    printList(upperList);

    printf("\nСоздание второго списка:\n");
    node_t* lowerList = createList();
    printList(lowerList);

    // Связываем списки
    linkLists(upperList, lowerList);

    // Навигация по списку
    printf("\nНавигация по списку:\n");
    navigate(upperList);

    return 0;
}


