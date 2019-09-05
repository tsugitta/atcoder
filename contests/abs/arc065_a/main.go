package main

import (
	"fmt"
	"strings"
)

func solve(S string) bool {
	if len(S) == 0 {
		return false
	}

	s := S

	words := []string{"dream", "dreamer", "erase", "eraser"}

	for len(s) > 0 {
		trimmed := false
		for _, word := range words {
			if strings.HasSuffix(s, word) {
				s = strings.TrimSuffix(s, word)
				trimmed = true
				break
			}
		}

		if !trimmed {
			return false
		}
	}

	return true
}

func solveFromPrefix(S string) bool {
	length := len(S)

	if length == 0 {
		return false
	}

	ptr := 0

	for ptr != length {
		rest := length - ptr

		if rest < 5 {
			return false
		}

		if S[ptr:ptr+5] == "dream" {
			ptr += 5 // dream
			// if `era` comes next, it can only be handled as dream + erase(r)
			if !(rest >= 8 && S[ptr:ptr+3] == "era") && rest >= 7 && S[ptr:ptr+2] == "er" {
				ptr += 2 // (dream)er
			}
		} else if S[ptr:ptr+5] == "erase" {
			ptr += 5 // erase
			if rest >= 6 && S[ptr] == 'r' {
				ptr++ // (erase)r
			}
		} else {
			return false
		}
	}
	return true
}

func main() {
	var S string
	fmt.Scan(&S)

	res := solve(S)

	if res {
		fmt.Println("YES")
	} else {
		fmt.Println("NO")
	}
}
