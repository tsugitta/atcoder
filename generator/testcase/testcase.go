package testcase

import (
	"github.com/pkg/errors"
	"gopkg.in/yaml.v2"
)

type TestCase struct {
	In  string
	Out string
}

func GenerateYaml(URL string) ([]byte, error) {
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
