package testcase

import (
	"os"

	"github.com/pkg/errors"
	"github.com/tsugitta/atcoder/generator/path"
	"gopkg.in/yaml.v2"
)

type TestCase struct {
	In  string
	Out string
}

// PrepareTestCasesYaml scrapes the test cases and place them in the dir as yaml
func PrepareTestCasesYaml(URL string) error {
	path, err := path.GetPath(URL)

	if err != nil {
		return err
	}

	testCaseData, err := generateYaml(URL)

	if err != nil {
		return err
	}

	err = writeTestCase(path, testCaseData)

	if err != nil {
		return err
	}

	return nil
}

func generateYaml(URL string) ([]byte, error) {
	testCases, err := scrapeTestCases(URL)

	if err != nil {
		return nil, errors.WithStack(err)
	}

	testCaseData, err := yaml.Marshal(testCases)

	if err != nil {
		return nil, errors.WithStack(err)
	}

	return testCaseData, err
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
