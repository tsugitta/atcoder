package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	cases := []struct {
		P        int
		Q        int
		R        int
		expected int
	}{
		{P: 1, Q: 3, R: 4, expected: 4},
		{P: 3, Q: 2, R: 3, expected: 5},
	}

	for idx, c := range cases {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(c.P, c.Q, c.R); actual != c.expected {
				t.Fatalf("expexted: %#v, actual: %#v", c.expected, actual)
			}
		})
	}
}
