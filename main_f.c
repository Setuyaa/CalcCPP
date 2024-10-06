#include "s21_smart_calc.h"

void make_tree(tree *Tree) {
  Tree->num_c_b = 0;
  Tree->num_o_b = 0;
  Tree->top = 0;
  for (int i = 0; i < 256; i++) {
    Tree->numbers[i] = 0;
    Tree->operations[i] = 0;
  }
}

int main_f(char *str, double *result) {
  char numb[256];
  strcpy(numb, "");
  tree *Tee = malloc(sizeof(tree));
  make_tree(Tee);
  calculate_brackets(Tee, str);
  return_code res = make_input_stack2(0, str, numb, Tee, 0, 1);
  if (res == OK) {
    tree *PofixTree = malloc(sizeof(tree));
    make_tree(PofixTree);
    res = to_pofix(PofixTree, Tee, result);
    *result = round(*result * 1000000) / 1000000;  //
    if (res != OK) {
      print_error(res);
    } else
      printf("Result %f\n", *result);
    free(PofixTree);
  } else
    print_error(res);
  free(Tee);
  return res;
}

// int main() {
//   char numb[256];
//   char* str="cos(0)=";
//   strcpy(numb, "");
//   tree *Tee = malloc(sizeof(tree));
//   make_tree(Tee);
//   double *result = NULL;
//   calculate_brackets(Tee, str);
//   printf("Result %f\n", *result);
//   return_code res = make_input_stack2(0, str, numb, Tee, 0, 1);
//   if (res == OK) {
//     tree *PofixTree = malloc(sizeof(tree));
//      make_tree(PofixTree);
//     res = to_pofix(PofixTree, Tee, result);
//     if (res != OK) {
//       print_error(res);
//     } else
//       printf("Result %f\n", *result);
//     free(PofixTree);
//   } else {
//     print_error(res);
//     free(Tee);
//   }
//  // return res;
// }
