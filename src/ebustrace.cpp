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

#include <ebus/Ebus.h>
#include <unistd.h>
#include <chrono>
#include <cstddef>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "datatypes.h"

class logger : public ebus::ILogger
{

public:
	void error(const std::string &message)
	{
		std::cout << "ERROR:    " << message << std::endl;
	}

	void warn(const std::string &message)
	{
		std::cout << "WARN:     " << message << std::endl;
	}

	void info(const std::string &message)
	{
		//std::cout << "INFO:     " << message << std::endl;
	}

	void debug(const std::string &message)
	{
		//std::cout << "DEBUG:    " << message << std::endl;
	}

	void trace(const std::string &message)
	{
		//std::cout << "TRACE: " << message << std::endl;
	}

};

enum class datatype
{
	bcd, uch, sch, uin, sin, d1b, d1c, d2b, d2c, flt
};

struct command
{
	const char *hex;
	const char *name;
	const char *unit;
	const datatype type;
	int pos;
	int len;
};

// @formatter:off
std::vector<command>commands = {
/* UIH00 Controller */
{ "15b509030d0100", "UIH00 Aussentemperatur           ", "°C ", datatype::d2c, 1, 2 }, // OK
{ "15b509030d0500", "UIH00 Solltemperatur             ", "°C ", datatype::d2c, 1, 2 }, // OK Pufferspeicher
{ "15b509030d0200", "UIH00 Vorlauftemperatur Ist      ", "°C ", datatype::d2c, 1, 2 }, // OK wie T6
/* EHP00 Wärmepumpe */
{ "08b509030d0000", "EHP00 Speichertemperatur         ", "°C ", datatype::d2c, 1, 2 }, // OK Pufferspeicher
{ "08b509030d0100", "EHP00 Vorlauftemperatur          ", "°C ", datatype::d2c, 1, 2 }, // OK Pufferspeicher VF1
{ "08b509030d0700", "EHP00 Rücklauftemperatur         ", "°C ", datatype::d2c, 1, 2 }, // OK Pufferspeicher RF1
{ "08b509030d0f00", "EHP00 Sole Eintritt              ", "°C ", datatype::d2c, 1, 2 }, // OK Solekreis Wärmequelle T3
{ "08b509030d0800", "EHP00 Sole Austritt              ", "°C ", datatype::d2c, 1, 2 }, // OK Solekreis Wärmequelle T8
{ "08b509030d1600", "EHP00 Druck Solekreis            ", "bar", datatype::flt, 1, 2 }, // OK Solekreis
{ "08b509030d0200", "EHP00 Kompressor Eintritt        ", "°C ", datatype::d2c, 1, 2 }, // OK Kältekreis T1
{ "08b509030d0400", "EHP00 Kompressor Austritt        ", "°C ", datatype::d2c, 1, 2 }, // OK Kältekreis T2
{ "08b509030d0d00", "EHP00 TEV Eintritt               ", "°C ", datatype::d2c, 1, 2 }, // OK Kältekreis T4
{ "08b509030d8d00", "EHP00 Ueberhitzung               ", "°C ", datatype::d2c, 1, 2 }, // OK Kältekreis
{ "08b509030d8e00", "EHP00 Unterkuehlung              ", "°C ", datatype::d2c, 1, 2 }, // OK Kältekreis
{ "08b509030d1400", "EHP00 Hochdruck Kaeltekreis      ", "bar", datatype::flt, 1, 2 }, // OK Kältekreis
{ "08b509030d1500", "EHP00 Niederdruck Kaeltekreis    ", "bar", datatype::flt, 1, 2 }, // OK Kältekreis
{ "08b509030d0900", "EHP00 Vorlauftemperatur          ", "°C ", datatype::d2c, 1, 2 }, // OK Wärmepumpenkreis T6
{ "08b509030d0a00", "EHP00 Rücklauftemperatur         ", "°C ", datatype::d2c, 1, 2 }, // OK Wärmepumpenkreis T5
{ "08b509030d1200", "EHP00 Heizanlagedruck            ", "bar", datatype::flt, 1, 2 }, // OK
{ "50b509030d4600", "EHP00 KG Vorlauftemperatur Soll  ", "°C ", datatype::d1c, 1, 1 }, // OK KG
{ "08b509030d0300", "EHP00 KG Vorlauftemperatur Ist   ", "°C ", datatype::d2c, 1, 2 }, // OK KG VF2
/* MC2   Mischermodul */
{ "52b509030d4600", "MC2   OG Vorlauftemperatur Soll  ", "°C ", datatype::d1c, 1, 1 }, // OK OG
{ "52b509030d0100", "MC2   OG Vorlauftemperatur Ist   ", "°C ", datatype::d2c, 1, 2 }, // OK OG
{ "53b509030d4600", "MC2   EG Vorlauftemperatur Soll  ", "°C ", datatype::d1c, 1, 1 }, // OK EG
{ "53b509030d0300", "MC2   EG Vorlauftemperatur Ist   ", "°C ", datatype::d2c, 1, 2 }, // OK EG
/* PMW00 Trinkwasserstation */
{ "0ab509030d0000", "PMW00 vom Speicher               ", "°C ", datatype::d2c, 1, 2 }, // OK
{ "0ab509030d0100", "PMW00 zum Speicher               ", "°C ", datatype::d2c, 1, 2 }, // OK
{ "0ab509030d0200", "PMW00 Warmwassertemperatur       ", "°C ", datatype::d2c, 1, 2 }, // OK
/* PMS00 Solarladestation */
{ "edb509030d0500", "PMS00 vom Kollektor              ", "°C ", datatype::d2c, 1, 2 }, // OK
{ "edb509030d0600", "PMS00 zum Kollektor              ", "°C ", datatype::d2c, 1, 2 }, // OK
{ "edb509030d0800", "PMS00 vom Speicher               ", "°C ", datatype::d2c, 1, 2 }, // OK
{ "edb509030d0700", "PMS00 zum Speicher               ", "°C ", datatype::d2c, 1, 2 }, // OK
};
// @formatter:on

auto old = std::chrono::system_clock::now();

ebus::Reaction process(const std::string &message, std::string &respone)
{
	std::cout << "process: " << message << std::endl;

	return (ebus::Reaction::undefined);
}

void publish(const std::string &message)
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

	auto ms_diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - old);
	old = now;

	std::ostringstream ostr;
	ostr << std::put_time(localtime(&in_time_t), "%Y-%m-%d %X.") << std::setw(3) << std::setfill('0') << ms.count() % 1000;

	//std::cout << std::setw(4) << ms_diff.count() << " ms : " << message << std::endl;
	//std::cout << ostr.str() << " " << std::setw(4) << ms_diff.count() << " ms : " << message << std::endl;
}

int main()
{
	ebus::Ebus service(std::byte(0xff), "/dev/ttyUSB0", std::make_shared<logger>(),
		std::bind(&process, std::placeholders::_1, std::placeholders::_2),
		std::bind(&publish, std::placeholders::_1));

	service.setReceiveTimeout(15000);
	sleep(1);

	while (true)
	{
		for (const command cmd : commands)
		{
			std::vector<std::byte> response;

			int state = service.transmit(cmd.hex, response);

			if (state == 0)
			{
				std::cout << cmd.name << " " << std::setw(5) << std::fixed << std::setprecision(2);

				if (cmd.type == datatype::d1c)
					std::cout << byte_2_data1c(ebus::Ebus::range(response, cmd.pos, cmd.len));
				if (cmd.type == datatype::d2c)
					std::cout << byte_2_data2c(ebus::Ebus::range(response, cmd.pos, cmd.len));
				if (cmd.type == datatype::flt)
					std::cout << byte_2_float(ebus::Ebus::range(response, cmd.pos, cmd.len));

				std::cout << " " << cmd.unit << " ==> " << ebus::Ebus::toString(response) << std::endl;
			}
			else
			{
				std::cout << service.errorText(state) << std::endl;
			}

			sleep(5);
		}

	}

	return (0);

}
