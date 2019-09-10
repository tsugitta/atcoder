// https://atcoder.jp/contests/abc140/tasks/abc140_e

package main

import (
	rbt "github.com/emirpasic/gods/trees/redblacktree"
)

// NOTE: this solution will be available after Go's language update (with library)
// d: debug IO. it can print debug in test.
func solve2(io *Io, d *Io) {
	N := io.NextInt()
	ps := io.NextInts(N)

	numToIndex := make([]int, N+1)

	for i, p := range ps {
		numToIndex[p] = i
	}

	largeIndices := rbt.NewWithIntComparator()
	largeIndices.Put(numToIndex[N], numToIndex[N])

	res := 0

	for num := N - 1; num >= 1; num-- {
		i := numToIndex[num]

		bi := N
		bi2 := N
		si := -1
		si2 := -1

		// その i より大きい index
		biCand, biFound := largeIndices.Ceiling(i + 1)

		if biFound {
			bi = biCand.Value.(int)

			bi2Cand, bi2Found := largeIndices.Ceiling(bi + 1)

			if bi2Found {
				bi2 = bi2Cand.Value.(int)
			}
		}

		siCand, siFound := largeIndices.Floor(i - 1)

		if siFound {
			si = siCand.Value.(int)

			si2Cand, si2Found := largeIndices.Floor(si - 1)

			if si2Found {
				si2 = si2Cand.Value.(int)
			}
		}

		// s を取る場合
		res += (si - si2) * (bi - i) * num
		// b ..
		res += (bi2 - bi) * (i - si) * num

		largeIndices.Put(i, i)
	}

	io.Println(res)
}
