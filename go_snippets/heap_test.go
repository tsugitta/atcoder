package go_snippets

import (
	"container/heap"
	"testing"
)

func TestPQ(t *testing.T) {
	assert := func(actual interface{}, expected interface{}) {
		if actual != expected {
			t.Fatalf("expected: %#v, actual: %#v", expected, actual)
		}
	}

	pq := PQ{}
	heap.Init(&pq)

	heap.Push(&pq, 3)
	heap.Push(&pq, 1)
	assert(pq[0], 1)
	assert(heap.Pop(&pq), 1)
	assert(pq[0], 3)
	assert(heap.Pop(&pq), 3)
}
