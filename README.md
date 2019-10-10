AtCoder challenge. mainly with Go, C++, & Rust.

## Structure

```
└── contests
    └── contest_name
        └── problem_id
            ├── // common
            ├── test.yaml
            ├── // for C++
            ├── main.cpp
            ├── main.h
            ├── test.cpp
            ├── // for Go
            ├── main.go
            ├── main_test.go
            ├── // for Rust
            ├── Cargo.toml
            ├── main.rs
            └── main_test.rs
```

- main.cpp, main.go, main.rs are the codes to submit
- test.yaml is test cases of stdin / stdout of the problem
- others are for the test which validates the stdin / stdout with the test case

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
