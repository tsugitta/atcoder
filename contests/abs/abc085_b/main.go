package main

import (
	"fmt"
)

func solve(ds []int) int {
	m := map[int]int{}

	length := len(ds)

	for i := 0; i < length; i++ {
		d := ds[i]
		m[d] = 1
	}

	return len(m)
}

func main() {
	var n int
	fmt.Scan(&n)

	ds := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&ds[i])
	}

	output := solve(ds)
	fmt.Println(output)
}
