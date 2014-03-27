Phoenix2D
==========

Phoenix2D team base code for RoboCup 2D Simulation League.

Build Instructions 
==================

The source code is divided in:

* Phoenix2D-CPP (Application)
* Phoenix2D-Library (Library)
* Phoenix2D-Tests (Test Application)

To create in Eclipse you will have to create a new project as follows:

+ A c++ Static Library project in which you'll use the Phoenix2D-Library folder
+ A c++ Console Application project in which you'll use the Phoenix2D-CPP folder
+ A c++ Console Application project in which you'll use the Phoenix2D-Tests folder code

###Eclipse CDT###
The Master folder is an eclipse workspace just open it with your eclipse and everything should be setup. Keep in mind that it may not work right off the bat with your system because:

* The libraries in our system are setup differently
* Aliens in the sky

###Codeblocks###
The *.cbp files are configuration files for Codeblocks IDE. The *.workspace file is also for codeblocks. 


##Dependencies##

+ boost_regex (libboost_regex)
+ pthread (libpthread)
+ boost_unit_test (libboost_unit_test_framework)
+ Internally you should link the Console Applications with the Static Library

To prevent any further problems, link the project with the dynamic libraries (*.so). If you link with the static libraries (*.a) you will most likely have to link with libc.a to make libpthread compile without any problems. Otherwise your compiler will have an error on undefined variables. 

Take on account that this project is just the code base for constructing agent for the RoboCup 2D Simulation League and it is focused to be compiled in Unix systems.

##Running the code##

You will also need RoboCup Soccer Server 2D to use this code properly. To do this perform the following:

1.     Go to [The RoboCup Soccer Simulator](http://sourceforge.net/projects/sserver/) website and download rcssserver and rcssmonitor
	* For rcssserver you'll be needing the following dependencies:
		*	build-essential
		*	bison
		*	flex
		*	libboost-all-dev
	* For rcssmonitor you'll be needing the following:
		*	build-essential
		*	libqt4-dev
		*	libboost-all-dev
		*	libaudio-dev
		*	libxt-dev
		*	libxi-dev
		*	libxrender-dev
		*	libfreetype6-dev
		*	libfontconfig1-dev
		*	python-gobject-dev
		*	libpng-dev
2.     `tar -xf  <tar_file>` for rcssserver
3.     cd rcssserver folder
4.	./configure --with-boost-libdir=<boost_libdir>
5.	make
6.	sudo make install
7.	Repeat from 2-6 for rcssmonitor

Afterwards just run the server and keep it running.

Now you can run the Main Application. :D

Once you have the server and the libraries you should be able to use the code without problems on an Unix System.     


##Generating the documentation##

The Library Documentation is contained in the doc folder inside the **Phoenix2D-Library** Project. You should generate the documentation at this level. The Doxyfile generates latex and html documentation. The dependencies you will need to install (besides doxygen) are as follows:

    libc6 (>= 2.14) [amd64]
        Embedded GNU C Library: Shared libraries
        also a virtual package provided by libc6-udeb 
    libc6 (>= 2.4) [i386]
    libstdc++6 (>= 4.1.1)
        GNU Standard C++ Library v3 
    doxygen-latex
        Documentation system for C, C++, Java, Python and other languages 
    doxygen-doc
        Documentation for doxygen 
    doxygen-gui
        GUI configuration tool for doxygen 
    graphviz
        rich set of graph drawing tools 

This will allow you to generate the complete documentation using the following line:

*	`~/<PathPhoenix2D-Library>/doc$ doxygen Phoenix2DLibrary.doxyfile` 

This will generate an both html and latex folders along with the documentation. Just open the index.html or generate the latex documentation pdf using the following:

*	`~/<PathPhoenix2D-Library>/doc/latex$ pdflatex refman.tex`

Keep in mind that you need a working pdflatex installation (texlive or miktex or similar)
