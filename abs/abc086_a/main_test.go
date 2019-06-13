package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	tests := []struct {
		a        int
		b        int
		expected string
	}{
		{a: 1, b: 2, expected: "Even"},
		{a: 0, b: 3, expected: "Even"},
		{a: 3, b: 7, expected: "Odd"},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(test.a, test.b); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
