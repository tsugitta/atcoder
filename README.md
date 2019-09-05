AtCoder challenge. mainly with Go (& Rust).

## Structure

```
└── contests
    └── contest_name
        └── problem_id
            ├── main.go
            ├── main_test.go
            ├── Cargo.toml
            ├── main.rs
            ├── main_test.rs
            └── test.yaml
```

- main.go is the problem to submit
- test.yaml is test cases of stdin / stdout of the proglam
- main_test.go is to test the result is same as test.yaml

## Generator

in the root dir, run

```
$ go run generator/main.go https://atcoder.jp/contests/foo/tasks/bar
```

and you can get the files noted above with the test cases shown at the page.

If the contet is in session, login is necessary to scrape the questions.
to provide the scraper with the login information, set below as environment variables.

```
ATCODER_USERNAME=foo
ATCODER_PASSWORD=bar
```
