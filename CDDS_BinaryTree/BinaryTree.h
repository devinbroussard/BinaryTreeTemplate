#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#pragma once
#include "TreeNode.h"
template<typename T>
class BinaryTree
{
public:

	BinaryTree(); //Initializes variables
	~BinaryTree(); //Deallocates memory of binary tree

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

	void draw(TreeNode<T>* selected = nullptr); //Calls the private draw function on the node gien

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent);

	//Calls the draw function for the given node and its children
	void draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr); 

	TreeNode<T>* m_root = nullptr; //Stores the root node of the binary tree
};
#endif _BINARYTREE_H_


template<typename T>
inline TreeNode<T>* BinaryTree<T>::find(T value)
{
	bool searching = true; //Used for while loop
	TreeNode<T>* currentNode = m_root; //Used to loop through the tree

	//While searching for the value...
	while (searching) { 
		//if the current node's data is less than the value given...
		if (value > currentNode->getData()) {
			//If the current node has a right child, set the current node to the current's right
			if (currentNode->hasRight())
				currentNode = currentNode->getRight();
			//Otherwise, stop searching because the value isn't in the tree
			else searching = false;
		}
		//If the current node's data is greather than the value given...
		else if (value < currentNode->getData()) {
			//Check to see if the current node has a left...
			if (currentNode->hasLeft())
				currentNode = currentNode->getLeft(); //..and if it has one, then set the current node to be its left
			//Otherwise, stop searching because the value isn't in the tree
			else searching = false;
		}
		//If the value is equal to the current node's data...
		else if (value == currentNode->getData())
			return currentNode; //Return the current node
	}

	return NULL; //Return NULL by default
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* selected) {
	draw(m_root, 400, 40, 400, selected);
}

template<typename T>
inline bool BinaryTree<T>::findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent)
{
	//If there is nothing in the tree, return false
	if (m_root == nullptr)
		return false;

	bool searching = true; //Used to break out of the while loop and stop searching
	TreeNode<T>* currentNode = m_root; //Used to hold the current node
	TreeNode<T>* currentParent = m_root; //Used to hold the parent of the current node

	//Used to search through the tree for the node 
	while (searching) {
		//If the search value is greater than the current node's data...
		if (searchValue > currentNode->getData()) {
			//Then check if the current node has a right....
			if (currentNode->hasRight()) {
				currentParent = currentNode; //If so, set the parent to the current node
				currentNode = currentNode->getRight(); //Then set the current node to the right
			}
			//Else, the search value is not in the list, so stop searching
			else searching = false; 
		}
		//If the search value is less than the current node's data...
		else if (searchValue < currentNode->getData()) {
			//Then check to see if the current node has a left...
			if (currentNode->hasLeft()) {
				currentParent = currentNode; //If so, then set the current parent to the current node
				currentNode = currentNode->getLeft(); //Set the current node to be the left
			}
			//Else, the serach vlaue is not in the list, so stop searching
			else searching = false;
		}
		//If the search value is equal to the current node's data
		else if (searchValue == currentNode->getData()) {
			//Set node found to be the current node
			nodeFound = currentNode;
			//If the current node was the first node found...
			if (currentParent->getData() == nodeFound->getData()) {
				nodeParent == nullptr; //Set the node's parent to nullptr
			}
			//Otherwise, set the node's parent to the current parent
			else nodeParent = currentParent; 
			return true; //Return true because the node was found
		}
	}

	return false; //Returns false by default
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
inline BinaryTree<T>::~BinaryTree() {
	while (m_root)
		remove(m_root->getData());
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
	TreeNode<T>* newNode = new TreeNode<T>(value); //A node created that holds the value given

	//If the tree is currently empty...
	if (m_root == NULL) {
		m_root = newNode; //Set the new node to be the new root..
		return; //...and return from the function
	}

	bool searching = true; //Used to sort the new node into the tree
	TreeNode<T>* currentNode = m_root; //Used loop through the tree into the spot where the new node belongs

	//While searching for the new node's location...
	while (searching) {
		//If the new node's data is greater than the current node's data...
		if (newNode->getData() > currentNode->getData()) {
			//Check to see if the current node has a right...
			if (currentNode->hasRight()) {
				//If so, then set the current node to be the current node's right
				currentNode = currentNode->getRight();
			}
			else {
				//Otherwise, set the current node's right to be the new node
				currentNode->setRight(newNode);
				searching = false; //Stop searching
			}
		}
		//If the new node's data is less than the current node's data...
		if (newNode->getData() < currentNode->getData()) {
			//Check to see if the current node has a left...
			if (currentNode->hasLeft()) {
				//...and if so, set the current node to the left
				currentNode = currentNode->getLeft();
			}
			else {
				//Otherwise, set the current node's left to be the new node
				currentNode->setLeft(newNode);
				searching = false; //Stop searching
			}
		}
		//If the new node's data is equal to the current node's data...
		if (newNode->getData() == currentNode->getData())
			searching = false; //Stop searching
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

				//Deletes node to remove, and returns
				delete nodeToRemove;
				return;
			}
			//Otherwise...
			else {
				//Set the parents pointer to the node to remove to null
				if (currentParent->getLeft() == nodeToRemove)
					currentParent->setLeft(nullptr);
				else if (currentParent->getRight() == nodeToRemove)
					currentParent->setRight(nullptr);
				//Delete the node to remove
				delete nodeToRemove;
			}
		}
		//Otherwise...
		else {
			//If the node to remove has a left..
			if (nodeToRemove->hasLeft()) {
				//Set the current node to the node to remove's left
				currentNode = nodeToRemove->getLeft();
				//Set the root to the current node
				m_root = currentNode;
				//Delete the node to remove, and return
				delete nodeToRemove;
				return;
			}
			else {
				//Delete the node to remove, and set root to nullptr
				delete nodeToRemove;
				m_root = nullptr;
			}
		}
		//Deletes the current node
		delete currentNode;
	}

}
