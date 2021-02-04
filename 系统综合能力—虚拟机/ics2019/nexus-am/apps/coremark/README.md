# Coremark

'''
File: CoreMark

Topic: Welcome
Copyright � 2009 EEMBC All rights reserved. 
CoreMark is a trademark of EEMBC and EEMBC is a registered trademark of the Embedded Microprocessor Benchmark Consortium.

CoreMark�s primary goals are simplicity and providing a method for testing only a processor�s core features. 

For more information about EEMBC's comprehensive embedded benchmark suites, please see www.eembc.org.

Topic: Building and running
	Download the release files from the www.coremark.org.
	You can verify the download using the coremark_<version>.md5 file
	> md5sum -c coremark_<version>.md5
	
	Unpack the distribution (tar -vzxf coremark_<version>.tgz && tar -vzxf coremark_<version>_docs.tgz) 
	then change to the coremark_<version> folder.
	
	To build and run the benchmark, type 
	> make
	Full results are available in the files run1.log and run2.log.
	CoreMark result can be found in run1.log.
	
	For self hosted Linux or Cygwin platforms, a simple make should work.
	
	Cross Compile:
	For cross compile platforms please adjust <core_portme.mak>, <core_portme.h> (and possibly <core_portme.c>) 
	according to the specific platform used.
	When porting to a new platform, it is recommended to copy one of the default port folders 
	(e.g. mkdir <platform> && cp linux/* <platform>), adjust the porting files, and run 
	> make PORT_DIR=<platform>
	
	Systems without make:
	The following files need to be compiled:
	- <core_list_join.c> 
	- <core_main.c> 
	- <core_matrix.c> 
	- <core_state.c>	
	- <core_util.c>	
	- <PORT_DIR>/<core_portme.c>
	
	For example
	> gcc -O2 -o coremark.exe core_list_join.c core_main.c core_matrix.c core_state.c core_util.c simple/core_portme.c -DPERFORMANCE_RUN=1 -DITERATIONS=1000 
	> ./coremark.exe > run1.log
	The above will compile the benchmark for a performance run and 1000 iterations. Output is redirected to run1.log.
	
	Make targets:
	run - Default target, creates run1.log and run2.log.
	run1.log - Run the benchmark with performance parameters, and output to run1.log
	run2.log - Run the benchmark with validation parameters, and output to run2.log
	run3.log - Run the benchmark with profile generation parameters, and output to run3.log
	compile - compile the benchmark executable 
	link - link the benchmark executable
	check - test MD5 of sources that may not be modified
	clean - clean temporary files
	
	ITERATIONS: 
	By default, the benchmark will run between 10-100 seconds.
	To override, use ITERATIONS=N
	> make ITERATIONS=10 
	Will run the benchmark for 10 iterations. 
	It is recommended to set a specific number of iterations in certain situations e.g.:
	- Running with a simulator
	- Measuring power/energy
	- Timing cannot be restarted
	
	Minimum required run time: 
	Results are only valid for reporting if the benchmark ran for at least 10 secs!
	
	XCFLAGS:
	To add compiler flags from the command line, use XCFLAGS e.g.
	> make XCFLAGS="-g -DMULTITHREAD=4 -DUSE_FORK=1"
	
	o CORE_DEBUG
	
	Define to compile for a debug run if you get incorrect CRC.
	> make XCFLAGS="-DCORE_DEBUG=1"
	
	o Parallel Execution
	
	Use XCFLAGS=-DMULTITHREAD=N where N is number of threads to run in parallel.
	Several implementations are available to execute in multiple contexts,
	or you can implement your own in <core_portme.c>.
	> make XCFLAGS="-DMULTITHREAD=4 -DUSE_PTHREAD" 
	Above will compile the benchmark for execution on 4 cores, using POSIX Threads API.
	
	REBUILD:
	To force rebuild, add the flag REBUILD to the command line
	> make REBUILD=1
	
	Check core_portme.mak for more important options.

	Run parameters for the benchmark executable:
	Coremark executable takes several parameters as follows (if main accepts arguments).
	1st - A seed value used for initialization of data.
	2nd - A seed value used for initialization of data.
	3rd - A seed value used for initialization of data.
	4th - Number of iterations (0 for auto : default value)
	5th - Reserved for internal use. 
	6th - Reserved for internal use. 
	7th - For malloc users only, ovreride the size of the input data buffer.
	
	The run target from make will run coremark with 2 different data initialization seeds.

	Alternative parameters: 
	If not using malloc or command line arguments are not supported, the buffer size
	for the algorithms must be defined via the compiler define TOTAL_DATA_SIZE.
	TOTAL_DATA_SIZE must be set to 2000 bytes (default) for standard runs.
	The default for such a target when testing different configurations could be ...
	> make XCFLAGS="-DTOTAL_DATA_SIZE=6000 -DMAIN_HAS_NOARGC=1"
	
Topic: Documentation
	When you unpack the documentation (tar -vzxf coremark_<version>_docs.tgz) a docs folder will be created.
	Check the file docs/html/index.html and the website http://www.coremark.org for more info.
	
Topic: Submitting results
	CoreMark results can be submitted on the web.
	
	Open a web browser and go to http://www.coremark.org/benchmark/index.php?pg=benchmark
	Select the link to add a new score and follow the instructions.
	
Topic: Run rules
	What is and is not allowed.
	
	Required:
	1 - The benchmark needs to run for at least 10 seconds.
	2 - All validation must succeed for seeds 0,0,0x66 and 0x3415,0x3415,0x66, 
		buffer size of 2000 bytes total.
		o If not using command line arguments to main:
		> make XCFLAGS="-DPERFORMANCE_RUN=1" REBUILD=1 run1.log
		> make XCFLAGS="-DVALIDATION_RUN=1" REBUILD=1 run2.log
	3 - If using profile guided optimization, profile must be generated using seeds of 8,8,8,
		and buffer size of 1200 bytes total.
		> make XCFLAGS="-DTOTAL_DATA_SIZE=1200 -DPROFILE_RUN=1" REBUILD=1 run3.log
	4 - All source files must be compiled with the same flags.
	5 - All data type sizes must match size in bits such that:
		o ee_u8 is an 8 bits datatype.
		o ee_s16 is an 16 bits datatype.
		o ee_u16 is an 16 bits datatype.
		o ee_s32 is an 32 bits datatype.
		o ee_u32 is an 32 bits datatype.
	
	Allowed:
	- Changing number of iterations
	- Changing toolchain and build/load/run options
	- Changing method of acquiring a data memory block
	- Changing the method of acquiring seed values
	- Changing implementation in core_portme.c
	- Changing configuration values in core_portme.h
	- Changing core_portme.mak
	
	Not allowed:
	- Changing of source file other then core_portme* (use make check to validate)

Topic: Reporting rules
	How to report results on a data sheet?

	CoreMark 1.0 : N / C [/ P] [/ M]
	
	N - Number of iterations per second with seeds 0,0,0x66,size=2000)
	C - Compiler version and flags
	P - Parameters such as data and code allocation specifics
		- This parameter *may* be omitted if all data was allocated on the heap in RAM.
		- This parameter *may not* be omitted when reporting CoreMark/MHz
	M - Type of parallel execution (if used) and number of contexts
		This parameter may be omitted if parallel execution was not used.

	e.g. 
	> CoreMark 1.0 : 128 / GCC 4.1.2 -O2 -fprofile-use / Heap in TCRAM / FORK:2 
	or
	> CoreMark 1.0 : 1400 / GCC 3.4 -O4 
	
	If reporting scaling results, the results must be reported as follows:
	
	CoreMark/MHz 1.0 : N / C / P [/ M]
	
	P - When reporting scaling results, memory parameter must also indicate memory frequency:core frequency ratio.
		- If the core has cache and cache frequency to core frequency ratio is configurable, that must also be included.
	
	e.g.
	> CoreMark/MHz 1.0 : 1.47 / GCC 4.1.2 -O2 / DDR3(Heap) 30:1 Memory 1:1 Cache

	
Topic: Log File Format
	The log files have the following format
(start example)
2K performance run parameters for coremark.	(Run type)
CoreMark Size    	: 666					(Buffer size)
Total ticks			: 25875					(platform dependent value)
Total time (secs) 	: 25.875000				(actual time in seconds)
Iterations/Sec 		: 3864.734300			(Performance value to report)
Iterations			: 100000				(number of iterations used)
Compiler version	: GCC3.4.4				(Compiler and version)	
Compiler flags		: -O2					(Compiler and linker flags)
Memory location		: Code in flash, data in on chip RAM
seedcrc				: 0xe9f5				(identifier for the input seeds)
[0]crclist			: 0xe714				(validation for list part)
[0]crcmatrix		: 0x1fd7				(validation for matrix part)
[0]crcstate			: 0x8e3a				(validation for state part)
[0]crcfinal			: 0x33ff				(iteration dependent output)
Correct operation validated. See readme.txt for run and reporting rules.  (*Only when run is successful*)
CoreMark 1.0 : 6508.490622 / GCC3.4.4 -O2 / Heap 						  (*Only on a successful performance run*)		
(end example)

Topic: Legal
See LICENSE.txt or the word document file under docs/LICENSE.doc.
For more information on your legal rights to use this benchmark, please see
http://www.coremark.org/download/register.php?pg=register	

Topic: Credits
Many thanks to all of the individuals who helped with the development or testing of CoreMark including (Sorted by company name)
o Alan Anderson, ADI
o Adhikary Rajiv, ADI
o Elena Stohr, ARM
o Ian Rickards, ARM
o Andrew Pickard, ARM
o Trent Parker, CAVIUM
o Shay Gal-On, EEMBC
o Markus Levy, EEMBC
o Ron Olson, IBM
o Eyal Barzilay, MIPS
o Jens Eltze, NEC
o Hirohiko Ono, NEC
o Ulrich Drees, NEC
o Frank Roscheda, NEC
o Rob Cosaro, NXP
o Shumpei Kawasaki, RENESAS
'''
