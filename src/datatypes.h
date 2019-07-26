/*
 * Copyright (C) Roland Jax 2017-2019 <roland.jax@liwest.at>
 *
 * This file is part of ebustrace.
 *
 * ebustrace is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ebustrace is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ebustrace. If not, see http://www.gnu.org/licenses/.
 */

#ifndef EBUSTRACE_DATATYPES_H
#define EBUSTRACE_DATATYPES_H

#include <bits/stdint-intn.h>
#include <bits/stdint-uintn.h>
#include <sys/types.h>
#include <cmath>
#include <cstddef>
#include <vector>

// templates for byte / integer conversion
template<typename T>
struct templateType
{
	using type = T;
};

template<typename T>
void byte2int(T &t, const std::vector<std::byte>& bytes)
{
	t = 0;

	for (size_t i = 0; i < bytes.size(); i++)
		t |= std::to_integer<unsigned>(bytes[i]) << (8 * i);
}

template<typename T>
typename templateType<T>::type byte2int(const std::vector<std::byte>& bytes)
{
	T t;
	byte2int(t, bytes);
	return (t);
}

template<typename T>
void int2byte(const T &t, std::vector<std::byte>& bytes)
{
	for (size_t i = 0; i < sizeof(T); i++)
		bytes.push_back(std::byte(t >> (8 * i)));
}

template<typename T>
std::vector<std::byte> int2byte(const T& t)
{
	std::vector<std::byte> bytes;
	int2byte(t, bytes);
	return (bytes);
}


// helper functions
uint convert_base(uint value, const uint& oldBase, const uint& newBase);

double_t round_digits(const double_t& value, const uint8_t& digits);


// BCD
uint8_t byte_2_bcd(const std::vector<std::byte>& bytes);

std::vector<std::byte> bcd_2_byte(const uint8_t& value);


// uint8_t
uint8_t byte_2_uint8(const std::vector<std::byte>& bytes);

std::vector<std::byte> uint8_2_byte(const uint8_t& value);


// int8_t
int8_t byte_2_int8(const std::vector<std::byte>& bytes);

std::vector<std::byte> int8_2_byte(const int8_t& value);


// uint16_t
uint16_t byte_2_uint16(const std::vector<std::byte>& bytes);

std::vector<std::byte> uint16_2_byte(const uint16_t& value);


// int16_t
int16_t byte_2_int16(const std::vector<std::byte>& bytes);

std::vector<std::byte> int16_2_byte(const int16_t& value);


// DATA1b
double_t byte_2_data1b(const std::vector<std::byte>& bytes);

std::vector<std::byte> data1b_2_byte(const double_t& value);


// DATA1c
double_t byte_2_data1c(const std::vector<std::byte>& bytes);

std::vector<std::byte> data1c_2_byte(const double_t& value);


// DATA2b
double_t byte_2_data2b(const std::vector<std::byte>& bytes);

std::vector<std::byte> data2b_2_byte(const double_t& value);


// DATA2c
double_t byte_2_data2c(const std::vector<std::byte>& bytes);

std::vector<std::byte> data2c_2_byte(const double_t& value);


// float
double_t byte_2_float(const std::vector<std::byte>& bytes);

std::vector<std::byte> float_2_byte(const double_t& value);


#endif // EBUSTRACE_DATATYPES_H
