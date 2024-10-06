#include "s21_smart_calc.h"

void to_final_number(tree *Pofixtree, tree *Final, int here) {
  int top_f = Final->top;
  Final->operations[top_f] = NUMBER;
  Final->numbers[top_f] = Pofixtree->numbers[here];
  Final->top++;
  Pofixtree->operations[here] = 0;
  Pofixtree->numbers[here] = 0;
}
void to_final_2_function(tree *Final, operation op) {
  double process = 0;
  int top = Final->top;
  double n2 = Final->numbers[top - 1];
  double n1 = Final->numbers[top - 2];
  switch (op) {
    case SUM:
      process = n1 + n2;
      break;
    case SUB:
      process = n1 - n2;
      break;
    case MUL:
      process = n1 * n2;
      break;
    case DIV:
      process = n1 / n2;
      break;
    case MOD:
      process = fmod(n1, n2);
      break;
    case POW:
      process = pow(n1, n2);
      break;
    default:
      break;
  }
  Final->numbers[top - 2] = process;
  Final->operations[top - 2] = 0;
  Final->numbers[top - 1] = 0;
  Final->operations[top - 1] = 0;
  Final->top--;
}
void to_final_1_function(tree *Final, operation op, return_code *res) {
  int top = Final->top;
  double process = 0;
  double n1 = Final->numbers[top - 1];
  switch (op) {
    case COS:
      process = cos(n1);
      break;
    case SIN:
      process = sin(n1);
      break;
    case TAN:
      process = tan(n1);
      break;
    case ACOS:
      process = acos(n1);
      break;
    case ASIN:
      process = asin(n1);
      break;
    case ATAN:
      process = atan(n1);
      break;
    case SQRT:
      if (n1 < 0)
        *res = MINUS_SQRT;
      else
        process = sqrt(n1);
      break;
    case LN:
      if (n1 <= 0)
        *res = MINUS_LOG;
      else
        process = log(n1);
      break;
    case LOG:
      if (n1 <= 0)
        *res = MINUS_LOG;
      else
        process = log10(n1);
      break;
    default:
      break;
  }
  Final->numbers[top - 1] = process;
}
return_code processing_expression(tree *PofixTree, tree *Final,
                                  return_code *res, int here) {
  if (PofixTree->operations[here] == NUMBER)
    to_final_number(PofixTree, Final, here);
  if (PofixTree->operations[here] >= SUM && PofixTree->operations[here] <= POW)
    to_final_2_function(Final, PofixTree->operations[here]);
  if (PofixTree->operations[here] >= COS && PofixTree->operations[here] <= LOG)
    to_final_1_function(Final, PofixTree->operations[here], res);
  if (PofixTree->top - 1 != here && *res == OK) {
    PofixTree->operations[here] = 0;
    PofixTree->numbers[here] = 0;
    processing_expression(PofixTree, Final, res, here + 1);
  }
  return *res;
}

return_code make_chislo(tree *PofixTree, double *result) {
  tree *Final = malloc(sizeof(tree));
  make_tree(Final);
  return_code res = OK;
  res = processing_expression(PofixTree, Final, &res, 0);
  if (res == OK) *result = Final->numbers[0];
  free(Final);
  return res;
}
