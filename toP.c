#include "s21_smart_calc.h"

void stack_brakets(tree *Stack, tree *PofixTree) {
  int top_s = Stack->top - 1;
  int top_p = PofixTree->top;
  while (Stack->operations[top_s] != L_S) {
    PofixTree->operations[top_p] = Stack->operations[top_s];
    PofixTree->numbers[top_p] = Stack->numbers[top_s];
    top_p++;
    PofixTree->top++;
    top_s--;
    Stack->top--;
    Stack->numbers[top_s + 1] = 0;
    Stack->operations[top_s + 1] = 0;
  }
  if (Stack->operations[top_s] == L_S) {
    top_s--;
    Stack->top--;
    Stack->numbers[top_s + 1] = 0;
    Stack->operations[top_s + 1] = 0;
  }
}
void polish_end(tree *Stack, tree *PofixTree) {
  int top_s = Stack->top - 1;
  int top_p = PofixTree->top;
  if (top_s + 1 != 0)
    while (top_s + 1 != 0) {
      PofixTree->operations[top_p] = Stack->operations[top_s];
      PofixTree->numbers[top_p] = 0;
      top_p++;
      PofixTree->top++;
      top_s--;
      Stack->top--;
      Stack->numbers[top_s + 1] = 0;
      Stack->operations[top_s + 1] = 0;
    }
}
void pofix_nod(tree *Tree, tree *PofixTree, tree *Stack, return_code *res,
               int here) {
  int top_p = PofixTree->top;
  int top_s = Stack->top;
  if (here != 0 && Tree->operations[here - 1] > 4 &&
      Tree->operations[here] > 4 && Tree->operations[here] < 10)
    *res = TWO_OPER_TOGETHER;
  if (here != 0 && Tree->operations[here - 1] > 8 &&
      Tree->operations[here - 1] < 20 && Tree->operations[here] > 8 &&
      Tree->operations[here] < 20)
    *res = TWO_OPER_TOGETHER;
  if (*res == OK) {
    int operator= 1;
    if (Tree->operations[here] == NUMBER) {
      PofixTree->numbers[top_p] = Tree->numbers[here];
      PofixTree->operations[top_p] = NUMBER;
      PofixTree->top++;
      top_p++;
    } else if (Tree->operations[here] == R_S) {
      if (Tree->operations[here - 1] == L_S)
        *res = INCORRECT_INPUT;
      else
        stack_brakets(Stack, PofixTree);
    } else {
      if ((Tree->operations[here] == SUM) || (Tree->operations[here] == SUB))
        operator= 5;
      if ((Tree->operations[here] == MUL) || (Tree->operations[here] == DIV) ||
          (Tree->operations[here] == MOD))
        operator= 7;
      if ((Tree->operations[here] >= POW) && (Tree->operations[here] != EQ))
        operator= 10;
      if (top_s != 0) {
        while (top_s != 0 &&
               Stack->operations[top_s - 1] >= (operation) operator&&
                                               Tree->operations[here] != L_S &&
                                               Tree->operations[here] != R_S) {
          PofixTree->operations[top_p] = Stack->operations[top_s - 1];
          PofixTree->numbers[top_p] = Stack->numbers[top_s - 1];
          PofixTree->top++;
          Stack->operations[top_s - 1] = 0;
          Stack->numbers[top_s - 1] = 0;
          Stack->top--;
          top_s--;
        }
      }
      if (Tree->operations[here] != EQ) {
        Stack->numbers[top_s] = Tree->numbers[here];
        Stack->operations[top_s] = Tree->operations[here];
        top_s++;
        Stack->top++;
      }
    }
    if (Tree->operations[here + 1] != EQ)
      pofix_nod(Tree, PofixTree, Stack, res, here + 1);
    else {
      if (Tree->operations[here] > 4 && Tree->operations[here] < 21)
        *res = INCORRECT_INPUT;
      else
        polish_end(Stack, PofixTree);
    }
  }
}
return_code to_pofix(tree *PofixTree, tree *Tree, double *result) {
  tree *Stack = malloc(sizeof(tree));
  ;
  make_tree(Stack);
  return_code res = OK;
  pofix_nod(Tree, PofixTree, Stack, &res, 0);
  if (res == OK) res = make_chislo(PofixTree, result);
  free(Stack);
  return res;
}
