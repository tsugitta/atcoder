package main

import (
	"fmt"
	"log"
	"os"

	"github.com/tsugitta/atcoder/generator/program"
	"github.com/tsugitta/atcoder/generator/testcase"
	"github.com/urfave/cli"
)

func prepareFiles(URL string) error {
	err := program.PrepareProgram(URL)

	if err != nil {
		return err
	}

	err = testcase.PrepareTestCasesYaml(URL)

	if err != nil {
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

	app.Action = func(context *cli.Context) error {
		URL := context.Args().Get(0)
		return prepareFiles(URL)
	}

	err := app.Run(os.Args)

	if err != nil {
		log.Fatalf("%+v\n", err)
	}
}
