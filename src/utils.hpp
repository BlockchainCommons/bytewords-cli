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

ByteVector data_to_base(const ByteVector& buf, size_t base);

std::string data_to_alphabet(const ByteVector &in,
    size_t base,
    std::string (to_alphabet)(size_t));

std::string data_to_ints(const ByteVector &in,
    size_t low, size_t high, const std::string &separator);

ByteVector digits_to_data(const std::string& in, size_t low, size_t high);

std::string join(const StringVector &strings, const std::string &separator);
StringVector split(const std::string& s, const char& separator);

std::string to_lower(const std::string& s);
std::string to_upper(const std::string& s);
bool has_prefix(const std::string& s, const std::string& prefix);

template<typename T>
std::vector<T> take(const std::vector<T> &buf, size_t count) {
    auto first = buf.begin();
    auto c = std::min(buf.size(), count);
    auto last = first + c;
    return std::vector(first, last);
}

std::string take(const std::string &s, size_t count);
std::string drop(const std::string &s, size_t count);

template<typename T>
void append(std::vector<T>& target, const std::vector<T>& source) {
    target.insert(target.end(), source.begin(), source.end());
}

StringVector partition(const std::string& string, size_t size);

int days_since_epoch();

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
