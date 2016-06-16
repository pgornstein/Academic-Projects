#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

// QuadraticProbing Hash table class, header file 
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
  public:
  explicit HashTable( int size );

  bool contains( const HashedObj & x ) const;

  void makeEmpty( );

  bool insert( const HashedObj & x );
    
  bool insert( HashedObj && x );

  bool remove( const HashedObj & x );

    enum EntryType { ACTIVE, EMPTY, DELETED };

    struct HashEntry
    {
        HashedObj element;
        EntryType info;

    HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const;

    int findPos( const HashedObj & x ) const;

    void rehash( );

    size_t myhash( const HashedObj & x ) const;

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
    bool isPrime( int n );

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
    int nextPrime( int n );

};

#include "QuadraticProbing.cpp"

#endif
