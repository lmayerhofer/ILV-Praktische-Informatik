/*
 * Aufgabe 1_1 - AvlTree.cpp
 * Lukas Mayerhofer
 * 27.10.12
 */

 #include "AvlTree.h"

void AvlTree::rotate_right(AvlNode* &node) {
 	AvlNode *temp = node->left;
 	node->left = temp->right;
 	temp->right = node;
	node = temp;
}

void AvlTree::rotate_right_left(AvlNode* &node) {
	rotate_right(node->right);
	rotate_left(node);
}

void AvlTree::rotate_left(AvlNode* &node) {
	AvlNode *temp = node->right;
 	node->right = temp->left;
 	temp->left = node;
	node = temp;
}

void AvlTree::rotate_left_right(AvlNode* &node) {
	rotate_left(node->left);
	rotate_right(node);
}