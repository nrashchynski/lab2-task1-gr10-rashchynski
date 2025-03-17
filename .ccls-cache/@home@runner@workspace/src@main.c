#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_STUDENTS 7
#define NUM_GRADES 4
#define NUM_BUYERS 5

typedef struct {
  char name[50];
  int group;
  int grades[NUM_GRADES];
  float average;
} STUDENT;

typedef struct {
  char surname[50];
  char name[50];
  char patronymic[50];
  char gender[10];
  char nationality[50];
  int height;
  int weight;
  struct {
    int year;
    int month;
    int day;
  } birthdate;
  char phone[20];
  struct {
    int postal_code;
    char country[50];
    char region[50];
    char district[50];
    char city[50];
    char street[50];
    int house;
    int apartment;
  } address;
  char credit_card[20];
  char bank_account[20];
} BUYER;

float calculate_average(int grades[], int size) {
  float sum = 0;
  for (int i = 0; i < size; i++) {
    sum += grades[i];
  }
  return sum / size;
}

void input_students(STUDENT students[], int size) {
  for (int i = 0; i < size; i++) {
    printf("Введите данные для студента %d:\n", i + 1);
    printf("Фамилия и инициалы: ");
    scanf("%s", students[i].name);
    printf("Номер группы: ");
    scanf("%d", &students[i].group);
    printf("Введите 4 оценки: ");
    for (int j = 0; j < NUM_GRADES; j++) {
      scanf("%d", &students[i].grades[j]);
    }
    students[i].average = calculate_average(students[i].grades, NUM_GRADES);
  }
}

void sort_students(STUDENT students[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = i + 1; j < size; j++) {
      if (students[i].average < students[j].average) {
        STUDENT temp = students[i];
        students[i] = students[j];
        students[j] = temp;
      }
    }
  }
}

void print_top_students(STUDENT students[], int size) {
  printf("\nСтуденты с оценками только 4 и 5:\n");
  for (int i = 0; i < size; i++) {
    int has_low_grades = 0;
    for (int j = 0; j < NUM_GRADES; j++) {
      if (students[i].grades[j] < 4) {
        has_low_grades = 1;
        break;
      }
    }
    if (!has_low_grades) {
      printf("%s (Группа: %d, Средний балл: %.2f)\n", students[i].name,
             students[i].group, students[i].average);
    }
  }
}

void remove_student_with_min_average(STUDENT students[], int *size) {
  if (*size == 0) {
    printf("Список студентов пуст.\n");
    return;
  }

  int min_index = 0;
  for (int i = 1; i < *size; i++) {
    if (students[i].average < students[min_index].average) {
      min_index = i;
    }
  }

  printf("Удалён студент: %s (Группа: %d, Средний балл: %.2f)\n",
         students[min_index].name, students[min_index].group,
         students[min_index].average);

  for (int i = min_index; i < *size - 1; i++) {
    students[i] = students[i + 1];
  }

  (*size)--;
}

void print_all_students(STUDENT students[], int size) {
  printf("\nСписок всех студентов:\n");
  for (int i = 0; i < size; i++) {
    printf("%s (Группа: %d, Средний балл: %.2f)\n", students[i].name,
           students[i].group, students[i].average);
  }
}

void input_buyers(BUYER buyers[], int size) {
  for (int i = 0; i < size; i++) {
    printf("\nВведите данные для покупателя %d:\n", i + 1);
    printf("Фамилия: ");
    scanf("%s", buyers[i].surname);
    printf("Имя: ");
    scanf("%s", buyers[i].name);
    printf("Отчество: ");
    scanf("%s", buyers[i].patronymic);
    printf("Пол: ");
    scanf("%s", buyers[i].gender);
    printf("Национальность: ");
    scanf("%s", buyers[i].nationality);
    printf("Рост: ");
    scanf("%d", &buyers[i].height);
    printf("Вес: ");
    scanf("%d", &buyers[i].weight);
    printf("Дата рождения (год месяц день): ");
    scanf("%d %d %d", &buyers[i].birthdate.year, &buyers[i].birthdate.month,
          &buyers[i].birthdate.day);
    printf("Номер телефона: ");
    scanf("%s", buyers[i].phone);
    printf("Адрес (почтовый индекс страна область район город улица дом "
           "квартира): ");
    scanf("%d %s %s %s %s %s %d %d", &buyers[i].address.postal_code,
          buyers[i].address.country, buyers[i].address.region,
          buyers[i].address.district, buyers[i].address.city,
          buyers[i].address.street, &buyers[i].address.house,
          &buyers[i].address.apartment);
    printf("Номер кредитной карточки: ");
    scanf("%s", buyers[i].credit_card);
    printf("Банковский счет: ");
    scanf("%s", buyers[i].bank_account);
  }
}

void print_buyers_from_brest(BUYER buyers[], int size) {
  printf("\nПокупатели из города Брест:\n");
  int found = 0;
  for (int i = 0; i < size; i++) {
    if (strcmp(buyers[i].address.city, "Брест") == 0) {
      printf("%s %s %s, Телефон: %s, Адрес: %s, %s, %s, %s, %s, %d, %d\n",
             buyers[i].surname, buyers[i].name, buyers[i].patronymic,
             buyers[i].phone, buyers[i].address.country,
             buyers[i].address.region, buyers[i].address.district,
             buyers[i].address.city, buyers[i].address.street,
             buyers[i].address.house, buyers[i].address.apartment);
      found = 1;
    }
  }
  if (!found) {
    printf("Покупатели из города Брест не найдены.\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Использование: %s <количество студентов>\n", argv[0]);
    return 1;
  }

  int size = atoi(argv[1]);
  if (size <= 0 || size > NUM_STUDENTS) {
    printf(
        "Некорректное количество студентов. Допустимое значение: от 1 до %d.\n",
        NUM_STUDENTS);
    return 1;
  }

  STUDENT students[NUM_STUDENTS];
  BUYER buyers[NUM_BUYERS];

  input_students(students, size);

  print_all_students(students, size);

  sort_students(students, size);
  printf("\nСписок студентов после сортировки:\n");
  print_all_students(students, size);

  print_top_students(students, size);

  remove_student_with_min_average(students, &size);
  printf("\nСписок студентов после удаления:\n");
  print_all_students(students, size);

  input_buyers(buyers, NUM_BUYERS);

  print_buyers_from_brest(buyers, NUM_BUYERS);

  return 0;
}
