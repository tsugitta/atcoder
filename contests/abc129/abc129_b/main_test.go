package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	cases := []struct {
		N        int
		ws       []int
		expected int
	}{
		{3, []int{1, 2, 3}, 0},
		{4, []int{1, 3, 1, 1}, 2},
		{8, []int{27, 23, 76, 2, 3, 5, 62, 52}, 2},
	}

	for idx, c := range cases {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(c.N, c.ws); actual != c.expected {
				t.Fatalf("expexted: %#v, actual: %#v", c.expected, actual)
			}
		})
	}
}
