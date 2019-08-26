package go_snippets

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestUnionFind(t *testing.T) {
	uf := &UnionFind{}

	uf.init(5)

	uf.merge(0, 1)
	assert.Equal(t, true, uf.same(0, 1))
	assert.Equal(t, false, uf.same(0, 2))
	uf.merge(1, 4)
	assert.Equal(t, true, uf.same(0, 4))
	assert.Equal(t, 3, uf.size(4))
	assert.Equal(t, 3, uf.groupCount())
}
