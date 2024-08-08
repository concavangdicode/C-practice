#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CONTACT 100 //max 100 contacts
#define MAX_PHONE 500 //max 500 phone numbers
#define MAX_NAME 50
#define MAX_REL_PTYPE 20

#define VERIFY(e,t) verify(e, t, #t)
#define VERIFY_NON_NEGATIVE(t) verify_non_negative(t, #t)

//num test passed and failed
int Tests_Passed = 0;
int Tests_Failed = 0;

int track_contact = 0; 
int track_phone = 0;
int track_id = 0;

typedef struct CONTACT{
    char name[MAX_NAME];
    char relationship[MAX_REL_PTYPE];  
    int id;  
} contact; 

void verify(int expected, int result, char test[]) {
  if (expected == result) {
    printf("Passed: expected %d, got %d for: %s\n", expected, result, test);
    Tests_Passed++;
  } else {
    printf("FAILED: expected %d, got %d for: %s\n", expected, result, test);
    Tests_Failed++;
  }
}

void verify_non_negative(int result, char test[]) {
  if (result >= 0) {
    printf("Passed: expected non-negative, got %d for: %s\n", result, test);
    Tests_Passed++;
  } else {
    printf("FAILED: expected non-negative, got %d for: %s\n", result, test);
    Tests_Failed++;
  }
}

typedef struct PHONE{
    int id;
    int area;
    int num;
    char type[MAX_REL_PTYPE];
} phone;

contact array_contact[MAX_CONTACT];
phone array_phone[MAX_PHONE];

typedef enum {
    FALSE = 0,
    TRUE = 1
} Boolean;

int compare_by_name(const void *a, const void *b){
    const contact *ca = (contact *)a; 
    const contact *cb = (contact *)b;
    return strcmp(ca->name, cb->name);
}

void sort_name(contact *array, int n){
    qsort(array, n, sizeof(contact), compare_by_name);
}

int compare_by_type(const void *a, const void *b){
    const phone *pa = (phone *)a; 
    const phone *pb = (phone *)b;
    return strcmp(pa->type, pb->type);
}

void sort_by_type(phone *array, int n){
    qsort(array, n, sizeof(phone), compare_by_type);
}

int new_contact(char name[], char relationship[]); // name is mandatory and unique, relationship may be empty
Boolean delete_contact(int contact); // contact ID as returned from new_contact
Boolean add_phone(int contact, int area, int number, char type[]); // area and number must be valid
Boolean remove_phone(int contact, char type[]); // phone of that type must exist
void print_contacts(Boolean with_phone);
Boolean save_contacts(char filename[]);

int count_contacts();
int count_contact_numbers(int id);
int count_all_numbers();

void test_empty_list() {
  printf("\n*** Testing empty list:\n");

  VERIFY(0, count_contacts());
  VERIFY(-1, count_contact_numbers(0));
  VERIFY(-1, count_contact_numbers(1));
  VERIFY(0, count_all_numbers());
  
  VERIFY(FALSE, delete_contact(0));
  VERIFY(FALSE, delete_contact(1));
  VERIFY(FALSE, remove_phone(0, ""));
  VERIFY(FALSE, remove_phone(1, ""));
}

void test_simple_list() {
  int contact1, contact2, contact3;
  printf("\n*** Testing a simple list:\n");
  
  VERIFY_NON_NEGATIVE(contact1 = new_contact("ghi", "xyz"));
  VERIFY_NON_NEGATIVE(contact2 = new_contact("abc def", "xyz"));

  VERIFY(TRUE, add_phone(contact1, 204, 5555555, "work"));
  VERIFY(TRUE, add_phone(contact2, 555, 5555556, "work"));
  VERIFY(TRUE, add_phone(contact2, 555, 5555556, "home office"));
  VERIFY(TRUE, add_phone(contact2, 555, 5555557, "work"));

  VERIFY_NON_NEGATIVE(contact3 = new_contact("jklm nop", ""));

  VERIFY(TRUE, add_phone(contact3, 204, 5555555, "work"));
  VERIFY(TRUE, add_phone(contact3, 204, 5555558, ""));
  VERIFY(TRUE, add_phone(contact1, 999, 9999999, "work"));
  VERIFY(TRUE, add_phone(contact1, 204, 5555559, "mobile"));

  // already added
  VERIFY(-1, new_contact("ghi", ""));
  
  VERIFY(3, count_contacts());
  VERIFY(8, count_all_numbers());
  VERIFY(3, count_contact_numbers(contact1));
  VERIFY(3, count_contact_numbers(contact2));
  VERIFY(2, count_contact_numbers(contact3));
  
  // this isn't an automated test since there's no way to verify:
  printf("\nExecuting print_contacts(TRUE):\n");
  print_contacts(TRUE);
  printf("\nExecuting print_contacts(FALSE):\n");
  print_contacts(FALSE);
  printf("\n");
  
  // this test is "fragile" as it could fail for reasons out of our control:
  VERIFY(TRUE, save_contacts("test_out.txt"));

  // manipulate the list
  VERIFY(TRUE, remove_phone(contact2, "home office"));
  VERIFY(FALSE, remove_phone(contact2, "mobile"));
  VERIFY(TRUE, remove_phone(contact1, "work")); // removes both!
  VERIFY(FALSE, remove_phone(contact1, "work"));
  VERIFY(5, count_all_numbers());
  VERIFY(1, count_contact_numbers(contact1));
  VERIFY(2, count_contact_numbers(contact2));
  
  VERIFY(TRUE, delete_contact(contact1));

  VERIFY(2, count_contacts());
  VERIFY(4, count_all_numbers());

  // can't use a non-existent contact:
  VERIFY(FALSE, add_phone(contact1, 204, 5555555, "work"));
  VERIFY(FALSE, remove_phone(contact1, "mobile"));
  VERIFY(-1, count_contact_numbers(contact1));

  VERIFY(TRUE, add_phone(contact3, 204, 5555555, "work"));

  VERIFY(TRUE, remove_phone(contact3, ""));
  VERIFY(4, count_all_numbers());
  VERIFY(TRUE, remove_phone(contact3, "work"));
  
  VERIFY_NON_NEGATIVE(contact1 = new_contact("qr stuvw", "xyz"));
  VERIFY(TRUE, add_phone(contact1, 204, 5555555, "work phone"));
  VERIFY(TRUE, add_phone(contact1, 204, 5555555, "work"));
  VERIFY(FALSE, remove_phone(contact1, "work mobile"));
  VERIFY(TRUE, remove_phone(contact1, "work"));

  VERIFY(3, count_all_numbers());
  VERIFY(1, count_contact_numbers(contact1));
  VERIFY(2, count_contact_numbers(contact2));
  VERIFY(0, count_contact_numbers(contact3));
  
  // clean up the list:
  VERIFY(TRUE, delete_contact(contact1));
  VERIFY(TRUE, delete_contact(contact2));
  VERIFY(TRUE, delete_contact(contact3));
  VERIFY(0, count_contacts());
  VERIFY(0, count_all_numbers());
}

void test_bounds() {
  int contact;

  printf("\n*** Testing boundary values:\n");
  
  // 50 and 20 chars:
  VERIFY_NON_NEGATIVE(contact = new_contact("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbb"));
  VERIFY(TRUE, add_phone(contact, 204, 5555555, "cccccccccccccccccccc"));

  VERIFY(TRUE, add_phone(contact, 100, 1000000, ""));
  VERIFY(FALSE, add_phone(contact, 99, 1000000, ""));
  VERIFY(FALSE, add_phone(contact, 100, 999999, ""));

  VERIFY(TRUE, delete_contact(contact));
  VERIFY(0, count_contacts());
  VERIFY(0, count_all_numbers());
}


void test_invalid() {
  int contact;

  printf("\n*** Testing invalid parameters:\n");
  
  VERIFY(-1, new_contact("", ""));
  VERIFY(-1, new_contact("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", ""));
  VERIFY(-1, new_contact("a", "aaaaaaaaaaaaaaaaaaaaa"));
  
  // one good contact:
  VERIFY_NON_NEGATIVE(contact = new_contact("a", "b"));
  VERIFY(FALSE, add_phone(contact, -1, 5555555, ""));
  VERIFY(FALSE, add_phone(contact, 204, -1, ""));
  VERIFY(FALSE, add_phone(contact, 204, 5555555, "bbbbbbbbbbbbbbbbbbbbbbb"));

  VERIFY(FALSE, delete_contact(-1));
  VERIFY(FALSE, add_phone(-1, 204, 5555555, ""));

  VERIFY(-1, count_contact_numbers(0));
  VERIFY(-1, count_contact_numbers(-1));

  VERIFY(FALSE, remove_phone(-1, ""));

  // remove the one good contact:
  VERIFY(TRUE, delete_contact(contact));
  VERIFY(0, count_contacts());
  VERIFY(0, count_all_numbers());

  // no longer valid:
  VERIFY(FALSE, add_phone(contact, 204, 5555555, ""));
  VERIFY(-1, count_contact_numbers(contact));
  
  // this should cause fopen() to fail on all systems:
  VERIFY(FALSE, save_contacts("."));
}

// Most tests are as simple as possible. This one is more complex because
// filling the capacity one item at a time would take a lot of code...
void test_capacity() {
  const int CONTACT_CAP = 100;
  const int PHONE_CAP = 500;
  int contact_ids[CONTACT_CAP];
  char name[3] = "aa";
  int count_successful_contacts, count_successful_phones, count;

  printf("\n*** Testing list capacity:\n");

  // this test only makes sense if the list starts out empty (which it should)
  VERIFY(0, count_contacts());
  VERIFY(0, count_all_numbers());

  // we're not going to VERIFY every single contact/phone (too much output,
  // and they're not each a separate test), just the final results

  count_successful_contacts = 0;
  for (int i = 0; i < CONTACT_CAP; i++) {
    name[0] = (i / 10) + 'a';
    name[1] = (i % 10) + 'a';
    contact_ids[i] = new_contact(name, "");
    if (contact_ids[i] > 0) {
      count_successful_contacts++;
    }
  }
  VERIFY(CONTACT_CAP, count_successful_contacts);

  count_successful_phones = 0;
  for (int i = 0; i < PHONE_CAP; i++) {
    if (add_phone(contact_ids[i % CONTACT_CAP], 204, 5555555, "mobile")) {
      count_successful_phones++;
    }
  }
  VERIFY(PHONE_CAP, count_successful_phones);

  VERIFY(CONTACT_CAP, count_contacts());
  VERIFY(PHONE_CAP, count_all_numbers());
  
  // can't exceed maximums:
  VERIFY(-1, new_contact("abc", ""));
  VERIFY(FALSE, add_phone(contact_ids[CONTACT_CAP - 1], 204, 5555555, "mobile"));

  // try again, adding all phone numbers to one contact
  
  count_successful_contacts = 1;
  count_successful_phones = count_contact_numbers(contact_ids[0]);
  for (int i = 1; i < CONTACT_CAP; i++) {
    count = count_contact_numbers(contact_ids[i]);
    if (remove_phone(contact_ids[i], "mobile")) {
      count_successful_contacts++;
    }
    for (int j = 0; j < count; j++) {
      if (add_phone(contact_ids[0], 204, 5555555, "mobile")) {
        count_successful_phones++;
      }
    }
  }
  VERIFY(CONTACT_CAP, count_successful_contacts);
  VERIFY(PHONE_CAP, count_successful_phones);
  VERIFY(PHONE_CAP, count_contact_numbers(contact_ids[0]));
  
  VERIFY(CONTACT_CAP, count_contacts());
  VERIFY(PHONE_CAP, count_all_numbers());
  
  // can't exceed maximums:
  VERIFY(-1, new_contact("abc", ""));
  VERIFY(FALSE, add_phone(contact_ids[0], 204, 5555555, "mobile"));
  
  // clean up the list:
  count_successful_contacts = 0;
  for (int i = 0; i < CONTACT_CAP; i++) {
    if (delete_contact(contact_ids[i])) {
      count_successful_contacts++;
    }
  }
  VERIFY(CONTACT_CAP, count_successful_contacts);

  VERIFY(0, count_contacts());
  VERIFY(0, count_all_numbers());
}


void printArray(){
    for(int i = 0; i < track_phone; i++){
        printf("%d %d %d\n", array_phone[i].id ,array_phone[i].area, array_phone[i].num);
    }
}

void test(){
  printf("*** Starting tests...\n");

  test_empty_list();
  test_simple_list();
  test_bounds();
  test_invalid();
  test_capacity();
  
  if (0 == Tests_Failed) {
    printf("\nAll %d tests passed.\n", Tests_Passed);
  } else {
    printf("\nFAILED %d of %d tests.\n", Tests_Failed, Tests_Failed+Tests_Passed);
  }

  printf("\n*** Tests complete.\n");
}

Boolean include_num(char string[], int length){
    for(int i = 0; i < length; i++){
        if(isdigit(string[i])){
            return TRUE;
        }
    }
    return FALSE;
}

void readFile(){
    FILE *f = stdin; 
    char line[MAX_NAME]; 
    char phoneDelimiters[] = " ";
    char contactDelimiters[] = "\n,\0";
    int id = 0; 
 
    while (fgets(line, MAX_NAME, f) != NULL){

        int len = strlen(line);
        if(strcmp(line, "\n") != 0){
            if(include_num(line, len)){
                char *token = strtok(line, phoneDelimiters);
                int area = atoi(token);
                token = strtok(NULL, phoneDelimiters); 
                int num = atoi(token); 
                token = strtok(NULL, "\n");
                char type[MAX_REL_PTYPE];
                strcpy(type, token);
                add_phone(id, area, num, type);
            }
            
            else{
                char *token = strtok(line, contactDelimiters); 
                char name[MAX_NAME]; 
                strcpy(name, token); 
                token = strtok(NULL, contactDelimiters);
                char relationship[MAX_REL_PTYPE];
                if(token != NULL){
                    strcpy(relationship, token); 
                } 
                id = new_contact(name, relationship); 
            }
        }
    } 
    print_contacts(TRUE); 

}

void reset(){
    track_contact = 0; 
    track_phone = 0;
    track_id = 0;
    memset(array_contact, '\0', sizeof(contact) * MAX_CONTACT);
    memset(array_phone, '\0', sizeof(phone) * MAX_PHONE);
}

int main(){
  test();
  reset();
  readFile();
  return 0;
}

int count_num_length(int num){
    int length = 0; 
    while(num > 0){
        ++length; 
        num /= 10;
    }
    return length;
}

int new_contact(char name[], char relationship[])
{   
    for(int i = 0; i < track_contact; i++){
        if(strcmp(array_contact[i].name, name) == 0){
            return -1;
        }
    }

    if(strlen(name) == 0 || strlen(name) > MAX_NAME || strlen(relationship) > MAX_REL_PTYPE || track_contact >= MAX_CONTACT){
        return -1;
    }
    
    contact contact; 
    strcpy(contact.name, name);
    strcpy(contact.relationship, relationship); 
    contact.id = track_id++; //pos in the array
    array_contact[track_contact++] = contact;
    return contact.id; //return the id of newly created contact
}

Boolean delete_contact(int contact){ //delete a contact based on its id
    for(int j = 0; j < track_contact; j++){
        if(array_contact[j].id == contact){
            for(int i = j; i < track_contact-1; i++){
                array_contact[i] = array_contact[i+1];
            }
            --track_contact;

            for(int i = track_phone - 1; i >= 0; i--){
                if(array_phone[i].id == contact){
                    for(int j = i; j < track_phone - 1; j++){
                        array_phone[j] = array_phone[j + 1];
                    }
                --track_phone;
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}  

Boolean add_phone(int contact, int area, int number, char type[]){
    if(count_num_length(area) < 3 || count_num_length(area) > 3 || count_num_length(number) < 7 || count_num_length(number) > 7 || strlen(type) > MAX_REL_PTYPE || track_phone >= MAX_PHONE){
        return FALSE;
    }
    for(int i = 0; i < track_contact; i++){
        if(array_contact[i].id == contact){
            phone phone; 
            phone.id = contact; 
            phone.area = area;
            phone.num = number;
            strcpy(phone.type, type);
            array_phone[track_phone++] = phone; 
            return TRUE;
        }
    }
    return FALSE;
}

Boolean remove_phone(int contact, char type[]){
    Boolean remove = FALSE;
        for(int i = track_phone - 1; i >= 0; i--){
            if(array_phone[i].id == contact && strcmp(array_phone[i].type, type) == 0){
                //printf("tmp %d %d %d\n", array_phone[i].id, array_phone[i].area, array_phone[i].num);
                for(int j = i; j < track_phone - 1; j++){
                    //printf("before %d %d %d\n", array_phone[j].id, array_phone[j].area, array_phone[j].num);
                    array_phone[j] = array_phone[j + 1];
                    //printf("after %d %d %d\n", array_phone[j].id, array_phone[j].area, array_phone[j].num);
                    //printf("%d ", array_phone[j].id);
                    //printf("%s\n", array_phone[j].type);
                }
                //memset(array_phone, '\0', track_phone);
                --track_phone;
                remove = TRUE;
            }
        }
    return remove;
}

void print_contacts(Boolean with_phone){
    sort_by_type(array_phone, track_phone);
    sort_name(array_contact, track_contact);
    for(int i = 0; i < track_contact; i++){
        printf("%s (%s)\n", array_contact[i].name, array_contact[i].relationship);
        if(with_phone != 0){
            for(int j = 0; j < track_phone; j++){
                if(array_phone[j].id == array_contact[i].id){
                    printf("%s (%d) %d\n", array_phone[j].type, array_phone[j].area, array_phone[j].num);
                }
            }
        }
        printf("\n");
    }
}

Boolean save_contacts(char file_name[]){
    if(strlen(file_name) < 5){ // an approprite file name x.txt so its length should be at least 5 where length of 'x' >= 1 and length of '.txt' = 4
        return FALSE;
    }
    FILE *f = fopen(file_name, "w");
    if(f != NULL){
        for(int i = 0; i < track_contact; i++){
            fprintf(f,"%s (%s)\n", array_contact[i].name, array_contact[i].relationship);
            for(int j = 0; j < track_phone; j++){
                if(array_phone[j].id == array_contact[i].id){
                    fprintf(f,"%s (%d) %d\n", array_phone[j].type, array_phone[j].area, array_phone[j].num);
                }
            }
        }
    }
    return TRUE;
}

int count_contacts(){
    return track_contact;
}

int count_contact_numbers(int id){
    Boolean found = FALSE;
    for(int i = 0; i < track_contact; i++){
        if(array_contact[i].id == id){
            found = TRUE;
        }
    }
    if(found){
        int count = 0;
        for(int i = 0; i < track_phone; i++){
            if(array_phone[i].id == id){
                count++;
            }
        }
        return count;
    }
    return -1;
}

int count_all_numbers(){
    return track_phone;
}

