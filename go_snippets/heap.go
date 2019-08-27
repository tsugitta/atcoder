package go_snippets

import "container/heap"

type PQ struct {
	values PQValues
}

func NewPQ() *PQ {
	pq := PQ{}
	heap.Init(&pq.values)
	return &pq
}

func (pq *PQ) Len() int {
	return len(pq.values)
}

func (pq *PQ) Push(v int) {
	heap.Push(&pq.values, v)
}

func (pq *PQ) Pop() int {
	return heap.Pop(&pq.values).(int)
}

type PQValues []int

func (vs *PQValues) Len() int { return len(*vs) }

// less なものから pop される
func (vs *PQValues) Less(i, j int) bool    { return (*vs)[i] < (*vs)[j] }
func (vs *PQValues) Swap(i, j int)         { (*vs)[i], (*vs)[j] = (*vs)[j], (*vs)[i] }
func (vs *PQValues) Push(item interface{}) { *vs = append(*vs, item.(int)) }

func (vs *PQValues) Pop() interface{} {
	old := *vs
	n := len(old)
	item := old[n-1]
	// heap.Pop 直前に取り出されるべき要素が先頭から末尾に移動する
	*vs = old[0 : n-1]
	return item
}
