#include <stdio.h>
#include <ctype.h>
#include <string.h>

int rsolve(int *array, int unprocessed, int *solution, int solutionCount, int soFar, int target){
    int lastPos, result;

    if(soFar == target){
        result = solutionCount;
    }
    else if(unprocessed == 0){
        result = 0;
    }
    else{
        lastPos = unprocessed - 1;
        result = rsolve(array, lastPos, solution, solutionCount, soFar, target);
        if(result == 0 && soFar+array[lastPos] <= target){
            solution[solutionCount] = array[lastPos];
            result = rsolve(array, unprocessed - 1, solution, solutionCount + 1, soFar + array[lastPos], target);
        }
    }
    return result;
}

int solve(int *array, int *solution, int target, int size){
    return rsolve(array, size, solution, 0, 0, target);
}

void reverseSort(int *array, int size){
    int max, maxPos;
    
    for(int i = 0; i < size - 1; i++){
        max = array[i];
        maxPos = -1;
        for(int j = i + 1; j < size; j++){
            if(array[j] > max){
                max = array[j];
                maxPos = j;
            }
        }
        if(maxPos > 0){
            array[maxPos] = array[i];
            array[i] = max;
        }
    }
}

int main(){
    const int MAX_COUNT = 30;
    int count = 0, target;  
    int solutionCount; 
    
    while(scanf("%d", &count) != EOF){
        if(count > MAX_COUNT){
            printf("Invalid count %d\n", count);
            char tmp = ' ';
            //scanf("%[^\n]%*c", &tmp);       
            while(tmp != '\n' && tmp != EOF){
                //tmp = getchar();
                scanf("%c", &tmp);
            }
        }
        else{
            int array[MAX_COUNT];  
            int keepTrack = 0;
            for(int i = 0; i <= count; i++){
                scanf("%d", &array[i]);
                keepTrack++;
            } 
           
            int solution[MAX_COUNT];
            int size = keepTrack - 1; //except the target
            target = array[keepTrack-1]; 
            reverseSort(array, size);
           
            solutionCount = solve(array, solution, target, size);
            if(solutionCount > 0){
                for(int i = 0; i < solutionCount; i++){
                   printf("%d ", (solution[i]));
                }
                printf("\n");
            }
            else{
                printf("Count = %d: no solution\n", count);
            }
            array[0] = '\0';
        }
    } 
}