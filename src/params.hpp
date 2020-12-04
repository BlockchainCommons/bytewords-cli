//
//  params.hpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <optional>
#include "utils.hpp"

#define MAX_GROUPS 16
#define MAX_RAW_GROUPS (MAX_GROUPS + 1)

#define MAX_ARGS 256

enum Format {
    standard,
    uri,
    minimal,
    bin,
    hex
};

class RawParams {
public:
    std::string input_format;
    std::string output_format;
    bool capitalize = false;

    StringVector args;
};

class Params {
public:
    Params() { }
    ~Params();

    void validate();
    void process();

    RawParams raw;
    
    Format input_format = bin;
    ByteVector input;

    ByteVector data;

    Format output_format = standard;
    ByteVector output;

    bool capitalize = false;

    struct argp_state* state = nullptr;

    static Params* parse( int argc, char *argv[] );

private:
    void process_input();
    void process_output();
    ByteVector encode(Bytewords::Style style, const ByteVector &data);
};
