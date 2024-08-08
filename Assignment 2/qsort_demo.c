// How to use qsort, by example

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 40

typedef struct STUDENT {
  int number;
  char name[MAX_NAME];
} Student;

// we will explain how this works later...
int compare_students_by_number(const void *a, const void *b)
{
  const Student *sa = (Student *)a;
  const Student *sb = (Student *)b;
  return sa->number - sb->number;
}

void sort_students_by_number(Student *array, int n)
{
  qsort(array, n, sizeof(Student), compare_students_by_number);
}

// we will explain how this works later...
int compare_students_by_name(const void *a, const void *b)
{
  const Student *sa = (Student *)a;
  const Student *sb = (Student *)b;
  return strcmp(sa->name, sb->name);
}

void sort_students_by_name(Student *array, int n)
{
  qsort(array, n, sizeof(Student), compare_students_by_name);
}

void print_students(Student *array, int n)
{
  for (int i = 0; i < n; i++) {
    printf("%4d %s\n", array[i].number, array[i].name); 
  }
}

int main()
{
  Student array[] = {
    { 1234, "gandalf" },
    { 576, "galadriel" },
    { 8056, "arwen" },
    { 5678, "elrond" }
  };
  const int NUM_STUDENTS = 4;

  printf("Original list:\n");
  print_students(array, NUM_STUDENTS);

  sort_students_by_number(array, NUM_STUDENTS);
  printf("\nSorted by number:\n");
  print_students(array, NUM_STUDENTS);

  sort_students_by_name(array, NUM_STUDENTS);
  printf("\nSorted by name:\n");
  print_students(array, NUM_STUDENTS);
  
  return 0;
}