//
//  params.cpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include <memory.h>
#include <argp.h>
#include <assert.h>
#include <iostream>
#include <stdexcept>
#include "params.hpp"
#include "config.h"

using namespace std;

Params::~Params() {
}

static Format parse_format(const string& s) {
    if(s == "standard") {
        return ::standard;
    } else if(s == "uri") {
        return ::uri;
    } else if(s == "minimal") {
        return ::minimal;
    } else if(s == "bin") {
        return ::bin;
    } else if(s == "hex") {
        return ::hex;
    }
    throw runtime_error("Unknown format: " + s);
}

void Params::validate() {
    if(raw.input_format.empty()) {
        input_format = Format::bin;
    } else {
        input_format = parse_format(raw.input_format);
    }

    if(raw.output_format.empty()) {
        output_format = Format::standard;
    } else {
        output_format = parse_format(raw.output_format);
    }

    if(raw.args.empty()) {
        input = read_data_from_stdin();
    } else {
        input = string_to_data(join(raw.args, " "));
    }
}

void Params::process_input() {
    switch (input_format) {
    case ::standard:
        data = Bytewords::decode(Bytewords::Style::standard, data_to_string(input));
        break;
    case ::uri:
        data = Bytewords::decode(Bytewords::Style::uri, data_to_string(input));
        break;
    case ::minimal:
        data = Bytewords::decode(Bytewords::Style::minimal, data_to_string(input));
        break;
    case ::bin:
        data = input;
        break;
    case ::hex:
        data = hex_to_data(data_to_string(input));
        break;
    }
}

void Params::process_output() {
    switch (output_format) {
    case ::standard:
        output = string_to_data(Bytewords::encode(Bytewords::Style::standard, data));
        break;
    case ::uri:
        output = string_to_data(Bytewords::encode(Bytewords::Style::uri, data));
        break;
    case ::minimal:
        output = string_to_data(Bytewords::encode(Bytewords::Style::minimal, data));
        break;
    case ::bin:
        output = data;
        break;
    case ::hex:
        output = string_to_data(data_to_hex(data));
        break;
    }
}

void Params::process() {
    process_input();
    process_output();
}

static int parse_opt(int key, char* arg, struct argp_state* state) {
    try {
        auto p = static_cast<Params*>(state->input);
        p->state = state;
        auto& raw = p->raw;

        switch (key) {
            case ARGP_KEY_INIT: break;
            case 'i': raw.input_format = arg; break;
            case 'o': raw.output_format = arg; break;
            case ARGP_KEY_ARG: raw.args.push_back(arg); break;
            case ARGP_KEY_END: {
                p->validate();
            }
            break;
        }
    } catch(exception &e) {
        argp_error(state, "%s", e.what());
    }
    return 0;
}

struct argp_option options[] = {
    {"input-format", 'i', "standard|uri|minimal|hex|bin", 0, "Input format. (default `bin`)."},
    {"output-format", 'o', "standard|uri|minimal|hex|bin", 0, "Output format. (default `standard`)."},

    { 0 }
};

auto argp_program_version = PACKAGE_VERSION;
const char* argp_program_bug_address = "ChristopherA@BlockchainCommons.com. © 2020 Blockchain Commons";

auto doc = "Converts data to and from Bytewords encoding.";
struct argp argp = { options, parse_opt, "INPUT", doc };

Params* Params::parse( int argc, char *argv[] ) {
    auto p = new Params();
    argp_parse( &argp, argc, argv, 0, 0, p );
    return p;
}

// string Params::get_one_argument() {
//     if(input.size() != 1) {
//         throw runtime_error("Only one argument accepted.");
//     }
//     return input[0];
// }

// string Params::get_combined_arguments() {
//     return join(input, " ");
// }

// StringVector Params::get_multiple_arguments() {
//     return input;
// }

// void Params::read_args_from_stdin() {
//     string line;
//     while(getline(cin, line)) {
//         raw.args.push_back(line);
//     }
// }
