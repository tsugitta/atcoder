package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	cases := []struct {
		N        int
		as       []int
		expected int
	}{
		{6, []int{3}, 4},
		{10, []int{4, 5}, 0},
		{100, []int{1, 23, 45, 67, 89}, 608200469},
	}

	for idx, c := range cases {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(c.N, c.as); actual != c.expected {
				t.Fatalf("expexted: %#v, actual: %#v", c.expected, actual)
			}
		})
	}
}
