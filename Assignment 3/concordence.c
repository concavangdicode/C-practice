#include "index_list.h"
#include <stdio.h>
#include <string.h>

int main(){
    List *new_list = construct();
    //FILE *f = stdin; 
    FILE *f = fopen("a3q2-1.txt", "r");
    char line[1000]; 
    boolean a = 1; 

    while(fgets(line, 1000, f) != NULL){
        if(strcmp(line, "") != 0){
            char delimiters[] = " \n";
            char *token; 
            token = strtok(line, delimiters);
            while(token != 0){
                if(find(new_list, token) != a){
                    a = insert(new_list, token);
                }
                token = strtok(NULL, delimiters);
            }
        }
    }
    //printf("%d", a);
    print(new_list);
    printf("size of list: %d\n", size(new_list));
    printf("total traversal: %d\n", traversals());
    //destroy(new_list);
    return 0;
}