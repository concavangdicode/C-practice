public class Reverser {
  private static int testsExecuted = 0;
  private static int testsFailed = 0;

  public static void main(String[] args) {
    System.out.println("Testing typical cases:\n");
    testReverseWords("olleh", "hello");
    testReverseWords("olleh dlrow", "hello world");
    testReverseWords("olleH, dlroW", "Hello, World");
    testReverseWords("eht kciuq nworb sexof depmuj revo eht yzal sgod", "the quick brown foxes jumped over the lazy dogs");
    testReverseWords("12345", "54321");
    testReverseWords("ysaE sa 321cba", "Easy as abc123");
    testReverseWords("ysaE  sa    321cba", "Easy  as    abc123");
    testReverseWords("ysaE... sa\tcba,321", "Easy... as\tabc,123");

    System.out.println("\nTesting empty cases:\n");
    testReverseWords("", "");
    testReverseWords("!", "!");
    testReverseWords(" ", " ");
    testReverseWords("\t", "\t");
    testReverseWords("      ", "      ");
    testReverseWords("# $ ? % !", "# $ ? % !");
    testReverseWords("!@#$%^&*()", "!@#$%^&*()");

    System.out.println("\nTesting edge cases:\n");
    testReverseWords("a", "a");
    testReverseWords(" cba ", " abc ");
    testReverseWords("? cba ?", "? abc ?");
    testReverseWords(" \"cba fed!\" ", " \"abc def!\" ");
    testReverseWords("a b c d efg", "a b c d gfe");
    testReverseWords("abc d e f g", "cba d e f g");

    System.out.println("\nTesting special cases:\n");
    testReverseWords("enil 1\n enil 2", "line 1\n line 2");
    testReverseWords("nI avaJ, eht sgnirts yam niatnoc \0 ni eht roiretni", "In Java, the strings may contain \0 in the interior");

    System.out.println("\nThis test will be opposite in the C version:\n");
    testReverseWords("tI saw eht tseb fo semit, ti saw eht tsrow fo semit, ti saw eht ega fo modsiw, ti saw eht ega fo ssenhsiloof, ti saw eht hcope fo feileb, ti saw eht hcope fo ytiludercni, ti saw eht nosaes fo thgiL, ti saw eht nosaes fo ssenkraD, ti saw eht gnirps fo epoh, ti saw eht retniw fo riapsed, ew dah gnihtyreve erofeb su, ew dah gnihton erofeb su, ew erew lla gniog tcerid ot nevaeH, ew erew lla gniog tcerid eht rehto yaw - ni trohs, eht doirep saw os raf ekil eht tneserp doirep, taht emos fo sti tseision seitirohtua detsisni no sti gnieb deviecer, rof doog ro rof live, ni eht evitalrepus eerged fo nosirapmoc ylno.", "It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way - in short, the period was so far like the present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.");
    testReverseWords("tI saw eht tseb fo semit, ti saw eht tsrow fo semit, ti saw eht ega fo modsiw, ti saw eht ega fo ssenhsiloof, ti saw eht hcope fo feileb, ti saw eht hcope fo ytiludercni, ti saw eht nosaes fo thgiL, ti saw eht nosaes fo ssenkraD, ti saw eht gnirps fo epoh", "It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way - in short, the period was so far like the present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.");
  
    System.out.println("\nTotal number of tests executed: " + testsExecuted);
    System.out.println("Number of tests passed:         " + (testsExecuted - testsFailed));
    System.out.println("Number of tests failed:         " + testsFailed);
  }
  
  public static void testReverseWords(String expected, String line) {
    String result = reverseWords(line);
    
    if (result.equals(expected)) {
      System.out.println("Passed: '" + result + "' from '" + line + "'");
    } else {
      System.out.println("FAILED: '" + result + "' instead of '" + expected + "' from '" + line + "'");
      testsFailed++;
    }
    
    testsExecuted++;
  }
  
  public static String reverseWords(String line) {
    int pos = 0, next;
    String reversedLine = "";
    String reversedWord = "";
    
    while (pos >= 0 && pos < line.length()) {
      next = findWordStart(line, pos);
      if (next < 0) {
        reversedLine += line.substring(pos);
      } else {
        reversedLine += line.substring(pos, next);
        pos = next;
        next = findWordEnd(line, pos + 1);
        if (next < 0) {
          reversedLine += new StringBuilder(line.substring(pos)).reverse();
        } else {
          reversedLine += new StringBuilder(line.substring(pos, next)).reverse();
        }
      }
      pos = next;
    }
    
    return reversedLine;
  }

  public static int findWordStart(String line, int pos) {
    while (pos < line.length() && !Character.isLetterOrDigit(line.charAt(pos))) {
      pos++;
    }
    if (pos >= line.length()) {
      return -1;
    } else {
      return pos;
    }
  }
  
  public static int findWordEnd(String line, int pos) {
    while (pos < line.length() && Character.isLetterOrDigit(line.charAt(pos))) {
      pos++;
    }
    if (pos >= line.length()) {
      return -1;
    } else {
      return pos;
    }
  }
}