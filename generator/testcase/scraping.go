package testcase

import (
	"github.com/gocolly/colly"
	"github.com/pkg/errors"
)

func scrapeTestCases(URL string) ([]*TestCase, error) {
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

	testCases := make([]*TestCase, len(inputs))

	for i, in := range inputs {
		out := outputs[i]
		testCases[i] = &TestCase{
			In:  in,
			Out: out,
		}
	}

	return testCases, nil
}
