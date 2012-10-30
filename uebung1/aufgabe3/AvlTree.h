/*
 * Aufgabe 1_1 - AvlTree.h
 * Lukas Mayerhofer
 * 27.10.12
 */

class AvlTree {
	public:
    	AvlTree() : root(0) { }

		void insert(double d) {
			if (!root) root = new AvlNode(d);
            else insert(root, d);
        }

		void print() const { print(root); }

		unsigned getHeight() { return height(root); }
	
	private:
		struct AvlNode {
			AvlNode(double d) : data(d), left(0), right(0) { }
			double data;
			AvlNode *left, *right;
		};

		void print(AvlNode *node) const {
			if (!node) return;
			print(node->left);
			printf("%.2f (%d)\n", node->data, height(node));
			print(node->right);
		}

		unsigned height(AvlNode *node) const {
			if (!node) return 0;
			return 1 + std::max(height(node->left), height(node->right));
		}

		void rotate_right(AvlNode* &node);
		void rotate_right_left(AvlNode* &node);
		void rotate_left(AvlNode* &node);
		void rotate_left_right(AvlNode* &node);
		
		void insert(AvlNode* &node, double d) {
			if (!node) node = new AvlNode(d);
			if (d < node->data) { insert(node->left, d);
			if (height(node->left) - height(node->right) == 2) {
				if (d < node->left->data) rotate_right(node);
				else rotate_left_right(node); }
			}
			else if (d > node->data) {
        			insert(node->right, d);
				if (height(node->right) - height(node->left) == 2) {
					if (d > node->right->data) rotate_left(node);
					else rotate_right_left(node);
				}
			}
		}

		AvlNode *root;
};