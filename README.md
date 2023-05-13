# osquery_ping_ext

## Build & Run
Copy paste the project into osquery/external/examples and compile the whole osquery repo. Run "osqueryi --extension {ping_extension.ext path}" where the path is osquery/build/external/examples/ping by default.

## Technical Decision Walkthrough
The extension program will first utilize the C++ regex library to validate the host input. This will prevent any injection attack because we will later run the ping command by interpolating the host string. After the validation, we will call system() with the right command, and pipe the average ping latency to our process. We will then make a row in the table that contains the host address and latency as attributes. 