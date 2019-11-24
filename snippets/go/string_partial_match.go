package go_snippets

// O(|s|)
func zAlgorithm(s string) []int {
	n := len(s)
	z := make([]int, n)
	z[0] = n
	for i, j := 1, 0; i < n; {
		for i+j < n && s[j:j+1] == s[i+j:i+j+1] {
			j++
		}

		z[i] = j

		if j == 0 {
			i++
			continue
		}

		k := 1

		for ; i+k < n && k+z[k] < j; k++ {
			z[i+k] = z[k]
		}

		i, j = i+k, j-k
	}
	return z
}

func getPatternIndices(s, pat string) (res []int) {
	arg := pat + s
	z := zAlgorithm(arg)
	ls := len(s)
	lp := len(pat)

	for i := 0; i < ls; i++ {
		if z[lp+i] >= lp {
			res = append(res, i)
		}
	}

	return
}
