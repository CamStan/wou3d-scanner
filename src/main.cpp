#include <iostream>
#include <cstdlib>
#include <csignal>

using std::cout;
using std::endl;

// Function prototypes
void quitHandler(int);		// handle SIGINT  signal

/**
 * @file
 * @brief Main program for the WOU Scanner
 * 
 * Entry point function.  This starts the scanner base unit
 * code.  No arguments are currently used.
 *
 * @param  argc Number of arguments passed
 * @param  argv Pointer to the first string passed
 * @return      Returns EXIT_SUCCESS upon normal termination,
 *              non-zero upon exceptional or failure exit
 */
int main (int argc, char *argv[])
{
    // register our signal handler
	std::signal(SIGINT, quitHandler);

	cout << "Hello Scanner!" << endl;
	return EXIT_SUCCESS;
}

/**
 * Receive the SIGINT (CTRL+C) signal.  Clean up and quit.
 * @param sig ID of the signal received
 */
void quitHandler(int sig)
{
	if (sig == SIGINT)
	{
		cout << "Received SIGINT" << endl;
	}
	exit(EXIT_SUCCESS);
}
