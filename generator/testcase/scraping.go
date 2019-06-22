package testcase

import (
	"strings"

	"github.com/gocolly/colly"
	"github.com/pkg/errors"
)

func scrapeTestCases(URL string) ([]*TestCase, error) {
	c := colly.NewCollector(
		colly.UserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.101 Safari/537.36"),
		colly.AllowedDomains("atcoder.jp"),
	)

	inputs := []string{}
	outputs := []string{}

	c.OnHTML("#task-statement .lang-ja div.part", func(e *colly.HTMLElement) {
		isInputExample := false
		isOutputExample := false

		// only one h3 is included
		e.ForEach("h3", func(i int, he *colly.HTMLElement) {
			if strings.Contains(e.Text, "入力例") {
				isInputExample = true
			} else if strings.Contains(e.Text, "出力例") {
				isOutputExample = true
			}
		})

		if !isInputExample && !isOutputExample {
			return
		}

		e.ForEach("pre", func(i int, pe *colly.HTMLElement) {
			if isInputExample {
				inputs = append(inputs, pe.Text)
			} else if isOutputExample {
				outputs = append(outputs, pe.Text)
			}
		})
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
