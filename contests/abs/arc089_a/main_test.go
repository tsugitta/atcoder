package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	tests := []struct {
		ps       []Position
		expected bool
	}{
		{ps: []Position{
			{
				t: 2,
				x: 100,
				y: 100,
			},
		}, expected: false},
		{ps: []Position{
			{
				t: 3,
				x: 1,
				y: 2,
			},
		}, expected: true},
		{ps: []Position{
			{
				t: 3,
				x: 1,
				y: 2,
			},
			{
				t: 6,
				x: 1,
				y: 1,
			},
		}, expected: true},
		{ps: []Position{
			{
				t: 5,
				x: 1,
				y: 1,
			},
			{
				t: 100,
				x: 1,
				y: 1,
			},
		}, expected: false},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(test.ps); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
