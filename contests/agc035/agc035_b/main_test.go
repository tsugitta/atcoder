package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io/ioutil"
	"os"
	"strings"
	"testing"

	"github.com/tsugitta/atcoder/testutil"
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

func NewMockIo(input string, outputBuffer *bytes.Buffer) *Io {
	return &Io{
		reader: bufio.NewReader(strings.NewReader(input)),
		writer: bufio.NewWriter(outputBuffer),
	}
}

func TestSolve(t *testing.T) {
	yamlBuf, _ := ioutil.ReadFile("./test.yaml")
	cases, _ := testutil.YamlBufToTestCases(yamlBuf)

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

func TestLarge(t *testing.T) {
	buffer := bytes.Buffer{}

	N := int(1e5)
	M := int(1e5 - 1)

	io := NewMockIo("", &buffer)
	io.Println(N, M)

	for i := 0; i < M; i++ {
		io.Println(i+1, i+2)
	}

	io.Flush()
	in := buffer.String()

	outBuffer := bytes.Buffer{}

	solveIo := NewMockIo(in, &outBuffer)
	debugIo := NewIo()

	solve(solveIo, debugIo)

}
