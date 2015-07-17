#SnapMatrixMarketConverter

A small utility for converting (in one direction only) between graph file formats. 

## Rationale

Certain graph analysis toolkits require their inputs in "matrix market" format. However, many benchmarks are delivered in "edge list" format. This toolkit converts from the latter format (edge list) to the former (matrix market).

## Building

To build, simply run the `make` command, which should automatically and correctly build the program.

## Running

The application is somewhat brittle, as it was written in a hurry to quickly convert some datafiles for benchmarking. Because of this, it only supports one invocation method:

    ./mm_convert_snap_file <input_file> <output_file>

The file specified in `<input_file>` must be a sequence of lines of the form:

    <node> <node>

Where each node is an integer. The input and output files *must* be passed as the first and second arguments (respectively) of the program; all other arguments are ignored.

