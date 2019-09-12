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
		"solve":  solve,
		"solve2": solve2,
		"naive":  naive,
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
	yamlBufRandom, _ := ioutil.ReadFile("./test_random.yaml")
	randomCases, _ := testutil.YamlBufToTestCases(yamlBufRandom)

	cases = append(cases, randomCases...)

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

func AddRandom(t *testing.T) {
	TIMES := 20

	cases := make([]testutil.TestCase, 0)

	for i := 0; i < TIMES; i++ {
		buffer := bytes.Buffer{}

		N := 20
		arr := make([]int, N)

		{
			io := NewMockIo("", &buffer)

			io.Println(N)

			for i := 0; i < N; i++ {
				arr[i] = i + 1
			}

			testutil.Shuffle(arr)
			io.PrintInts(arr)

			io.Flush()
		}

		in := buffer.String()

		var naiveRes string

		{
			buffer = bytes.Buffer{}
			io := NewMockIo(in, &buffer)

			naive(io, nil)
			io.Flush()

			naiveRes = buffer.String()
		}

		c := testutil.TestCase{
			In:  in,
			Out: naiveRes,
		}

		cases = append(cases, c)
	}

	buf, err := testutil.AppendTestCases([]byte{}, cases)

	if err != nil {
		log.Fatal(err)
	}

	ioutil.WriteFile("./test_random.yaml", buf, 0644)
}
func TestRandom(t *testing.T) {
	TIMES := 200

	for i := 0; i < TIMES; i++ {
		buffer := bytes.Buffer{}

		N := 20
		arr := make([]int, N)

		{
			io := NewMockIo("", &buffer)

			io.Println(N)

			for i := 0; i < N; i++ {
				arr[i] = i + 1
			}

			testutil.Shuffle(arr)
			io.PrintInts(arr)

			io.Flush()
		}

		in := buffer.String()

		var naiveRes string
		var solveRes string

		{
			buffer = bytes.Buffer{}
			io := NewMockIo(in, &buffer)

			naive(io, nil)
			io.Flush()

			naiveRes = buffer.String()
		}

		{
			buffer = bytes.Buffer{}
			io := NewMockIo(in, &buffer)

			solve(io, nil)
			io.Flush()

			solveRes = buffer.String()
		}

		if ok := assert.Equal(t, naiveRes, solveRes); !ok {
			fmt.Println(arr)
		}
	}
}
