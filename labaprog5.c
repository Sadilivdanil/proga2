#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

#define MAX_NAME_LEN 50
#define MAX_SHOP_LEN 50
#define FILENAME "PriceList.dat"

typedef struct {
    char product[MAX_NAME_LEN];
    char shop[MAX_SHOP_LEN];
    float price;
} PriceRecord;
// создание файла 
void create_file() {  
    FILE *file = fopen(FILENAME, "wb");  
    if (file == NULL) {
        printf("Ошибка создания файла!\n");  
        exit(1);
    }

    PriceRecord records[] = {
        {"Молоко", "Ярче", 123.40f},  
        {"Сок", "Светофор", 123.00f},
        {"Хлеб", "Пятерочка", 34.50f},
        {"Мясо", "Ашан", 567.00f},
        {"Рыба", "Окей", 90.25f}
    };

    int count = sizeof(records) / sizeof(records[0]); 

    fwrite(records, sizeof(PriceRecord), count, file);
    fclose(file);
}
// выполнение поиска 
void search_by_shop() {
    char search_shop[MAX_SHOP_LEN];
    printf("Введите название магазина: "); 
    fgets(search_shop, MAX_SHOP_LEN, stdin);// чтение ввода 
    search_shop[strcspn(search_shop, "\n")] = '\0'; // удаление символа 

    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Файл не найден!\n"); 
        exit(1);
    }

    PriceRecord record;
    int found = 0;

    printf("\nРезультаты поиска в магазине '%s':\n", search_shop);
    printf("%-20s %-20s %s\n", "Товар", "Магазин", "Цена");
    printf("--------------------------------------------\n");
    // чтение записи из файла 

    while (fread(&record, sizeof(PriceRecord), 1, file)) {
        if (strcmp(record.shop, search_shop) == 0) {
            printf("%-20s %-20s %.2f руб.\n", 
                   record.product, record.shop, record.price);
            found = 1;
        }
    }

    if (!found) {
        printf("Товары в магазине '%s' не найдены.\n", search_shop);
    }

    fclose(file);
}

int main() {
    create_file();
    search_by_shop();
    return 0;
}