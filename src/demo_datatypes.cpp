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

#include <datatypes.h>

#include <iostream>
#include <iomanip>

const std::string toString(const std::vector<std::byte>& seq)
{
	std::ostringstream ostr;

	for (size_t i = 0; i < seq.size(); i++)
		ostr << std::nouppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned>(seq[i]);

	return (ostr.str());
}

void printLine(const std::vector<std::byte>& bytes, const std::vector<std::byte>& result, const std::string& value)
{
	std::cout << "bytes " << toString(bytes) << " encode " << toString(result) << " decode " << value << std::endl;
}

// BCD
void compareBCD(const std::vector<std::byte>& bytes, const bool& print)
{
	uint8_t value = byte_2_bcd(bytes);
	std::vector<std::byte> result(1, bcd_2_byte(value)[0]);

	if ((value != 0xff && bytes != result) || print) printLine(bytes, result, std::to_string(value));
}

// uint8_t
void compareUINT8(const std::vector<std::byte>& bytes, const bool& print)
{
	uint8_t value = byte_2_uint8(bytes);
	std::vector<std::byte> result = uint8_2_byte(value);

	if (bytes != result || print) printLine(bytes, result, std::to_string(value));
}

// int8_t
void compareINT8(const std::vector<std::byte>& bytes, const bool& print)
{
	int8_t value = byte_2_int8(bytes);
	std::vector<std::byte> result = int8_2_byte(value);

	if (bytes != result || print) printLine(bytes, result, std::to_string(value));
}

// uint16_t
void compareUINT16(const std::vector<std::byte>& bytes, const bool& print)
{
	uint16_t value = byte_2_uint16(bytes);
	std::vector<std::byte> result = uint16_2_byte(value);

	if (bytes != result || print) printLine(bytes, result, std::to_string(value));
}

// int16_t
void compareINT16(const std::vector<std::byte>& bytes, const bool& print)
{
	int16_t value = byte_2_int16(bytes);
	std::vector<std::byte> result = int16_2_byte(value);

	if (bytes != result || print) printLine(bytes, result, std::to_string(value));
}

// DATA1b
void compareDATA1b(const std::vector<std::byte>& bytes, const bool& print)
{
	double_t value = byte_2_data1b(bytes);
	std::vector<std::byte> result = data1b_2_byte(value);

	if (bytes != result || print) printLine(bytes, result, std::to_string(value));
}

// DATA1c
void compareDATA1c(const std::vector<std::byte>& bytes, const bool& print)
{
	double_t value = byte_2_data1c(bytes);
	std::vector<std::byte> result = data1c_2_byte(value);

	if (bytes != result || print) printLine(bytes, result, std::to_string(value));
}

// DATA2b
void compareDATA2b(const std::vector<std::byte>& bytes, const bool& print)
{
	double_t value = byte_2_data2b(bytes);
	std::vector<std::byte> result = data2b_2_byte(value);

	if (bytes != result || print) printLine(bytes, result, std::to_string(value));
}

// DATA2c
void compareDATA2c(const std::vector<std::byte>& bytes, const bool& print)
{
	double_t value = byte_2_data2c(bytes);
	std::vector<std::byte> result = data2c_2_byte(value);

	if (bytes != result || print) printLine(bytes, result, std::to_string(value));
}

// float
void compareFLOAT(const std::vector<std::byte>& bytes, const bool& print)
{
	double_t value = byte_2_float(bytes);
	std::vector<std::byte> result = float_2_byte(value);

	if (bytes != result || print) printLine(bytes, result, std::to_string(value));
}



int main()
{
	std::vector<std::byte> b1 =
	{ std::byte(0x00), std::byte(0x01), std::byte(0x64), std::byte(0x7f), std::byte(0x80), std::byte(0x81), std::byte(0xc8),
		std::byte(0xfe), std::byte(0xff) };

	std::vector<std::byte> b2 =
	{ std::byte(0x00), std::byte(0x00), std::byte(0x01), std::byte(0x00), std::byte(0xff), std::byte(0xff), std::byte(0x00),
		std::byte(0xff), std::byte(0xf0), std::byte(0xff), std::byte(0x00), std::byte(0x80), std::byte(0x01), std::byte(0x80),
		std::byte(0xff), std::byte(0x7f), std::byte(0x65), std::byte(0x02), std::byte(0x77), std::byte(0x02) };

	// BCD
	std::cout << std::endl << std::endl << "Examples BCD" << std::endl << std::endl;

	for (size_t i = 0; i < b1.size(); i++)
	{
		std::vector<std::byte> src(1, b1[i]);

		compareBCD(src, true);
	}

	std::cout << std::endl << "Check range BCD" << std::endl;

	for (int low = 0x00; low <= 0xff; low++)
	{
		std::vector<std::byte> src(1, std::byte(low));

		compareBCD(src, false);
	}

	// uint8_t
	std::cout << std::endl << std::endl << "Examples uint8_t" << std::endl << std::endl;

	for (size_t i = 0; i < b1.size(); i++)
	{
		std::vector<std::byte> src(1, b1[i]);

		compareUINT8(src, true);
	}

	std::cout << std::endl << "Check range uint8_t" << std::endl;

	for (int low = 0x00; low <= 0xff; low++)
	{
		std::vector<std::byte> src(1, std::byte(low));

		compareUINT8(src, false);
	}

	// int8_t
	std::cout << std::endl << std::endl << "Examples int8_t" << std::endl << std::endl;

	for (size_t i = 0; i < b1.size(); i++)
	{
		std::vector<std::byte> src(1, b1[i]);

		compareINT8(src, true);
	}

	std::cout << std::endl << "Check range int8_t" << std::endl;

	for (int low = 0x00; low <= 0xff; low++)
	{
		std::vector<std::byte> src(1, std::byte(low));

		compareINT8(src, false);
	}

	// uint16_t
	std::cout << std::endl << std::endl << "Examples uint16_t" << std::endl << std::endl;

	for (size_t i = 0; i < b2.size(); i += 2)
	{
		std::vector<std::byte> src
		{ b2[i], b2[i + 1] };

		compareUINT16(src, true);
	}

	std::cout << std::endl << "Check range uint16_t" << std::endl;

	for (int high = 0x00; high <= 0xff; high++)
	{
		for (int low = 0x00; low <= 0xff; low++)
		{
			std::vector<std::byte> src
			{ std::byte(low), std::byte(high) };

			compareUINT16(src, false);
		}
	}

	// int16_t
	std::cout << std::endl << std::endl << "Examples int16_t" << std::endl << std::endl;

	for (size_t i = 0; i < b2.size(); i += 2)
	{
		std::vector<std::byte> src
		{ b2[i], b2[i + 1] };

		compareINT16(src, true);
	}

	std::cout << std::endl << "Check range int16_t" << std::endl;

	for (int high = 0x00; high <= 0xff; high++)
	{
		for (int low = 0x00; low <= 0xff; low++)
		{
			std::vector<std::byte> src
			{ std::byte(low), std::byte(high) };

			compareINT16(src, false);
		}
	}

	// DATA1b
	std::cout << std::endl << std::endl << "Examples DATA1b" << std::endl << std::endl;

	for (size_t i = 0; i < b1.size(); i++)
	{
		std::vector<std::byte> source(1, b1[i]);

		compareDATA1b(source, true);
	}

	std::cout << std::endl << "Check range DATA1b" << std::endl;

	for (int low = 0x00; low <= 0xff; low++)
	{
		std::vector<std::byte> source(1, std::byte(low));

		compareDATA1b(source, false);
	}

	// DATA1c
	std::cout << std::endl << std::endl << "Examples DATA1c" << std::endl << std::endl;

	for (size_t i = 0; i < b1.size(); i++)
	{
		std::vector<std::byte> source(1, b1[i]);

		compareDATA1c(source, true);
	}

	std::cout << std::endl << "Check range DATA1c" << std::endl;

	for (int low = 0x00; low <= 0xff; low++)
	{
		std::vector<std::byte> source(1, std::byte(low));

		compareDATA1c(source, false);
	}

	// DATA2b
	std::cout << std::endl << std::endl << "Examples DATA2b" << std::endl << std::endl;

	for (size_t i = 0; i < b2.size(); i += 2)
	{
		std::vector<std::byte> source(&b2[i], &b2[i + 2]);

		compareDATA2b(source, true);
	}

	std::cout << std::endl << "Check range DATA2b" << std::endl;

	for (int high = 0x00; high <= 0xff; high++)
	{
		for (int low = 0x00; low <= 0xff; low++)
		{
			std::vector<std::byte> source
			{ std::byte(low), std::byte(high) };

			compareDATA2b(source, false);
		}
	}

	// DATA2c
	std::cout << std::endl << std::endl << "Examples DATA2c" << std::endl << std::endl;

	for (size_t i = 0; i < b2.size(); i += 2)
	{
		std::vector<std::byte> source(&b2[i], &b2[i + 2]);

		compareDATA2c(source, true);
	}

	std::cout << std::endl << "Check range DATA2c" << std::endl;

	for (int high = 0x00; high <= 0xff; high++)
	{
		for (int low = 0x00; low <= 0xff; low++)
		{
			std::vector<std::byte> source
			{ std::byte(low), std::byte(high) };

			compareDATA2c(source, false);
		}
	}

	// float
	std::cout << std::endl << std::endl << "Examples float" << std::endl << std::endl;

	for (size_t i = 0; i < b2.size(); i += 2)
	{
		std::vector<std::byte> source(&b2[i], &b2[i + 2]);

		compareFLOAT(source, true);
	}

	std::cout << std::endl << "Check range float" << std::endl;

	for (int high = 0x00; high <= 0xff; high++)
	{
		for (int low = 0x00; low <= 0xff; low++)
		{
			std::vector<std::byte> source
			{ std::byte(low), std::byte(high) };

			compareFLOAT(source, false);
		}
	}

	return (0);
}
