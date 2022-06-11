 #include <iostream>
 #include <utility>

 using namespace std;


 class Pair
 {
	//TODO : Inplement Pair class
  public:
    int row;
    int col;
 };

 struct ListNode{
 	Pair data;
	ListNode * next;
 };

 class Stack
 {

	int stackSize;

	public:

		Stack();
		void push(Pair item);
		Pair pop();
		ListNode *head;
};
