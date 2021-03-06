# r5embed

**UPDATE:** 2020-04-10	Markku-Juhani O. Saarinen <mjos@pqshield.com>

Switches to use NIST SP 800-185 TupleHash and TupleHashXOF for better
domain separation.


**UPDATE:** 2020-01-27	Markku-Juhani O. Saarinen <mjos@pqshield.com>

This release updates the parameters, removes some the "public key encryption" 
wrappers (this is KEM only) and alternative symmetric algorithms, and makes 
CCA variants directly available as KEMs. 

2019-03-04  Markku-Juhani O. Saarinen <mjos@pqshield.com>

A self-contained version of Round5 post-quantum algorithms for embedded 
platforms. This heavily modified fork is **NOT OFFICIAL** -- but is 
testvector-compatible with the NIST submission. 
Round5 (in a slightly different form) is a currently a 2nd round 
[NIST PQC](https://csrc.nist.gov/Projects/Post-Quantum-Cryptography)
standardization candidate. 

For a summary of performance and code size of all supported variants on 
Cortex M4, see the [benchmarks](./benchmarks.md) page. The raw
benchmark data is at [stm32f4/bench.txt](stm32f4/bench.txt).
A very brief report [rep.pdf](rep/rep.pdf) is also available, which 
additionally offers RISC-V hardware-software numbers (running essentially 
the same code, but with hardware drivers for SHA3 and ring arithmetic).


## Supported variants

Otherwise the variants supported are the same as in the "submission":

| **Sec** | **NIST 1** | **NIST 3**	| **NIST 5** | **Type** | **FEC** |
| --- | -------------- | -------------- | -------------- | ---- | ----|
| CPA | `R5ND_1CPA_5d` | `R5ND_3CPA_5d` | `R5ND_5CPA_5d` | Ring | 5   |
| CCA | `R5ND_1CCA_5d` | `R5ND_3CCA_5d` | `R5ND_5CCA_5d` | Ring | 5   |
| CPA | `R5ND_1CPA_0d` | `R5ND_3CPA_0d` | `R5ND_5CPA_0d` | Ring | No  |
| CCA |	`R5ND_1CCA_0d` | `R5ND_3CCA_0d` | `R5ND_5CCA_0d` | Ring | No  |
| CPA | `R5N1_1CPA_0d` | `R5N1_3CPA_0d`	| `R5N1_5CPA_0d` | Gen  | No  |
| CCA |	`R5N1_1CCA_0d` | `R5N1_3CCA_0d` | `R5N1_5CCA_0d` | Gen  | No  |

* **Sec:** CPA or CCA Security. The NIST 1/3/5 security classes indicate 
equivalent of 128/192/256 - bit classical security (quantum security is 
required to be at least half of that).
* **Type:** whe ring-structured or general lattice. 
* **FEC:** Forward error correction. If used the number indicates how
many bits are guaranteed to be corrected.

Two special cases are supported: `R5ND_0CPA_2iot` and `R5ND_1CPA_4longkey`
which operate in the ring setting and have 2/4 - bit error correction.

This version does *not* support `R5N1_3CCA_0smallCT` which has very large 
(165kB) public keys and requires some special implementation techniques.


### Constant Time Option

**EXPERIMENTAL** 2019-09-23 mjos

I've added a "truly constant time" option to this implementation; this is 
enabled with the `ROUND5_CT` compile-time flag and currently applies only for the 
ring variant. 

### Compiling "natively"

These instructions were created and tested on an Ubuntu 18.04 LTS system.

The script `./test/testkat.sh` will compile all targets on the local system
and verify the (sha256 hashes of) KAT outputs against known good ones 
contained in file `test/good.kat`. The script launches all kat generation
threads at once (fast testing if you have a lot of cores in your system).

For performance testing on your native system, you can use the 
`test/speed.sh` script. It also computes the simple "tv" test vector 
checksums that our embedded test programs display.

### Emulation: ARM, MIPS, POWERPC, etc

QEMU on Linux allows transparent execution of foreign binaries of many
targets, including 32 and 64 bit MIPS, POWERPC, SPARC, and ARM. This works by
the kernel's `binfmt_misc` module recognising the executable architecture
from the binary elf headers and lauching a QEMU interpreter to execute it. 
The interpreter translates all of the system calls made by the application 
to host machine system calls; the emulated binary can therefore access files 
and services on the host machine transparently. The executables must be
statically linked.

You need to install at least `binfmt-support` `qemu-user-static` packages
to enable the feature. You may use `update-binfmts --display` to display all 
of the available interpreters.

You can comment relevant cross-compiler lines in `./test/testkat.sh` 
to check the portability of the code. The cross compilers must be separately 
installed, but many are available as standard Ubuntu/Debian packages; 
`apt install gcc-arm-linux-gnueabihf` suffices for the 32-bit emulated ARMv7 
target, for example.

We have used this feature to verify that `r5embed` works correctly on 
big-endian systems (MIPS). It is also noteworthy that since ARMv7-a 
instruction set is basically a superset of the ARMv7-m instruction set used in 
(Cortex M3/M4) embedded devices, we are able to directly compile and test 
our ARMv7 optimizations by using the `arm-linux-gnueabihf-gcc` cross compiler
(`apt install gcc-multilib-arm-linux-gnueabihf`) and compiling with flags 
`-march=armv7-a -DARMV7_ASM`.

However, this type of emulation is not cycle accurate and therefore not
directly useful for performance testing.


### Cortex-M4: Compiling and running Round5 on the STM32F407 Discovery board

We use a very similar, but somewhat simpler set-up than the 
[PQM4](https://github.com/mupq/pqm4) project. The system requirements are
basically the same (with the exception that we do not use or require Python). 
If you don't care about public key encryption (just KEM), 
you should be able to compile `r5embed` with `PQM4` fairly easily; just 
remember to define the `ARMV7_ASM` macro to enable ARMv7-m assembler
optimizations (up to 50% faster).


#### Hardware requirements

We are providing build instructions for the
[STM32F407 Discovery](https://www.st.com/en/evaluation-tools/stm32f4discovery.html)
evaluation board, which we bought for 
[£20](https://smile.amazon.co.uk/dp/B072K267DK/ref=cm_sw_em_r_mt_dp_U_B4rICbWT49B46).
You'll also need a USB to TTL Serial cable. You can get two of those for
[£5](https://smile.amazon.co.uk/gp/product/B01N4X3BJB/ref=ppx_yo_dt_b_asin_title_o02_s00).

For this interface the wires are defined as: Red +5V, Black GND, Green TXD, 
White RXD. Connect the green TXD to PA3 and white RXD to PA2 on the board.
The black GND and red +5V wires can be left unconnected.
Like this: ![stdisco.jpg](https://user-images.githubusercontent.com/6192929/78308686-0545b580-7541-11ea-8eba-72ec956ffa06.jpg)

In our system the ST-LINK programming interface appears as `/dev/ttyACM0` while
the USB serial interface is `/dev/USB0`. You will have to manually change
the scripts if you have other names for these hardware interfaces.

#### Software prerequisites

You'll need at least `git` to fetch the source code, `make` and some other 
standard software development tools (`build-essential`), and the 
`arm-none-eabi` cross compiler toolchain to compile to code.

For the cross compiler you can either install the standard Ubuntu/Debian
`gcc-arm-none-eabi` package, or use the distribution provided by
[ARM](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads).
We use the ARM toolchain version ourselves.

To actually program the ST Discovery board we are using 
[stlink](https://github.com/texane/stlink), which we compiled from source.


#### Building the OpenCM3 firmware

You must first initialize and build the OpenCM3 firmware, which is 
included as a submodule in this distribution. This is something that
needs to be done only once. From the beginning:
```
$ git clone git@gitlab.com:round5/r5embed.git
$ cd r5embed
$ git submodule init
$ git submodule update
$ cd libopencm3
$ make
[..]
$ cd ..
```
If you don't have the submodule set up you can just clone
`https://github.com/libopencm3/libopencm3.git` under the 
the `r5embed` directory and build it.


#### Compiling and executing Round5 variants

Now we can preceed to build the test harness and `r5embed` algorithms
themselves. For example:

```
$ cd stm32f4
$ make ROUND5=R5ND_3CPA_5d run
[.. after compiling, flashing, few seconds for measurement:]
..				#R5ND_3CPA_5d
R5ND_3CPA_5d	kilo cycles	KG 	#784
R5ND_3CPA_5d	kilo cycles	Enc	#1081
R5ND_3CPA_5d	kilo cycles	Dec	#396
R5ND_3CPA_5d	kilo cycles	KEX	#2262
R5ND_3CPA_5d	stack bytes	KG	#5550
..
```
The `Makefile` expects ROUND5 variable to be defined as one of the variants
given above. The `run` argument will also directly flash the implementation
and dump the output.

If you want to just run it again, you can invoke the `dump.sh` shell script
and press the black reset button on the board. This will restart the program
on the board and its output will be displayed on console.

Our STTY setup defines ascii 4 (ctrl-D) as EOF -- this causes the dump to 
exit after output from the board is finished. Otherwise the serial protocol 
is standard 115200N81 (115200 baud, 1 stop bit, no parity).

The script `run_bench.sh` benchmarks all variants and writes it to 
`run_bench.log`. It uses `codesize.sh`, a *ridiculously* hacky script that 
computes the relevant code size by summing up the sizes of all functions 
with `r5_`, `crypto_` or `xe` in their name.

