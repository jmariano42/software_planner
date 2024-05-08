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

| Keyword | Output      | Usage                                                                | Example                            |
| ------- | ----------- | -------------------------------------------------------------------- | ---------------------------------- |
| CLASS   | Class       | %modifier% CLASS %accessibility% %name%                              | CS CLASS public MyClass            |
| COTR    | Constructor | %modifier% COTR %accessibility% %param datatype% %param name%        | CS COTR public int MyParam         |
| DIR     | Directory   | DIR %name%                                                           | DIR MyDirectory                    |
| FIELD   | Field       | %modifier% FIELD %accessibility% %datatype% %name%                   | CS FIELD private int _myField      |
| FILE    | File        | FILE %name%.%extension%                                              | FILE MyFile.txt                    |
| INC     | Include     | INC %include%                                                        | INC "myHeader.h"                   |
| METD    | Method      | %modifier% METD %accessibility% %return type% %name%                 | CS METD public void MyMethod       |
| PROP    | Property    | %modifier% PROP %accessibility% %datatype% %name% %associated field% | CS PROP public int MyProp _myField |
| REF     | Reference   | %modifier% REF %name%                                                | CS REF MyRefProject                |
| USE     | Using       | %modifier% USE %name%                                                | CS USE System                      |

#### Specific

##### C#

| Keyword | Output   | Usage                        | Example                   |
| ------- | -------- | ---------------------------- | ------------------------- |
| CSSLN   | Solution | CSSLN %name%                 | CSSLN MySolution          |
| CSPROJ  | Project  | CSPROJ %name% %project type% | CSPROJ MyProject classlib |

[C# project types](https://learn.microsoft.com/en-us/dotnet/core/tools/dotnet-new)

#### Modifiers

| Keyword | Langauge   |
| ------- | ---------- |
| C       | C          |
| CPP     | C++        |
| CS      | C#         |
| GO      | Golang     |
| JS      | JavaScript |
| RUST    | Rust       |