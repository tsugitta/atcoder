package go_snippets

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestBit(t *testing.T) {
	bit := NewFenwick(5)

	bit.Add(0, 1)
	bit.Add(1, 2)
	bit.Add(2, 3)
	bit.Add(3, 4)

	for _, pair := range []struct {
		in  int
		out int
	}{
		{in: 0, out: 0},
		{in: 1, out: 1},
		{in: 2, out: 3},
		{in: 3, out: 6},
		{in: 4, out: 10},
	} {
		assert.Equal(t, pair.out, bit.Sum(pair.in))
	}
}
