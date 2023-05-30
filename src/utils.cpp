//
//  utils.cpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include "utils.hpp"

#include <math.h>
#include <stdexcept>
#include <sstream>
#include <chrono>
#include <array>
#include <bc-bytewords/bc-bytewords.h>

using namespace std;

string data_to_hex(const ByteVector& in) {
    auto hex = "0123456789abcdef";
    string result;
    for(auto c: in) {
        result.append(1, hex[(c >> 4) & 0xF]);
        result.append(1, hex[c & 0xF]);
    }
    return result;
}

uint8_t hex_digit_to_bin(char hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10;
    } else if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 10;
    } else {
        throw runtime_error("Invalid hex digit");
    }
}

ByteVector hex_to_data(const string& hex) {
    ByteVector result;

    auto len = hex.length();
    if(len % 2 != 0) {
        throw runtime_error("Hex string must have even number of characters.");
    }
    auto count = len / 2;
    result.reserve(count);
    for(auto i = 0; i < count; i++) {
        auto b1 = hex_digit_to_bin(hex[i * 2]);
        auto b2 = hex_digit_to_bin(hex[i * 2 + 1]);
        result.push_back((b1 << 4) | b2);
    }

    return result;
}

string join(const StringVector &strings, const string &separator) {
    ostringstream result;
    bool first = true;
    for(auto s: strings) {
        if(!first) {
            result << separator;
        }
        result << s;
        first = false;
    }
    return result.str();
}

string to_upper(const string& s) {
    string out;
    transform(s.begin(), s.end(), back_inserter(out), ::toupper);
    return out;
}

string Bytewords::encode(Style style, const ByteVector& bytes) {
    auto a = bytewords_encode(static_cast<bw_style>(style), &bytes[0], bytes.size());
    auto s = string(a);
    free(a);
    return s;
}

ByteVector Bytewords::decode(Style style, const string& string) {
    uint8_t* out_buf;
    size_t out_len;
    auto success = bytewords_decode(static_cast<bw_style>(style), string.c_str(), &out_buf, &out_len);
    if(!success) {
        throw runtime_error("Invalid Bytewords.");
    }
    auto result = ByteVector(out_buf, out_buf + out_len);
    free(out_buf);
    return result;
}

ByteVector string_to_data(const string& s) {
    return ByteVector(s.begin(), s.end());
}

string data_to_string(const ByteVector& d) {
    return string(d.begin(), d.end());
}

ByteVector read_data_from_stdin() {
    // Based on https://stackoverflow.com/a/39758021/2413963
    (void)freopen(nullptr, "rb", stdin);

    if(ferror(stdin))
        throw runtime_error(strerror(errno));

    size_t len;
    array<char, 1024> buf;

    ByteVector result;

    while((len = fread(buf.data(), sizeof(buf[0]), buf.size(), stdin)) > 0)
    {
        if(ferror(stdin) && !feof(stdin))
            throw runtime_error(strerror(errno));

        result.insert(result.end(), buf.data(), buf.data() + len); 
    }

    return result;
}

void write_data_to_stdout(const ByteVector& data) {
    fwrite(data.data(), 1, data.size(), stdout);
}
