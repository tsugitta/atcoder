package main

import (
	"bufio"
	"bytes"
	"fmt"
	"strings"
	"testing"
	"io/ioutil"
	"log"

	"gopkg.in/yaml.v2"
)

type TestCase struct {
	In string
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

	for idx, c := range cases {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			buffer := bytes.Buffer{}

			io := NewMockIo(c.In, &buffer)
			solve(io)
			io.Flush()

			output := strings.TrimSuffix(buffer.String(), "\n")
			if output != c.Out {
				t.Fatalf("expected: %#v, actual: %#v", c.Out, output)
			}
		})
	}
}
