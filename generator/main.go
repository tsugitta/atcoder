package main

import (
	"log"
	"os"
	"os/exec"
	"regexp"

	"github.com/gocolly/colly"
	"github.com/pkg/errors"
	"github.com/urfave/cli"
	"gopkg.in/yaml.v2"
)

type testCase struct {
	In  string
	Out string
}

func scrapeTestCases(URL string) ([]*testCase, error) {
	c := colly.NewCollector(
		colly.AllowedDomains("atcoder.jp"),
	)

	inputs := []string{}
	outputs := []string{}
	elementCount := 0

	c.OnHTML("#task-statement .lang-ja pre", func(e *colly.HTMLElement) {
		elementCount++

		if elementCount == 1 {
			// this is not a test case, but a description about input / output
			return
		} else if elementCount%2 == 0 {
			inputs = append(inputs, e.Text)
		} else {
			outputs = append(outputs, e.Text)
		}
	})

	err := c.Visit(URL)

	if err != nil {
		return nil, errors.WithStack(err)
	}

	c.Wait()

	testCases := make([]*testCase, len(inputs))

	for i, in := range inputs {
		out := outputs[i]
		testCases[i] = &testCase{
			In:  in,
			Out: out,
		}
	}

	return testCases, nil
}

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

func writeTestCase(path string, testCases []*testCase) error {
	testCaseData, err := yaml.Marshal(testCases)

	if err != nil {
		return errors.WithStack(err)
	}

	file, err := os.Create(path + "/test.yaml")

	if err != nil {
		return errors.WithStack(err)
	}

	_, err = file.Write(testCaseData)

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

	testCases, err := scrapeTestCases(URL)

	if err != nil {
		return errors.WithStack(err)
	}

	err = writeTestCase(path, testCases)

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
