#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#pragma once
#include "TreeNode.h"
template<typename T>
class BinaryTree
{
public:

	BinaryTree();
	~BinaryTree();

	/// <summary>
	/// Returns whether or not there are any nodes in the list
	/// </summary>
	bool isEmpty() const;

	/// <summary>
	/// Creates a new node that stores the given value and places it into the tree
	/// </summary>
	/// <param name="value">The new value to add to the tree</param>
	void insert(T value);

	/// <summary>
	/// Finds the node with the given value and removes it from the tree
	/// </summary>
	/// <param name="value">The value of the node to search for in the tree</param>
	void remove(T value);

	/// <summary>
	/// Finds and returns a node with the given value in the tree
	/// </summary>
	/// <param name="value">The value of the node to search for</param>
	TreeNode<T>* find(T value);

	void draw(TreeNode<T>* selected = nullptr);

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent);

	void draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr);

	TreeNode<T>* m_root = nullptr;
};
#endif _BINARYTREE_H_


template<typename T>
inline TreeNode<T>* BinaryTree<T>::find(T value)
{
	bool searching = true;
	TreeNode<T>* currentNode = m_root;

	while (searching) {
		if (value > currentNode->getData()) {
			if (currentNode->hasRight())
				currentNode = currentNode->getRight();
			else break;
		}
		else if (value < currentNode->getData()) {
			if (currentNode->hasLeft())
				currentNode = currentNode->getLeft();
			else break;
		}
		else if (value == currentNode->getData())
			return currentNode;
	}

	return NULL;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* selected) {
	draw(m_root, 400, 40, 400, selected);
}

template<typename T>
inline bool BinaryTree<T>::findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent)
{
	bool searching = true;
	TreeNode<T>* currentNode = m_root;
	TreeNode<T>* currentParent = m_root;


	while (searching) {
		if (searchValue > currentNode->getData()) {
			if (currentNode->hasRight()) {
				currentParent = currentNode;
				currentNode = currentNode->getRight();
			}
			else break;
		}
		else if (searchValue < currentNode->getData()) {
			if (currentNode->hasLeft()) {
				currentParent = currentNode;
				currentNode = currentNode->getLeft();
			}
			else break;
		}
		else if (searchValue == currentNode->getData()) {
			nodeFound = currentNode;
			if (currentParent->getData() == nodeFound->getData()) {
				nodeParent == nullptr;
			}
			else nodeParent = currentParent;
			return true;
		}
	}

	return false;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected) {
	//Decrease the horizontal space as the nodes draw
	horizontalSpacing /= 2;

	//Check if the current node is null
	if (currentNode)
	{
		//Draws the left child if this node has one
		if (currentNode->hasLeft())
		{
			//Draws a line between the left child and the current node
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the right child if this node has one
		if (currentNode->hasRight())
		{
			//Draws a line between this child and the current node
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			//Draws the right child
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//Draws the current node
		currentNode->draw(x, y, (selected == currentNode));
	}
}

template<typename T>
inline BinaryTree<T>::BinaryTree() {
	m_root = nullptr;
}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
}

template<typename T>
inline bool BinaryTree<T>::isEmpty() const
{
	if (m_root == nullptr) //If there is no root, return true
		return true;
	else return false;
}

template<typename T>
inline void BinaryTree<T>::insert(T value)
{
	TreeNode<T>* newNode = new TreeNode<T>(value);

	if (m_root == NULL) {
		m_root = newNode;
		return;
	}

	bool sorting = true;
	TreeNode<T>* currentNode = m_root;

	while (sorting) {
		if (newNode->getData() > currentNode->getData()) {
			if (currentNode->hasRight()) {
				currentNode = currentNode->getRight();
			}
			else {
				currentNode->setRight(newNode);
				return;
			}
		}
		if (newNode->getData() < currentNode->getData()) {
			if (currentNode->hasLeft()) {
				currentNode = currentNode->getLeft();
			}
			else {
				currentNode->setLeft(newNode);
				return;
			}
		}
		if (newNode->getData() == currentNode->getData())
			return;
	}
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	//Creating pointers to store nodes;
	TreeNode<T>* nodeToRemove = nullptr; //going to use NTR in comments 
	TreeNode<T>* currentParent = nullptr;
	TreeNode<T>* currentNode = nullptr;

	//Checks to see if the node is in the list, and changes the node to remove and currentParent pointers
	if (!findNode(value, nodeToRemove, currentParent))
		return; //Returns from the function if the node is not in the list

	//If the node has a right...
	if (nodeToRemove->hasRight()) { 
		//Set the current node to be the node to remove's right node
		currentNode = nodeToRemove->getRight();

		//If the current node has a left node...
		if (currentNode->hasLeft()) {
			//Set the current parent to be the current node
			currentParent = currentNode;
			//Creates a bool to use with while loops
			bool searching = true;

			//While the program is searching...
			while (searching) {
				//If the current parent's left has another left...
				if (currentParent->getLeft()->hasLeft()) {
					//...set the current parent to be the current parent's left
					currentParent = currentParent->getLeft();
				}
				//Otherwise...
				else {
					//...set the current node to be the current parent's left...
					currentNode = currentParent->getLeft();
					//...and set searching to false, which breaks out of the loop
					searching = false;
				}
			}

			//Set the node to remove's data to the current node's
			nodeToRemove->setData(currentNode->getData());
			//Set the current parent to point at the current node's right
			currentParent->setLeft(currentNode->getRight());
			//Deletes the current node
			delete currentNode;
		}
		//Otherwise...
		else {
			//Set the node to remove's data to be the current node's data
			nodeToRemove->setData(currentNode->getData());

			//If the current node has a right...
			if (currentNode->hasRight()) {
				//..sets the node to remove's right to be the current node's right
				nodeToRemove->setRight(currentNode->getRight());
			}
			//Otherwise, set the node to remove's right to be nullptr
			else nodeToRemove->setRight(nullptr);
			//Deletes the current node
			delete currentNode;
		}
	}
	//Otherwise...
	else {
		//If the node to delete has a parent...
		if (currentParent) {
			//...and if the node to remove has a left node...
			if (nodeToRemove->hasLeft()) {
				//...set the current node to its left
				currentNode = nodeToRemove->getLeft();
				//If the current parent's left is the node to remove, set it to the current node
				if (currentParent->getLeft() == nodeToRemove) 
					currentParent->setLeft(currentNode);
				//Otherwise, set its right node to currentNode
				else if (currentParent->getRight() == nodeToRemove) 
					currentParent->setRight(currentNode);

				//Deletes node to remove
				delete nodeToRemove;
				return;
			}
			else {
				if (currentParent->getLeft() == nodeToRemove)
					currentParent->setLeft(nullptr);
				else if (currentParent->getRight() == nodeToRemove)
					currentParent->setRight(nullptr);
				delete nodeToRemove;
			}
		}
		else {
			if (nodeToRemove->hasLeft()) {
				currentNode = nodeToRemove->getLeft();
				m_root = currentNode;
				delete nodeToRemove;
				return;
			}
			else {
				delete nodeToRemove;
				m_root = nullptr;
			}
		}
		delete currentNode;
	}

}
