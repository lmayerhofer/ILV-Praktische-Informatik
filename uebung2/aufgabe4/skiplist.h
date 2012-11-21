#ifndef SKIPLIST_H
#define SKIPLIST_H

template<typename Tkey, typename Tdata> class Skiplist {
	public:
		Skiplist(int levelMax) : levelMax(levelMax), head(...) { }
		~Skiplist() { };

		int generateRandomLevel() {
			/*
			Calculate random Level
			*/
		}

		bool insert(Tkey key, Tdata data) {
			/*
			Get random level => Level of Node = generateRandomLevel()
			If level > levelMax => update levelMax
			New node has number of level pointers
			Search given key in List => search(key)
			Splice and insert node (next pointer to next node) => return true
			*/
		}

		Tdata search(Tkey key) {
			/*
			TRAVERSING NODES BY NEXT-POINTER
			Start at the first position of the first node (head)
			Compare the key of the current position (x) with the key of next node (y)
			if(x > y)  => if there is a next node => move to next node
			if(x <= y) => move one level down, if we are at the bottom list (level 1) => key not found => return current node (if search is used for insert)
			if(x == y) => element in node found => return element
			*/
		}

	private:
		int levelMax;
		Node* head;			

		struct Node {
			Tkey key
			Tdata data;
			int level;
			Node **next;

			// Contructor & Destructor
			Node(Tkey key, Tdata data, int level) : key(key), data(data), level(level), next(new node*[size]) {}
			~Node() {}
		};
};

#endif