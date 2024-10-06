#include "s21_smart_calc.h"
void calculate_brackets(tree *Tree, char *str) {
  int open = 0;
  int close = 0;
  int flag = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == '(') {
      if (open < close) flag = 1;
      open++;
    }
    if (str[i] == ')') close++;
  }
  if (flag) {
    Tree->num_o_b = -1;
    Tree->num_c_b = -1;
  } else {
    Tree->num_o_b = open;
    Tree->num_c_b = close;
  }
}

int functions(int i, char *str, tree *Tree) {
  int delta = 0;
  int top = Tree->top;
  Tree->operations[top] = EQ;
  if (str[i] == '+') Tree->operations[top] = SUM;
  if (str[i] == '*') Tree->operations[top] = MUL;
  if (str[i] == '/') Tree->operations[top] = DIV;
  if (str[i] == '-' && ((i == 0) || (Tree->operations[top - 1] == L_S)))
    Tree->operations[top] = UNAR;
  else if (Tree->operations[top] == EQ)
    Tree->operations[top] = SUB;
  if (str[i] == '(') Tree->operations[top] = L_S;
  if (str[i] == ')') Tree->operations[top] = R_S;
  if (str[i] == '^') Tree->operations[top] = POW;
  if (str[i] == 'x') Tree->operations[top] = X;
  if (str[i] == 'l' && str[i + 1] == 'n')
    Tree->operations[top] = LN;  // delta = 2;
  if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd')
    Tree->operations[top] = MOD;  // delta = 3;
  if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's')
    Tree->operations[top] = COS;
  if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n')
    Tree->operations[top] = SIN;
  if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n')
    Tree->operations[top] = TAN;
  if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g')
    Tree->operations[top] = LOG;
  if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
      str[i + 3] == 'n')
    Tree->operations[top] = ASIN;  // delta = 4;
  if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
      str[i + 3] == 's')
    Tree->operations[top] = ACOS;
  if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
      str[i + 3] == 'n')
    Tree->operations[top] = ATAN;
  if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
      str[i + 3] == 't')
    Tree->operations[top] = SQRT;
  if (Tree->operations[top] <= DIV || Tree->operations[top] == POW ||
      Tree->operations[top] == X)
    delta = 1;
  else if (Tree->operations[top] == LN)
    delta = 2;
  else if (Tree->operations[top] == MOD ||
           (Tree->operations[top] >= COS && Tree->operations[top] <= TAN) ||
           Tree->operations[top] == LOG)
    delta = 3;
  else if (Tree->operations[top] >= ACOS && Tree->operations[top] <= SQRT)
    delta = 4;
  Tree->top++;
  return delta;
}
int make_number(char *numb, char *str, int i, int k) {
  numb[k] = str[i];
  numb[k + 1] = '\0';
  k++;
  return k;
}
int make_nod_from_number(char *numb, tree *Tree) {
  double n = 0;
  n = atof(numb);
  int top = Tree->top;
  if (Tree->operations[top - 1] == UNAR) {
    Tree->operations[top - 1] = NUMBER;
    Tree->numbers[top - 1] = -n;
  } else {
    Tree->numbers[top] = n;
    Tree->operations[top] = NUMBER;
    top++;
  }
  return top;
}
return_code make_input_stack2(int i, char *str, char *numb, tree *Tree, int k,
                              return_code res) {
  if (((str[i] > 47) && (str[i] < 58)) || (str[i] == '.')) {
    if (str[i] == '0' && i != 0 && str[i - 1] == '/')
      res = DIV_0;
    else
      k = make_number(numb, str, i, k);
    if (res == 1) res = make_input_stack2(i + 1, str, numb, Tree, k, res);
  } else {
    if (strcmp(numb, "") != 0) {
      Tree->top = make_nod_from_number(numb, Tree);
      strcpy(numb, "\0");
      k = 0;
    }
    int top = Tree->top;
    int delta = functions(i, str, Tree);
    if (Tree->operations[top] == SQRT && str[i + 5] == '-') res = MINUS_SQRT;
    if (delta == 0 && str[i] != '=') res = INCORRECT_INPUT;
    if ((str[i] == '(') || (str[i] == ')'))
      if ((Tree->num_o_b != Tree->num_c_b) || (Tree->num_o_b == -1))
        res = BRACKETS;
    if (i == (int)strlen(str) - 1 && res == OK) {
      if (str[i] == '=') Tree->operations[top] = EQ;
      Tree->top = ++top;
    }
    if (res == 1 && i != (int)strlen(str) - 1)
      res = make_input_stack2(i + delta, str, numb, Tree, k, res);
  }
  return res;
}

// void print_stack(tree *Tree) {
//   int i = 0;
//   while (i != Tree->top) {
//     if (Tree->operations[i] == NUMBER)
//       printf("%f\n", Tree->numbers[i]);
//     else
//       printf("%d\n", Tree->operations[i]);
//   }
// }
