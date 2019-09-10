package go_snippets

type OrderedSet struct {
	tree *Fenwick
	max  int
}

func NewOrderedSet(max int) *OrderedSet {
	s := &OrderedSet{}
	s.tree = NewFenwick(max + 1)
	s.max = max
	return s
}

// n 以下の最大の要素 O(log^2 N)
func (s *OrderedSet) Left(n int) (res int, found bool) {
	nCt := s.tree.Sum(n + 1)

	if nCt == 0 {
		return
	}

	// 0 ~ n で nCt となる最大が求めるもの

	// (l, r] に答えがあるとする
	// mid が条件を満たす → r を置き換えることとなる
	l := -1
	r := n

	for r-l > 1 {
		mid := (l + r) / 2

		midCt := s.tree.Sum(mid + 1)

		if midCt == nCt {
			r = mid
		} else {
			l = mid
		}
	}

	return r, true
}

// n 以上の最小の要素 O(log^2 N)
func (s *OrderedSet) Right(n int) (res int, found bool) {
	if s.tree.Sum(n) == s.tree.Sum(s.max+1) {
		return
	}

	nCt := s.tree.Sum(n) // n-1 以下の個数であることに注意

	// n ~ max で > nCt となる最小が求めるもの

	// (l, r] に答えがあるとする
	// mid が条件を満たす → r を置き換えることとなる
	l := n - 1
	r := s.max

	for r-l > 1 {
		mid := (l + r) / 2

		midCt := s.tree.Sum(mid + 1)

		if midCt > nCt {
			r = mid
		} else {
			l = mid
		}
	}

	return r, true
}

func (s *OrderedSet) Add(n int) {
	s.tree.Add(n, 1)
}
