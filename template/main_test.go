package main

import (
	"bufio"
	"bytes"
	"fmt"
	"strings"
	"testing"
)

func NewMockIo(input string, outputBuffer *bytes.Buffer) *Io {
	return &Io{
		reader: bufio.NewReader(strings.NewReader(input)),
		writer: bufio.NewWriter(outputBuffer),
	}
}

func TestSolve(t *testing.T) {
	cases := []struct {
		input    string
		expected string
	}{
		{
`foo`,
`foo
`},
	}

	for idx, c := range cases {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			buffer := bytes.Buffer{}

			io := NewMockIo(c.input, &buffer)
			solve(io)
			io.Flush()

			if actual := buffer.String(); actual != c.expected {
				t.Fatalf("expected: %#v, actual: %#v", c.expected, actual)
			}
		})
	}
}
