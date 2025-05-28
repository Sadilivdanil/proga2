#include<stdio.h>
#include<stdlib.h>



#define M_L 100
#define M_LE 1000

int main(int argc,char*argv[]) {
    
    
    //Создаем исходный файл с несколькими строками
    FILE* file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("Ошибка создания файла");
        return 1;
    }
    
    fprintf(file, "Первая строка\n");
    fprintf(file, "Вторая строка\n");
    fprintf(file, "Третья строка\n");
    fprintf(file, "Последняя строка\n");
    fclose(file);
    
    //Читаем все строки из файла в массив
    char lines[M_L][M_LE]; //двумерный масив для хранения строк
    int line_count = 0;
    
    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }
    
    while (fgets(lines[line_count], M_LE, file) != NULL && line_count < M_L) {
        line_count++;
    }
    fclose(file);
    
    //Переписываем файл с строками в обратном порядке
    file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("Ошибка открытия файла для записи");
        return 1;
    }
    
    for (int i = line_count - 1; i >= 0; i--) {
        fprintf(file, "%s", lines[i]);
    }
    fclose(file);
    
    printf("Файл успешно перезаписан со строками в обратном порядке.\n");
    
    return 0;
}