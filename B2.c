#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FULL_TIME = 0,
    CONTRACT = 1
} EmployeeType;

typedef struct {
    float hourly_rate;
    int hours_worked;
} ContractDetails;

typedef struct {
    char name[20];
    int emp_id;
    EmployeeType type;
    union {
        float salary;
        ContractDetails contract;
    } pay;
} Employee;

float calculatePay(Employee e)
{
    if (e.type == FULL_TIME)
        return e.pay.salary;
    return e.pay.contract.hourly_rate *
           e.pay.contract.hours_worked;
}

int main(void)
{
    int n, i, type;
    float total_bill = 0;
    Employee *staff;
    printf("Enter number of employees: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }
    staff = malloc(n * sizeof(Employee));
    if (staff == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        printf("\nEmployee %d details\n", i + 1);
        printf("Enter name: ");
        scanf("%19s", (staff + i)->name);
        printf("Enter employee ID: ");
        scanf("%d", &(staff + i)->emp_id);
        printf("Enter type (0 = Full-time, 1 = Contract): ");
        if (scanf("%d", &type) != 1 ||
            (type != FULL_TIME && type != CONTRACT)) {
            printf("Invalid employee type.\n");
            free(staff);
            return 1;
        }
        (staff + i)->type = (EmployeeType)type;
        if (type == FULL_TIME) {
            printf("Enter monthly salary: ");
            scanf("%f", &(staff + i)->pay.salary);
        } else {
            printf("Enter hourly rate: ");
            scanf("%f",
                  &(staff + i)->pay.contract.hourly_rate);
            printf("Enter hours worked: ");
            scanf("%d",
                  &(staff + i)->pay.contract.hours_worked);
        }
    }
    printf("\n========== EMPLOYEE PAYSLIPS ==========\n");
    for (i = 0; i < n; i++) {
        Employee *e = staff + i;
        float pay = calculatePay(*e);
        printf("\nName: %s\n", e->name);
        printf("Employee ID: %d\n", e->emp_id);
        if (e->type == FULL_TIME) {
            printf("Employment type: Full-time\n");
            printf("Monthly salary: %.2f\n",
                   e->pay.salary);
        } else {
            printf("Employment type: Contract\n");
            printf("Hourly rate: %.2f\n",
                   e->pay.contract.hourly_rate);
            printf("Hours worked: %d\n",
                   e->pay.contract.hours_worked);
        }
        printf("Total pay: %.2f\n", pay);
        total_bill += pay;
    }
    printf("\nTotal salary bill: %.2f\n", total_bill);
    free(staff);
    return 0;
}