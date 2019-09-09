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

	"github.com/tsugitta/atcoder/testutil"
)

func naive(io *Io, d *Io) {
	N := io.NextInt()
	ps := io.NextInts(N)

	res := 0

	for l := 0; l+1 < len(ps); l++ {
		for r := l + 1; r < len(ps); r++ {
			max := -1
			sec := -1

			for i := l; i <= r; i++ {
				if ps[i] > max {
					sec = max
					max = ps[i]
				} else if ps[i] > sec {
					sec = ps[i]
				}
			}

			res += sec
		}
	}

	io.Println(res)
}

type SolveFunction = func(io, debugIo *Io)

var solveFuncMap map[string]SolveFunction

func TestMain(m *testing.M) {
	solveFuncMap = map[string]SolveFunction{
		// Add solve functions here to test another solution
		"solve": solve,
		"naive": naive,
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
	yamlBuf, err := ioutil.ReadFile("./test.yaml")

	if err != nil {
		log.Fatal(err)
	}

	cases, err := testutil.YamlBufToTestCases(yamlBuf)

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
