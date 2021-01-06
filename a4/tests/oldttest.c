#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 128
struct record
{
  char last_name[STRLEN];
  char first_name[STRLEN];
  char phone_number[13];
};

void print_tree( struct Node *node, char indent[100]){
    char indent_with_connect[100];
    char indent0[100];
    char indent1[100];
 
    // make a copy of indent with the last two characters replaced by +-
    strcpy( indent_with_connect, indent );
    strcpy( indent_with_connect + strlen(indent_with_connect)-2, "+-");
 
    if (node)
    {
        int *temp = node->data;
        printf("%s", indent_with_connect);
        printf(" %d\n", *temp);
 
        // add vertical line to indent
 
        strcpy( indent0, indent );
        strcat( indent0, "| " );
 
        print_tree( node->lt, indent0 );
        //add two spaces to the indent
        strcpy( indent1, indent );
        strcat( indent1, "  ");
 
        print_tree( node->gte, indent1);
    }
    else
    {
        printf("%s", indent_with_connect);
        printf("NULL\n");
    }
}


int comp_first_name( const void *ptr1, const void *ptr2 )
{
  const struct record *rec1, *rec2;
  int result;

  rec1 = ptr1;
  rec2 = ptr2;

  result = strcmp( rec1->first_name, rec2->first_name );

#ifdef DEBUG
  printf( "strcmp( \"%s\", \"%s\" )=%d\n", 
          rec1->first_name, rec2->first_name, result );
#endif
  return result;
}

int comp_last_name( const void *ptr1, const void *ptr2 )
{
  const struct record *rec1, *rec2;
  int result;

  rec1 = ptr1;
  rec2 = ptr2;

  result = strcmp( rec1->last_name, rec2->last_name );
#ifdef DEBUG
  printf( "strcmp( \"%s\", \"%s\" )=%d\n", 
          rec1->last_name, rec2->last_name, result );
#endif
  return result;
}

int main( int argc, char **argv )
{
  FILE *fp;
  int result;
  char buffer[256];

  struct record record;
  struct Node *by_last_name=NULL;
  struct Node *by_first_name=NULL;
  struct Performance *performance = newPerformance();

  // read names and phone numbers for the file, into record
  // add record to two different trees
  fp = fopen( "names1.txt", "r" );
  fgets( buffer, 256, fp );

  while (!feof(fp))
  {
    result = fscanf( fp, "%s %s", record.first_name, record.last_name );
    result += fscanf( fp, "%s", record.phone_number );

    if (result==3)
    {
      printf( "Adding %s, %s\n", record.last_name, record.first_name );
      addItem( performance, &by_last_name, &comp_last_name, 
  	       &record, sizeof(record) );

      addItem( performance, &by_first_name, &comp_first_name, 
	       &record, sizeof(record) );
    }
  }
  printf("PERFORMANCE\nreads: %d\nwrites: %d\nmallocs: %d\nfrees: %d\n", performance->reads, performance->writes, performance->mallocs, performance->frees);
  
  printf( "Trees built\n" );

  strcpy( record.last_name, "Pollard" );
  searchItem( performance, &by_last_name, &comp_last_name,
              &record, sizeof(record) );
  printf( "%s, %s.....%s\n", record.last_name, record.first_name, 
                             record.phone_number );

  strcpy( record.first_name, "Frida" );
  searchItem( performance, &by_first_name, &comp_first_name,
              &record, sizeof(record) );
  printf( "%s, %s.....%s\n", record.last_name, record.first_name, 
                             record.phone_number );
  //print_tree(by_first_name, ""); 
  freeTree( performance, &by_last_name );
  freeTree( performance, &by_first_name );
  fclose(fp);
  printf("PERFORMANCE\nreads: %d\nwrites: %d\nmallocs: %d\nfrees: %d\n", performance->reads, performance->writes, performance->mallocs, performance->frees);
  free(performance); 
}
