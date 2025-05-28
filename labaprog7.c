#include <stdio.h>
#include <pthread.h>   // Библиотека для работы с потоками
#include <unistd.h>    // Для sleep() и usleep()
#include <stdlib.h>    // Для стандартных функций
#include <string.h>    // Для работы со строками

// ================= 1. Создание потока =================
void* thread_func_1(void* arg) {  // Функция, выполняемая в дочернем потоке
    for (int i = 0; i < 5; i++) { // i - счетчик итераций
        printf("Дочерний поток 1: строка %d\n", i+1);
    }
    return NULL;
}

void task1() {
    printf("\n=== Задание 1: Создание потока ===\n");
    pthread_t thread;  // Идентификатор потока
    if (pthread_create(&thread, NULL, thread_func_1, NULL) != 0) {
        perror("Ошибка создания потока");
        return;
    }
    
    for (int i = 0; i < 5; i++) { // i - счетчик итераций
        printf("Родительский поток 1: строка %d\n", i+1);
    }
    
    if (pthread_join(thread, NULL) != 0) {
        perror("Ошибка ожидания потока");
    }
}

// ================= 2. Ожидание потока =================
void* thread_func_2(void* arg) {  // Функция для дочернего потока
    for (int i = 0; i < 5; i++) { // i - счетчик итераций
        printf("Дочерний поток 2: строка %d\n", i+1);
    }
    return NULL;
}

void task2() {
    printf("\n=== Задание 2: Ожидание потока ===\n");
    pthread_t thread;  // Идентификатор потока
    if (pthread_create(&thread, NULL, thread_func_2, NULL) != 0) {
        perror("Ошибка создания потока");
        return;
    }
    
    if (pthread_join(thread, NULL) != 0) {
        perror("Ошибка ожидания потока");
    }
    
    for (int i = 0; i < 5; i++) { // i - счетчик итераций
        printf("Родительский поток 2: строка %d\n", i+1);
    }
}

// ================= 3. Параметры потока =================
typedef struct {
    char messages[5][100];  // Массив сообщений для потока
    int count;              // Количество сообщений
} ThreadData;

void* thread_func_3(void* arg) {
    ThreadData* data = (ThreadData*)arg;  // Принимаем структуру с данными
    for (int i = 0; i < data->count; i++) { // i - счетчик сообщений
        printf("Поток %lu: %s\n", (unsigned long)pthread_self(), data->messages[i]);
    }
    return NULL;
}

void task3() {
    printf("\n=== Задание 3: Параметры потока ===\n");
    pthread_t threads[4];      // Массив идентификаторов потоков
    ThreadData data[4] = {     // Данные для каждого потока
        {{"Сообщение 1", "Сообщение 2", "Сообщение 3", "Сообщение 4", "Сообщение 5"}, 5},
        {{"Другое 1", "Другое 2", "Другое 3", "Другое 4", "Другое 5"}, 5},
        {{"Текст 1", "Текст 2", "Текст 3", "Текст 4", "Текст 5"}, 5},
        {{"Строка 1", "Строка 2", "Строка 3", "Строка 4", "Строка 5"}, 5}
    };
    
    for (int i = 0; i < 4; i++) { // i - индекс потока
        if (pthread_create(&threads[i], NULL, thread_func_3, &data[i]) != 0) {
            perror("Ошибка создания потока");
            continue;
        }
    }
    
    for (int i = 0; i < 4; i++) { // i - индекс потока
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Ошибка ожидания потока");
        }
    }
}

// ================= 4. Завершение потока без ожидания =================
void* thread_func_4(void* arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);  // Разрешаем отмену
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL); // Отложенная отмена
    
    for (int i = 0; i < 5; i++) { // i - счетчик итераций
        printf("Поток 4.%lu: строка %d\n", (unsigned long)pthread_self(), i+1);
        sleep(1);
        
        pthread_testcancel();  // Точка отмены
    }
    return NULL;
}

void task4() {
    printf("\n=== Задание 4: Завершение потока без ожидания ===\n");
    pthread_t threads[4];  // Массив идентификаторов потоков
    
    for (int i = 0; i < 4; i++) { // i - индекс потока
        if (pthread_create(&threads[i], NULL, thread_func_4, NULL) != 0) {
            perror("Ошибка создания потока");
            continue;
        }
    }
    
    sleep(2);  // Ждем 2 секунды
    
    for (int i = 0; i < 4; i++) { // i - индекс потока
        if (pthread_cancel(threads[i]) != 0) {
            perror("Ошибка отмены потока");
        }
    }
    
    printf("Основной поток завершил работу\n");
}

// ================= 5. Обработка завершения потока =================
void cleanup_handler(void* arg) {  // Функция очистки
    printf("Поток 5.%lu: выполняется очистка перед завершением\n", (unsigned long)pthread_self());
}

void* thread_func_5(void* arg) {
    pthread_cleanup_push(cleanup_handler, NULL);  // Регистрируем обработчик
    
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    
    for (int i = 0; i < 5; i++) { // i - счетчик итераций
        printf("Поток 5.%lu: строка %d\n", (unsigned long)pthread_self(), i+1);
        sleep(1);
        
        pthread_testcancel();  
    }
    
    pthread_cleanup_pop(1);  // Выполняем cleanup и удаляем его
    return NULL;
}

void task5() {
    printf("\n=== Задание 5: Обработка завершения потока ===\n");
    pthread_t thread;  // Идентификатор потока
    
    if (pthread_create(&thread, NULL, thread_func_5, NULL) != 0) {
        perror("Ошибка создания потока");
        return;
    }
    
    sleep(2);
    if (pthread_cancel(thread) != 0) {
        perror("Ошибка отмены потока");
    }
    
    if (pthread_join(thread, NULL) != 0) {
        perror("Ошибка ожидания потока");
    }
    printf("Основной поток завершил работу\n");
}

// ================= 6. Sleepsort =================
void* sleep_sort(void* arg) {
    int value = *(int*)arg;  // Получаем значение из аргумента
    usleep(value * 1000);    // Задержка пропорциональна значению (в микросекундах)
    printf("%d ", value);    // Выводим значение после задержки
    return NULL;
}

void task6() {
    printf("\n=== Задание 6: Sleepsort ===\n");
    int arr[] = {34, 23, 122, 9, 87, 45};  // Массив для сортировки
    int n = sizeof(arr)/sizeof(arr[0]);     // n - количество элементов
    
    printf("Исходный массив: ");
    for (int i = 0; i < n; i++) { // i - индекс элемента
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    printf("Отсортированный массив: ");
    pthread_t threads[n];  // Массив идентификаторов потоков
    
    for (int i = 0; i < n; i++) { // i - индекс элемента/потока
        if (pthread_create(&threads[i], NULL, sleep_sort, &arr[i]) != 0) {
            perror("Ошибка создания потока");
            continue;
        }
    }
    
    for (int i = 0; i < n; i++) { // i - индекс потока
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Ошибка ожидания потока");
        }
    }
    printf("\n");
}

// ================= Главная функция =================
int main() {
    task1();  // Вызов задания 1
    task2();  // Вызов задания 2
    task3();  // Вызов задания 3
    task4();  // Вызов задания 4
    task5();  // Вызов задания 5
    task6();  // Вызов задания 6
    return 0;
}