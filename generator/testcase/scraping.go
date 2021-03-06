package testcase

import (
	"fmt"
	"net/http"
	"strings"

	"github.com/gocolly/colly"
	"github.com/kelseyhightower/envconfig"
	"github.com/pkg/errors"
)

type AuthCredential struct {
	Username string
	Password string
}

const topURL = "https://atcoder.jp/"
const loginURL = "https://atcoder.jp/login"

func newCollector() *colly.Collector {
	c := colly.NewCollector(
		colly.UserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.101 Safari/537.36"),
		colly.AllowedDomains("atcoder.jp"),
	)

	c.OnRequest(func(r *colly.Request) {
		r.Headers.Set("Accept-Language", "ja-JP")
	})

	return c
}

func getCredentialsToLogin() (string, []*http.Cookie, error) {
	c := newCollector()

	var token string

	c.OnHTML("input[name=csrf_token]", func(e *colly.HTMLElement) {
		token = e.Attr("value")
	})

	if err := c.Visit(loginURL); err != nil {
		return "", nil, errors.WithStack(err)
	}

	c.Wait()

	if token == "" {
		return "", nil, errors.New("Login URL does not have csrf token")
	}

	return token, c.Cookies(loginURL), nil
}

func getAuthedCookies(cred *AuthCredential) ([]*http.Cookie, error) {
	csrfToken, cookies, err := getCredentialsToLogin()

	if err != nil {
		return nil, errors.WithStack(err)
	}

	c := newCollector()
	c.SetCookies(loginURL, cookies)

	c.RedirectHandler = func(req *http.Request, via []*http.Request) error {
		return nil
	}

	err = c.Post(loginURL, map[string]string{
		"username":   cred.Username,
		"password":   cred.Password,
		"csrf_token": csrfToken,
	})

	c.Wait()

	if err != nil {
		return nil, errors.WithStack(err)
	}

	return c.Cookies(topURL), nil
}

func scrapeTestCases(URL string) ([]*TestCase, error) {
	var cred AuthCredential
	if err := envconfig.Process("ATCODER", &cred); err != nil {
		return nil, errors.WithStack(err)
	}

	c := newCollector()

	if cred.Username != "" && cred.Password != "" {
		cookies, err := getAuthedCookies(&cred)

		if err != nil {
			return nil, errors.WithStack(err)
		}

		c.SetCookies(URL, cookies)
	}

	inputs := []string{}
	outputs := []string{}

	c.OnHTML(".nav.navbar-nav.navbar-right", func(e *colly.HTMLElement) {
		// When logged-in, language dropdown and profile dropdown exist.
		// When not logged-in, only language dropdown exists.
		selection := e.DOM.ChildrenFiltered(".dropdown")
		if len(selection.Nodes) == 2 {
			fmt.Println("Authed with " + cred.Username)
		} else {
			fmt.Println("Not authed. (cannot crawl test data for the contest in session)")
		}
	})

	c.OnHTML("#task-statement div.part", func(e *colly.HTMLElement) {
		isInputExample := false
		isOutputExample := false

		// only one h3 is included
		e.ForEach("h3", func(i int, he *colly.HTMLElement) {
			trimmed := strings.TrimSpace(e.Text)

			if strings.HasPrefix(trimmed, "入力例") {
				isInputExample = true
			} else if strings.HasPrefix(trimmed, "出力例") {
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

	if err := c.Visit(URL); err != nil {
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
