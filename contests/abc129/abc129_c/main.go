package main

import (
	"fmt"
)

func abs(n int) int {
	if n < 0 {
		return -n
	}

	return n
}

func solve(N int, as []int) int {
	dp := map[int]int{}

	broken := map[int]bool{}

	for i := 0; i < len(as); i++ {
		broken[as[i]] = true
	}

	dp[0] = 1
	if broken[1] {
		dp[1] = 0
	} else {
		dp[1] = 1
	}

	for i := 2; i <= N; i++ {
		if broken[i] {
			dp[i] = 0
		} else {
			dp[i] = (dp[i-1] + dp[i-2]) % 1000000007
		}
	}

	return dp[N]
}

func main() {
	var N, M int

	fmt.Scan(&N)
	fmt.Scan(&M)

	as := make([]int, M)

	for i := 0; i < M; i++ {
		fmt.Scan(&as[i])
	}

	output := solve(N, as)

	fmt.Println(output)
}
