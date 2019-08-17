package go_snippets

type PQ []int

func (pq *PQ) Len() int { return len(*pq) }

// less なものから pop される
func (pq *PQ) Less(i, j int) bool    { return (*pq)[i] < (*pq)[j] }
func (pq *PQ) Swap(i, j int)         { (*pq)[i], (*pq)[j] = (*pq)[j], (*pq)[i] }
func (pq *PQ) Push(item interface{}) { *pq = append(*pq, item.(int)) }

func (pq *PQ) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	// heap.Pop 直前に取り出されるべき要素が先頭から末尾に移動する
	*pq = old[0 : n-1]
	return item
}
