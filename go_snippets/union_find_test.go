package go_snippets

import (
	"testing"
)

func TestUnionFind(t *testing.T) {
	uf := &UnionFind{}

	assert := func(actual interface{}, expected interface{}) {
		if actual != expected {
			t.Fatalf("expected: %#v, actual: %#v", expected, actual)
		}
	}

	uf.init(5)

	uf.merge(0, 1)
	assert(uf.same(0, 1), true)
	assert(uf.same(0, 2), false)
	uf.merge(1, 4)
	assert(uf.same(0, 4), true)
	assert(uf.size(4), 3)
	assert(uf.groupCount(), 3)
}
