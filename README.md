<p style="font-size: 3em;">🅱🆈🆃🅴🆆🅾🆁🅳🆂</p>

# Blockchain Commons bytewords-cli
### _by [Wolf McNally](https://www.github.com/wolfmcnally) and [Christopher Allen](https://www.github.com/ChristopherA)_

**Version 0.2.1**<br/>**December 1, 2023**

* <img src="https://github.com/BlockchainCommons/crypto-commons/blob/master/images/logos/crypto-commons-super-simple.png" width=16 valign="bottom">&nbsp;&nbsp; ***part of the [crypto commons](https://github.com/BlockchainCommons/crypto-commons/blob/master/README.md) technology family***
* <img src="https://github.com/BlockchainCommons/Gordian/blob/master/Images/logos/gordian-icon.png" width=16 valign="bottom"> ***part of the [gordian](https://github.com/BlockchainCommons/gordian/blob/master/README.md) technology family***

![Build](https://github.com/BlockchainCommons/bytewords-cli/workflows/ci/badge.svg)

## Introduction

This repo contains `bytewords`, a command line tool used to explore, test, and exercise Blockchain Commons' C reference implementation of the **Bytewords** encoding.

**NOTE:** In this document the Bytewords encoding method is referred to with a capitalized first letter, and the CLI tool `bytewords` is referred to in `code voice`.

Bytewords is a method for encoding arbitary binary data in plain text as a sequence of common four-letter English words. Bytewords defines exactly 256 such words, one for each possible combination of bits in a byte (octet).

Bytewords is useful, for example, when recording a cryptographic seed as a series of words engraved on permanent media such as a tungsten plate; a procedure common in the cryptocurrency community. Bytewords can be easily used in self-contained URIs, or shortened further to just the first and last letter of each word, which is comparable to hexadecimal but less prone to human transcription error. For error detection Bytewords also adds a CRC32 checksum.

The Bytewords encoding is detailed [here](https://github.com/BlockchainCommons/Research/blob/master/papers/bcr-2020-012-bytewords.md).

Bytewords is used to encode CBOR-structured binary as part of the specification for Uniform Resources (URs) defined [here](https://github.com/BlockchainCommons/Research/blob/master/papers/bcr-2020-005-ur.md).

## Status - First Testing Release

This release is feature complete and ready for testing.

## Dependencies

`bytewords` requires the following Blockchain Commons libraries:

* [`bc-crypto-base`](https://github.com/blockchaincommons/bc-crypto-base)
* [`bc-bytewords`](https://github.com/blockchaincommons/bc-bytewords)

It also requires the following additional library:

* [`GNU argp`](https://www.gnu.org/software/libc/manual/html_node/Argp.html)

### Tool Dependencies

To build `seedtool` you'll need to use the following tools:

- autotools - Gnu Build System from Free Software Foundation ([intro](https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html)).

## Recommended Installation instructions

The dependencies will be automatically installed as submodules when you run the build script. This is the recommended way to install.

### Build on MacOS

```bash
$ brew install autoconf automake libtool shunit2
```

You must then download or clone this repo. Afterward, cd into the repo directory and:

```bash
$ ./build.sh
$ sudo make install
```

### Build on Linux

Make sure you have `llvm`/`clang`, `libc++` and `libc++abi` installed, all with
a minimum recommended version 10.

#### Build on Ubuntu and Debian

```bash
$ sudo apt install build-essential

$ wget https://apt.llvm.org/llvm.sh
$ chmod +x llvm.sh
$ sudo apt install lsb-release wget software-properties-common
$ sudo ./llvm.sh 10  # version 10

$ sudo apt-get install libc++-10-dev libc++abi-10-dev
```

```bash
$ sudo apt-get install git
$ git clone https://github.com/BlockchainCommons/bytewords-cli.git
$ cd seedtool-cli/
$ export CC="clang-10" && export CXX="clang++-10" && ./build.sh
$ sudo make install
```

## Incremental Build Instructions

If you wish to make changes to the source code and rebuild:

```bash
# Make source changes
$ source set_build_paths.sh # sets shell variables used by make
$ make clean # If you want a clean build
$ make
```

## Usage

### Input and Output

`bytewords` can take its input from either the command line arguments or from STDIN.

Input on the command line. Note that the string provided explicitly encodes a newline character at the end.

```
$ bytewords $'Hello\n'
fund inch jazz jazz jowl back each mint epic calm
```

Input on the terminal via STDIN (`^D` represents Control-D (EOF)).

```
$ bytewords
Hello
^D
fund inch jazz jazz jowl back each mint epic calm
```

`bytewords` writes its output to STDOUT.

Input from a file and output back to another file:

```
$ cat >input.txt
Hello
^D

$ bytewords <input.txt >output.txt
$ cat output.txt
fund inch jazz jazz jowl back each mint epic calm
```

### Formats

The five possible input and output formats are:

|    |    |
|:---|:---|
| `standard` | Bytewords standard encoding
| `uri` | Bytewords URI-compatible encoding
| `minimal` | Bytewords minimal encoding
| `bin` | Binary
| `hex` | Hexadecimal

By default `bytewords` takes binary data as input and encodes it in the "standard" Bytewords format. This is as if you typed:

```
bytewords -i bin -o standard ...
```

### Case

Input of textual formats to `bytewords` is case-insensitive. Output of textual formats is lower case by default, but can be forced to upper case with the `--capitalize` option. No case conversion is ever performed on binary input or output data.

```
$ bytewords --capitalize $'Hello\n'
FUND INCH JAZZ JAZZ JOWL BACK EACH MINT EPIC CALM
```

`--capitalize` is ignored for binary output.

```
$ bytewords --capitalize -i standard -o bin FUND INCH JAZZ JAZZ JOWL BACK EACH MINT EPIC CALM
Hello
```

## Examples

Convert a string to the five output formats.

```
$ bytewords $'Hello\n'
fund inch jazz jazz jowl back each mint epic calm

$ bytewords -o uri $'Hello\n'
fund-inch-jazz-jazz-jowl-back-each-mint-epic-calm

$ bytewords -o minimal $'Hello\n'
fdihjzjzjlbkehmteccm

$ bytewords -o bin $'Hello\n'
Hello

$ bytewords -o hex $'Hello\n'
48656c6c6f0a
```

Convert the minimal encoding to the other output formats:

```
$ bytewords -i minimal fdihjzjzjlbkehmteccm
fund inch jazz jazz jowl back each mint epic calm

$ bytewords -i minimal -o uri fdihjzjzjlbkehmteccm
fund-inch-jazz-jazz-jowl-back-each-mint-epic-calm

$ bytewords -i minimal -o minimal fdihjzjzjlbkehmteccm
fdihjzjzjlbkehmteccm

$ bytewords -i minimal -o bin fdihjzjzjlbkehmteccm
Hello

$ bytewords -i minimal -o hex fdihjzjzjlbkehmteccm
48656c6c6f0a
```

Strings that are not well-formed Bytewords or where the CRC32 checksum does not match are rejected.

```
$ bytewords -i minimal -o hex fdihjzjzjlbkehmtecec
bytewords: Invalid Bytewords.
```

## Notes for Maintainers

Before accepting a PR that can affect build or unit tests, make sure the following sequence of commands succeeds:

```bash
$ ./build.sh
$ make lint
$ make distcheck
$ make distclean
```

`make lint` uses [Cppcheck](https://en.wikipedia.org/wiki/Cppcheck) to perform static analysis on the code. All PRs should pass with no warnings.

## Related Projects

* [bc-ur](https://github.com/BlockchainCommons/bc-ur) is our C++ Uniform Resource (UR) library. It contains a its own C++ implementation of Bytewords.

## Origin, Authors, Copyright & Licenses

Unless otherwise noted (either in this [/README.md](./README.md) or in the file's header comments) the contents of this repository are Copyright © 2020 by Blockchain Commons, LLC, and are [licensed](./LICENSE) under the [spdx:BSD-2-Clause Plus Patent License](https://spdx.org/licenses/BSD-2-Clause-Patent.html).

In most cases, the authors, copyright, and license for each file reside in header comments in the source code. When it does not we have attempted to attribute it accurately in the table below.

This table below also establishes provenance (repository of origin, permalink, and commit id) for files included from repositories that are outside of this repository. Contributors to these files are listed in the commit history for each repository, first with changes found in the commit history of this repo, then in changes in the commit history of their repo of their origin.

| File      | From                                                         | Commit                                                       | Authors & Copyright (c)                                | License                                                     |
| --------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------ | ----------------------------------------------------------- |
| This section blank. |

### Tool Dependencies

To build `seedtool` you'll need to use the following tools:

- autotools - Gnu Build System from Free Software Foundation ([intro](https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html)).
- shunit2 - Unit testing for shell scripts

## Financial Support

Seedtool is a project of [Blockchain Commons](https://www.blockchaincommons.com/). We are proudly a "not-for-profit" social benefit corporation committed to open source & open development. Our work is funded entirely by donations and collaborative partnerships with people like you. Every contribution will be spent on building open tools, technologies, and techniques that sustain and advance blockchain and internet security infrastructure and promote an open web.

To financially support further development of Seedtool and other projects, please consider becoming a Patron of Blockchain Commons through ongoing monthly patronage as a [GitHub Sponsor](https://github.com/sponsors/BlockchainCommons). You can also support Blockchain Commons with bitcoins at our [BTCPay Server](https://btcpay.blockchaincommons.com/).

## Contributing

We encourage public contributions through issues and pull-requests! Please review [CONTRIBUTING.md](./CONTRIBUTING.md) for details on our development process. All contributions to this repository require a GPG signed [Contributor License Agreement](./CLA.md).

### Discussions

The best place to talk about Blockchain Commons and its projects is in our GitHub Discussions areas.

[**Gordian Developer Community**](https://github.com/BlockchainCommons/Gordian-Developer-Community/discussions). For standards and open-source developers who want to talk about interoperable wallet specifications, please use the Discussions area of the [Gordian Developer Community repo](https://github.com/BlockchainCommons/Gordian-Developer-Community/discussions). This is where you talk about Gordian specifications such as [Gordian Envelope](https://github.com/BlockchainCommons/Gordian/tree/master/Envelope#articles), [bc-shamir](https://github.com/BlockchainCommons/bc-shamir), [Sharded Secret Key Reconstruction](https://github.com/BlockchainCommons/bc-sskr), and [bc-ur](https://github.com/BlockchainCommons/bc-ur) as well as the larger [Gordian Architecture](https://github.com/BlockchainCommons/Gordian/blob/master/Docs/Overview-Architecture.md), its [Principles](https://github.com/BlockchainCommons/Gordian#gordian-principles) of independence, privacy, resilience, and openness, and its macro-architectural ideas such as functional partition (including airgapping, the original name of this community).

[**Gordian User Community**](https://github.com/BlockchainCommons/Gordian/discussions). For users of the Gordian reference apps, including [Gordian Coordinator](https://github.com/BlockchainCommons/iOS-GordianCoordinator), [Gordian Seed Tool](https://github.com/BlockchainCommons/GordianSeedTool-iOS), [Gordian Server](https://github.com/BlockchainCommons/GordianServer-macOS), [Gordian Wallet](https://github.com/BlockchainCommons/GordianWallet-iOS), and [SpotBit](https://github.com/BlockchainCommons/spotbit) as well as our whole series of [CLI apps](https://github.com/BlockchainCommons/Gordian/blob/master/Docs/Overview-Apps.md#cli-apps). This is a place to talk about bug reports and feature requests as well as to explore how our reference apps embody the [Gordian Principles](https://github.com/BlockchainCommons/Gordian#gordian-principles).

[**Blockchain Commons Discussions**](https://github.com/BlockchainCommons/Community/discussions). For developers, interns, and patrons of Blockchain Commons, please use the discussions area of the [Community repo](https://github.com/BlockchainCommons/Community) to talk about general Blockchain Commons issues, the intern program, or topics other than those covered by the [Gordian Developer Community](https://github.com/BlockchainCommons/Gordian-Developer-Community/discussions) or the
[Gordian User Community](https://github.com/BlockchainCommons/Gordian/discussions).

### Other Questions & Problems

As an open-source, open-development community, Blockchain Commons does not have the resources to provide direct support of our projects. Please consider the discussions area as a locale where you might get answers to questions. Alternatively, please use this repository's [issues](./issues) feature. Unfortunately, we can not make any promises on response time.

If your company requires support to use our projects, please feel free to contact us directly about options. We may be able to offer you a contract for support from one of our contributors, or we might be able to point you to another entity who can offer the contractual support that you need.

### Credits

The following people directly contributed to this repository. You can add your name here by getting involved — the first step is to learn how to contribute from our [CONTRIBUTING.md](./CONTRIBUTING.md) documentation.

| Name              | Role                | Github                                            | Email                                 | GPG Fingerprint                                    |
| ----------------- | ------------------- | ------------------------------------------------- | ------------------------------------- | -------------------------------------------------- |
| Christopher Allen | Principal Architect | [@ChristopherA](https://github.com/ChristopherA) | \<ChristopherA@LifeWithAlacrity.com\> | FDFE 14A5 4ECB 30FC 5D22  74EF F8D3 6C91 3574 05ED |
| Wolf McNally      | Project Lead        | [@WolfMcNally](https://github.com/wolfmcnally)    | \<Wolf@WolfMcNally.com\>              | 9436 52EE 3844 1760 C3DC  3536 4B6C 2FCF 8947 80AE |

## Responsible Disclosure

We want to keep all our software safe for everyone. If you have discovered a security vulnerability, we appreciate your help in disclosing it to us in a responsible manner. We are unfortunately not able to offer bug bounties at this time.

We do ask that you offer us good faith and use best efforts not to leak information or harm any user, their data, or our developer community. Please give us a reasonable amount of time to fix the issue before you publish it. Do not defraud our users or us in the process of discovery. We promise not to bring legal action against researchers who point out a problem provided they do their best to follow the these guidelines.

## Reporting a Vulnerability

Please report suspected security vulnerabilities in private via email to ChristopherA@BlockchainCommons.com (do not use this email for support). Please do NOT create publicly viewable issues for suspected security vulnerabilities.

The following keys may be used to communicate sensitive information to developers:

| Name              | Fingerprint                                        |
| ----------------- | -------------------------------------------------- |
| Christopher Allen | FDFE 14A5 4ECB 30FC 5D22  74EF F8D3 6C91 3574 05ED |

You can import a key by running the following command with that individual’s fingerprint: `gpg --recv-keys "<fingerprint>"` Ensure that you put quotes around fingerprints that contain spaces.

## Version History

### 0.2.1, 11/31/2020

* Update dependencies.

### 0.1.0, 11/31/2020

* First testing release.
