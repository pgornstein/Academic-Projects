// Binomial queue class, implementation file
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
BinomialQueue<Comparable>::BinomialQueue( ) : theTrees( DEFAULT_TREES )
{
  comparisonCount = 0;
  assignmentCount = 0;
  for( auto & root : theTrees )
  root = nullptr;
  currentSize = 0;
}

template <typename Comparable> 
BinomialQueue<Comparable>::BinomialQueue( const Comparable & item ) : theTrees( 1 ), currentSize{ 1 }
 {
 theTrees[ 0 ] = new BinomialNode{ item, nullptr, nullptr, nullptr };
 comparisonCount = 0;
 assignmentCount = 0;
 }

template <typename Comparable> 
BinomialQueue<Comparable>::BinomialQueue( const BinomialQueue & rhs ) : theTrees( rhs.theTrees.size( ) ), currentSize{ rhs.currentSize }
    {
        for( int i = 0; i < rhs.theTrees.size( ); ++i )
            theTrees[ i ] = clone( rhs.theTrees[ i ] );
	comparisonCount = rhs.comparisonCount;
	assignmentCount = rhs.assignmentCount;
    }

template <typename Comparable> 
BinomialQueue<Comparable>::BinomialQueue( BinomialQueue && rhs )
      : theTrees{ std::move( rhs.theTrees ) }, currentSize{ rhs.currentSize }
    {
      comparisonCount = rhs.comparisonCount;
      assignmentCount = rhs.assignmentCount; 
    }

template <typename Comparable> 
BinomialQueue<Comparable>::~BinomialQueue( )
      { makeEmpty( ); }

    /**
     * Deep copy.
     */
template <typename Comparable>
BinomialQueue<Comparable> & BinomialQueue<Comparable>::operator=( const BinomialQueue & rhs )
    {
        BinomialQueue copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move.
     */
template <typename Comparable>
BinomialQueue<Comparable> & BinomialQueue<Comparable>::operator=( BinomialQueue && rhs )
    {
        std::swap( currentSize, rhs.currentSize );
        std::swap( theTrees, rhs.theTrees );
        
        return *this;
    }

    /**
     * Return true if empty; false otherwise.
     */
template <typename Comparable>
bool BinomialQueue<Comparable>::isEmpty( ) const
      { return currentSize == 0; }

    /**
     * Returns minimum item.
     * Throws UnderflowException if empty.
     */
template <typename Comparable>
const Comparable & BinomialQueue<Comparable>::findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        return theTrees[ findMinIndex( ) ]->element;
    }

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
template <typename Comparable>
typename BinomialQueue<Comparable>::BinomialNode * BinomialQueue<Comparable>::insert( const Comparable & x )
{ 
  BinomialQueue oneItem{ x };
  BinomialNode *node = oneItem.theTrees[0]; 
  merge( oneItem );
  return node;
}

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
template <typename Comparable>
typename BinomialQueue<Comparable>::BinomialNode * BinomialQueue<Comparable>::insert( Comparable && x )
{
  BinomialQueue oneItem{ std::move( x ) };
  BinomialNode *node = oneItem.theTrees[0]; 
  merge( oneItem );
  return node; 
}

    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     */
template <typename Comparable>
void BinomialQueue<Comparable>::deleteMin( )
    {
        Comparable x;
        deleteMin( x );
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
template <typename Comparable>
void BinomialQueue<Comparable>::deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        int minIndex = findMinIndex( );
        minItem = theTrees[ minIndex ]->element;

        BinomialNode *oldRoot = theTrees[ minIndex ];
        BinomialNode *deletedTree = oldRoot->leftChild;
        delete oldRoot;
	if (deletedTree != nullptr) {
	  deletedTree->parent = nullptr;
	  BinomialNode *counter = deletedTree;
	  while (counter->nextSibling != nullptr) {
	    counter = counter->nextSibling;
	    counter->parent = nullptr;
	  }
	}

        // Construct H''
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize( minIndex + 1 );
        deletedQueue.currentSize = ( 1 << minIndex ) - 1;
        for( int j = minIndex - 1; j >= 0; --j )
        {
            deletedQueue.theTrees[ j ] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[ j ]->nextSibling = nullptr;
        }

        // Construct H'
        theTrees[ minIndex ] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;

        merge( deletedQueue );
    }

    /**
     * Make the priority queue logically empty.
     */
template <typename Comparable>
void BinomialQueue<Comparable>::makeEmpty( )
    {
        currentSize = 0;
        for( auto & root : theTrees )
            makeEmpty( root );
    }

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     */
template <typename Comparable>
void BinomialQueue<Comparable>::merge( BinomialQueue & rhs )
    {
      if( this == &rhs ) {   // Avoid aliasing problems
	comparisonCount++;            
	return;
      }

        currentSize += rhs.currentSize;
	assignmentCount++;

        if( currentSize > capacity( ) ) 
        {
	  comparisonCount++;
	  int oldNumTrees = theTrees.size( );
	  int newNumTrees = max( theTrees.size( ), rhs.theTrees.size( ) ) + 1;
	  assignmentCount += 2;
	  theTrees.resize( newNumTrees );
	  for( int i = oldNumTrees; i < newNumTrees; ++i ) {
	    theTrees[ i ] = nullptr;
	    assignmentCount++;
	  }
        }

        BinomialNode *carry = nullptr;
	assignmentCount++;
        for( int i = 0, j = 1; j <= currentSize; ++i, j *= 2 )
        {
            BinomialNode *t1 = theTrees[ i ];
            BinomialNode *t2 = i < rhs.theTrees.size( ) ? rhs.theTrees[ i ] : nullptr;
	    comparisonCount++;
	    assignmentCount += 2;

            int whichCase = t1 == nullptr ? 0 : 1;
            whichCase += t2 == nullptr ? 0 : 2;
            whichCase += carry == nullptr ? 0 : 4;
	    comparisonCount += 3;
	    assignmentCount += 3;

            switch( whichCase )
            {
              case 0: /* No trees */
              case 1: /* Only this */
                break;
              case 2: /* Only rhs */
                theTrees[ i ] = t2;
                rhs.theTrees[ i ] = nullptr;
		assignmentCount += 2;
                break;
              case 4: /* Only carry */
                theTrees[ i ] = carry;
                carry = nullptr;
		assignmentCount += 2;
                break;
              case 3: /* this and rhs */
                carry = combineTrees( t1, t2 );
                theTrees[ i ] = rhs.theTrees[ i ] = nullptr;
		assignmentCount += 3; 
                break;
              case 5: /* this and carry */
                carry = combineTrees( t1, carry );
                theTrees[ i ] = nullptr;
		assignmentCount += 2;
                break;
              case 6: /* rhs and carry */
                carry = combineTrees( t2, carry );
                rhs.theTrees[ i ] = nullptr;
		assignmentCount += 2;
                break;
              case 7: /* All three */
                theTrees[ i ] = carry;
                carry = combineTrees( t1, t2 );
                rhs.theTrees[ i ] = nullptr;
		assignmentCount += 3;
                break;
            }
        }

        for( auto & root : rhs.theTrees ) {
	  root = nullptr;
	  assignmentCount++;
	}
        rhs.currentSize = 0;
	assignmentCount++;
    }

    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     */
template <typename Comparable>
int BinomialQueue<Comparable>::findMinIndex( ) const
    {
        int i;
        int minIndex;

        for( i = 0; theTrees[ i ] == nullptr; ++i )
            ;

        for( minIndex = i; i < theTrees.size( ); ++i )
            if( theTrees[ i ] != nullptr &&
                theTrees[ i ]->element < theTrees[ minIndex ]->element )
                minIndex = i;

        return minIndex;
    }

    /**
     * Return the capacity.
     */
template <typename Comparable>
int BinomialQueue<Comparable>::capacity( ) const
      { return ( 1 << theTrees.size( ) ) - 1; }

    /**
     * Return the result of merging equal-sized t1 and t2.
     */
template <typename Comparable>
typename BinomialQueue<Comparable>::BinomialNode * BinomialQueue<Comparable>::combineTrees( BinomialNode *t1, BinomialNode *t2 )
    {
        if( t2->element < t1->element )
            return combineTrees( t2, t1 );
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
	t2->parent = t1;
        return t1;
    }

    /**
     * Make a binomial tree logically empty, and free memory.
     */
template <typename Comparable>
void BinomialQueue<Comparable>::makeEmpty( BinomialNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->leftChild );
            makeEmpty( t->nextSibling );
            delete t;
            t = nullptr;
        }
    }

    /**
     * Internal method to clone subtree.
     */
template <typename Comparable>
typename BinomialQueue<Comparable>::BinomialNode * BinomialQueue<Comparable>::clone( BinomialNode * t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
	  return new BinomialNode{ t->element, clone( t->leftChild ), clone( t->nextSibling ), clone( t->parent ) };
    }
