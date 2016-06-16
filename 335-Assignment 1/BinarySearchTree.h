#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <iostream>
#include <algorithm>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:

  int insertCount, containsCount, removeCount; 

  BinarySearchTree( );

    /**
     * Copy constructor
     */
  BinarySearchTree( const BinarySearchTree & rhs );

    /**
     * Move constructor
     */
  BinarySearchTree( BinarySearchTree && rhs );
    
    /**
     * Destructor for the tree
     */
  ~BinarySearchTree( );

    /**
     * Copy assignment
     */
  BinarySearchTree & operator=( const BinarySearchTree & rhs );
        
    /**
     * Move assignment
     */
  BinarySearchTree & operator=( BinarySearchTree && rhs );
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
  const Comparable & findMin( ) const;

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
  const Comparable & findMax( ) const;

    /**
     * Returns true if x is found in the tree.
     */
  bool contains( Comparable & x );

    /**
     * Returns element if found in the tree 
     */
  Comparable find( Comparable & x );

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
  bool isEmpty( ) const;

    /**
     * Print the tree contents in sorted order.
     */
  void printTree(ostream &out = cout) const;

    /**
     * Make the tree logically empty.
     */
  void makeEmpty( );

    /**
     * Insert x into the tree; duplicates are ignored.
     */
  void insert( Comparable & x );
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
  void insert( Comparable && x );
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
  void remove( Comparable & x );

    /**
     * Returns number of nodes in the tree. 
     */
  int nodes();

    /**
     * Returns internal path length of the tree. 
     */
  int internalPathLength();


  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt ) : element( theElement ), left( lt ), right( rt ) { } 
        
    BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt ) : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable & x, BinaryNode * & t );
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t );

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( Comparable & x, BinaryNode * & t );

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const;

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const;

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( Comparable & x, BinaryNode *t );

    /**
     * Internal method that returns element if found in the tree 
     */
    Comparable find( Comparable & x, BinaryNode *t );

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t );

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream &out ) const;

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const;

    /**
     *Internal method to return number of nodes in the tree
     */
    int nodes(BinaryNode *t);

    /**
     *Internal method to return internal path length of the tree
     */
    int internalPathLength(BinaryNode *t, int depth);
};

#endif
