**Devin Brousard**  
s218014  
Code Design and Data Structures  
Binary Tree Demo
  
## **I. Requirements:**  
### 1. Description of Problem: 
* **Name:** Binary Tree Demo
* **Problem Statement:**   
    * Implement a Binary Tree
* **Problem Specifications:**  
    * Successful creation of a project which implemetns and demonstrates a binary tree
      * The created program must maintain an ordered tree
      * The created program demonstrates insertion and removal of ndoes
      * The created program allows the user to search for a value in the tree
      * The created program uses a third-party library
    * Project submitted as an executable binary file that can be run external to an IDE
    * Source code and project files also submitted for review  
### 2. Input Information:
* The demonstration allows the user to add and remove values up to 100 to a binary tree.
### 3. Output Information:
* The demonstration draws the binary tree to the screen for better visualization.
  
## **II. Design:**
### 1. System Architecture: 
* The binary tree is composed of the binary tree and tree node classes. The tree nodes are added to the binary tree when a new value is added, and sorted apropriately. The tree node class is responsible for adding and deleting new nodes, sorting the nodes, and calling the nodes' draw function.
### 2. Object Information:
*  File name: BinaryTree.h
    * Name: BinaryTree()
      * Description: Creates a new Binary Tree with default values
      * Visibility: Public
      * Arguments: None
    * Name: ~BinaryTree()
      * Description: Deallocates the binary tree's memory upon deletion
      * Visibility: Public
      * Arguments: None
    * Name: isEmpty(bool) const
      * Description: Returns whether or not there are any nodes in the list
      * Visibility: Public
      * Arguments:  None
    * Name: insert()
      * Description: Creates a new node that stores the given value and places it into the tree
      * Visibility: Public
      * Arguments: T value
    * Name: remove()
      * Description: Finds the node with the given value and removes it form the tree
      * Visibility: Public
      * Arguments: T value
    * Name: find(TreeNode&lt;T>*)
      * Description: Finds and returns a node with the given value in the tree
      * Visibility: Public
      * Arguments: T value
    * Name: draw()
      * Description: Calls the private draw function on the node given
      * Visibility: Public
      * Arguments: TreeNode&lt;T>* selected = nullptr
    * Name: findNode(bool)
      * Description: Finds the node that matches the value in the list
      * Visibility: Private
      * Arguments: T searchValue, TreeNode&lt;T>*& nodeFound, TreeNode&lt;T> *& nodeParent
    * Name: draw()
      * Description: Calls the draw function for the current node and all of its children 
      * Visibility: Private
      * Arguments: TreeNode&lt;T>* currentNode, int x, int y, int horizontalSpacing, TreeNode&lt;T>* selected = nullptr)
    * Name: m_root(TreeNode&lt;T>* m_root = nullptr;)
      * Description: Stores the root node of the binary tree
      * Visibility: Private