package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"strconv"
	"strings"
	"testing"

	"gopkg.in/yaml.v2"
)

type SolveFunction = func(io, debugIo *Io)

var solveFuncMap map[string]SolveFunction

func TestMain(m *testing.M) {
	solveFuncMap = map[string]SolveFunction{
		// Add solve functions here to test another solution
		"solve": solve,
	}

	exit := m.Run()

	if exit != 0 {
		os.Exit(exit)
	}
}

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

func NewMockIo(input string, outputBuffer *bytes.Buffer) *Io {
	return &Io{
		reader: bufio.NewReader(strings.NewReader(input)),
		writer: bufio.NewWriter(outputBuffer),
	}
}

func TestSolve(t *testing.T) {
	yamlBuf, err := ioutil.ReadFile("./test.yaml")

	if err != nil {
		log.Fatal(err)
	}

	cases, err := YamlBufToTestCases(yamlBuf)

	for funcName, solveFunc := range solveFuncMap {
		for idx, c := range cases {
			t.Run(fmt.Sprintf("%s %d", funcName, idx), func(t *testing.T) {
				buffer := bytes.Buffer{}

				io := NewMockIo(c.In, &buffer)
				debugIo := NewIo()
				debugIo.Printfln("--- Func: %s, TestCase: %d ---", funcName, idx)
				solveFunc(io, debugIo)
				io.Flush()

				output := buffer.String()

				expectedF := stringToFloat(c.Out)
				outputF := stringToFloat(output)

				if !floatEqual(expectedF, outputF, 10) {
					t.Fatalf("expected: %#v, actual: %#v", c.Out, output)
				}
			})
		}
	}
}

func floatEqual(a, b float64, digit int) bool {
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

func stringToFloat(v string) float64 {
	res, _ := strconv.ParseFloat(strings.Trim(v, "\n"), 64)
	return res
}
