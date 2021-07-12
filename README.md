# Plain Old Data Mate
Is a prototyp of a source code generator for simple C++ pods.

## Roadmap
- [x] generate operator==
- [x] generate operator!=
- [x] generate the code within the namespace of the structs
- [] generate operator<<(std::ostream&, ..)
- [] generate json serialization
- [] generate json deserialization glue code for e.g. simdjson

## Build
To build the project execute the bash script build.sh

## Examples
To see how the podmate app can be used, see the semi automated integration test
within build_and_run_sample.sh
