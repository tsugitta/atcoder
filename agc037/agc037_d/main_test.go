package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"sort"
	"strings"
	"testing"

	"github.com/stretchr/testify/assert"
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
				var output string

				{
					buffer := bytes.Buffer{}

					io := NewMockIo(c.In, &buffer)
					debugIo := NewIo()
					debugIo.Printfln("--- Func: %s, TestCase: %d ---", funcName, idx)
					solveFunc(io, debugIo)
					io.Flush()

					output = buffer.String()
				}

				{
					io := NewMockIo(c.In, nil)
					N := io.NextInt()
					M := io.NextInt()

					io = NewMockIo(output, nil)

					{
						b := make([][]int, N)

						for i := range b {
							b[i] = make([]int, M)
						}

						for i := 0; i < N; i++ {
							for j := 0; j < M; j++ {
								v := io.NextInt()
								b[i][j] = v
							}
						}

						for j := 0; j < M; j++ {
							tmp := make([]int, N)

							for i := 0; i < N; i++ {
								tmp[i] = (b[i][j] - 1) / M
							}

							sort.Ints(tmp)

							expected := make([]int, N)
							for i := 0; i < N; i++ {
								expected[i] = i
							}

							assert.Equal(t, expected, tmp)
						}
					}

					{
						for i := 0; i < N; i++ {
							row := make([]int, M)

							for j := 0; j < M; j++ {
								v := io.NextInt()
								row[j] = v % M
							}

							sort.Ints(row)

							expected := make([]int, M)
							for i := 0; i < M; i++ {
								expected[i] = i
							}

							assert.Equal(t, expected, row)
						}
					}
				}
			})
		}
	}
}
