#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

const int MAX_WORD_LENGTH = 15;
static int testsExecuted = 0;
static int testsFailed = 0;


char *substring(int start, char *origin){
    return &origin[start];
}

bool findWord (char *str, char *word){
    int maxLength = 50;
    char checkWord[maxLength]; 
    int keepTrack = 0;
    int checkPos = 0;
    bool dontCheckWord, found = false; 
    char checkChar; 

    dontCheckWord = false;
    while(str[checkPos] != '\0' && !found){
        checkChar = str[checkPos];
        if(isspace(checkChar)){
            if((strcmp(word, checkWord) == 0) && !dontCheckWord){
                found = true;
            }
            dontCheckWord = false;
            checkWord[0] = '\0';
            keepTrack = 0;
        }
        else{
            if(strlen(checkWord) >= strlen(word)){
                dontCheckWord = true;
            }
            else{
                checkWord[keepTrack++] = checkChar;
                checkWord[keepTrack] = '\0';
            }
        }
        checkPos++;
    }
    if(!found && !dontCheckWord && strlen(word) > 0){
        found = (strcmp(word, checkWord) == 0);
    }
    return found;
}

int countDuplicateWords(char *str){
    int count = 0; 
    int pos;
    char currentChar; 
    int lengthWord = 16;
    char word[50];
    int keepTrack = 0; //index word

    pos = 0; 
    while(str[pos] != '\0' && count >= 0){
        currentChar = str[pos]; 
        if(isspace(currentChar)){
            if(strlen(word) > 0){
                if(findWord(substring(pos, str), word)){
                    count++;
                }
                word[0] = '\0';
                keepTrack = 0;
            }
        }
        else{
            if(strlen(word) >= MAX_WORD_LENGTH){
                count = -1;
            }
            else{
                word[keepTrack++] = currentChar;
                word[keepTrack] = '\0';
            }
        }
        pos++;
    }
    return count;
}

void testCountDuplicateWords(int expected, char *str){
    int result = countDuplicateWords(str); 

    if(result == expected){
        printf("Pass: %d from '%s'\n", result, str);
    }
    else{
        printf("Failed: %d instead of %d from '%s'\n", result, expected, str);
        testsFailed++;
    }
    testsExecuted++;
}


int main(void){
    printf("Testing typical cases\n");
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

    printf("\nTesting empty cases\n");
    testCountDuplicateWords(0, "");
    testCountDuplicateWords(0, " ");
    testCountDuplicateWords(0, "\t \t");
    testCountDuplicateWords(0, "   \n  \n  ");

    printf("\nTesting invalid cases\n");
    testCountDuplicateWords(-1, "the word antidisestablishmentarianism is very long but antidisestablishmentarianism is a political movement");
    testCountDuplicateWords(-1, "abcdefghijabcdef");
    testCountDuplicateWords(0, "abcdefghijabcde");

    printf("\nTesting edge cases\n");
    testCountDuplicateWords(1, "go Jets go");
    testCountDuplicateWords(2, "tomato tomato potato potato");
    testCountDuplicateWords(2, " tomato tomato potato potato ");
    testCountDuplicateWords(7, "buffalo buffalo buffalo buffalo buffalo buffalo buffalo buffalo");

    printf("\nThese tests will be opposite in the C version\n");
    testCountDuplicateWords(1, "In Java, the strings may contain \0 in the interior");
    testCountDuplicateWords(0, "In C, the strings cannot contain \0 in the interior");
  
    printf("\nTotal number of tests executed: %d\n", testsExecuted);
    printf("Number of tests passed:         %d\n", (testsExecuted - testsFailed));
    printf("Number of tests failed:         %d\n", testsFailed);
    return 0;
}
