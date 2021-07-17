# Plain Old Data Mate
Is a prototyp of a source code generator for simple C++ pods.
The envisioned usage of the tool is to generate source code
for simple structs as a seperate build-step.
To ease the scripting process errors are returned via cout with the reason of failure.

## Roadmap for Alpha
- [x] generate operator==
- [x] generate operator!=
- [x] generate the code within the namespace of the structs
- [x] generate operator<<(std::ostream&, ..)
- [] generate json deserialization glue code for e.g. simdjson

## Build
To build the project execute the bash script build.sh

## Examples
To see how the podmate app can be used, see the semi automated integration test
within build_and_run_sample.sh
