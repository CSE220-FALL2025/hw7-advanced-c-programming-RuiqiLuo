#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 128

typedef struct
{
    char name;
    unsigned int num_rows;
    unsigned int num_cols;
    int values[];
} matrix_sf;

// 你的 create_matrix_sf 函数
matrix_sf *create_matrix_sf(char name, const char *expr)
{
    printf("-----now it's create_matrix_sf function-----\n");
    fflush(stdout);
    unsigned int num_rows = 0;
    unsigned int num_cols = 0;

    const char *str = expr;
    int tem_num[MAX_LINE_LEN];

    int str_count = 0;
    int tem_num_count = 0;

    // skip the start space
    while (isspace(str[str_count]))
    {
        str_count++;
    }
    // now meet the rows number
    char *end = NULL;
    num_rows = strtol(&str[str_count], &end, 10);
    str_count = (const char *)end - str;

    // now meet the cols number
    end = NULL;
    num_cols = strtol(&str[str_count], &end, 10);
    str_count = (const char *)end - str;

    // skip the white space and '[' to get the first number
    while (isspace(str[str_count]) || str[str_count] == '[')
    {
        str_count++;
    }

    end = NULL;
    while (str[str_count] != ']')
    {
        // skip the  white space
        while (isspace(str[str_count]) || str[str_count] == ';')
        {
            str_count++;
        }
        if (str[str_count] == ']')
        {
            break;
        }
        char *start = expr + str_count;
        int num = strtol(start, &end, 10);
        tem_num[tem_num_count] = num;
        printf("count[%d]: %d \n", tem_num_count, num);
        tem_num_count++;
        start = end;
        str_count = end - expr;
    }
    matrix_sf *m = malloc(sizeof(matrix_sf) + tem_num_count * sizeof(int));
    for (int count = 0; count < tem_num_count; count++)
    {
        *(m->values + count) = tem_num[count];
        printf("final value:%d\n", *(m->values + count));
    }
    m->name = name;
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    return m;
}

int main()
{
    printf("=== Test 1: 8x1 matrix ===\n");
    matrix_sf *mat1 = create_matrix_sf('V', "8 1 [-105 ; -19 ; -140 ; 122 ; -123 ; 105 ; 90 ; 90 ; ]");

    if (mat1)
    {
        printf("\n✓ Matrix created!\n");
        printf("Name: %c, Rows: %u, Cols: %u\n", mat1->name, mat1->num_rows, mat1->num_cols);
        printf("Values: ");
        for (int i = 0; i < 8; i++)
        {
            printf("%d ", mat1->values[i]);
        }
        printf("\n");
        free(mat1);
    }

    printf("\n=== Test 2: 7x3 matrix ===\n");
    matrix_sf *mat2 = create_matrix_sf('Z', "7 3 [137 39 111 ; -142 -128 -45 ; 116 -135 134 ; 91 64 32 ; 88 148 139 ; 51 -45 35 ; 143 89 -64 ; ]");

    if (mat2)
    {
        printf("\n✓ Matrix created!\n");
        printf("Name: %c, Rows: %u, Cols: %u\n", mat2->name, mat2->num_rows, mat2->num_cols);
        printf("First 6 values: ");
        for (int i = 0; i < 6; i++)
        {
            printf("%d ", mat2->values[i]);
        }
        printf("\n");
        free(mat2);
    }

    return 0;
}