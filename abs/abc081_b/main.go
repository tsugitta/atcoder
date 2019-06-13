package main

import (
	"fmt"
	"math"
)

// number cannot be 0
func getCountOfFactor2(number int) int {
	res := 0

	for number%2 == 0 {
		number = number >> 1
		res++
	}

	return res
}

func solve(as []int) int {
	var minCountOfFactor2 = math.MaxInt64

	for _, a := range as {
		ct := getCountOfFactor2(a)

		if ct == 0 {
			return 0
		}

		if ct < minCountOfFactor2 {
			minCountOfFactor2 = ct
		}
	}

	return minCountOfFactor2
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
