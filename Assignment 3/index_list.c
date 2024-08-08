#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "index_list.h"

static int total_num_traversals = 0;
//typedef enum BOOL { false, true} boolean;

// Linked list node definition
typedef struct NODE Node;

struct NODE
{ 
  char *string;
  Node *next;
};

typedef struct LIST List;

struct LIST {
  Node *index[256];
  //Node *top; //del later 
};


// construct a linked list
List *construct() {
  List *list;

  list = malloc( 256 * sizeof( Node ) );
  memset(list->index, '\0', 256 * sizeof(Node)); //set null for all index of array

  return list;
}

//validate valid ascii characters
boolean valid_ascii(char *new_string){
    int len = strlen(new_string); 
    for(int i = 0; i < len; i++){
       if(!isascii(new_string[i])){
        return false;
       }
    } 
    return true;
}

//return the integer value of the first char in a string
int search_index(char *new_string){
    int value = new_string[0];
    //printf("%d ", value);
    return value;
}

// perform an ordered insertion of an item into a list
boolean insert( List *list, char *new_string )
{
  //precondition of a string 
  assert(new_string != NULL && strlen(new_string) > 0 && valid_ascii(new_string));

  boolean rc = true;
  Node *newNode = NULL;
  Node *curr;
  Node *prev;

  newNode = malloc( sizeof( Node ) );
  newNode->string = new_string;
  
  //find the index in the array of list
  
  if(new_string == NULL || strlen(new_string) <= 0 || !valid_ascii(new_string)){
    return false;
  }

  int ind = search_index(new_string) - 1;
  curr = list->index[ind];
  
  prev = NULL;
  while ( NULL != curr && strcmp( curr->string, new_string ) < 0 ) {
    prev = curr;
    curr = curr->next;
    total_num_traversals++;
  }

  if ( prev == NULL ) {
    newNode->next = list->index[ind];
    list->index[ind] = newNode;
  } else {
    
    newNode->next = curr;
    prev->next = newNode;
  }

  // note that we need to have space for the string as well!
  newNode->string = malloc( strlen( new_string ) + 1 );
  strcpy( newNode->string, new_string );

  return rc;

}

// tells us whether or not the given string is in the list
boolean find( List *list, char *target )
{
  assert(list != NULL && target != NULL && valid_ascii(target));
  if(list == NULL || target == NULL || !valid_ascii(target)){
      return false;
  }
  
  boolean found = false;
  int compare;
  //find the index of the target
  int ind = (search_index(target) - 1);
  Node *curr = list->index[ind];
  while ( NULL != curr && !found ) {
    compare = strcmp( curr->string, target );
    if ( compare == 0 ) {
      found = true;
    } 
    else if (compare > 0) {
      // gone too far
      curr = NULL;
    } 
    else {
      total_num_traversals++;
      curr = curr->next;
    }
  }

  return found;
}

// calculates the number of nodes in a list
int node_count( List *list )
{
  assert(list != NULL);
  int count;
  count = 0;
  for(int i = 0; i < 256; i++){
    Node *curr = list->index[i];
    while( NULL != curr ) {
      count++;
      curr = curr->next;
    }
  }

  return count;
}

// calculates the size of a list
int size( List *list )
{
  assert(list != NULL);
  return node_count( list );
}

// print the contents of a list, one item per line
void print( List *list )
{ 
  assert(list != NULL);
  if(list != NULL){
    for(int i = 0; i < 256; i++){
      Node *curr = list->index[i];
      if(curr != NULL){
        printf("index: %d\n", i);
        while ( NULL != curr && list != NULL){
          printf( "%s\n", curr->string );
          curr = curr->next;
        }
        printf( "\n");
      }     
    }             
  }
}

// returns the total number of items traversed in the list
int traversals( )
{
  return total_num_traversals;
}

// destroy the nodes in a list
void destroy( List *list )
{
  for(int i = 0; i < 256; i++){
    Node *curr = list->index[i];
    Node *next;

    while ( NULL != curr ) {
      next = curr->next;
      free( curr->string );
      free( curr );
      curr = next;
    }
  }
  free( list );
  
}
