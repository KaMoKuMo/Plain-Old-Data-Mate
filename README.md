# Plain Old Data Mate
Is a prototyp of a source code generator for simple C++ pods.
The envisioned usage of the tool is to generate source code
for simple structs as a seperate build-step.
To ease the scripting process errors are returned via cout with the reason of failure.

## Roadmap for the alpha version
- [x] generate operator==
- [x] generate operator!=
- [x] generate the code within the namespace of the structs
- [x] generate operator<<(std::ostream&, ..)
- [x] generate json deserialization glue code for simdjson
- [] add warnings for not supported fundamental types for the simdjson framework
- [] add support for json deserialization/serialization for std container types (optional, variant, vector)
- [] add support for custom json-key usage
- [] add support for configuration file instead of command line arguments


## Build
To build the project execute the bash script build.sh

## Examples
To see how the podmate app can be used, see the semi automated integration test
within build_and_run_sample.sh
