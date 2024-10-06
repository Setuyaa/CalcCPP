#include "s21_smart_calc.h"

void print_error(return_code res) {
  switch (res) {
    case BRACKETS:  // 3 brackets
      printf("Incorrect input brackets!\n");
      break;
    case INCORRECT_INPUT:  // 4 incorrect input
      printf("Unknown expression!\n");
      break;
    case DIV_0:  // 5 ДЕЛЕНИЕ НА 0
      printf("Division by 0!\n");
      break;
    case MINUS_SQRT:  // 6 МИНУС В КОРНЕ
      printf("Negative value under the sqrt!\n");
      break;
    case MINUS_LOG:  // 7
      printf("Negative value under the log!\n");
      break;
    case TWO_OPER_TOGETHER:  // 8
      printf("Two operands stand together!\n");
      break;
    default:
      break;
  }
}
