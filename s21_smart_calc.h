#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

#endif  // S21_SMART_CALC_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {
  OK = 1,            // 1
  WO_EQ,             // 2 Exprssion must end with =
  BRACKETS,          // 3 brackets
  INCORRECT_INPUT,   // 4 incorrect input
  DIV_0,             // 5 ДЕЛЕНИЕ НА 0
  MINUS_SQRT,        // 6 МИНУС В КОРНЕ
  MINUS_LOG,         // 7
  TWO_OPER_TOGETHER  // 8
} return_code;

typedef enum {
  NUMBER = 1,  // 1 приоритет 0
  L_S,         // 2 левая скобка
  R_S,         // 3 правая скобка
  UNAR,        // 4
  SUM,         // 5 приоритет 1
  SUB,         // 6 приоритет 1
  MUL,         // 7 приоритет 2
  DIV,         // 8 приоритет 2
  MOD,         // 9 приоритет 2
  POW,         // 10 приоритет 3
  COS,         // 11 отдельно кос 3
  SIN,         // 12 отдельно син 3
  TAN,         // 13 отдельно тан 3
  ACOS,        // 14 отдельно акос 3
  ASIN,        // 15 отдельно асин 3
  ATAN,        // 16 отдельно атан 3
  SQRT,        // 17 отдельно скрт 3
  LN,          // 18 отдельно лн 3
  LOG,         // 19 отдельно лог 3
  X,           // 20 х в выходную строку 3
  EQ           // 21 последний символ 3
} operation;

typedef struct tree {
  operation operations[256];
  double numbers[256];
  int top;
  int num_o_b;
  int num_c_b;
} tree;

void make_tree(tree *Tree);
void calculate_brackets(tree *Tree, char *str);
return_code make_input_stack2(int i, char *str, char *numb, tree *Tree, int k,
                              return_code res);
void print_stack(tree *Tree);
return_code to_pofix(tree *PofixTree, tree *Tree, double *result);
return_code make_chislo(tree *PofixTree, double *result);
void print_error(return_code res);
int main_f(char str[256], double *result);
