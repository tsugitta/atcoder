package go_snippets

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestOrderedSet(t *testing.T) {
	{
		set := NewOrderedSet(5)

		_, found := set.Left(1)
		assert.Equal(t, false, found)

		_, found = set.Left(5)
		assert.Equal(t, false, found)

		set.Add(5)

		res, found := set.Left(5)
		assert.Equal(t, true, found)
		assert.Equal(t, 5, res)

		res, found = set.Right(5)
		assert.Equal(t, true, found)
		assert.Equal(t, 5, res)

		res, found = set.Right(4)
		assert.Equal(t, true, found)
		assert.Equal(t, 5, res)

		set.Add(2)

		res, found = set.Left(4)
		assert.Equal(t, true, found)
		assert.Equal(t, 2, res)

		_, found = set.Left(1)
		assert.Equal(t, false, found)
	}

	{
		set := NewOrderedSet(3)

		set.Add(2)

		res, found := set.Right(0)
		assert.Equal(t, true, found)
		assert.Equal(t, 2, res)
	}
}
