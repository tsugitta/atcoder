package main

import (
	"fmt"
	"testing"
)

func TestGetCountOfFactor2(t *testing.T) {
	tests := []struct {
		number   int
		expected int
	}{
		{number: 128, expected: 7},
		{number: -1, expected: 0},
		{number: -2, expected: 1},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := getCountOfFactor2(test.number); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
func TestSolve(t *testing.T) {
	tests := []struct {
		as       []int
		expected int
	}{
		{as: []int{2, 4, 8}, expected: 1},
		{as: []int{8, 16, 20}, expected: 2},
		{as: []int{8, 16, 21}, expected: 0},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(test.as); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
