package go_snippets

type Fenwick struct {
	tree []int
}

func NewFenwick(n int) *Fenwick {
	return &Fenwick{
		tree: make([]int, n),
	}
}

// sum of [0, i)
func (f *Fenwick) Sum(i int) (sum int) {
	for i--; i >= 0; i = (i & (i + 1)) - 1 {
		sum += f.tree[i]
	}

	return
}

func (f *Fenwick) Add(i, n int) {
	for l := len(f.tree); i < l; i |= i + 1 {
		f.tree[i] += n
	}
}
