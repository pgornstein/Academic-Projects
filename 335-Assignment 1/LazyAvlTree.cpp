#include "LazyAvlTree.h"
    
    template <typename Comparable>
    LazyAvlTree<Comparable>::LazyAvlTree( ) : root{ nullptr }
      { }
    
    template <typename Comparable>
    LazyAvlTree<Comparable>::LazyAvlTree( const LazyAvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    template <typename Comparable>
    LazyAvlTree<Comparable>::LazyAvlTree( LazyAvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    template <typename Comparable>
    LazyAvlTree<Comparable>::~LazyAvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    template <typename Comparable>
    LazyAvlTree<Comparable> & LazyAvlTree<Comparable>::operator=( const LazyAvlTree & rhs )
    {
        LazyAvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    template <typename Comparable>
    LazyAvlTree<Comparable> & LazyAvlTree<Comparable>::operator=( LazyAvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    template<typename Comparable>
    const Comparable & LazyAvlTree<Comparable>::findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    template<typename Comparable>
    const Comparable & LazyAvlTree<Comparable>::findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    template<typename Comparable>
    bool LazyAvlTree<Comparable>::contains(  Comparable & x ) 
    {
        return contains( x, root );
    }

    /**
     * Returns true if x is found in the tree.
     */
    template<typename Comparable>
    Comparable LazyAvlTree<Comparable>::find( Comparable & x )
    {
      return find( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    template<typename Comparable>
    bool LazyAvlTree<Comparable>::isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::insert( Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::remove( Comparable & x )
    {
        remove( x, root );
    }

    /**
     * Returns the number of nodes in the tree. 
     */
    template <typename Comparable>
    int LazyAvlTree<Comparable>::nodes() 
    {
      return nodes(root);
    }

    /**
     * Returns the internal path length of the tree.  
     */
    template<typename Comparable>
    int LazyAvlTree<Comparable>::internalPathLength()
    {
      return internalPathLength(root, 0);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::insert( Comparable & x, AvlNode * & t )
    {
      insertCount++;
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else {
	  if (!t->removed) t->element.merge(x);
	  else t->element = x;
	}
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::insert( Comparable && x, AvlNode * & t )
    {
      insertCount++;
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else {
	  if (!t.removed) t->element.merge(x);
	  else t->element = x;
	}
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::remove( Comparable & x, AvlNode * & t )
    {
      removeCount++;
        if( t == nullptr )
            return;   // Item not found; do nothing
        
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else t->removed = true;
        
        balance( t );
    }

    // Assume t is balanced or within one of being balanced
    template<typename Comparable>
    void LazyAvlTree<Comparable>::balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
        {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        }
        else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
        {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
        }
                
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    template<typename Comparable>
    typename LazyAvlTree<Comparable>::AvlNode * LazyAvlTree<Comparable>::findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    template<typename Comparable>
    typename LazyAvlTree<Comparable>::AvlNode * LazyAvlTree<Comparable>::findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    template<typename Comparable>
    bool LazyAvlTree<Comparable>::contains( Comparable & x, AvlNode *t ) 
    {
      containsCount++;
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else {
	  if (!t->removed) return true;
	  else return false;
	}
    }

    /**
     * Internal method that returns item if it exists in the tree
     */
    template<typename Comparable>
    Comparable LazyAvlTree<Comparable>::find( Comparable & x, AvlNode *t )
    {
        if( x < t->element )
            return find( x, t->left );
        else if( t->element < x )
            return find( x, t->right );
        else return t->element;  // Natch
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            if (!t.removed) cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    template<typename Comparable>
    typename LazyAvlTree<Comparable>::AvlNode * LazyAvlTree<Comparable>::clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    template<typename Comparable>
    int LazyAvlTree<Comparable>::height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }
    template<typename Comparable>
    int LazyAvlTree<Comparable>::max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    template<typename Comparable>
    void LazyAvlTree<Comparable>::doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

    /**
     * Internal method to return the number of nodes in the tree. 
     */
    template<typename Comparable>
    int LazyAvlTree<Comparable>::nodes(AvlNode *t) 
    {
      int num = 0; 
      if (!t->removed) num++; 
      if (t->left != nullptr) num += nodes(t->left);
      if (t->right != nullptr) num += nodes(t->right); 
      return num;
    }

    /**
     * Internal method to return the internal path length of the tree. 
     */
    template<typename Comparable> 
    int LazyAvlTree<Comparable>::internalPathLength(AvlNode *t, int depth)
    {
      int num = 0; 
      if (t->left != nullptr) num += internalPathLength(t->left, depth + 1); 
      if (t->right != nullptr) num += internalPathLength(t->right, depth + 1);
      if (!t->removed) num += depth;
      return num; 
    }
