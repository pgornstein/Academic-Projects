#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <iostream>
#include <vector>
#include "dsexceptions.h"
using namespace std;

// Binomial queue class, header file
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( )           --> Return and remove smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinomialQueue
{
  public:

  int comparisonCount, assignmentCount;

  BinomialQueue( );

  BinomialQueue( const Comparable & item );

  BinomialQueue( const BinomialQueue & rhs );

  BinomialQueue( BinomialQueue && rhs );

  ~BinomialQueue( );

    struct BinomialNode
    {
        Comparable    element;
        BinomialNode *leftChild;
        BinomialNode *nextSibling;
        BinomialNode *parent;

    BinomialNode( const Comparable & e, BinomialNode *lt, BinomialNode *rt, BinomialNode *p )
    : element{ e }, leftChild{ lt }, nextSibling{ rt }, parent{ p } { }
        
    BinomialNode( Comparable && e, BinomialNode *lt, BinomialNode *rt, BinomialNode *p )
    : element{ std::move( e ) }, leftChild{ lt }, nextSibling{ rt }, parent{ p } { }
    };

    
    /**
     * Deep copy.
     */
  BinomialQueue & operator=( const BinomialQueue & rhs );
        
    /**
     * Move.
     */
  BinomialQueue & operator=( BinomialQueue && rhs );
    
    /**
     * Return true if empty; false otherwise.
     */
  bool isEmpty( ) const;

    /**
     * Returns minimum item.
     * Throws UnderflowException if empty.
     */
  const Comparable & findMin( ) const;
    
    /**
     * Insert item x into the priority queue; allows duplicates.
     */
  BinomialNode * insert( const Comparable & x );

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
  BinomialNode * insert( Comparable && x );
    
    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     */
  void deleteMin( );

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
  void deleteMin( Comparable & minItem );

    /**
     * Make the priority queue logically empty.
     */
  void makeEmpty( );

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     */
  void merge( BinomialQueue & rhs );   

    const static int DEFAULT_TREES = 1;

    vector<BinomialNode *> theTrees;  // An array of tree roots
    int currentSize;                  // Number of items in the priority queue
    
    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     */
    int findMinIndex( ) const;

    /**
     * Return the capacity.
     */
    int capacity( ) const;

    /**
     * Return the result of merging equal-sized t1 and t2.
     */
    BinomialNode * combineTrees( BinomialNode *t1, BinomialNode *t2 );

    /**
     * Make a binomial tree logically empty, and free memory.
     */
    void makeEmpty( BinomialNode * & t );

    /**
     * Internal method to clone subtree.
     */
    BinomialNode * clone( BinomialNode * t ) const;
};

#include "BinomialQueue.cpp"

#endif
