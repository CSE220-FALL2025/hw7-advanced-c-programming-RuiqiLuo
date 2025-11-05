#include "hw7.h"
// in the begnning:[====] Synthesis: Tested: 70 | Passing: 29 | Failing: 41 | Crashing: 18
// now:[====] Synthesis: Tested: 70 | Passing: 31 | Failing: 41 | Crashing: 18
bst_sf *insert_bst_sf(matrix_sf *mat, bst_sf *root)
{
    return NULL;
}

matrix_sf *find_bst_sf(char name, bst_sf *root)
{
    return NULL;
}

void free_bst_sf(bst_sf *root)
{
}
// day 1
/*
typedef struct {
    char name;
    unsigned int num_rows;
    unsigned int num_cols;
    int values[];
} matrix_sf;
 */
matrix_sf *add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{
    printf("-----now it's add_mats_sf function-----\n");
    unsigned int num_rows = mat1->num_rows;
    unsigned int num_cols = mat1->num_cols;

    printf("name: %c and %c\n", mat1->name, mat2->name); // can I use mat1.name? or in here they are equal,mat1->name==(*mat1).name
    printf("num_rows:%u\n", num_rows);                   // usigned int-> %u
    printf("num_cols:%u\n", num_cols);
    // get the length of the values
    // unsigned int length = strlen(mat1->values); // is that right? no, this is totally wrong
    unsigned int length = num_rows * num_cols;
    printf("lenhth:%u\n", length);
    // create a new matrix to store the outcome
    matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));

    m->name = '\0';
    m->num_rows = num_rows;
    m->num_cols = num_cols;

    for (int count = 0; count < num_cols * num_rows; count++)
    {
        printf("num1:%d\n", mat1->values[count]);
        printf("num2:%d\n", mat2->values[count]);
        m->values[count] = mat1->values[count] + mat2->values[count];
        printf("count:%d\n value:%d\n", count, m->values[count]);
    }
    // when should I free the m?
    return m;
}
// day 1
matrix_sf *mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{
    printf("-----now it's mult_mats_sf function-----\n");

    unsigned int num_rows = mat1->num_rows;
    unsigned int num_cols = mat2->num_cols; // here is different with the add function
    int n = mat1->num_cols;

    printf("name: %c and %c\n", mat1->name, mat2->name);
    printf("num_rows:%u\n", num_rows); // usigned int-> %u
    printf("num_cols:%u\n", num_cols);

    printf("mat1:num_row:%u\n", mat1->num_rows);
    printf("mat1:num_cols:%u\n", mat1->num_cols);

    printf("mat2:num_row:%u\n", mat2->num_rows);
    printf("mat2:num_cols:%u\n", mat2->num_cols);

    // unsigned int length = strlen(mat1->values);// this is wrong
    unsigned int length = num_cols * num_cols;
    printf("length:%u\n", length);
    matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));

    m->name = '\0';
    m->num_rows = num_rows;
    m->num_cols = num_cols;

    unsigned int i = num_rows;
    unsigned int j = num_cols;
    for (int count_i = 0; count_i < num_rows; count_i++)
    {
        for (int count_j = 0; count_j < num_cols; count_j++)
        {
            *(m->values + count_i * num_cols + count_j) = 0;
            for (int k = 0; k < n; k++)
            {
                // turn 1D array to 2D
                /*
            [1,2,3],
            [3,4,5].

            a[1][2]=a[i][j]=*(a+i*num_cols+j)
                */
                printf("------now the position is a[%d][%d]-----\n", count_i, count_j);
                printf("------now the k is %d-----\n", k);
                *(m->values + count_i * num_cols + count_j) += *(mat1->values + mat1->num_cols * count_i + k) * (*(mat2->values + mat2->num_cols * k + count_j));
                printf("result:%d\n", *(m->values + count_i * num_cols + count_j));
            }
        }
    }
    return m;
}
// (day 1)
matrix_sf *transpose_mat_sf(const matrix_sf *mat)
{
    printf("previous cols:%d\n", mat->num_cols);
    printf("previous rows:%d\n", mat->num_rows);

    unsigned int num_rows = mat->num_cols;
    unsigned int num_cols = mat->num_rows;
    matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));

    m->name = '\0';
    m->num_rows = num_rows;
    m->num_cols = num_cols;

    printf("now cols:%d\n", m->num_cols);
    printf("now rows:%d\n", m->num_rows);

    for (unsigned int count_i = 0; count_i < num_rows; count_i++)
    {
        for (unsigned int count_j = 0; count_j < num_cols; count_j++)
        {
            printf("now the position:[%d][%d]\n", count_i, count_j);
            *(m->values + count_i * num_cols + count_j) = *(mat->values + count_j * mat->num_cols + count_i);
            printf("result:%d\n", *(m->values + count_i * num_cols + count_j));
        }
    }
    return m;
}
// day 1
matrix_sf *create_matrix_sf(char name, const char *expr)
{
    printf("-----now it's create_matrix_sf function-----\n");
    fflush(stdout);
    unsigned int num_rows = 0;
    unsigned int num_cols = 0;

    // need isspace
    const char *str = expr; // should I use *?
    int tem_num[MAX_LINE_LEN];

    int str_count = 0;
    int tem_num_count = 0;

    // first: get the rows and cols;
    // when is the end: meet the ']' -> end
    // skip the start space
    while (isspace(str[str_count]))
    {
        str_count++;
    }
    // now meet the rows number
    char *end = NULL;
    num_rows = strtol(&str[str_count], &end, 10);
    str_count = (const char *)end - str; // to avoid warning

    // now meet the cols number
    end = NULL;
    num_cols = strtol(&str[str_count], &end, 10);
    str_count = (const char *)end - str;

    // skip the white space and '[' to get the first number
    while (isspace(str[str_count]) || str[str_count] == '[')
    {
        str_count++;
    }
    // check and write the number

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
        const char *start = expr + str_count;
        // use strtol to get number
        int num = strtol(start, &end, 10); // notice that "end" is wrong,"&end" is right
        // write
        tem_num[tem_num_count] = num;
        printf("count[%d]: %d \n", tem_num_count, num);
        tem_num_count++;
        // move the "start" pointer to the "end" position
        start = end;
        str_count = end - expr;
    }
    matrix_sf *m = malloc(sizeof(matrix_sf) + tem_num_count * sizeof(int));
    // write the number to structure
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

char *infix2postfix_sf(char *infix)
{
    return NULL;
}

matrix_sf *evaluate_expr_sf(char name, char *expr, bst_sf *root)
{
    return NULL;
}
// day 1
matrix_sf *execute_script_sf(char *filename)
{
    return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[])
{
    matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows * num_cols * sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat)
{
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows * mat->num_cols; i++)
    {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows * mat->num_cols - 1)
            printf(" ");
    }
    printf("\n");
}
