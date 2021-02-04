#include <benchmark.h>
#include "puzzle.h"
#include "heap.h"

const int N = 4;

static int PUZZLE_S[N*N] = {
  1, 2, 3, 4,
  5, 6, 7, 8,
  9, 10, 0, 11,
  13, 14, 15, 12,
};

static int PUZZLE_M[N*N] = {
  1, 2, 3, 4,
  5, 6, 7, 8,
  12, 0, 14, 13,
  11, 15, 10, 9,
};

static int PUZZLE_L[N*N] = {
  0, 2, 3, 4,
  9, 6, 7, 8,
  5, 11, 10, 12,
  1, 15, 13, 14,
};

static int ans;

extern "C" {

void bench_15pz_prepare() {
}

void bench_15pz_run() {
  N_puzzle<N> puzzle;
  int MAXN;

  switch (setting->size) {
    case 0: puzzle = N_puzzle<N>(PUZZLE_S); MAXN = 10; break;
    case 1: puzzle = N_puzzle<N>(PUZZLE_M); MAXN = 2048; break;
    case 2: puzzle = N_puzzle<N>(PUZZLE_L); MAXN = 16384; break;
    default: assert(0);
  }
  assert(puzzle.solvable());

  auto *heap = (Updatable_heap<N_puzzle<N>> *) bench_alloc(sizeof(Updatable_heap<N_puzzle<N>>));
  heap->init(MAXN);
  heap->push( puzzle, 0 );

  int n = 0;
  ans = -1;

  while( heap->size() != 0 && n != MAXN ) {
    N_puzzle<N> top = heap->pop();
    ++n;

    if ( top == N_puzzle<N>::solution() ) {
      // We are done
      ans = heap->length(top) * n;
      return;
    }

    if ( top.tile_left_possible() ) {
      heap->push( top.tile_left(), heap->length( top ) + 1 );
    }

    if ( top.tile_right_possible() ) {
      heap->push( top.tile_right(), heap->length( top ) + 1 );
    }

    if ( top.tile_up_possible() ) {
      heap->push( top.tile_up(), heap->length( top ) + 1 );
    }

    if ( top.tile_down_possible() ) {
      heap->push( top.tile_down(), heap->length( top ) + 1 );
    }
  }
}


int bench_15pz_validate() {
  return (uint32_t)ans == setting->checksum;
}

}

