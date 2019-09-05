package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	tests := []struct {
		string   string
		expected string
	}{
		{string: "000", expected: "0"},
		{string: "011", expected: "2"},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(test.string); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
