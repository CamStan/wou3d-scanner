# README #

WOU 3D Scanner is a repository for the CS 490 Physical Computing course at Western Oregon University during Fall term 2015.  The course is a senior elective in the Computer Science program.  This repository hosts resources for the students (i.e. the developers) and the codebase for the main course project: a custom-built 3D scanner.

### What is the scanner? ###

* Laser triangulation scanner using a line laser
* Digital SLR camera
* Intel Edison controller
* Intel Edison remote controller using Bluetooth
* 2 degrees of freedom (DOF) mechanical rotation

### Status ###
Barely started!  Nothing works yet, but development is ongoing.

### Building ###

This project can be built from the Makefile or via Eclipse
using the Intel Edison version.  Both methods assume you have
installed the Intel Edison cross compiling development environment.

#### make ####
If you are using Windows, please install [Cygwin](https://www.cygwin.com) or [Mingw](http://www.mingw.org) so you have access to GNU Make.  Minimally, install make (Devel) and OpenSSH (net).

Edit the Makefile if you are using a 32 bit OS (default assumes 64 bit).  The top of the Makefile has versions commented out -- just switch the comments.

Now execute

    touch .depend    #only the first time
    make

The Makefile assumes you have installed the development environment at the default location.  Edit the appropriate variable if you installed it at a different location.

The executable can be found in the bin folder; to load it onto the Edison, use sftp or the following (in this version the base unit is named everest)

    scp bin/Scanner root@everest.local:Scanner

#### Eclipse ####
Start up Eclipse and make a new empty Intel Edison C++ project.  After setting it up, import all the files from the src folder here into your Eclipse project, preferably importing by reference rather than copying into your workspace.  Build and deploy as with your usual Edison projects.

### Contributing ###

Students, please see this [Guidelines](guidelines.md)
