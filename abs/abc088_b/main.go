package main

import (
	"fmt"
)

func sortDesc(numbers []int) []int {
	if len(numbers) < 2 {
		return numbers
	}

	pivot := numbers[0]

	left := []int{}
	right := []int{}

	for _, n := range numbers[1:] {
		if n > pivot {
			left = append(left, n)
		} else {
			right = append(right, n)
		}
	}

	left = sortDesc(left)
	right = sortDesc(right)

	res := append(append(left, pivot), right...)
	return res
}

func solve(as []int) int {
	res := 0
	sorted := sortDesc(as)

	length := len(sorted)

	for i := 0; i < length; i += 2 {
		res += sorted[i]

		if i+1 < length {
			res -= sorted[i+1]
		}
	}

	return res
}

func main() {
	var n int
	fmt.Scan(&n)

	as := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&as[i])
	}

	output := solve(as)
	fmt.Println(output)
}
