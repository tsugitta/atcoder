package main

import (
	"fmt"
	"reflect"
	"testing"
)

func TestSortDesc(t *testing.T) {
	tests := []struct {
		numbers  []int
		expected []int
	}{
		{numbers: []int{2, 1, 9, 5, 3}, expected: []int{1, 2, 3, 5, 9}},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := sortDesc(test.numbers); reflect.DeepEqual(actual, test.expected) {
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
		{as: []int{3, 1}, expected: 2},
		{as: []int{2, 7, 4}, expected: 5},
		{as: []int{20, 18, 2, 18}, expected: 18},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(test.as); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
