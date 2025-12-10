#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct node{ // trong C++ khong can phai ghi struct node chi can ghi node cung la 1 kieu du lieu
	int data; // co the thay bang struct data neu can luu tru nhieu
	struct node *next;
};

node* create(int x){
	node* newnode=new node; // cap phat bo nho tren heap ( cu phap cua C++ )
	// doi voi C node *u=(node*)malloc(sizeof(node)) ;
	newnode->data=x;
	newnode->next=NULL;
	return newnode;
}
// them vao cuoi
void insert_at_end(node *&a,int x){ // ta truyen tham tri de thay doi con tro a neu a la null
	if(a==NULL){
		a=create(x);
		return;
	}
	node *temp=a; // khoang lam mat dia chi cua node head
	while(temp->next!=NULL){
		temp=temp->next;
	}
	node *newnode=create(x);
	temp->next=newnode;
	return;
	
}
// them vao dau 
void insert_at_begin(node *&a,int x){
	if(a==NULL){
		a=create(x);
		return;
	}
	node *newnode=create(x); 
	newnode->next=a; 
	a=newnode;
}
// dem so phan tu
int count(node *a){ // khong can thay doi node a, neu ta truyen & thi se mat node head.
	int cnt=0;
	while(a!=NULL){
		cnt++;
		a=a->next;
	}
	return cnt;
	
}
void insert_at_pos(node *&a,int x,int pos){
	if(a==NULL){
		a=create(x);
		return;
	}
	if(pos==1) insert_at_begin(a,x);
	else if(pos==count(a)+1) insert_at_end(a,x);
	else {
		
		node *newnode=create(x);
		node *left=a;node *right=a->next;
		for(int i=0;i<pos-2;i++){
			left=left->next;
			right=right->next;
		}
		newnode->next=right;
		left->next=newnode;
		/* cach khac 
		node *newnode=create(x);
		node *temp=a;
		for(int i=0;i<pos-2;i++) temp=temp->next; 
		// dich den phan tu truoc pos 1 don vi
		newnode->next=temp->next; 
		// noi newnode vao vi tri sau pos;
		temp->next=newnode; 
		// noi phan tu truoc pos 1 don vi vao pos;
		*/
		
	}
	return;
	
}
// xoa dau
void erase_at_begin(node*& a) {
	if (a == NULL) return;
	node* temp = a;
	a = a->next;
	delete temp;
	return;
}
// xoa cuoi
void erase_at_end(node*& a) {
	if (a == NULL) return;
	if (a->next == NULL) {
		delete a;
		a = NULL;
		return;
	}
	node* temp = a;
	while (temp->next->next != NULL) {
		temp = temp->next;
	}
	delete temp->next;
	temp->next = NULL;
	return;
}
// xoa giua
void erase_at_pos(node*& a, int pos) {
	if (a == NULL || pos <1 || pos > count(a) ) return;
	if (pos == 1) {
		erase_at_begin(a);
		return;
	}
	else if (pos == count(a)) {
		erase_at_end(a);
		return;
	}
	node* temp = a;
	for (int i = 0;i < pos - 2;i++) {
		temp = temp->next;
	}
	node* k = temp->next->next;
	delete temp->next;
	temp->next = k;
	return;

}
	



int main(){
	node *a=create(1); // node head

	insert_at_end(a,2);
	insert_at_begin(a,3);
	cout << count(a) << endl;
	insert_at_pos(a,10,1);
	while(a != NULL){
		cout << a->data << endl;
		a=a->next;
	}




    	
	
	

	
	

	
}

