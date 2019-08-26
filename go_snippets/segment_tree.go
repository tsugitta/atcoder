package go_snippets

type SegmentTree struct {
	n         int // 最下段の数
	nodes     []int
	zeroValue int
}

func (st *SegmentTree) calc(a, b int) int {
	// EDIT HERE
	if a > b {
		return b
	}

	return a
}

func (st *SegmentTree) init(vs []int, zeroValue int) {
	st.zeroValue = zeroValue
	st.n = 1

	for st.n < len(vs) {
		st.n *= 2
	}

	st.nodes = make([]int, 2*st.n-1)

	for i := range st.nodes {
		st.nodes[i] = st.zeroValue
	}

	for i, v := range vs {
		st.nodes[i+st.n-1] = v
	}

	for i := st.n - 2; i >= 0; i-- {
		st.nodes[i] = st.calc(st.nodes[i*2+1], st.nodes[i*2+2])
	}
}

func (st *SegmentTree) update(i, val int) {
	i += st.n - 1
	st.nodes[i] = val

	for i > 0 {
		i = (i - 1) / 2
		st.nodes[i] = st.calc(st.nodes[2*i+1], st.nodes[2*i+2])
	}
}

// [from, to)
func (st *SegmentTree) query(from, to int) int {
	return st.queryInternal(from, to, 0, 0, st.n)
}

func (st *SegmentTree) queryInternal(from, to, k, l, r int) int {
	if r <= from || to <= l {
		return st.zeroValue
	}

	if from <= l && r <= to {
		return st.nodes[k]
	}

	vl := st.queryInternal(from, to, 2*k+1, l, (l+r)/2)
	vr := st.queryInternal(from, to, 2*k+2, (l+r)/2, r)

	return st.calc(vl, vr)
}
