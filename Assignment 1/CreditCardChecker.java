public class CreditCardChecker {
  public static void main(String[] args) {
    System.out.println("Checking \"VISA\" numbers:");
    testCheckCC(true, 4024007145523840L);
    testCheckCC(false, -4024007145523840L);
    testCheckCC(false, 402400714552383L);
    testCheckCC(false, 40240071455238409L);
    testCheckCC(false, 4024007145523841L);
    testCheckCC(false, 4024007145523850L);
    testCheckCC(false, 4024007145523830L);
    testCheckCC(true, 4924007145523833L);
    testCheckCC(true, 4914007145523835L);
    testCheckCC(true, 4999999999999996L);
    testCheckCC(false, 5000000000000009L);

    System.out.println("\nChecking \"Mastercard\" numbers:");
    testCheckCC(true, 5443125292494464L);
    testCheckCC(true, 5543125292494463L);
    testCheckCC(false, 5543125292494464L);
    testCheckCC(false, 5643125292494462L);
    testCheckCC(true, 5371782889929827L);
    testCheckCC(true, 5238977931446001L);
    testCheckCC(false, 5038977931446003L);

    System.out.println("\nChecking \"American Express\" numbers:");
    testCheckCC(true, 342854389676369L);
    testCheckCC(true, 375202466264198L);
    testCheckCC(true, 375202466264198L);

    System.out.println("\nChecking other numbers:");
    testCheckCC(false, 0);
    testCheckCC(false, 18);
    testCheckCC(false, -18);
    
    System.out.println("\nEnd of processing.");
  }
  
  public static void testCheckCC(boolean expected, long num) {
    boolean result = checkCC(num);
    
    if (result == expected) {
      System.out.println("Passed: " + result + " for " + num);
    } else {
      System.out.println("FAILED: " + result + " instead of " + expected + " for " + num);
    }
  }
  
  public static boolean checkCC(long num) {
    return num > 0 && checkType(num) && luhnDigit(num / 10) == num % 10;
  }
  
  public static boolean checkType(long num) {
    long leftmost;
    boolean valid = false;
    if (num >= 100000000000000L && num < 1000000000000000L) {
      // 15 digits, must be amex
      leftmost = num / 10000000000000L;
      valid = leftmost == 34 || leftmost == 37;
    } else if (num >= 1000000000000000L && num < 10000000000000000L) {
      // 16 digits, visa or m/c
      leftmost = num / 100000000000000L;
      valid = (leftmost / 10 == 4) || ((leftmost >= 51) && (leftmost <= 55));
    }
    return valid;
  }
  
  public static int luhnDigit(long num) {
    long sum = 0, digit;
    boolean doubled = true;

    num = Math.abs(num);
    while (num > 0) {
      digit = num % 10;
      if (doubled) {
        digit *= 2;
        if (digit >= 10) {
          digit -= 9;
        }
      }
      sum += digit;
      doubled = !doubled;
      num = num / 10;
    }

    return (int)((10 - (sum  % 10)) % 10);
  }
}