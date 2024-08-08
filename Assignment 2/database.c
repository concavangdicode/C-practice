#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LIMIT 1000
#define MAX_ABBR 3
#define MAX_ARRAY 100000

int sizeIndustry;
int sizeIncome;
int sizeProvince;

typedef struct Income
{
    char province[MAX_ABBR]; 
    int year; 
    int income; 
    int code;
}income;
income *incomeArray;

income *mallocIncome(int num){
    return (income *)malloc(num * sizeof(income));
}

typedef struct Industry
{
    int code;
    char nameInd[MAX_LIMIT];
}industry;
industry *industryArray;

industry *mallocIndustry(int num){
    return (industry *)malloc(num * sizeof(industry));
}

typedef struct Province
{
    char provname[MAX_LIMIT]; 
    char province[MAX_ABBR];
}province;
province *provinceArray;

province *mallocProvince(int num){
    return (province *)malloc(num * sizeof(province));
}

int findSize(char *fileName){
    FILE *f; 
    int count = 0; 
    char c; 

    //printf("Enter file name\n"); 
    //scanf("%s", fileName); 

    f = fopen(fileName, "r"); 
    if(f == NULL){
        printf("Could not open the file %s", fileName); 
        return 0;
    }

    else{
        for(c = getc(f); c != EOF; c = getc(f)){
            if(c == '\n'){
                count = count + 1;
            }
        }
    }
    fclose(f); 
    return (count + 1);
}

//sort by year for income
int compare_by_year_income(const void *a, const void *b){
    const income *inca = (income *)a; 
    const income *incb = (income *)b;
    return inca -> year - incb -> year; 
}

void sort_by_year_income(income *incArray, int n){
    qsort(incArray, n, sizeof(income), compare_by_year_income);
}

//sort by name for income
int compare_by_name_income(const void *a, const void *b){
    const income *inca = (income *)a;
    const income *incb = (income *)b;
    return strcmp(inca->province, incb->province);
}

void sort_by_name_income(income *incArray, int n){
    qsort(incArray, n, sizeof(income), compare_by_name_income);
}

//sort by name for industry
int compare_by_name_industry(const void *a, const void *b){
    const industry *inda = (industry *)a; 
    const industry *indb = (industry *)b;
    return (strcmp(inda -> nameInd, indb -> nameInd));
}

void sort_by_name_industry(industry *indArray, int n){
    qsort(indArray, n, sizeof(industry), compare_by_name_industry);
}

void readFile(char *incometxt, char *industrytxt, char *provincetxt){
    //Free struct array

    sizeIndustry = findSize(industrytxt); 
    sizeIncome = findSize(incometxt); 
    sizeProvince = findSize(provincetxt); 
    char delimiters[] = ",\0";

    industryArray = mallocIndustry(sizeIndustry); 
    incomeArray = mallocIncome(sizeIncome); 
    provinceArray = mallocProvince(sizeProvince);

    FILE *id = fopen(industrytxt, "r"); 
    FILE *ic = fopen(incometxt, "r"); 
    FILE *pr = fopen(provincetxt, "r");
    
    char idLine[MAX_LIMIT]; 
    char icLine[MAX_LIMIT]; 
    char prLine[MAX_LIMIT]; 

    //ignore first line
    fgets(idLine, MAX_LIMIT, id); 
    fgets(icLine, MAX_LIMIT, ic); 
    fgets(prLine, MAX_LIMIT, pr);  
    

    for(int i = 0; i < sizeIndustry - 1; i++){
        fgets(idLine, MAX_LIMIT, id);
        //code
        char *token = strtok(idLine, delimiters); 
        industryArray[i].code = atoi(token);
        //printf("%d ",industryArray[i].code);
        //name
        token = strtok(NULL, delimiters); 
        strcpy(industryArray[i].nameInd, token);   
        int len = strlen(industryArray[i].nameInd);
        industryArray[i].nameInd[len - 1] = '\0';
        //printf("%s\n",industryArray[i].nameInd);
    }

    for(int i = 0; i < sizeIncome - 1; i++){
        fgets(icLine, MAX_LIMIT, ic);
        //prov
        char *token = strtok(icLine, delimiters); 
        strcpy(incomeArray[i].province, token);
        //printf("%s ",incomeArray[i].province);
        //year
        token = strtok(NULL, delimiters);
        incomeArray[i].year = atoi(token);
        //printf("%d ",incomeArray[i].year);
        //income
        token = strtok(NULL, delimiters);
        incomeArray[i].income = atoi(token);
        //printf("%d ",incomeArray[i].income);
        //code
        token = strtok(NULL, delimiters);
        incomeArray[i].code = atoi(token);
        //printf("%d\n",incomeArray[i].code);
    }

    for(int i = 0; i < sizeProvince - 1; i++){
        fgets(prLine, MAX_LIMIT, pr);
        //name
        char *token = strtok(prLine, delimiters);
        strcpy(provinceArray[i].provname, token);
        //printf("%s ",provinceArray[i].provname);
        token = strtok(NULL, delimiters);
        strcpy(provinceArray[i].province, token);
        provinceArray[i].province[MAX_ABBR - 1] = '\0';
        //printf("%s",provinceArray[i].province);
    }

}

void findProvince(char *provname, char *province){ 
    for(int i = 0; i < sizeProvince - 1; i++){
        //printf("%s\n", provinceArray[i].provname);
        if(strcmp(provinceArray[i].provname, provname) == 0){
            strcpy(province, provinceArray[i].province);
            //printf("%s\n", province);         
        }
    }
}

void findProvname(char *provname, char *province){
    for(int i = 0; i < sizeProvince; i++){
        if(strcmp(provinceArray[i].province, province) == 0){
            strcpy(provname, provinceArray[i].provname);
        }
    }
}

//FIND command
void find(char *provname, int year, char *nameInd){
    sort_by_name_industry(industryArray, sizeIndustry);

    char province[MAX_ABBR];
    memset(province,'\0', MAX_ABBR);
    findProvince(provname, province);

    int lenthIndName = strlen(nameInd);
    //printf("%d\n", lenthIndName);
    for(int i = 0; i < sizeIndustry - 1; i++){
        char tmp[MAX_LIMIT];
        memset(tmp, '\0', MAX_LIMIT); 
        strncpy(tmp, industryArray[i].nameInd, lenthIndName); 
        if(strcmp(tmp, nameInd) == 0){
           //printf("%s", tmp);
           int indCode = industryArray[i].code;   
           //printf("%d", indCode);
           for(int j = 0; j < sizeIncome - 1; j++){
           //printf("%s %s %d\n",province, incomeArray[j].province, strcmp(incomeArray[j].province, province));
                if((strcmp(incomeArray[j].province, province) == 0) && incomeArray[j].code == indCode && incomeArray[j].year == year){
                 printf("%s $%d\n", industryArray[i].nameInd, incomeArray[j].income);
              }
           }
        }
    }
    printf("\n");
}

//SUM command
void sum_province(char *provname){
    sort_by_year_income(incomeArray, sizeIncome);
    
    char province[MAX_ABBR]; 
    memset(province, '\0', MAX_ABBR); 
    findProvince(provname, province);

    //add all of given province to an array
    income tmpArray[MAX_ARRAY];
    int keepTrack = 0;
    for(int i = 0; i < sizeIncome; i++){
        income tmp = incomeArray[i];
        if(strcmp(tmp.province, province) == 0){
            tmpArray[keepTrack++] = tmp;
        }
    }

    //
    int inc = tmpArray[0].income; 
    int year = tmpArray[0].year;
    for(int i = 1; i < keepTrack; i++){
        if(year == tmpArray[i].year){
            inc += tmpArray[i].income;
        }
        else{
            printf("%d $%d\n", year, inc);
            inc = tmpArray[i].income;
            year = tmpArray[i].year;
        }
    }
    //print last year
    printf("%d $%d\n\n", year, inc);
    memset(tmpArray,'\0',sizeIncome);
}

void sum_ind_year(char *ind, int year){
    sort_by_name_income(incomeArray, sizeIncome);
    
    int length = strlen(ind); 
    income tmpArr[MAX_ARRAY];
    int keepTrack = 0;

    for(int i = 0; i < sizeIndustry; i++){
        char tmp[MAX_LIMIT]; 
        memset(tmp,'\0', MAX_LIMIT);
        strncpy(tmp, industryArray[i].nameInd, length);
        if(strcmp(ind, tmp) == 0){ //check if abbr equals to the name of industry
            int code = industryArray[i].code; //if they are same, retrieve the code
            for(int j = 0; j < sizeIncome; j++){
                if(code == incomeArray[j].code && year == incomeArray[j].year){ //check if code and year is same as input
                    tmpArr[keepTrack++] = incomeArray[j];
                }
            }
        }
    }

    //sort tmpArr
    sort_by_name_income(tmpArr, keepTrack);

    //print total income for each province
    int inc = tmpArr[0].income; 
    char pr[MAX_ABBR];
    strcpy(pr, tmpArr[0].province);
    char provname[MAX_LIMIT];
    memset(provname, '\0', MAX_LIMIT);

    for(int i = 1; i < keepTrack; i++){
        if(strcmp(pr, tmpArr[i].province) == 0){
            inc += tmpArr[i].income;
        }
        else{
            findProvname(provname, pr);
            printf("%s %d: $%d\n", provname, year, inc);
            inc = tmpArr[i].income; 
            year = tmpArr[i].year;
            //reset the memory 
            memset(pr, '\0', MAX_ABBR);
            //copy new data
            strcpy(pr, tmpArr[i].province);
            //reset the memory
            memset(provname, '\0', MAX_LIMIT);
        }
    }
    //print the final province
    findProvname(provname, pr);
    printf("%s %d: $%d\n\n", provname, year, inc);
    
    //reset memory
    memset(pr, '\0', MAX_ABBR);
    memset(provname, '\0', MAX_LIMIT);
    memset(tmpArr, '\0', sizeIncome);
    /*
    for(int k = 0; k < sizeProvince; k++){
        if(strcmp(provinceArray[k].province, incomeArray[j].province) == 0){
            printf("%s %d: $%d\n", provinceArray[k].provname, incomeArray[j].year, incomeArray[j].income);
    }

    for(int i = 0; i < keepTrack; i++){
        printf("%s %d %d %d\n", tmpArr[i].province, tmpArr[i].code, tmpArr[i].income, tmpArr[i].year);
    }
    */
}

void provinceSubstring(char *origin, char *provname){
    char *start = origin; 
    char *end = &origin[strlen(origin) - 1];

    //shift the start pointer until it reaches the blank
    while(*start != ' '){
        start += 1;
    }

    //shift the end pointer until it reachs the 'B' letter
    while(*end != 'B'){
        end -= 1;
    }

    int length = (--end) - (++start); //pointer arithmetic to find the length of substring
    strncpy(provname, start, length);
}

void processCommand(){
    FILE *f = stdin;
    char delimiters [] = " ,\n";
    char category[] = "Year";
    char *p;

    char line[MAX_LIMIT];
    char tmpLine[MAX_LIMIT];
    char provname[MAX_LIMIT];
    char nameInd[MAX_LIMIT];
    memset(line, '\0', MAX_LIMIT);
    memset(provname,'\0',MAX_LIMIT);
    memset(nameInd,'\0',MAX_LIMIT);

    if (f != NULL)
    {
        while(fgets(line, MAX_LIMIT, f) != NULL){
            strcpy(tmpLine, line);
            char *token = strtok(line, delimiters);
            if(strcmp(token, "FIND") == 0){
                //province name
                token = strtok(NULL, delimiters);
                strcpy(provname, token);
                //year
                token = strtok(NULL, delimiters);
                int year = atoi(token);
                //name industry
                token = strtok(NULL, delimiters);
                strcpy(nameInd, token);
                find(provname, year, nameInd);
            }
            else{
                p = strstr(tmpLine, category);
                //printf("%s", tmpLine);
                //printf("%s", p);
                if(p){
                    provinceSubstring(tmpLine, provname);
                    sum_province(provname);
                }
                else{
                    provinceSubstring(tmpLine, provname);
                    //char *c = provname;
                    //printf("%s\n", c);
                    char *end = &provname[strlen(provname) - 1];
                    char *start = provname;
                    int trackLength = 0;
                    //shift left pointer until it reaches blank
                    while(*start != ' '){
                        ++start;
                        ++trackLength; //find the length of industry
                    }
                    //shift right pointer until it reaches blank
                    while(*end != ' '){
                        --end;
                    }
                    char nameInd[MAX_LIMIT]; 
                    memset(nameInd,'\0', MAX_LIMIT); 
                    strncpy(nameInd, provname, trackLength); //copy from start of provname until the length of industry
                    int year = atoi(end); //convert string to int
                    sum_ind_year(nameInd, year);
                    memset(nameInd,'\0', MAX_LIMIT); 
                }
            }
            memset(line, '\0', MAX_LIMIT);
            memset(provname,'\0',MAX_LIMIT);
            memset(nameInd,'\0',MAX_LIMIT);
            memset(tmpLine, '\0', MAX_LIMIT);
        }
    } 
    fclose(f);
}

int main(){

    char incometxt[] = "D:/COMP 2160/COMP 2160/Assignments/Assignment 2/q1_income.txt";
    char industrytxt[] = "D:/COMP 2160/COMP 2160/Assignments/Assignment 2/q1_industry.txt";
    char provincetxt[] = "D:/COMP 2160/COMP 2160/Assignments/Assignment 2/q1_province.txt";
    /*
    int sizeIncome = findSize(incometxt); 
    int sizeIndustry = findSize(industrytxt);
    int sizeProvince = findSize(provincetxt);

    printf("Number of line is %d\n", sizeIncome);
    printf("Number of line is %d\n", sizeIndustry);
    printf("Number of line is %d\n", sizeProvince);
    */
    
    readFile(incometxt, industrytxt, provincetxt);
    /*
    find("Ontario",2017,"Aqua");
    find("Manitoba",2017,"R");
    sum_province("Manitoba");
    sum_province("Newfoundland and Labrador");
    sum_province("New Brunswick");
    sum_ind_year("Pu", 2017);
    sum_ind_year("A", 2017);
    */
    processCommand();
    free(incomeArray); 
    free(industryArray); 
    free(provinceArray);
    return 0;
}