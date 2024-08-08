import java.util.Scanner;

public class Solver {
  public static final int MAX_COUNT = 30;

  public static void main(String args[]) {
    int count = 0, target;
    int[] array, solution;
    int solutionCount;

    Scanner stdin = new Scanner(System.in);

    while (stdin.hasNextLine()) {   
      count = stdin.nextInt();
      if (count > MAX_COUNT) {
        System.err.println("Invalid count: " + count + ".");
      } else {
        array = new int[count];
        for (int i = 0; i < count; i++) {
          array[i] = stdin.nextInt();
        }
        target = stdin.nextInt();

        solution = new int[count];
        reverseSort(array);
        solutionCount = solve(array, solution, target);
    
        if (solutionCount > 0) {
          for (int i = 0; i < solutionCount; i++) {
            System.out.print(solution[i] + " ");
          }
          System.out.println();
        } else {
          System.out.println("Count = " + count + ": no solution.");
        }
      }
      stdin.nextLine(); // get rid of the newline at the end
    }
    
    stdin.close();
    
    System.out.println("\nEnd of processing.");
    System.exit(0);
  }
  
  public static void reverseSort(int[] array) {
    int max, maxPos;
    for (int i = 0; i < array.length-1; i++) {
      max = array[i];
      maxPos = -1;
      for (int j = i+1; j < array.length; j++) {
        if (array[j] > max) {
          max = array[j];
          maxPos = j;
        }
      }
      if (maxPos > 0) {
        array[maxPos] = array[i];
        array[i] = max;
      }
    }
  }
  
  public static int solve(int[] array, int[] solution, int target) {
    return rsolve(array, array.length, solution, 0, 0, target);
  }

  public static int rsolve(int[] array, int unprocessed, int[] solution, int solutionCount, int soFar, int target) {
    int lastPos, result;
    
    if (soFar == target) {
      result = solutionCount;
    } else if (unprocessed == 0) {
      result = 0;
    } else {
      lastPos = unprocessed - 1;
      result = rsolve(array, lastPos, solution, solutionCount, soFar, target);
      if (result == 0 && soFar+array[lastPos] <= target) {
        solution[solutionCount] = array[lastPos];
        result = rsolve(array, unprocessed-1, solution, solutionCount+1, soFar+array[lastPos], target);
      }
    }
    
    return result;
  }
} 