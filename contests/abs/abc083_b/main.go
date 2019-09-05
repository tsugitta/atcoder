package main

import (
	"fmt"
)

func solve(n, a, b int) int {
	res := 0

	for i := 1; i <= n; i++ {
		resI := 0

		j := i

		for j >= 10 {
			resI += j % 10
			j /= 10
		}

		resI += j

		if resI >= a && resI <= b {
			res += i
		}
	}

	return res
}

func main() {
	var n, a, b int

	fmt.Scanf("%d %d %d", &n, &a, &b)

	output := solve(n, a, b)

	fmt.Println(output)
}
