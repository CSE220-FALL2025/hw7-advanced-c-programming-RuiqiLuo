#include "hw7.h"
// in the begnning:[====] Synthesis: Tested: 70 | Passing: 29 | Failing: 41 | Crashing: 18
// now:[====] Synthesis: Tested: 70 | Passing: 50 | Failing: 23 | Crashing: 3

/*
typedef struct bst_sf {
    matrix_sf *mat;
    struct bst_sf *left_child;
    struct bst_sf *right_child;
} bst_sf;
*/
struct calculate
{
    char store[MAX_LINE_LEN];
    int top;
};

struct calculate_matrix
{
    matrix_sf *store[MAX_LINE_LEN];
    int top;
};

// free temporary space
void free_temporary(matrix_sf *input)
{
    if (input->name == '\0')
    {
        free(input);
    }
}

void push_matrix(struct calculate_matrix *stack, matrix_sf *input);
void push_matrix(struct calculate_matrix *stack, matrix_sf *input)
{
    stack->top++;
    stack->store[stack->top] = input;
}

matrix_sf *pop_matrix(struct calculate_matrix *stack); // don't forget how to declare the function which return matrix_sf's pointer
matrix_sf *pop_matrix(struct calculate_matrix *stack)
{
    if (stack->top == -1)
    {
        return '\0';
    }
    matrix_sf *popped_value = stack->store[stack->top];
    stack->top--;
    return popped_value;
}

int operator_precedence(char x); // use in infix2postfix_sf
int operator_precedence(char x)
{
    if (x == '\'')
    {
        return 3;
    }
    else if (x == '*')
    {
        return 2;
    }
    else if (x == '+')
    {
        return 1;
    }
    else
    {
        return -1; // because of this, I should check the '(' ')' before the alphabet
    }
}
// push into stack
void push(struct calculate *stack, char input);
void push(struct calculate *stack, char input)
{
    stack->top++;
    stack->store[stack->top] = input;
}

// pop out of stack
char pop(struct calculate *stack);
char pop(struct calculate *stack)
{
    if (stack->top == -1)
    {
        return '\0';
    }
    char popped_value = stack->store[stack->top];
    stack->top--;
    return popped_value;
}

bst_sf *insert_bst_sf(matrix_sf *mat, bst_sf *root)
{
    // printf("----insert_bst_sf start----\n");
    bst_sf *new_root;
    // if root == NULL
    if (root == NULL)
    {
        new_root = malloc(sizeof(bst_sf));
        new_root->mat = mat;
        new_root->left_child = NULL;
        new_root->right_child = NULL;
        // printf("create the root node: %c\n", new_root->mat->name);
        return new_root;
    }
    else
    {
        new_root = root;
    }
    bst_sf *insert = new_root;
    bst_sf *new_node = malloc(sizeof(bst_sf));

    // if root != NULL

    while (1)
    {
        // printf("now we at: %c\n", insert->mat->name);
        if (insert->mat->name > mat->name) //(*(*insert).mat).name
        {
            // put at left,notice the sequence about "check" and "move"
            if (insert->left_child == NULL)
            {
                new_node->mat = mat;
                new_node->left_child = NULL;
                new_node->right_child = NULL;
                insert->left_child = new_node;
                // printf("insert at left: %c\n", insert->left_child->mat->name);
                return new_root;
            }
            else
            {
                insert = insert->left_child;
            }
        }
        if (insert->mat->name < mat->name)
        {
            // put at right
            if (insert->right_child == NULL)
            {
                new_node->mat = mat;
                new_node->left_child = NULL;
                new_node->right_child = NULL;
                insert->right_child = new_node;
                // printf("insert at right: %c\n", insert->right_child->mat->name);
                return new_root;
            }
            else
            {
                insert = insert->right_child;
            }
        }
    }
    return 0;
}

matrix_sf *find_bst_sf(char name, bst_sf *root)
{
    // printf("----find_bst_df----\n");
    // printf("Should find:%c\n", name);
    // root == NULL
    if (root == NULL)
    {
        return NULL;
    }
    bst_sf *search = root;
    while (search != NULL)
    {
        // printf("now we at: %c\n", search->mat->name);
        if (search->mat->name == name)
        {
            return search->mat;
        }
        if (search->mat->name > name)
        {
            if (search->left_child != NULL)
            {
                search = search->left_child;
            }
            else
            {
                return NULL;
            }
        }
        if (search->mat->name < name)
        {
            if (search->right_child != NULL)
            {
                search = search->right_child;
            }
            else
            {
                return NULL;
            }
        }
    }
    return NULL;
}

void free_bst_sf(bst_sf *root)
{
    // printf("----free_bst_sf----\n");
    //=====!!!!important=====
    if (root == NULL)
    {
        return;
    }
    free_bst_sf(root->left_child);
    free_bst_sf(root->right_child);

    free(root->mat);
    free(root);
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
    // printf("-----now it's add_mats_sf function-----\n");
    unsigned int num_rows = mat1->num_rows;
    unsigned int num_cols = mat1->num_cols;

    // printf("name: %c and %c\n", mat1->name, mat2->name); // can I use mat1.name? or in here they are equal,mat1->name==(*mat1).name
    // printf("num_rows:%u\n", num_rows);                   // usigned int-> %u
    // printf("num_cols:%u\n", num_cols);
    // get the length of the values
    // unsigned int length = strlen(mat1->values); // is that right? no, this is totally wrong

    // printf("lenhth:%u\n", length);
    // create a new matrix to store the outcome
    matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));

    m->name = '\0';
    m->num_rows = num_rows;
    m->num_cols = num_cols;

    for (unsigned int count = 0; count < num_cols * num_rows; count++)
    {
        // printf("num1:%d\n", mat1->values[count]);
        // printf("num2:%d\n", mat2->values[count]);
        m->values[count] = mat1->values[count] + mat2->values[count];
        // printf("count:%d\n value:%d\n", count, m->values[count]);
    }
    // when should I free the m?
    return m;
}
// day 1
matrix_sf *mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{
    // printf("-----now it's mult_mats_sf function-----\n");

    unsigned int num_rows = mat1->num_rows;
    unsigned int num_cols = mat2->num_cols; // here is different with the add function
    int n = mat1->num_cols;

    // printf("name: %c and %c\n", mat1->name, mat2->name);
    // printf("num_rows:%u\n", num_rows); // usigned int-> %u
    // printf("num_cols:%u\n", num_cols);

    // printf("mat1:num_row:%u\n", mat1->num_rows);
    // printf("mat1:num_cols:%u\n", mat1->num_cols);

    // printf("mat2:num_row:%u\n", mat2->num_rows);
    // printf("mat2:num_cols:%u\n", mat2->num_cols);

    // unsigned int length = strlen(mat1->values);// this is wrong

    // printf("length:%u\n", length);
    matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));

    m->name = '\0';
    m->num_rows = num_rows;
    m->num_cols = num_cols;

    for (unsigned int count_i = 0; count_i < num_rows; count_i++)
    {
        for (unsigned int count_j = 0; count_j < num_cols; count_j++)
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
                // printf("------now the position is a[%d][%d]-----\n", count_i, count_j);
                // printf("------now the k is %d-----\n", k);
                *(m->values + count_i * num_cols + count_j) += *(mat1->values + mat1->num_cols * count_i + k) * (*(mat2->values + mat2->num_cols * k + count_j));
                // printf("result:%d\n", *(m->values + count_i * num_cols + count_j));
            }
        }
    }
    return m;
}
// (day 1)
matrix_sf *transpose_mat_sf(const matrix_sf *mat)
{
    // printf("previous cols:%d\n", mat->num_cols);
    // printf("previous rows:%d\n", mat->num_rows);

    unsigned int num_rows = mat->num_cols;
    unsigned int num_cols = mat->num_rows;
    matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));

    m->name = '\0';
    m->num_rows = num_rows;
    m->num_cols = num_cols;

    // printf("now cols:%d\n", m->num_cols);
    // printf("now rows:%d\n", m->num_rows);

    for (unsigned int count_i = 0; count_i < num_rows; count_i++)
    {
        for (unsigned int count_j = 0; count_j < num_cols; count_j++)
        {
            // printf("now the position:[%d][%d]\n", count_i, count_j);
            *(m->values + count_i * num_cols + count_j) = *(mat->values + count_j * mat->num_cols + count_i);
            // printf("result:%d\n", *(m->values + count_i * num_cols + count_j));
        }
    }
    return m;
}
// day 1
matrix_sf *create_matrix_sf(char name, const char *expr)
{
    // printf("-----now it's create_matrix_sf function-----\n");
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
        // printf("count[%d]: %d \n", tem_num_count, num);
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
        // printf("final value:%d\n", *(m->values + count));
    }
    m->name = name;
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    return m;
}

char *infix2postfix_sf(char *infix)
{
    // printf("----infix2postfix_sf----\n");
    // create stack, and a string to store the print
    // char should_print[MAX_LINE_LEN];// I can't use this to return, think carefully why this is wrong
    char *should_print = malloc(MAX_LINE_LEN * sizeof(char));
    int count_infix = 0;
    int count_array = 0;
    // struct calculate stack = malloc(sizeof(calculate)); // this is wrong, only use malloc in pointer,and "calculate" is wrong, shuold use "struct calculate"
    struct calculate *stack = malloc(sizeof(struct calculate));
    stack->top = -1;
    // scan the infix expression from left to right
    // if the scanned character is an operand, print it, else
    while (*(infix + count_infix) != '\0')
    {
        if (isspace(*(infix + count_infix)))
        {
            count_infix++; // skip white space
            continue;
        }
        // printf("----now:%c----\n", *(infix + count_infix));
        if (isalpha(*(infix + count_infix)))
        {
            // printf("isalpha:print:%c\n", *(infix + count_infix));
            should_print[count_array] = *(infix + count_infix);
            count_array++;
        }
        else if (stack->top == -1)
        {
            // printf("stack is empty:%c\n", *(infix + count_infix));
            push(stack, *(infix + count_infix));
        }
        else if (*(infix + count_infix) == '(')
        {
            // printf("scanned meet ( now\n");
            push(stack, *(infix + count_infix));
        }
        else if (*(infix + count_infix) == ')')
        {
            // printf("scanned meet ) now\n");
            while (stack->top != -1 && stack->store[stack->top] != '(')
            {
                if (stack->store[stack->top] != '(' || stack->store[stack->top] != ')')
                {
                    should_print[count_array] = stack->store[stack->top];
                    count_array++;
                }
                stack->top--;
            }
            if (stack->store[stack->top] == '(')
            {
                stack->top--; // skip (
            }
        }
        else if (operator_precedence(*(infix + count_infix)) > operator_precedence(stack->store[stack->top])) // put into the stack
        {
            // printf("scanned operator is greater than the precedence of the operator in the stack\n");
            // printf("scanned:%c\n", *(infix + count_infix));
            // printf("in stack:%c\n", stack->store[stack->top]);
            push(stack, *(infix + count_infix));
        }
        else if (operator_precedence(*(infix + count_infix)) <= operator_precedence(stack->store[stack->top]))
        {
            // printf("Pop\n");
            while (operator_precedence(*(infix + count_infix)) <= operator_precedence(stack->store[stack->top]) && stack->top != -1 && stack->store[stack->top] != '(')
            {
                should_print[count_array] = pop(stack);
                // printf("Poped:%c\n", should_print[count_array]);
                count_array++;
            }
            push(stack, *(infix + count_infix));
            // printf("Pushed:%c\n", *(infix + count_infix));
        }
        else if (stack->store[stack->top] == '(')
        {
            // printf("stack meet ( now\n");
            push(stack, *(infix + count_infix));
        }
        count_infix++; // each time, move to next
    }
    // printf("----print alphabet end----\n");
    while (stack->top != -1)
    {
        should_print[count_array] = pop(stack);
        // printf("now:%c\n", should_print[count_array]);
        count_array++;
    }
    should_print[count_array] = '\0';
    // printf("final print:%s\n", should_print);
    // free the stack
    free(stack);
    return should_print;
}

matrix_sf *evaluate_expr_sf(char name, char *expr, bst_sf *root)
{
    // printf("----evaluate_expr_sf----\n");
    // use infix2postfix_sf
    char *postfix = infix2postfix_sf(expr);
    // printf("postfix:%s\n", postfix);
    //  create stack to store the value
    struct calculate_matrix *stack = malloc(sizeof(struct calculate_matrix));
    stack->top = -1;
    //   read all the text
    for (int count = 0; postfix[count] != '\0'; count++)
    {
        if (isalpha(postfix[count]))
        {
            // find from bst_tree
            matrix_sf *input = find_bst_sf(postfix[count], root);
            if (input != NULL)
            {
                // printf("now find %c\n", postfix[count]);
                push_matrix(stack, input);
                // free(input); // is that legal?will that clean the bst_tree? No!, free's function is free the space that pointer point to
            }
        }
        else if (postfix[count] == '\'')
        {
            // printf("----now find '----\n");
            matrix_sf *pop = pop_matrix(stack);
            matrix_sf *outcome = transpose_mat_sf(pop);
            outcome->name = '\0';
            push_matrix(stack, outcome);
            free_temporary(pop);
            // free_temporary(outcome);can't free the value in stack, just free left and right is OK
        }
        else if (postfix[count] == '+')
        {
            // printf("----now find +----\n");
            matrix_sf *right = pop_matrix(stack);
            matrix_sf *left = pop_matrix(stack);
            matrix_sf *outcome = add_mats_sf(left, right);
            outcome->name = '\0';
            push_matrix(stack, outcome);
            // free_temporary(outcome);
            free_temporary(left);
            free_temporary(right);
        }
        else if (postfix[count] == '*')
        {
            // printf("----now find *----\n");
            matrix_sf *right = pop_matrix(stack);
            matrix_sf *left = pop_matrix(stack);
            matrix_sf *outcome = mult_mats_sf(left, right);
            outcome->name = '\0';
            push_matrix(stack, outcome);
            // free_temporary(outcome);
            free_temporary(left);
            free_temporary(right);
        }
    }
    matrix_sf *final = stack->store[stack->top];
    final->name = name;
    // free_temporary(stack); no need to free here, think carefully
    // free postfix
    free(postfix);
    // free stack
    free(stack);
    return final;
}

matrix_sf *execute_script_sf(char *filename)
{

    // 1.open file
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("fopen");
        return NULL;
    }
    // 2.read file
    char *line = NULL;
    size_t len = MAX_LINE_LEN;
    bst_sf *root = NULL;          // shouldn't in the while
    matrix_sf *final_node = NULL; // same as root pointer
    // 3.process each line
    while (getline(&line, &len, file) != -1)
    {
        // skip white space line
        if (strlen(line) == 0)
        {
            continue;
        }

        // clear the \n
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == '\n')
            {
                line[i] = '\0';
            }
        }

        // clean the preceding space
        int count = 0;
        while (isspace(line[count]))
        {
            count++;
        }
        // get the name of matrix
        char name = line[count];
        // find '='
        char *white_space = strchr(line, '='); // char *strchr(const char *s, int c);
        if (white_space == NULL)
        {
            continue;
        }

        white_space = white_space + 1;
        while (*white_space == ' ')
        {
            white_space++;
        }
        char *flag = white_space;
        //  process different situation based on each line
        matrix_sf *node = NULL;
        if (strchr(flag, '['))
        {
            node = create_matrix_sf(name, flag);
        }
        else
        {
            node = evaluate_expr_sf(name, flag, root);
        }
        // insert in tree
        root = insert_bst_sf(node, root);
        final_node = node; // reuturn the last time matrix, but why it's wrong if I paln to free here
    }
    // close the file
    // free(line); // should free that because of getline，should use free_bst_sf

    fclose(file);

    matrix_sf *result = NULL;
    if (final_node != NULL)
    {
        int total = final_node->num_rows * final_node->num_cols;

        result = malloc(sizeof(matrix_sf) + total * sizeof(int));

        result->name = final_node->name;
        result->num_rows = final_node->num_rows;
        result->num_cols = final_node->num_cols;

        for (int i = 0; i < total; i++)
        {
            result->values[i] = final_node->values[i];
        }
    }
    free_bst_sf(root);
    return result;
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
