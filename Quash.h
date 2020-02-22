
#ifndef QUASH_H
#define QUASH_H

#include <string>
#include <vector>
#include <list>

class Quash {
	public:
		Quash();
		void insert(int i);
		void lookup(int i);
		void deleteMin(bool min);
		void deleteElement(int i);
		void print();
		void heapify(int i);
		void decreaseKey(int i , int val);
		void createQuash(std::string str);
		void performOp(std::string str);

	private:
		struct Node {
			int key, count, position;
			Node* point;
		};

		int total;
		int totalCount;
		std::list<Node> *hash[43];
		std::vector<Node*> *heap;
		void insertHeap(Node *n);
};

#endif
