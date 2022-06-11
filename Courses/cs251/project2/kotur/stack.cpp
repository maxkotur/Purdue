 #include "stack.h"
 #include <utility>

 using namespace std;


 Stack::Stack()
 {
	 //TODO: Write the constructor
   head = NULL;
   stackSize = 0;
 }

 void Stack::push(Pair p)
 {
	 //TODO: Write the push method
   ListNode *temp = new ListNode;
   temp->data = p;
   temp->next = head;
   head = temp;
   stackSize++;
 }

 Pair Stack::pop()
 {
	//TODO: Write the pop method
  if (head != NULL) {
    Pair p;
    p = head->data;
    ListNode *temp = head;
    head = temp->next;
    temp->next = NULL;
    free(temp);
    temp = NULL;
    stackSize--;
    return p;
  }
  Pair bad;
  bad.row = -1;
  bad.col = -1;
 	return bad;
 }
