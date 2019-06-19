package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"os/exec"
	"regexp"

	"github.com/pkg/errors"
	"github.com/tsugitta/atcoder/generator/testcase"
	"github.com/urfave/cli"
)

// https://atcoder.jp/contests/abc130/tasks/abc130_d -> (abc130, abc130_d)
func getProblemIdentifiers(URL string) (string, string, error) {
	reg := regexp.MustCompile(`contests\/(.+)\/tasks\/(.+)`)
	res := reg.FindStringSubmatch(URL)

	if len(res) != 3 {
		return "", "", errors.New("URL invalid")
	}

	return res[1], res[2], nil
}

func getPath(contest, problem string) string {
	return "./" + contest + "/" + problem
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
		return nil, err
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
		return err
	}

	defer file.Close()

	writer := bufio.NewWriter(file)
	comment := fmt.Sprintf("// %s\n\n", url)
	writer.WriteString(comment)
	for _, line := range lines {
		_, err = writer.WriteString(fmt.Sprintf("%s\n", line))
		if err != nil {
			return err
		}
	}

	if err := writer.Flush(); err != nil {
		return err
	}

	return nil
}

func writeTestCase(path string, testCaseYamlData []byte) error {
	file, err := os.Create(path + "/test.yaml")

	if err != nil {
		return errors.WithStack(err)
	}

	defer file.Close()

	_, err = file.Write(testCaseYamlData)

	if err != nil {
		return errors.WithStack(err)
	}

	return nil
}

func prepareFiles(URL string) error {
	contest, problem, err := getProblemIdentifiers(URL)

	if err != nil {
		return err
	}

	path := getPath(contest, problem)

	err = copyTemplates(path)

	if err != nil {
		return errors.WithStack(err)
	}

	err = prependURLToCode(path, URL)

	if err != nil {
		return errors.WithStack(err)
	}

	testCaseData, err := testcase.GenerateYaml(URL)

	if err != nil {
		return errors.WithStack(err)
	}

	err = writeTestCase(path, testCaseData)

	if err != nil {
		return errors.WithStack(err)
	}

	return nil
}

func main() {
	app := cli.NewApp()

	app.Name = "AtCoder preparer"
	app.Usage = "Prepare boilerplate with test cases for the passed URL. Run at root dir."
	app.Version = "0.0.1"

	app.Action = func(context *cli.Context) error {
		URL := context.Args().Get(0)
		return prepareFiles(URL)
	}

	err := app.Run(os.Args)

	if err != nil {
		log.Fatalf("%+v\n", err)
	}
}
