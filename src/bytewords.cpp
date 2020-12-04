//
//  bytewords.cpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include <iostream>
#include <stdexcept>

#include "params.hpp"
#include "utils.hpp"

using namespace std;

int main( int argc, char *argv[] ) {
    auto p = Params::parse(argc, argv);

    try {
        p->process();

        if(p->output.empty()) {
            throw runtime_error("An internal error occurred.");
        }

        write_data_to_stdout(p->output);
        if(p->output_format != bin) {
            cout << endl;
        }
    } catch(exception &e) {
        cerr << argv[0] << ": " << e.what() << endl;
        exit(1);
    }

    delete p;
    return 0;
}
