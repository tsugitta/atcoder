package testutil

import (
	"fmt"

	"strconv"
	"strings"

	"gopkg.in/yaml.v2"
)

type TestCase struct {
	In  string
	Out string
}

func YamlBufToTestCases(buf []byte) ([]TestCase, error) {
	cases := make([]TestCase, 10)
	err := yaml.Unmarshal(buf, &cases)

	if err != nil {
		fmt.Println(err)
		return nil, err
	}

	return cases, nil
}

func FloatEqual(a, b float64, digit int) bool {
	var diff float64

	if a > b {
		diff = a - b
	} else {
		diff = b - a
	}

	threshold := 1.0
	for i := 0; i < digit; i++ {
		threshold /= 10
	}

	return diff <= threshold
}

func StringToFloat(v string) float64 {
	res, _ := strconv.ParseFloat(strings.Trim(v, "\n"), 64)
	return res
}
