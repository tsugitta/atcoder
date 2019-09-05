package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	tests := []struct {
		n        int
		y        int
		expected []string
	}{
		{n: 9, y: 45000, expected: []string{"4 0 5", "0 9 0"}},
		{n: 20, y: 196000, expected: []string{"-1 -1 -1"}},
		{n: 2000, y: 20000000, expected: []string{"2000 0 0"}},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			actual := solve(test.n, test.y)

			found := false

			for _, exp := range test.expected {
				if exp == actual {
					found = true
				}
			}

			if !found {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
