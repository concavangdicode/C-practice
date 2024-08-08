#include "index_list.h"
#include <stdio.h>
#include <string.h>

int Tests_Passed = 0;
int Tests_Failed = 0;

#define VERIFY(e,t) verify(e, t, #t)

void verify(int expected, int result, char test[]){
    if(expected == result){
        printf("Passed: expected %d, got %d for: %s\n", expected, result, test);
        Tests_Passed++;
    } 
    else{
        printf("FAILED: expected %d, got %d for: %s\n", expected, result, test);
        Tests_Failed++;
    }
}

void test_insertion(List *new_list){
    printf("\n*** Testing insertion:\n");
    VERIFY(1, insert(new_list, "abc")); 
    VERIFY(1, insert(new_list, "a'd&#@sa")); 
    VERIFY(1, insert(new_list, "156+5^$#@45458")); 
    VERIFY(1, insert(new_list, "IhatetHiscOuRse bcuz iT's sO haRd")); 
    VERIFY(1, insert(new_list, "Iamsdw")); 
    VERIFY(1, insert(new_list, "Fak you")); 
    VERIFY(0, insert(new_list, "~`!@#$^&*()_+}{|?><"":;/*-+}ì")); 
    VERIFY(0, insert(new_list, "À~H‹E‹UàH‹MØH‰LÐ‹"));
    VERIFY(0, insert(new_list, "ƒÀ‰P@USHƒì8Hl$0H‰M H‰U(L‰E0L‰M8HE(H‰EðH‹]ð¹   H‹ "));
    VERIFY(0, insert(new_list, "유 니 코 드 로 하십시오 제10회"));
    VERIFY(0, insert(new_list, "sja1세bd@)!계를"));
    VERIFY(1, insert(new_list, "apple")); 
    VERIFY(1, insert(new_list, "egg")); 
    VERIFY(1, insert(new_list, "nuke the uofm")); 
    VERIFY(1, insert(new_list, "dit me truong concac uofm")); 
    VERIFY(1, insert(new_list, "an cuop giua ban ngay")); 
    VERIFY(1, insert(new_list, "tu ban? boc lot dan")); 
    VERIFY(1, insert(new_list, "truong loz")); 
    VERIFY(1, insert(new_list, "return")); 
    VERIFY(1, insert(new_list, "my tuition")); 
    VERIFY(1, insert(new_list, "need a discount")); 
    VERIFY(1, insert(new_list, "on")); 
    VERIFY(1, insert(new_list, "tuition")); 
    VERIFY(0, insert(new_list, "♒︎♏︎❒︎♏︎📬︎"));
    VERIFY(0, insert(new_list, "abs1❄︎⍓︎◻︎♏︎"));
    VERIFY(1, insert(new_list, " "));
    VERIFY(0, insert(new_list, ""));
    VERIFY(0, insert(new_list, "おはようございます"));
}

void test_print(List *new_list){
    printf("\n*** Testing print:\n");
    print(new_list);
}

void test_find(List *new_list){
    printf("\n*** Testing find:\n");
    VERIFY(1, find(new_list, "egg"));
    VERIFY(1, find(new_list, "an cuop giua ban ngay"));
    VERIFY(1, find(new_list, "nuke the uofm")); 
    VERIFY(0, find(new_list, "유 니 코 드 로 하십시오 제10회")); 
    VERIFY(0, find(new_list, "おはようございます")); 
    VERIFY(0, find(new_list, "abs1❄︎⍓︎◻︎♏︎"));
    VERIFY(0, find(new_list, "truong nhu concac"));
    VERIFY(0, find(new_list, "ƒÀ‰P@USHƒì8Hl$0H‰M H‰U(L‰E0L‰M8HE(H‰EðH‹]ð¹   H‹ "));
    VERIFY(1, find(new_list, "truong loz"));
    VERIFY(0, find(new_list, "cdf"));
}

void test_size(List *new_list){
    printf("\n*** Testing size:\n");
    VERIFY(19, size(new_list));
    insert(new_list, " ?");
    insert(new_list, " /");
    VERIFY(21, size(new_list));
    insert(new_list, "%#@$@#$1vrew3");
    insert(new_list, "유 니 코 드 로 하십시오 제10회 ");
    insert(new_list, "ƒÀ‰P@USHƒì8Hl$0H‰M H‰U(L‰E0L‰M8HE(H‰EðH‹]ð¹   H‹ ");
    insert(new_list, "cdfeas"); 
    insert(new_list, "ditconmetruonglz");
    VERIFY(24, size(new_list));
    print(new_list);
}

void test_destroy(List *new_list){
    printf("\n*** Testing destroy:\n");
    destroy(new_list);
}

int main(){
    List *new_list = construct();

    test_insertion(new_list);
    test_print(new_list); 
    test_find(new_list);
    test_size(new_list);
    test_destroy(new_list);

    if (0 == Tests_Failed) {
        printf("\nAll %d tests passed.\n", Tests_Passed);
    } else {
        printf("\nFAILED %d of %d tests.\n", Tests_Failed, Tests_Failed+Tests_Passed);
    }

    printf("\n*** Tests complete.\n");
    return 0;
    
}


 /* used for concordance
    FILE *f = stdin; 
    char line[1000]; 
    while(fgets(line, 1000, f) != NULL){
        if(strcmp(line, "") != 0){
            char delimiters[] = " \n";
            char *token; 
            token = strtok(line, delimiters);
            while(token != 0){
                a = insert(new_list, token);
                token = strtok(NULL, delimiters);
            }
        }
    }
    */