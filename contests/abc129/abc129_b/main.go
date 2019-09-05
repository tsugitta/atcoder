package main

import (
	"fmt"
	"math"
)

func abs(n int) int {
	if n < 0 {
		return -n
	}

	return n
}

func solve(N int, ws []int) int {
	sum := 0

	for i := 0; i < len(ws); i++ {
		sum += ws[i]
	}

	min := math.MaxInt64
	leftSum := 0
	for t := 0; t < len(ws)-1; t++ {
		leftSum += ws[t]
		rightSum := sum - leftSum

		if abs(leftSum-rightSum) < min {
			min = abs(leftSum - rightSum)
		}
	}

	return min
}

func main() {
	var N int

	fmt.Scan(&N)

	ws := make([]int, N)

	for i := 0; i < N; i++ {
		fmt.Scan(&ws[i])
	}

	output := solve(N, ws)

	fmt.Println(output)
}
