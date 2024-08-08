#ifndef INDEX_LIST_H
#define INDEX_LIST_H 


typedef enum BOOL{false, true} boolean;

typedef struct NODE Node;
struct NODE;

typedef struct LIST List;
struct LIST;

List *construct();
boolean insert( List *list, char *new_string );
boolean find( List *list, char *target );
int node_count( List *list );
int size( List *list );
void print( List *list );
int traversals( );
void destroy( List *list );

#endif 