# osquery_ping_ext

## My Thoughts
I really want to join the team! Due to time constraints (it is currently Cornell's finals week), I know that my implementation isn't best of the best, but I would like to demonstrate my effort and thoughts in this seciton. I spent ~16 hours on this project in total. ~5 hours are spent figuring out environment setup and making sure everything links together. ~6 hours are spent on learning about OSQuery and how to write extensions. I tried to use the icmp library in boost::asio to issue a ping request, but I keep running into root priviledge issues that I was unable to avoid. I settled on using system() and piping the result of the standard output, but I made sure that the input is sanitized. The final ~5 hours were spent on figuring out how to build, link and run unittests. 

## Build & Run
Copy paste the project into osquery/external/examples and compile the whole osquery repo. Run "osqueryi --extension {ping_extension.ext path}" where the path is "osquery/build/external/examples/ping/ping_extension.ext" by default.

To run unittests, simply run "ctest -R ping_test -V" in osquery/build.

Sample Query:
select * from ping where host = "google.com";
select latency from ping where host = "8.8.8.8";

## Technical Decision Walkthrough
The extension program will first utilize the C++ regex library to validate the host input. This will prevent any injection attack because we will later run the ping command by interpolating the host string. After the validation, we will call system() with the right command, and pipe the average ping latency to our process. We will then make a row in the table that contains the host address and latency as attributes. 

