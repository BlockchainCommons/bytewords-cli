//
//  utils.hpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <vector>

typedef std::vector<uint8_t> ByteVector;
typedef std::vector<std::string> StringVector;

std::string data_to_hex(const ByteVector& in);
uint8_t hex_digit_to_bin(char hex);

ByteVector hex_to_data(const std::string& hex);

std::string join(const StringVector &strings, const std::string &separator);

std::string to_upper(const std::string& s);

template<typename T>
std::vector<T> take(const std::vector<T> &buf, size_t count) {
    auto first = buf.begin();
    auto c = std::min(buf.size(), count);
    auto last = first + c;
    return std::vector(first, last);
}

template<typename T>
void append(std::vector<T>& target, const std::vector<T>& source) {
    target.insert(target.end(), source.begin(), source.end());
}

template<typename T>
std::vector<T> flatten(const std::vector<std::vector<T>>& source) {
    std::vector<T> result;
    for(auto item: source) {
        append(result, item);
    }
    return result;
}

class Bytewords final {
public:
    enum Style {
        standard,
        uri,
        minimal
    };

    static std::string encode(Style style, const ByteVector& bytes);
    static ByteVector decode(Style style, const std::string& string);
};

ByteVector string_to_data(const std::string& s);
std::string data_to_string(const ByteVector& d);

ByteVector read_data_from_stdin();
void write_data_to_stdout(const ByteVector& data);
