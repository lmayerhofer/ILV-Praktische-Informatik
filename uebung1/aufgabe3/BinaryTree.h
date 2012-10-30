/*
 * Aufgabe 1_1 - BinaryTree.h
 * Lukas Mayerhofer
 * 27.10.12
 */

class BinaryTree {
	public:
    	BinaryTree() : root(0) { }

		void insert(double d) {
			if (!root) root = new Node(d);
            else insert(root, d);
        }

		void print() const { print(root); }

		unsigned getHeight() { return height(root); }

	private:
		struct Node {
			Node(double d) : data(d), left(0), right(0) { }
			double data;
			Node *left, *right;
		};

		void print(Node *node) const {
			if (!node) return;
			print(node->left);
			printf("%.2f (%d)\n", node->data, height(node));
			print(node->right);
		}
		
		unsigned height(Node *node) const {
			if (!node) return 0;
			return 1 + std::max(height(node->left), height(node->right));
		}

		void insert(Node* &node, double d) {
			if (!node) node = new Node(d);
			if (d < node->data)
				insert(node->left, d);
			else if (d > node->data)
				insert(node->right, d);
		}

		Node *root;
};