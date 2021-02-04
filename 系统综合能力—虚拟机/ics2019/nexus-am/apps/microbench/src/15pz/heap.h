// Author:  Douglas Wilhelm Harder
// Copyright (c) 2009 by Douglas Wilhelm Harder.  All rights reserved.

template <typename T>
T max(T a, T b) {
  return a > b ? a : b;
}

template <typename T>
class Updatable_heap {
  private:
    int M;
    class Step;
    Step **hash_table;
    Step **heap;
    int heap_size;
    int maximum_heap_size;

    void inline swap( int, int );
    void percolate_down();
    void percolate_up( int );
    Step *pointer( T const & ) const;

  public:
    void init(int m); 
    ~Updatable_heap();
    T pop();
    void push( T const &, int );
    int size() const;
    int maximum_size() const;
    int length( T const & ) const;
};

template <typename T>
class Updatable_heap<T>::Step {
  public:
    T element;
    Step *next;
    int heap_index;
    int path_length;
    int path_weight;
    bool visited;
    Step *previous_step;

    void init( T const &, Step *, int, int );
    int length() const;
    int weight() const;
};

template <typename T>
void Updatable_heap<T>::init(int m) {
  M = m;
  heap = (Step **)bench_alloc(sizeof(void *) * M);
  hash_table = (Step **)bench_alloc(sizeof(void *) * (M + 1));

  heap_size = 0;
  maximum_heap_size = 0;
  for ( int i = 0; i < M; ++i ) {
    hash_table[i] = 0;
  }
}

template <typename T>
Updatable_heap<T>::~Updatable_heap() {
  for ( int i = 0; i < M; ++i ) {
    Step *ptr = hash_table[i];

    while ( ptr != 0 ) {
      Step *tmp = ptr;
      ptr = ptr->next;
    }
  }
}

template <typename T>
T Updatable_heap<T>::pop() {
  if ( size() == 0 ) {
    return T();
  }

  T top = heap[1]->element;

  if ( size() == 1 ) {
    heap_size = 0;
  } else {
    assert( size() > 1 );

    heap[1] = heap[size()];
    heap[1]->heap_index = 1;

    --heap_size;
    percolate_down();
  }

  return top;
}

template <typename T>
void inline Updatable_heap<T>::swap( int i, int j ) {
  Step *tmp = heap[j];
  heap[j] = heap[i];
  heap[i] = tmp;

  heap[i]->heap_index = i;
  heap[j]->heap_index = j;
}

template <typename T>
void Updatable_heap<T>::percolate_down() {
  int n = 1;

  while ( 2*n + 1 <= size() ) {
    if ( heap[n]->weight() < heap[2*n]->weight() && heap[n]->weight() < heap[2*n + 1]->weight() ) {
      return;
    }

    if ( heap[2*n]->weight() < heap[2*n + 1]->weight() ) {
      swap( n, 2*n );
      n = 2*n;
    } else {
      assert( heap[2*n]->weight() >= heap[2*n + 1]->weight() );

      swap( n, 2*n + 1 );
      n = 2*n + 1;
    }
  } 

  if ( 2*n == size() &&  heap[2*n]->weight() < heap[n]->weight() ) {
    swap( n, 2*n );
  }
}

template <typename T>
void Updatable_heap<T>::percolate_up( int n ) {
  while ( n != 1 ) {
    int parent = n/2;

    if ( heap[parent]->weight() > heap[n]->weight() ) {
      swap( parent, n );
      n = parent;
    } else {
      return;
    }
  }
}

template <typename T>
void Updatable_heap<T>::push( T const &pz, int path_length ) {
  Step *ptr = pointer( pz );

  if ( ptr == 0 ) {
    assert( heap_size <= M );
    ++heap_size;

    Step *ptr = (Step*)bench_alloc(sizeof(Step));
    ptr->init( pz, hash_table[pz.hash() & (M - 1)], size(), path_length );
    hash_table[pz.hash() & (M - 1)] = ptr;
    heap[size()] = ptr;

    percolate_up( size() );

    maximum_heap_size = max( maximum_heap_size, size() );
  } else {
    if ( !ptr->visited ) {
      if ( path_length + ptr->element.lower_bound() < ptr->weight() ) {
        ptr->path_weight = path_length + ptr->element.lower_bound();
        percolate_up( ptr->heap_index );
      }
    }
  }
}

template <typename T>
int Updatable_heap<T>::size() const {
  return heap_size;
}

template <typename T>
int Updatable_heap<T>::maximum_size() const {
  return maximum_heap_size;
}

template <typename T>
int Updatable_heap<T>::length( T const &pz ) const {
  Step *ptr = pointer( pz );

  return ( ptr == 0 ) ? 2147483647 : ptr->length();
}

template <typename T>
typename Updatable_heap<T>::Step *Updatable_heap<T>::pointer( T const &pz ) const {
  for ( Step *ptr = hash_table[pz.hash() & (M - 1)]; ptr != 0; ptr = ptr->next ) {
    if ( ptr->element == pz ) {
      return ptr;
    }
  }

  return 0;
}

/****************************************************
 * ************************************************ *
 * *                   Iterator                   * *
 * ************************************************ *
 ****************************************************/

template <typename T>
void Updatable_heap<T>::Step::init( T const &pz, Step *n, int hi, int dist ) {
  element = pz;
  next = n;
  heap_index = hi;
  path_length = dist;
  path_weight = dist + element.lower_bound();
  visited = false;
  previous_step = 0;
}

template <typename T>
int Updatable_heap<T>::Step::length() const {
  return path_length;
}

template <typename T>
int Updatable_heap<T>::Step::weight() const {
  return path_weight;
}

