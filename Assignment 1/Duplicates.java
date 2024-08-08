public class Duplicates {
  private static int testsExecuted = 0;
  private static int testsFailed = 0;

  private static final int MAX_WORD_LENGTH=15;

  public static void main(String[] args) {
    System.out.println("Testing typical cases\n");
    testCountDuplicateWords(0, "hello world");
    testCountDuplicateWords(0, "bye-bye");
    testCountDuplicateWords(1, "the quick brown foxes jumped over the lazy dogs");
    testCountDuplicateWords(0, "The quick brown foxes jumped over the lazy dogs");
    testCountDuplicateWords(2, "A palindrome: a man a plan a canal panama");
    testCountDuplicateWords(8, "I felt happy because I saw the others were happy and because I knew I should feel happy but I wasn’t really happy");
    testCountDuplicateWords(3, "One fish two fish\nred fish blue\nfish");
    testCountDuplicateWords(5, "doo be \t doo be \t doo be \t  doo");
    testCountDuplicateWords(8, "... -- -- -- ...\n... -- -- -- ...");
    testCountDuplicateWords(26, "a b c d e f g h i j k l m n o p q r s t u v w x y z a b c d e f g h i j k l m n o p q r s t u v w x y z");

    System.out.println("\nTesting empty cases\n");
    testCountDuplicateWords(0, "");
    testCountDuplicateWords(0, " ");
    testCountDuplicateWords(0, "\t \t");
    testCountDuplicateWords(0, "   \n  \n  ");

    System.out.println("\nTesting invalid cases\n");
    testCountDuplicateWords(-1, "the word antidisestablishmentarianism is very long but antidisestablishmentarianism is a political movement");
    testCountDuplicateWords(-1, "abcdefghijabcdef");
    testCountDuplicateWords(0, "abcdefghijabcde");

    System.out.println("\nTesting edge cases\n");
    testCountDuplicateWords(1, "go Jets go");
    testCountDuplicateWords(2, "tomato tomato potato potato");
    testCountDuplicateWords(2, " tomato tomato potato potato ");
    testCountDuplicateWords(7, "buffalo buffalo buffalo buffalo buffalo buffalo buffalo buffalo");

    System.out.println("\nThese tests will be opposite in the C version\n");
    testCountDuplicateWords(1, "In Java, the strings may contain \0 in the interior");
    testCountDuplicateWords(0, "In C, the strings cannot contain \0 in the interior");
  
    System.out.println("\nTotal number of tests executed: " + testsExecuted);
    System.out.println("Number of tests passed:         " + (testsExecuted - testsFailed));
    System.out.println("Number of tests failed:         " + testsFailed);
  }

  private static void testCountDuplicateWords(int expected, String str) {
    int result = countDuplicateWords(str);
    
    if (result == expected) {
      System.out.println("Passed: " + result + " from '" + str + "'");
    } else {
      System.out.println("FAILED: " + result + " instead of " + expected + " from '" + str + "'");
      testsFailed++;
    }
    
    testsExecuted++;
  }

  public static int countDuplicateWords(String str) {
    int count = 0;
    String word = "";
    int pos;
    char currentChar;
    
    pos = 0;
    while (pos < str.length() && count >= 0) {
      currentChar = str.charAt(pos);
      if (Character.isWhitespace(currentChar)) {
        if (word.length() > 0) {
          if (findWord(str.substring(pos), word)) {
            count++;
          }
          word = "";
        }
      } else {
        if (word.length() >= MAX_WORD_LENGTH) {
          count = -1;
        } else {
          word += currentChar;
        }
      }
      pos++;
    }
    
    return count;
  }
  
  private static boolean findWord(String str, String word) {
    String checkWord = "";
    int checkPos = 0;
    boolean dontCheckWord, found = false;
    char checkChar;

    dontCheckWord = false;
    while (checkPos < str.length() && !found) {
      checkChar = str.charAt(checkPos);
      if (Character.isWhitespace(checkChar)) {
        if (word.equals(checkWord) && !dontCheckWord) {
          found = true;
        }
        dontCheckWord = false;
        checkWord = "";
      } else {
        if (checkWord.length() >= word.length()) {
          dontCheckWord = true;
        } else {
          checkWord += checkChar;
        }
      }
      checkPos++;
    }
    
    if (!found && !dontCheckWord && word.length() > 0)
      found = word.equals(checkWord);
    
    return found;
  }
}