#include <stdio.h>
#include <ctype.h>
#include <string.h>

static int testsExecuted = 0; 
static int testsFailed = 0;

int findWordStart(char *line, int pos, int length){
    while(pos < length && !isalnum(line[pos])){
        pos++;
    }
    if(pos >= length){
        return -1;
    }
    else{
        return pos;
    }
}

int findWordEnd(char *line, int pos, int length){
    while(pos < length && isalnum(line[pos])){
        pos++;
    }
    if(pos >= length){
        return -1;
    }
    else{
        return pos;
    }
}

void substring1(char *line, int pos, char *substring){
    int keepTrack = 0;
    for(int i = 0; i < strlen(line); i++){
        substring[keepTrack++] = line[pos + i];
    }
    substring[keepTrack] = '\0';
}

void substring2(char *line, int pos, int next, char *substring){
    int keepTrack = 0;
    for(int i = pos; i < next; i++){
        substring[keepTrack++] = line[i]; 
    }
    substring[keepTrack] = '\0';
}

void reverseWord(char *line, char *reversedLine, int length){
    int pos = 0, next = 0; 
    int maxLength = 1000;
    char substring[maxLength];
    char subrev[maxLength]; 
    memset(subrev, '\0', maxLength);  
    memset(substring, '\0', maxLength); 

    while(pos >= 0 && pos < length){
        next = findWordStart(line, pos, length);
        
        if(next < 0){
            substring1(line, pos, substring);
            strcat(reversedLine, substring);
        }
        else{
            substring2(line, pos, next, substring);
            strcat(reversedLine, substring);
            pos = next; 
            next = findWordEnd(line, pos, length);
            
            if(next < 0){
                substring1(line, pos, subrev); 
                strcat(reversedLine, strrev(subrev));
            }
            else{
                substring2(line, pos, next, subrev);
                strcat(reversedLine, strrev(subrev));
            }          
        }  
        pos = next;  
        memset(subrev, '\0', maxLength);  
        memset(substring, '\0', maxLength); 
    }
    reversedLine[length] = '\0';
}

void testReverseWords(char *expected, char *line){
    char result[1000];
    //result[0] = '\0';
    memset(result, '\0', 1000);
    int length = strlen(line); 
    reverseWord(line, result, length);

    if(strcmp(result, expected) == 0){
        printf("Pass: '%s' from '%s'\n", result, line);
    }
    else{
        printf("FAILED: '%s' instead of '%s' from '%s'\n", result, expected, line);
        testsFailed++;
    }
    testsExecuted++;
}

int main(){
    printf("Testing typical cases:\n");
    testReverseWords("olleh", "hello");
    testReverseWords("olleh dlrow", "hello world");
    testReverseWords("olleH, dlroW", "Hello, World");
    testReverseWords("eht kciuq nworb sexof depmuj revo eht yzal sgod", "the quick brown foxes jumped over the lazy dogs");
    testReverseWords("12345", "54321");
    testReverseWords("ysaE sa 321cba", "Easy as abc123");
    testReverseWords("ysaE  sa    321cba", "Easy  as    abc123");
    testReverseWords("ysaE... sa\tcba,321", "Easy... as\tabc,123");

    printf("\nTesting empty cases:\n");
    testReverseWords("", "");
    testReverseWords("!", "!");
    testReverseWords(" ", " ");
    testReverseWords("\t", "\t");
    testReverseWords("      ", "      ");
    testReverseWords("# $ ? % !", "# $ ? % !");
    testReverseWords("!@#$%^&*()", "!@#$%^&*()");

    printf("\nTesting edge cases:\n");
    testReverseWords("a", "a");
    testReverseWords(" cba ", " abc ");
    testReverseWords("? cba ?", "? abc ?");
    testReverseWords(" \"cba fed!\" ", " \"abc def!\" ");
    testReverseWords("a b c d efg", "a b c d gfe");
    testReverseWords("abc d e f g", "cba d e f g");

    printf("\nTesting special cases:\n");
    testReverseWords("enil 1\n enil 2", "line 1\n line 2");
    testReverseWords("nI avaJ, eht sgnirts yam niatnoc \0 ni eht roiretni", "In Java, the strings may contain \0 in the interior");

    printf("\nThis test will be opposite in the C version:\n");
    testReverseWords("tI saw eht tseb fo semit, ti saw eht tsrow fo semit, ti saw eht ega fo modsiw, ti saw eht ega fo ssenhsiloof, ti saw eht hcope fo feileb, ti saw eht hcope fo ytiludercni, ti saw eht nosaes fo thgiL, ti saw eht nosaes fo ssenkraD, ti saw eht gnirps fo epoh, ti saw eht retniw fo riapsed, ew dah gnihtyreve erofeb su, ew dah gnihton erofeb su, ew erew lla gniog tcerid ot nevaeH, ew erew lla gniog tcerid eht rehto yaw - ni trohs, eht doirep saw os raf ekil eht tneserp doirep, taht emos fo sti tseision seitirohtua detsisni no sti gnieb deviecer, rof doog ro rof live, ni eht evitalrepus eerged fo nosirapmoc ylno.", "It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way - in short, the period was so far like the present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.");
    testReverseWords("tI saw eht tseb fo semit, ti saw eht tsrow fo semit, ti saw eht ega fo modsiw, ti saw eht ega fo ssenhsiloof, ti saw eht hcope fo feileb, ti saw eht hcope fo ytiludercni, ti saw eht nosaes fo thgiL, ti saw eht nosaes fo ssenkraD, ti saw eht gnirps fo epoh", "It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way - in short, the period was so far like the present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.");

    printf("\nTotal number of tests executed: %d\n", testsExecuted);
    printf("Number of tests passed:         %d\n", (testsExecuted - testsFailed));
    printf("Number of tests failed:         %d\n", testsFailed);
}   