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

	"github.com/stretchr/testify/assert"
	"github.com/tsugitta/atcoder/testutil"
	"gopkg.in/yaml.v2"
)

type SolveFunction = func(io, debugIo *Io)

var solveFuncMap map[string]SolveFunction

func TestMain(m *testing.M) {
	solveFuncMap = map[string]SolveFunction{
		// Add solve functions here to test another solution
		// "naive":  naive,
		"solve":  solve,
		"solve2": solve2,
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
				if output != c.Out {
					t.Fatalf("expected: %#v, actual: %#v", c.Out, output)
				}
			})
		}
	}
}

func TestRandom(t *testing.T) {
	TIMES := 100

	for i := 0; i < TIMES; i++ {
		N := 5

		buffer := bytes.Buffer{}
		io := NewMockIo("", &buffer)
		io.Println(N)

		for i := 1; i <= N; i++ {
			arr := []int{}

			for j := 1; j <= N; j++ {
				if i != j {
					arr = append(arr, j)
				}
			}

			testutil.Shuffle(arr)

			io.PrintInts(arr)
		}

		io.Flush()
		in := buffer.String()

		var naiveRes string
		var solveRes string

		{
			buffer = bytes.Buffer{}
			io = NewMockIo(in, &buffer)

			naive(io, nil)
			io.Flush()

			naiveRes = buffer.String()
		}

		if naiveRes == "-1\n" {
			continue
		}

		{
			buffer = bytes.Buffer{}
			io = NewMockIo(in, &buffer)

			solve2(io, nil)
			io.Flush()

			solveRes = buffer.String()
		}

		assert.Equal(t, naiveRes, solveRes)
	}
}
