package path

import (
	"regexp"

	"github.com/pkg/errors"
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

func GetPath(URL string) (string, error) {
	contest, problem, err := getProblemIdentifiers(URL)

	if err != nil {
		return "", errors.WithStack(err)
	}

	return "./" + contest + "/" + problem, nil
}
