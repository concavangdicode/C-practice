#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define TRUE_WORD "true"
#define FALSE_WORD "false"

// This will not compile until you write a check_cc() function

int luhnDigit(long long int num){
   long long int sum = 0, digit; 
   bool doubled = TRUE; 
   
   num = llabs(num);
   while(num > 0){
     digit = num % 10; 
     if(doubled){
        digit *= 2;
        if(digit >= 10){
          digit -= 9;
        }
     }
     sum += digit;
     doubled = !doubled;
     num = num / 10;
   }

   return (int)((10 - (sum % 10)) % 10);
}

bool checkType(long long int num){
   long long int leftmost;
   bool valid = false;
   if(num > 100000000000000L && num < 1000000000000000L){
     leftmost = num / 10000000000000L;
     valid = leftmost == 34 || leftmost == 37;
   }
   else if(num >= 1000000000000000L && num < 10000000000000000L){
     leftmost = num / 100000000000000L;
     valid = (leftmost / 10 == 4) || ((leftmost >= 51) && (leftmost <= 55));
   }
   return valid;
}

int check_cc(long long int num){
    if(num > 0 && checkType(num) && luhnDigit(num / 10) == num % 10){
       return TRUE;
    }
    return FALSE;
}
void test_check_cc(int expected, long long int num) {
  int result = check_cc(num);
  char *expected_word = FALSE_WORD, *result_word = FALSE_WORD;
  
  if (expected) {
    expected_word = TRUE_WORD;
  }
  if (result) {
    result_word = TRUE_WORD;
  }
  
  if (result == expected) {
    printf("Passed: %s for %lld\n", result_word, num);
  } else {
    printf("FAILED: %s instead of %s for %lld\n", result_word, expected_word, num);
  }
 }


int main() {
  printf("Checking \"VISA\" numbers:\n");
  test_check_cc(TRUE, 4024007145523840L);
  test_check_cc(FALSE, -4024007145523840L);
  test_check_cc(FALSE, 402400714552383L);
  test_check_cc(FALSE, 40240071455238409L);
  test_check_cc(FALSE, 4024007145523841L);
  test_check_cc(FALSE, 4024007145523850L);
  test_check_cc(FALSE, 4024007145523830L);
  test_check_cc(TRUE, 4924007145523833L);
  test_check_cc(TRUE, 4914007145523835L);
  test_check_cc(TRUE, 4999999999999996L);
  test_check_cc(FALSE, 5000000000000009L);

  printf("\nChecking \"Mastercard\" numbers:\n");
  test_check_cc(TRUE, 5443125292494464L);
  test_check_cc(TRUE, 5543125292494463L);
  test_check_cc(FALSE, 5543125292494464L);
  test_check_cc(FALSE, 5643125292494462L);
  test_check_cc(TRUE, 5371782889929827L);
  test_check_cc(TRUE, 5238977931446001L);
  test_check_cc(FALSE, 5038977931446003L);

  printf("\nChecking \"American Express\" numbers:\n");
  test_check_cc(TRUE, 342854389676369L);
  test_check_cc(TRUE, 375202466264198L);
  test_check_cc(TRUE, 375202466264198L);

  printf("\nChecking other numbers:\n");
  test_check_cc(FALSE, 0);
  test_check_cc(FALSE, 18);
  test_check_cc(FALSE, -18);
  
  printf("\nEnd of processing.\n");
  
  return 0;
}
