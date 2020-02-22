#include "Quash.h"
#include <string>
#include <iostream>
#include <climits>

using namespace std;

int hashKey(int k)
{
	k = k % 43;
	if(k < 0)
	{k += 43;}
	return k;
}

Quash::Quash(){
	this->total = 0;
	this->totalCount = 0;
	for(int i = 0; i < 43; i++)
	{
		this->hash[i] = new list<Node>;
	}
	this->heap = new vector<Node*>;
	Node *zero = new Node;
	zero->key = 0;
	zero->count = -1;
	zero->point = NULL;
	this->heap->push_back(zero);
}

void Quash::insert(int i) {
	int k = hashKey(i);
	int listSize = this->hash[k]->size();
	if(listSize <= 0)
	{
		this->total++;
		this->totalCount++;
		Node* n1 = new Node;
		n1->key = i;
		n1->count = 0;
		n1->position = -1;
		Node* n2 = new Node;
		n2->key = i;
		n2->count = 1;
		n2->position = 0;
		n1->point = n2;
		n2->point = n1;
		this->hash[k]->push_front(*n1);
		this->insertHeap(n2);
	}
	else
	{
		bool found = false;
		int j = 0;
		list<Node>::iterator it = this->hash[k]->begin();
		while(found == false && j < listSize)
		{
			if(it->key == i)
			{found = true;}
			else
			{
				it++;
				j++;
			}
		}
		if(found == true)
		{	
		//	it->count++;
			it->point->count++;
			this->totalCount++;
			cout << "item successfully inserted, count = ";
			cout << it->point->count << endl;
			return;
		}
		else
		{
			this->total++;
			this->totalCount++;
			Node *n3 = new Node;
			n3->key = i;
			n3->count = 0;
			n3->position = -1;
			Node *n4 = new Node;
			n4->key = i;
			n4->count = 1;
			n4->position = 0;
			n3->point = n4;
			n4->point = n3;
			this->hash[k]->push_front(*n3);
			this->insertHeap(n4);
		}
	}
}

void Quash::insertHeap(Node *n) {
	int i = this->total;
	n->position = i;
	this->heap->push_back(n);
	while(i > 1 && this->heap->at(i/2)->key > this->heap->at(i)->key)
	{
		swap(this->heap->at(i), this->heap->at(i/2));
		int temp = this->heap->at(i)->position;
		this->heap->at(i)->position = this->heap->at(i/2)->position;
		this->heap->at(i/2)->position = temp;
		i = i/2;
	}
	cout << "item successfully inserted, count = 1" << endl;
}

void Quash::heapify(int i) {
	int l = 2*i;
	int r = 2*i+1;
	int smallest = i;
	if(l <= this->total && this->heap->at(l)->key < this->heap->at(smallest)->key)
	{smallest = l;}
	if(r <= this->total && this->heap->at(r)->key < this->heap->at(smallest)->key)
	{smallest = r;}
	if(smallest != i)
	{
		swap(this->heap->at(i), this->heap->at(smallest));
		int temp = this->heap->at(i)->position;
		this->heap->at(i)->position = this->heap->at(smallest)->position;
		this->heap->at(smallest)->position = temp;
		heapify(smallest);
	}
}

void Quash::lookup(int i) {
	int k = hashKey(i);
	int listSize = this->hash[k]->size();
	if(listSize <= 0)
	{
		cout << "item not found" << endl;
	}
	else
	{
		bool found = false;
		int j = 0;
		list<Node>::iterator it = this->hash[k]->begin();
		while(found == false && j < listSize)
		{
			if(it->key == i)
			{found = true;}
			else
			{
				it++;
				j++;
			}
		}
		if(found == true)
		{
			cout << "item found, count = ";
			cout << it->point->count << endl;
		}
		else
		{
			cout << "item not found" << endl;
		}
	}
}

void Quash::deleteMin(bool min) {
	if(this->total <= 0 && min == true)
	{
		cout << "min item not present since table is empty" << endl;
		return;
	}
	int value = this->heap->at(1)->point->key;
	int c = this->heap->at(1)->count;
		if(c > 1)
		{
			c--;
			this->heap->at(1)->count--;
		//	this->heap->at(1)->point->count--;
			this->totalCount--;
			if(min == true)
			{
			cout << "min item = " << value << ", count decremented, ";
			cout << "new count = " << c << endl;
			}
			return;
		}
	else if(this->total == 1)
	{
		int k = hashKey(this->heap->at(1)->point->key);
		list<Node>::iterator it = this->hash[k]->begin();
		this->total = 0;
		this->totalCount = 0;
		delete this->heap->at(1)->point;
		delete this->heap->at(1);
		this->heap->at(1) = NULL;
		this->heap->pop_back();
		this->hash[k]->erase(it);
		if(min == true)
		{cout << "min item " << value << " successfully deleted" << endl;}
	}
	else
	{	if(min == true)
		{cout << "min item " << value << " successfully deleted" << endl;}
		int t = this->total;
		int val = this->heap->at(1)->point->key;
		int k = hashKey(val);
		list<Node>::iterator it = this->hash[k]->begin();
		bool found = false;
		while(found == false)
		{
			if(it->key == val)
			{found = true;}
			else
			{it++;}
		}	
		swap(this->heap->at(1), this->heap->at(t));
		this->heap->at(1)->position = 1;
		this->total--;
		this->totalCount--;
		delete this->heap->at(t)->point;
		delete this->heap->at(t);
		this->heap->at(t) = NULL;
		this->heap->pop_back();
		this->hash[k]->erase(it);
		heapify(1);
	}
		


}

void Quash::decreaseKey(int i , int val) {
	if(i == 1)
	{return;}
	this->heap->at(i)->key = val;
	while(i > 1 && this->heap->at(i/2)->key > this->heap->at(i)->key)
	{
		swap(this->heap->at(i/2), this->heap->at(i));
		int temp = this->heap->at(i)->position;
		this->heap->at(i)->position = this->heap->at(i/2)->position;
		this->heap->at(i/2)->position = temp;
		i = i/2;
	}
}

void Quash::deleteElement(int i) {
	int k = hashKey(i);
	list<Node>::iterator it = this->hash[k]->begin();
	bool found = false;
	while(it != this->hash[k]->end() && found == false)
	{
		if(it->key == i)
		{found = true;}
		else
		{it++;}
	}
	if(found == false)
	{
		cout << "item not present in the table" << endl;
		return;
	}
	else
	{
		int count = it->point->count;
		if(count > 1)
		{
		//	it->count--;
			it->point->count--;
			int a = it->point->count;
			this->totalCount--;
			cout << "item count decremented, new count = " << a << endl;
			return;
		}
		bool pureMin = false;
		decreaseKey(it->point->position, INT_MIN);
		deleteMin(pureMin);
		cout << "item successfully deleted" << endl;
	}
}

void Quash::createQuash(string str) {
	int length = str.length();
	string comma = ",";
	int j = 0;
	for(int i = 0; i < length; i++)
	{
		string ch = str.substr(i, 1);
		if(comma.compare(ch) == 0)
		{
			string op = str.substr(j, i-j);
			this->performOp(op);
			j = i+2;
		}
		else if((i+1) == length)
		{
			string lastOp = str.substr(j, length-j);
			this->performOp(lastOp);
		}
	}

}

void Quash::performOp(string str) {
	int length = str.length();
	string print = "print";
	string insert = "insert ";
	string lookup = "lookup ";
	string del = "delete ";
	string delMin = "deleteMin";
	if(print.compare(str.substr(0, 5)) == 0)
	{
		this->print();
		return;
	}
	if(insert.compare(str.substr(0,7)) == 0)
	{
		int num1 = stoi(str.substr(7, length-7)); 
		this->insert(num1);
		return;
	}
	if(lookup.compare(str.substr(0,7)) == 0)
	{
		int num2 = stoi(str.substr(7,length-7));
		this->lookup(num2);
		return;
	}
	if(del.compare(str.substr(0,7)) == 0)
	{
		int num3 = stoi(str.substr(7, length-7));
		this->deleteElement(num3);
		return;
	}
	if(delMin.compare(str.substr(0,9)) == 0)
	{
		this->deleteMin(true);
		return;
	}
}

void Quash::print() {
	for(int i = 1; i <= this->total; i++)
	{
		if(i == this->total)
		{
			cout << this->heap->at(i)->key << endl;
		}
		else
		{
			cout << this->heap->at(i)->key << " ";
		}
	}
}

int main(int argc, char* argv[]) {
	Quash q;
	q.createQuash(argv[1]);
	return 0;
}
