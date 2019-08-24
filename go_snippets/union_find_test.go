package go_snippets

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestUnionFind(t *testing.T) {
	uf := &UnionFind{}

	uf.init(5)

	uf.merge(0, 1)
	assert.Equal(t, uf.same(0, 1), true)
	assert.Equal(t, uf.same(0, 2), false)
	uf.merge(1, 4)
	assert.Equal(t, uf.same(0, 4), true)
	assert.Equal(t, uf.size(4), 3)
	assert.Equal(t, uf.groupCount(), 3)
}
