# MATIEC examples

MATIEC is a opensource compiler for programming languages defined in IEC 61131-3. This examples show how to use this compiler to test IEC 61131-3 programs in a softplc program. 

# Prerequisites

## Installing MATIEC

To compile MATIEC you need to download and install [flex](https://github.com/westes/flex) and [bison](https://www.gnu.org/software/bison/). You can download compile and isntall or use your preferred package manager.
	
```
	$ cd ~/
	$ hg clone ssh://hg@bitbucket.org/mjsousa/matiec
	$ cd matiec
	$ autoreconf -i
	$ ./configure
	$ make
```

## Setting some enviromnent variables

To use MATIEC is need define some enviromnent variables used in the makefile of the examples

```
	$ export MATIEC_INCLUDE_PATH=/home/user/matiec/lib
	$ export MATIEC_C_INCLUDE_PATH=/home/user/matiec/lib/C
	$ export PATH=/home/user/matiec:$PATH
```

# Compiling the examples

You can edit the logic using PLCOpenEditor from [Beremiz project](http://www.beremiz.org/). The project format is a XML format for IEC 61131-3.

```
	$ cd ~/
	$ git clone https://github.com/Felipeasg/matiec_examples.git
	$ cd matiec_examples
	$ cd and_logic
	$ make
``` 

This will generate a executable softplc.
