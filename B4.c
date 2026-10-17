#include <stdio.h>

#define MAX_DIM 50
#define MAX_TERMS (MAX_DIM * MAX_DIM)

typedef struct {
    int row;
    int col;
    int value;
} Term;

void printTriples(Term a[])
{
    int i;
    printf("Row  Col  Value\n");
    for (i = 0; i <= a[0].value; i++) {
        printf("%3d  %3d  %5d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

void fastTranspose(Term a[], Term b[])
{
    int row_terms[MAX_DIM] = {0};
    int starting_pos[MAX_DIM];
    int columns = a[0].col;
    int terms = a[0].value;
    int i, position;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = terms;
    if (terms == 0) {
        printf("\nrow_terms[]: all zeros\n");
        printf("starting_pos[]: no entries\n");
        return;
    }
    /* Count non-zero terms in every original column. */
    for (i = 1; i <= terms; i++)
        row_terms[a[i].col]++;
    /* Find the first destination position for each column. */
    starting_pos[0] = 1;
    for (i = 1; i < columns; i++) {
        starting_pos[i] = starting_pos[i - 1]
                        + row_terms[i - 1];
    }
    printf("\nrow_terms[]: ");
    for (i = 0; i < columns; i++)
        printf("%d ", row_terms[i]);
    printf("\nstarting_pos[]: ");
    for (i = 0; i < columns; i++)
        printf("%d ", starting_pos[i]);
    printf("\n");
    /* Place each term directly in its final position. */
    for (i = 1; i <= terms; i++) {
        position = starting_pos[a[i].col]++;
        b[position].row = a[i].col;
        b[position].col = a[i].row;
        b[position].value = a[i].value;
    }
}

int main(void)
{
    Term original[MAX_TERMS + 1];
    Term transposed[MAX_TERMS + 1];
    int rows, cols, value;
    int i, j, k = 1;
    int ordered = 1;
    printf("Enter rows and columns: ");
    if (scanf("%d %d", &rows, &cols) != 2 ||
        rows <= 0 || cols <= 0 ||
        rows > MAX_DIM || cols > MAX_DIM) {
        printf("Invalid dimensions. Use 1 to %d.\n", MAX_DIM);
        return 1;
    }
    printf("Enter matrix elements row by row:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (scanf("%d", &value) != 1) {
                printf("Invalid matrix input.\n");
                return 1;
            }
            if (value != 0) {
                original[k].row = i;
                original[k].col = j;
                original[k].value = value;
                k++;
            }
        }
    }
    /* Store rows, columns and number of non-zero terms. */
    original[0].row = rows;
    original[0].col = cols;
    original[0].value = k - 1;
    printf("\nOriginal triples:\n");
    printTriples(original);
    fastTranspose(original, transposed);
    printf("\nTransposed triples:\n");
    printTriples(transposed);
    /* Check row-major order without sorting the result. */
    for (i = 1; i < transposed[0].value; i++) {
        if (transposed[i].row > transposed[i + 1].row ||
           (transposed[i].row == transposed[i + 1].row &&
            transposed[i].col > transposed[i + 1].col)) {
            ordered = 0;
            break;
        }
    }
    printf("\nTransposed triples are %s in row-major order.\n",
           ordered ? "already" : "NOT");
    return 0;
}