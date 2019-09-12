package testutil

import (
	"math/rand"
	"time"

	"strconv"
	"strings"

	"github.com/pkg/errors"
	"gopkg.in/yaml.v3"
)

type TestCase struct {
	In  string
	Out string
}

func AppendTestCases(buf []byte, cases []TestCase) ([]byte, error) {
	alreadyAdded, err := YamlBufToTestCases(buf)

	if err != nil {
		return nil, errors.WithStack(err)
	}

	toBeWritten := append(alreadyAdded, cases...)

	res, err := yaml.Marshal(toBeWritten)

	if err != nil {
		return nil, errors.WithStack(err)
	}

	return res, nil
}

func YamlBufToTestCases(buf []byte) ([]TestCase, error) {
	cases := make([]TestCase, 0)
	err := yaml.Unmarshal(buf, &cases)

	if err != nil {
		return nil, errors.WithStack(err)
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

func Shuffle(arr []int) {
	rand.Seed(time.Now().UnixNano())
	rand.Shuffle(len(arr), func(i, j int) { arr[i], arr[j] = arr[j], arr[i] })
}
