#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores
 * Person data (name, age)
 */
typedef struct person_t
{
    char* name;
    int age;
} Person;

/* Example functions given to you. If you want to truly grasp these concepts, try
 * writing your own structs and functions as well!
 */

// Create a new Person
Person* create_person(const char* name, int age)
{
    Person* p = (Person*) malloc(sizeof(Person));
    p->name = strdup(name); // Uses malloc!
    p->age = age;
    return p;
}

// Make a deep copy of a Person
void* copy_person(const void* data)
{
    Person *p = (Person*) data;
    return create_person(p->name, p->age);
}

// Print a Person
void print_person(void* data)
{
    Person *p = (Person*) data;
    printf("%s, %d\n", p->name, p->age);
}

// Free a Person
void free_person(void* data)
{
    // This is safe because we should only be passing in Person struct pointers
    Person *p = (Person*) data;
    // free any malloc'd pointers contained in the Person struct (just name)
    free(p->name);
    // Now free the struct itself; this takes care of non-malloc'd data, like age.
    free(p);
}

// Return 1 if the person's name is 8+ characters long
int long_name(const void *data)
{
	Person *p = (Person*) data;
	return strlen(p->name) > 7;
}

/* This main function does a little testing
   Like all good CS Majors you should test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void)
{
 	/* Now to make use of all of this stuff */
 	list* llist = create_list();
 
   	/* What does an empty list contain?  Lets use our handy traversal function */
   	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
   	traverse(llist, print_person);
 	printf("\n");
 
  	/* Lets add a person and then print */
  	push_front(llist, create_person("Andrew", 24));
  	printf("TEST CASE 2\nA List with one person should print that person:\n");
  	traverse(llist, print_person);
  	printf("\n");
 
  	/* Lets remove that person and then print */
  	remove_front(llist, free_person);
  	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
  	traverse(llist, print_person);
  	printf("\n");
 
  	/* Lets add two people and then print */
  	push_front(llist, create_person("Nick", 22));
  	push_front(llist, create_person("Randal", 21));
  	printf("TEST CASE 4\nA List with two people should print those two people:\n");
  	traverse(llist, print_person);
  	printf("\n");
 
 	/* Lets copy this list */
 	list* llist2 = copy_list(llist, copy_person);
 	printf("TEST CASE 5\nA copied list should print out the same two people:\n");
  	traverse(llist2, print_person);
  	printf("\n");
 
   	/* Lets kill the list */
   	empty_list(llist, free_person);
  	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
  	traverse(llist, print_person);
 	printf("\n");
 
 	/* Let's make a list of people, and remove certain ones! */
 	/* Should remove anyone whose name is 8+ characters long */
 	push_front(llist, create_person("Josephine", 27));
 	push_front(llist, create_person("Dave", 34));
 	push_front(llist, create_person("Benjamin", 23));
 	push_front(llist, create_person("Lisa", 41));
 	push_front(llist, create_person("Maximilian", 24));
 	remove_if(llist, long_name, free_person);
 	printf("TEST CASE 7\nShould only print 2 people with short names:\n");
 	traverse(llist, print_person);

 	/* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
 	/* You will get points off if you do not, you should at least test each function here */

 	/* Testing over clean up*/
	empty_list(llist, free_person);
  	free(llist);
 	empty_list(llist2, free_person);
 	free(llist2);
	list* myList = create_list();
	printf("***create a new list\n");
	printf("IS_EMPTY         : Expected: %d, actual %d\n", 1, is_empty(myList));
	printf("SIZE             : Expected: %d, actual %d\n", 0, size(myList));
	
	push_front(myList, create_person("Elisa", 21));
	printf("\n***push_front Elisa, 19\n");
	printf("IS_EMPTY         : Expected: %d, actual %d\n", 0, is_empty(myList));
	printf("SIZE             : Expected: %d, actual %d\n", 1, size(myList));
	printf("TRAVERSE	 : Expected: elisa21 actual \n");
	traverse(myList, print_person);
	printf("FRONT		 : Expected: Elisa, actual");
	print_person(front(myList));
	printf("\nBACK		 : Expected: Elisa, actual");
	print_person(back(myList));
	remove_front(myList, free_person);

	printf("\n***remove front\n");
	printf("IS_EMPTY         : Expected: %d, actual %d\n", 1, is_empty(myList));
	printf("SIZE             : Expected: %d, actual %d\n", 0, size(myList));
	printf("TRAVERSE	 : Expected: NONE actual");
	traverse(myList, print_person);

	printf("\n\n***remove front\n");
	printf("remove_front     : Expected: %d, actual %d\n", -1, remove_front(myList, free_person));
	
	push_back(myList, create_person("Elisa", 21));
	printf("\n\n***push_back Elisa, 21");
	push_back(myList, create_person("Lovissa", 20));
	printf("\n***push_back Lovissa,20");
	push_back(myList, create_person("Felly", 19));
	printf("\n***push_back Elisa, 19\n");
	printf("IS_EMPTY         : Expected: %d, actual %d\n", 0, is_empty(myList));
	printf("SIZE             : Expected: %d, actual %d\n", 3, size(myList));
	printf("TRAVERSE	 : Expected: elisa21 lovissa20 felly19 actual \n");
	traverse(myList, print_person);
	printf("FRONT		 : Expected: Elisa, actual");
	print_person(front(myList));
	printf("BACK		 : Expected: felly, actual");
	print_person(back(myList));

	printf("\n\n***copy list\n");
	list* myListCopy = copy_list(myList, copy_person);
	remove_front(myListCopy, free_person);
	printf("IS_EMPTY         : Expected: %d, actual %d\n", 0, is_empty(myListCopy));
	printf("SIZE             : Expected: %d, actual %d\n", 2, size(myListCopy));
	printf("TRAVERSEcpy	 : Expected: elisa21 lovissa20 felly19 actual \n");
	traverse(myListCopy, print_person);
	printf("FRONT		 : Expected: Lovissa, actual");
	print_person(front(myList));
	printf("BACK		 : Expected: felly, actual");
	print_person(back(myList));
	printf("\n\nthe original list:\n");
	printf("IS_EMPTY         : Expected: %d, actual %d\n", 0, is_empty(myList));
	printf("SIZE             : Expected: %d, actual %d\n", 3, size(myList));
	printf("TRAVERSEorg	 : Expected: elisa21 lovissa20 felly19 actual \n");
	traverse(myList, print_person);
	printf("FRONT		 : Expected: Elisa, actual");
	print_person(front(myList));
	printf("BACK		 : Expected: felly, actual");
	print_person(back(myList));


		
	printf("\n");
	empty_list(myList, free_person);
	empty_list(myListCopy, free_person);

	printf("\n\n***empty original list\n");
	printf("IS_EMPTYorg      : Expected: %d, actual %d\n", 1, is_empty(myList));
	printf("SIZE             : Expected: %d, actual %d\n", 0, size(myList));
	printf("TRAVERSEorg	 : Expected: NONE actual \n");
	traverse(myList, print_person);
	printf("\n\n***empty copy list\n");
	printf("IS_EMPTYcpy      : Expected: %d, actual %d\n", 1, is_empty(myList));
	printf("SIZE             : Expected: %d, actual %d\n", 0, size(myList));
	printf("TRAVERSEcpy	 : Expected: NONE actual \n");
	traverse(myListCopy, print_person);


	free(myList);
	free(myListCopy);
  	
	return 0;
}

