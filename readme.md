# Software Planner

## Summary

This is an application that will allow users to easily design and generate software application skeletons. It will be built off of a DSL that will allow generation without the use of the UI if desired by the user.

## Software Planner Transpiler

### Goal

Transpile DSL into other language projects.

### DSL

#### Rules

Tabs signify that the line above with a lower tab count contains this line

#### Generic

- CLASS: Class
- COTR: Constructor
- DIR: Directory
- FIELD: Field
- FILE: File
- INC: Include
- METD: Method
- PROP: Property
- REF: Reference
- USE: Using

#### Modifiers

- C: C
- CPP: C++
- CS: C Sharp
- GO: Golang
- JS: JavaScript
- RUST: Rust