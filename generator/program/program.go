package program

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"strings"
	"text/template"

	"github.com/pkg/errors"
	"github.com/tsugitta/atcoder/generator/path"
)

// PrepareProgram create dir for the problem and copy the program template there
func PrepareProgram(URL, lang string) error {
	dirPath, err := path.GetPath(URL)

	if err = copyTemplates(dirPath, lang, URL); err != nil {
		return err
	}

	return nil
}

func fillTemplate(path, URL, taskName string) error {
	t, err := template.ParseFiles(path)
	if err != nil {
		return errors.WithStack(err)
	}

	f, err := os.Create(path)

	if err != nil {
		return errors.WithStack(err)
	}

	defer f.Close()

	config := map[string]string{
		"URL":      URL,
		"TaskName": taskName,
	}

	if err = t.Execute(f, config); err != nil {
		return errors.WithStack(err)
	}

	return nil
}

func copyTemplates(dirPath, lang, URL string) error {
	mkdir := exec.Command("mkdir", "-p", dirPath)
	mkdir.Stderr = os.Stderr
	if err := mkdir.Run(); err != nil {
		return errors.WithStack(err)
	}

	cp := exec.Command("cp", "-rf", fmt.Sprintf("./generator/template/%s/.", lang), dirPath)
	cp.Stderr = os.Stderr
	if err := cp.Run(); err != nil {
		return errors.WithStack(err)
	}

	files, err := ioutil.ReadDir(dirPath)
	if err != nil {
		return errors.WithStack(err)
	}

	_, taskName, _ := path.GetProblemIdentifiers(URL)

	for _, file := range files {
		filePath := fmt.Sprintf("%s/%s", dirPath, file.Name())
		if err := fillTemplate(filePath, URL, taskName); err != nil {
			return errors.WithStack(err)
		}

		if err := os.Rename(filePath, strings.Replace(filePath, ".tmpl", "", 1)); err != nil {
			return errors.WithStack(err)
		}
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
