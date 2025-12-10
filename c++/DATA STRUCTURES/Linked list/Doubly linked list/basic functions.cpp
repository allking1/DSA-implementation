#include <bits/stdc++.h>
using namespace std;
struct node{
	int data;
	node* prev;
	node* next;
};
// tao node moi
node* create(int x){
	node *temp= new node;
	temp->data=x;
	temp->prev=nullptr;
	temp->next=nullptr;
	return temp;
}
// them node vao dau 
void insert_at_begin(node* &a,int x){
	node *temp=create(x);
	if(a==nullptr){
		a=temp;
		return;
	}
	temp->next=a;
	a->prev=temp;
	a=temp;
	return;
}
// them node vao cuoi
void insert_at_end(node *&a,int x){
	node * temp=create(x);
	if(a==nullptr) {
		a=temp;return;
	}
	node * b=a;
	while(b->next != nullptr){
		b=b->next;
	}
	b->next=temp;
	temp->prev=b;
	return;
}
// dem
int count(node *a){
	if(a==nullptr) return 0;
	int cnt=0;
	while(a!=nullptr){
		cnt++;
		a=a->next;
	}
	return cnt;
}
// them vao pos;
void insert_at_pos(node *&a,int x,int pos){
	if(pos<1 || pos > count(a)+1) return;
	if(pos==1){
		insert_at_begin(a,x); // da xet truong hop a=nullptr;
		return;
	}
	if(pos==count(a)+1){
		insert_at_end(a,x);return;
	}
	if(a==nullptr) return;
	node *temp=a;
	for(int i=1;i<pos-1;i++){
		temp=temp->next;
	}
	node *k=create(x); // tao node moi
	k->next=temp->next; 
	k->prev=temp; 
	// gan cho xong k
	temp->next->prev=k;
	temp->next=k;
	
	return;
}
// xoa dau
void erase_at_begin(node *&a){
	if(a==nullptr) return;
	if(a->next==nullptr) {
		delete a;
		a=nullptr;
		return;
		
	}
	a=a->next;
	delete a->prev;

	return;

}
// xoa cuoi
void erase_at_end(node *&a){
	if(a==nullptr) return;
	if(a->next==nullptr){
		delete a;
		a=nullptr;
		return;
	}
	node *temp=a;
	while(temp->next!=nullptr){
		temp=temp->next;
	}
	temp->prev->next=nullptr;
	delete temp;

}
// xoa giua
void erase_at_pos(node *&a,int pos){
	if(pos < 1 || pos > count(a)) return;
	if(pos==1){
		erase_at_begin(a);return;
	}
	if(pos==count(a)){
		erase_at_end(a);return;
	}
	node *temp=a;
	for(int i=1;i<pos;i++){
		temp=temp->next;
	}
	temp->prev->next=temp->next;
	temp->next->prev=temp->prev;
	delete temp;

	return;	
}






int main(){
	node *a=create(1);
	insert_at_begin(a,0);
	insert_at_pos(a,10,4);
	insert_at_end(a,2);
	insert_at_end(a,3);
	insert_at_end(a,4);
	insert_at_end(a,5);
	insert_at_end(a,6);
	insert_at_end(a,7);
	node*p=a;
	while(p!=nullptr){
		cout << p->data << endl;
		p=p->next;
	}
	cout << count(a) << endl;
	erase_at_pos(a,3);
	erase_at_end(a);
	while(a!=nullptr){
		cout << a->data << endl;
		a=a->next;
	}
	
	
}

