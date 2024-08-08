#include <stdio.h>
int max(int a, int b){
    return (a > b) ? a : b;
}

int ldsr(int *array, int pOrig, int pDup, int attempt, int arrayLength){
    int best;

    if(pOrig >= arrayLength || pDup >= arrayLength){
        return attempt;
    }

    if(pOrig == pDup){
        best = ldsr(array, pOrig + 1, pDup + 1, 0, arrayLength);
    }
    else if(array[pOrig] == array[pDup]){
        best = max(attempt, ldsr(array, pOrig + 1, pDup + 1, attempt + 1, arrayLength));
    }
    else{
        best = attempt;
    }

    attempt = ldsr(array, pOrig, pDup + 1, 0, arrayLength);
    return max(attempt, best);
}

int longestDuplicateSubsequence(int *array, int arrayLength){
    return ldsr(array, 0, 0, 0, arrayLength);
}


void toString(int *array, char* string, int size){
    int i = 0;
    int pos = 0;
    while(i < size){
        sprintf(&string[pos++], "%d", array[i]);
        string[pos++] = ' ';
        i++;
    } 
    string[pos] = '\0';
    //remove last comma
}

void testLDS(int expected, int *array, int arrayLength){
    char arrayString[50];
    toString(array, arrayString, arrayLength);

    int result = longestDuplicateSubsequence(array, arrayLength); 

    if(expected == result){
        printf("Test succeeded: [ %s]\n", arrayString);
    }
    else{
        printf("Test FAILED (expected %d, got %d): %s\n", expected, result, arrayString);
    }
    array[arrayLength] = '\0';
}

int main(){
    
    int array1[] = { 1, 5, 3, 7, 9, 1, 3, 7, 5, 3, 7, 1, 9 };
    int arrayLength = sizeof(array1) / sizeof(array1[0]);
    testLDS(3, array1, arrayLength);
    
    int array2[] = { 3, 4, 1, 2, 4, 1, 2, 4, 3 };
    arrayLength = sizeof(array2) / sizeof(array2[0]);
    testLDS(4, array2, arrayLength);

    int array3[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    arrayLength = sizeof(array3) / sizeof(array3[0]);
    testLDS(0, array3, arrayLength);

    int array4[] = { 1, 2, 3, 4, 5, 10, 6, 7, 8, 9, 10 };
    arrayLength = sizeof(array4) / sizeof(array4[0]);
    testLDS(1, array4, arrayLength);

    int array5[] = { 1, 2, 3, 4, 5, 6, 1, 2, 1, 2, 3, 4, 5, 1, 2, 3, 4 };
    arrayLength = sizeof(array5) / sizeof(array5[0]);
    testLDS(5, array5, arrayLength);

    int array6[] = { 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 };
    arrayLength = sizeof(array6) / sizeof(array6[0]);
    testLDS(11, array6, arrayLength);

    int array7[] = { 1, 1, 1, 1, 1 };
    arrayLength = sizeof(array7) / sizeof(array7[0]);
    testLDS(4, array7, arrayLength);

    int array8[] = { }; 
    arrayLength = sizeof(array8) / sizeof(array8[0]);
    testLDS(0, array8, arrayLength);

    return 0;
}