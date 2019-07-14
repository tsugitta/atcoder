package main

import (
	"fmt"
	"log"
	"os"

	"github.com/pkg/errors"
	"github.com/tsugitta/atcoder/generator/program"
	"github.com/tsugitta/atcoder/generator/testcase"
	"github.com/urfave/cli"
)

func validateLanguage(lang string) error {
	for _, available := range []string{
		"go",
		"rust",
	} {
		if lang == available {
			return nil
		}
	}

	return errors.New(fmt.Sprintf("%s is not supported lang.\n", lang))
}

func prepareFiles(URL, lang string) error {
	if err := validateLanguage(lang); err != nil {
		return err
	}

	if err := program.PrepareProgram(URL, lang); err != nil {
		return err
	}

	if err := testcase.PrepareTestCasesYaml(URL); err != nil {
		return err
	}

	fmt.Println("done.")
	return nil
}

func main() {
	app := cli.NewApp()

	app.Name = "AtCoder preparer"
	app.Usage = "Prepare boilerplate with test cases for the passed URL. Run at root dir."
	app.Version = "0.0.1"

	app.Flags = []cli.Flag{
		cli.StringFlag{
			Name:  "lang, l",
			Value: "go",
			Usage: "Language to use. go or rust.",
		},
	}

	app.Action = func(c *cli.Context) error {
		URL := c.Args().Get(0)
		return prepareFiles(URL, c.String("l"))
	}

	err := app.Run(os.Args)

	if err != nil {
		log.Fatalf("%+v\n", err)
	}
}
