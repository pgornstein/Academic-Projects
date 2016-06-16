#include "BinarySearchTree.h"

    template <typename Comparable>    
    BinarySearchTree<Comparable>::BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    template <typename Comparable>    
    BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    template <typename Comparable>    
    BinarySearchTree<Comparable>::BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    template <typename Comparable>    
    BinarySearchTree<Comparable>::~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    template <typename Comparable>    
    BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    template <typename Comparable>
    BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
   
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    template <typename Comparable>
    const Comparable & BinarySearchTree<Comparable>::findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    template <typename Comparable>
    const Comparable & BinarySearchTree<Comparable>::findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    template <typename Comparable>
    bool BinarySearchTree<Comparable>::contains( Comparable & x )
    {
        return contains( x, root );
    }

    /**
     * Returns element if found in the tree 
     */
    template <typename Comparable>
    Comparable  BinarySearchTree<Comparable>::find( Comparable & x )
    {
      return find( x, root );
    }
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    template <typename Comparable>
    bool BinarySearchTree<Comparable>::isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::printTree(ostream &out) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::insert( Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::remove( Comparable & x )
    {
        remove( x, root );
    }

    /**
     * Returns number of nodes in the tree. 
     */
    template <typename Comparable>
    int BinarySearchTree<Comparable>::nodes()
    {
      return nodes(root);
    }

    /**
     * Returns internal path length of the tree. 
     */
    template <typename Comparable>
    int BinarySearchTree<Comparable>::internalPathLength() 
    {
      return internalPathLength(root, 0);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::insert( Comparable & x, BinaryNode * & t )
    {
      insertCount++;
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else t->element.merge(x);
            ;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::insert( Comparable && x, BinaryNode * & t )
    {
      insertCount++;
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else t->element.merge(x);
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::remove( Comparable & x, BinaryNode * & t )
    {
      removeCount++;
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    template <typename Comparable>
    typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMin( BinaryNode *t ) const
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
    template <typename Comparable>
    typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    template <typename Comparable>
    bool BinarySearchTree<Comparable>::contains( Comparable & x, BinaryNode *t )
    {
      containsCount++;
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    /**
     * Internal method that returns element if found in the tree 
     */
    template <typename Comparable>
    Comparable BinarySearchTree<Comparable>::find( Comparable & x, BinaryNode *t)
    {
        if( x < t->element )
            return find( x, t->left );
        else if( t->element < x )
            return find( x, t->right );
        else
            return t->element;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
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
    template <typename Comparable> 
    void BinarySearchTree<Comparable>::makeEmpty( BinaryNode * & t )
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
    template <typename Comparable>
    void BinarySearchTree<Comparable>::printTree( BinaryNode *t, ostream &out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    template <typename Comparable>
    typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }

    /**
     *Internal method to return number of nodes in the tree
     */
    template<typename Comparable>
    int BinarySearchTree<Comparable>::nodes(BinaryNode *t) 
    {
      int num = 1; 
      if (t->left != nullptr) num += nodes(t->left);
      if (t->right != nullptr) num += nodes(t->right);
      return num;
    }

    /**
     *Internal method to return internal path length of the tree
     */
    template<typename Comparable> 
    int BinarySearchTree<Comparable>::internalPathLength(BinaryNode *t, int depth) 
    {
      int num = depth; 
      if (t->left != nullptr) num += internalPathLength(t->left, depth + 1);
      if (t->right != nullptr) num += internalPathLength(t->right, depth + 1);
      return num;
    }
