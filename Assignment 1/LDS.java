import java.util.Arrays;

public class LDS {
  public static void main(String[] args) {
    testLDS(3, new int[] { 1, 5, 3, 7, 9, 1, 3, 7, 5, 3, 7, 1, 9 });
    testLDS(4, new int[] { 3, 4, 1, 2, 4, 1, 2, 4, 3 });
    testLDS(0, new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    testLDS(1, new int[] { 1, 2, 3, 4, 5, 10, 6, 7, 8, 9, 10 });
    testLDS(5, new int[] { 1, 2, 3, 4, 5, 6, 1, 2, 1, 2, 3, 4, 5, 1, 2, 3, 4 });
    testLDS(11, new int[] { 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 });
    testLDS(4, new int[] { 1, 1, 1, 1, 1 });
    testLDS(0, new int[] { });
    
    System.out.println("\n*** End of program. ***");
  }
  
  public static void testLDS(int expected, int[] array) {
    String arrayString = Arrays.toString(array);
    int result = longestDuplicateSubsequence(array);

    if (expected == result) {
      System.out.printf("Test succeeded: %s\n", arrayString);
    } else {
      System.out.printf("Test FAILED (expected %s, got %s): %s\n", expected, result, arrayString);
    }
  }

  public static int longestDuplicateSubsequence(int[] array) {
    return ldsR(array, 0, 0, 0);
  }
  
  public static int ldsR(int[] array, int pOrig, int pDup, int attempt) {
    int best;

    if (pOrig >= array.length || pDup >= array.length) {
      return attempt;
    }

    if (pOrig == pDup) {
      best = ldsR(array, pOrig + 1, pDup + 1, 0);
    } else if (array[pOrig] == array[pDup]) {
      best = Math.max(attempt, ldsR(array, pOrig + 1, pDup + 1, attempt + 1));
    } else {
      best = attempt;
    }
    
    attempt = ldsR(array, pOrig, pDup + 1, 0);
    
    return Math.max(attempt, best);
  }
}