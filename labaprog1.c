#include <stdio.h>
#include <stdlib.h>

// Структура узла
struct node {
    int data;
    struct node *next;
};

// Функция для добавления узла в конец списка
void addNode(struct node **head, int value) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Функция для вывода списка на экран
void printList(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Главная функция
int main() {
    struct node *list1 = NULL;
    struct node *list2 = NULL;
    int value;

    // Ввод первого списка
    printf("Введите элементы первого списка (0 для завершения ввода):\n");
    while (1) {
        scanf("%d", &value);
        if (value == 0) break;
        addNode(&list1, value);
    }

    // Вывод первого списка
    printf("Первый список: ");
    printList(list1);

    // Ввод второго списка
    printf("Введите элементы второго списка (0 для завершения ввода):\n");
    while (1) {
        scanf("%d", &value);
        if (value == 0) break;
        addNode(&list2, value);
    }

    // Вывод второго списка
    printf("Второй список: ");
    printList(list2);

    // Создаем ссылку S на начало первого списка
    struct node *current = list1;

    // Интерфейс для прохода по списку
    char command;
    while (1) {
        if (current != NULL) {
            printf("Текущее значение: %d\n", current->data);
        }

        printf("Введите команду (WASD для перемещения, Q для выхода): ");
        scanf(" %c", &command);
        
        if (command == 'D' || command == '6') {
            if (current != NULL && current->next != NULL) {
                current = current->next;
            } else {
                printf("Достигли конца списка. Вернуться в начало (S)? (Y/N): ");
                char back;
                scanf(" %c", &back);
                if (back == 'Y' || back == 'y') {
                    current = list1;
                }
            }
        } else if (command == 'A' || command == '4') {
            // Реализация возможности перемещения влево можно добавить, если сохранить указатели на предыдущие узлы
            printf("Перемещение влево не реализовано.\n");
        } else if (command == 'W' || command == '8') {
            // Заглушка для "вверх", если список будет двумерным
            printf("Перемещение вверх не реализовано.\n");
        } else if (command == 'S' || command == '2') {
            current = list1; // Вернуться в начало
        } else if (command == 'Q' || command == 'q') {
            break;
        }
    }

    // Освобождение памяти
    while (list1 != NULL) {
        struct node *temp = list1;
        list1 = list1->next;
        free(temp);
    }

    while (list2 != NULL) {
        struct node *temp = list2;
        list2 = list2->next;
     free(temp);
    }

    return 0;
}

