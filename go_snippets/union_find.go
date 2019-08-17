package go_snippets

type UnionFind struct {
	// for children, the value is its parent index. for root, the value is -1 * the size of the group
	parents []int
}

func (uf *UnionFind) init(n int) {
	uf.parents = make([]int, n)

	for i := range uf.parents {
		uf.parents[i] = -1
	}
}

func (uf *UnionFind) root(x int) int {
	if uf.parents[x] < 0 {
		return x
	}

	r := uf.root(uf.parents[x])
	uf.parents[x] = r
	return r
}

func (uf *UnionFind) same(x, y int) bool {
	return uf.root(x) == uf.root(y)
}

func (uf *UnionFind) merge(x, y int) {
	xr := uf.root(x)
	yr := uf.root(y)

	if xr == yr {
		return
	}

	// make less index one as a root
	if xr > yr {
		xr, yr = yr, xr
	}

	uf.parents[xr] += uf.parents[yr]
	uf.parents[yr] = xr
}

func (uf *UnionFind) size(x int) int {
	return -uf.parents[uf.root(x)]
}

func (uf *UnionFind) groupCount() (res int) {
	for _, parent := range uf.parents {
		if parent < 0 {
			res++
		}
	}

	return
}
