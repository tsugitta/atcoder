package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io/ioutil"
	"log"
	"os"
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

func TestCombination(t *testing.T) {
	cases := []struct {
		n        int
		k        int
		expected int
	}{
		{6, 3, 20},
		{1, 1, 1},
		{1, 0, 1},
		{7, 3, 35},
		{8, 4, 70},
		{40, 10, 847660528},
	}

	for _, c := range cases {
		prepareCombination()
		res := combinationM(c.n, c.k)
		if c.expected != res {
			t.Fatalf("expected: %#v, actual: %#v", c.expected, res)
		}
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
				if output != c.Out {
					t.Fatalf("expected: %#v, actual: %#v", c.Out, output)
				}
			})
		}
	}
}
