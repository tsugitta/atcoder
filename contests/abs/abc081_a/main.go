package main

import (
	"fmt"
	"strings"
)

func solve(str string) string {
	res := strings.Count(str, "1")
	return fmt.Sprintf("%d", res)
}

func main() {
	var str string
	fmt.Scan(&str)

	output := solve(str)

	fmt.Println(output)
}
