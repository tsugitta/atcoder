package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
	"testing"

	"github.com/tsugitta/atcoder/testutil"
)

type SolveFunction = func(io, debugIo *Io)

var solveFuncMap map[string]SolveFunction

func TestMain(m *testing.M) {
	solveFuncMap = map[string]SolveFunction{
		// Add solve functions here to test another solution
		"solve":  solve,
		"solve2": solve2,
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

				isValid := func(output string) bool {
					inputIo := NewMockIo(c.In, nil)

					H := inputIo.NextInt()
					W := inputIo.NextInt()
					A := inputIo.NextInt()
					B := inputIo.NextInt()

					outIo := NewMockIo(output, nil)

					mat := make([][]int, H)
					for i := range mat {
						mat[i] = make([]int, W)
					}

					for i := 0; i < H; i++ {
						chs := outIo.NextRunes()
						for j := 0; j < W; j++ {
							mat[i][j], _ = strconv.Atoi(string(chs[j]))
						}
					}

					for i := 0; i < H; i++ {
						zeroCt := 0
						oneCt := 0

						for j := 0; j < W; j++ {
							if mat[i][j] == 0 {
								zeroCt++
							} else if mat[i][j] == 1 {
								oneCt++
							}
						}

						if Min(zeroCt, oneCt) != A {
							return false
						}
					}

					for j := 0; j < W; j++ {
						zeroCt := 0
						oneCt := 0

						for i := 0; i < H; i++ {
							if mat[i][j] == 0 {
								zeroCt++
							} else if mat[i][j] == 1 {
								oneCt++
							}
						}

						if Min(zeroCt, oneCt) != B {
							return false
						}
					}

					return true
				}

				if !isValid(output) {
					t.Fatalf("expected: %#v, actual: %#v", c.Out, output)
				}
			})
		}
	}
}
