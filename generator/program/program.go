package program

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"

	"github.com/pkg/errors"
	"github.com/tsugitta/atcoder/generator/path"
)

// PrepareProgram create dir for the problem and copy the program template there
func PrepareProgram(URL string) error {
	path, err := path.GetPath(URL)

	err = copyTemplates(path)

	if err != nil {
		return err
	}

	err = prependURLToCode(path, URL)

	if err != nil {
		return err
	}

	return nil
}

func copyTemplates(path string) error {
	mkdir := exec.Command("mkdir", "-p", path)
	mkdir.Stderr = os.Stderr
	if err := mkdir.Run(); err != nil {
		return errors.WithStack(err)
	}

	cp := exec.Command("cp", "-rf", "./generator/template/.", path)
	cp.Stderr = os.Stderr
	if err := cp.Run(); err != nil {
		return errors.WithStack(err)
	}

	return nil
}

func readFile(path string) ([]string, error) {
	file, err := os.OpenFile(path, os.O_RDONLY, 0600)
	if err != nil {
		return nil, errors.WithStack(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	lines := make([]string, 0)

	for scanner.Scan() {
		line := scanner.Text()
		lines = append(lines, line)
	}

	return lines, nil
}

func prependURLToCode(dirPath, url string) error {
	path := dirPath + "/main.go"
	lines, err := readFile(path)

	if err != nil {
		return err
	}

	file, err := os.OpenFile(path, os.O_WRONLY|os.O_TRUNC, 0600)

	if err != nil {
		return errors.WithStack(err)
	}

	defer file.Close()

	writer := bufio.NewWriter(file)
	comment := fmt.Sprintf("// %s\n\n", url)
	writer.WriteString(comment)
	for _, line := range lines {
		_, err = writer.WriteString(fmt.Sprintf("%s\n", line))
		if err != nil {
			return errors.WithStack(err)
		}
	}

	if err := writer.Flush(); err != nil {
		return errors.WithStack(err)
	}

	return nil
}
