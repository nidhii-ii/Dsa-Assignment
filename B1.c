#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int roll_no;
    char name[20];
    float marks;
} Student;

void readStudents(Student *p, int start, int count)
{
    int i;
    for (i = start; i < count; i++) {
        printf("\nEnter roll number, name and marks: ");
        if (scanf("%d %19s %f",
                  &(p + i)->roll_no,
                  (p + i)->name,
                  &(p + i)->marks) != 3) {
            printf("Invalid input.\n");
            exit(1);
        }
    }
}

void showReport(Student *p, int n)
{
    int i;
    float total = 0;
    Student *best = p;
    for (i = 0; i < n; i++) {
        Student *current = p + i;
        total += current->marks;
        if (current->marks > best->marks)
            best = current;
    }
    printf("\nAverage marks: %.2f\n", total / n);
    printf("Topper: %s\n", best->name);
    printf("Roll number: %d\n", best->roll_no);
    printf("Marks: %.2f\n", best->marks);
}

int main(void)
{
    int n;
    char choice;
    Student *students, *temp;
    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Enter a valid positive number.\n");
        return 1;
    }
    students = malloc(n * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    readStudents(students, 0, n);
    showReport(students, n);
    printf("\nAdd 2 more students? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        temp = realloc(students, (n + 2) * sizeof(Student));
        if (temp == NULL) {
            printf("Unable to increase memory.\n");
            free(students);
            return 1;
        }
        students = temp;
        readStudents(students, n, n + 2);
        n += 2;
        printf("\nUpdated student report:\n");
        showReport(students, n);
    }
    free(students);
    students = NULL;
    return 0;
}