#include <iostream>
#include <cstdlib>		// for exit() and exit status
#include <unistd.h>		// provides sleep()
#include <csignal>		// for signals

using std::cout;
using std::endl;

/*
 * Example to show how to intercept signals from the Linux OS to:
 * 		- quit nicely, i.e. release resources, turn off stepper motors, ...
 * 		- perhaps pause a scan
 * 		- respond to a request for information from the running process
 *
 * 	These signals are asynchronous and may be called at any time.  Think of
 * 	them as software interrupts that come from the OS, and in this case,
 * 	from the user via the keyboard or terminal.
 */

// Function prototypes
void quitHandler(int);		// handle SIGINT  signal
void infoHandler(int);		// handle SIGTSTP signal

// shared data
bool infoFlag = false;

int main()
{
	// register our signal handlers
	std::signal(SIGINT, quitHandler);
	std::signal(SIGTSTP, infoHandler);

	int cycleCount = 0;

	cout << "Welcome to this example, press CTRL+Z for info, CTRL+C to quit" << endl;
	
	for (;;)
	{
		++cycleCount;
		// When convenient, update the user with current info
		if(infoFlag)
		{
			cout << "The current cycle count is: " << cycleCount << endl;
			infoFlag = false;
		}
		usleep(50000);
	}

	return EXIT_SUCCESS;
}

/* Receive the SIGINT (CTRL+C) signal.  Clean up and quit. */
void quitHandler(int sig)
{
	if (sig == SIGINT)
	{
		cout << "Received SIGINT" << endl;
	}
	exit(EXIT_SUCCESS);
}

/*
 * Receive the SIGTSTP (CTRL+Z) signal.
 * Ideally we'd respond to SIGINFO (CTRL+T) signal, but that isn't
 * a standard POSIX signal and isn't available on our version of Linux.
 * You can list all signals by running kill -l from the command line.
 */
void infoHandler(int sig)
{
	if (sig == SIGTSTP)
	{
		cout << "Received SIGTSTP" << endl;
		// set shared flag to indicate the user wishes to receive information
		infoFlag = true;
	}
}
