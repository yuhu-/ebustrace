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

#include <logger.h>

#include <ebusfsm/EbusFSM.h>
#include <ebusfsm/EbusSequence.h>
#include <ebusfsm/EbusCommon.h>

#include <iostream>
#include <functional>
#include <sstream>
#include <chrono>
#include <iomanip>

#include <unistd.h>
#include <sys/time.h>

auto old = std::chrono::system_clock::now();

ebusfsm::Reaction identify(ebusfsm::EbusSequence& eSeq)
{
	//std::cout << "identify: " << eSeq.toString().c_str() << std::endl;

	return (ebusfsm::Reaction::undefined);
}

void publish(ebusfsm::EbusSequence& eSeq)
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

	auto ms_diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - old);
	old = now;

	std::ostringstream ostr;
	ostr << std::put_time(localtime(&in_time_t), "%Y-%m-%d %X.") << std::setw(3) << std::setfill('0') << ms.count() % 1000;

	//std::cout << std::setw(4) << ms_diff.count() << " ms : " << eSeq.toString().c_str() << std::endl;
	std::cout << ostr.str() << " " << std::setw(4) << ms_diff.count() << " ms : " << eSeq.toString().c_str() << std::endl;
}

struct command
{
	const char* hex;
	const char* name;
	const char* unit;
	int pos;
	int len;
};

int main()
{
	ebusfsm::EbusFSM fsm(std::byte(0xff), "/dev/ttyUSB0", false, std::make_shared<logger>(),
		std::bind(&identify, std::placeholders::_1),
		std::bind(&publish, std::placeholders::_1));

	fsm.setReceiveTimeout(15000);

	ebusfsm::EbusSequence eSeq;

	std::vector<command> commands =
	{
	/* UIH00 Controller */
//	{ "15b509030d0100", "UIH00 Aussentemperatur           ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK
//		{ "15b509030d0500", "UIH00 Solltemperatur             ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Pufferspeicher
//		{ "15b509030d0200", "UIH00 Vorlauftemperatur Ist      ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK wie T6
		/* EHP00 Wärmepumpe */
		//	{ "08b509030d0000", "EHP00 Speichertemperatur       ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Pufferspeicher
//		{ "08b509030d0100", "EHP00 Vorlauftemperatur        ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Pufferspeicher VF1
		//	{ "08b509030d0700", "EHP00 Rücklauftemperatur       ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Pufferspeicher RF1
		//	{ "08b509030d0f00", "EHP00 Sole Eintritt            ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Wärmequelle T3
		//	{ "08b509030d0800", "EHP00 Sole Austritt            ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Wärmequelle T8
//			{ "08b509030d1600", "EHP00 Druck Solekreis          ", "bar", ebusfsm::Type::data2c, 1, 2 },
		//	{ "08b509030d0200", "EHP00 Kompressor Eintritt ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Kältekreis T1
		//	{ "08b509030d0400", "EHP00 Kompressor Austritt ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Kältekreis T2
		//	{ "08b509030d0d00", "EHP00 TEV Eintritt             ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Kältekreis T4
		//	{ "08b509030d8d00", "EHP00 Ueberhitzung             ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Kältekreis
		//	{ "08b509030d8e00", "EHP00 Unterkuehlung            ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Kältekreis
//			{ "08b509030d1400", "EHP00 Hochdruck Kaeltekreis    ", "bar", ebusfsm::Type::data2c, 1, 2 },
//			{ "08b509030d1500", "EHP00 Niederdruck Kaeltekreis  ", "bar", ebusfsm::Type::data2c, 1, 2 },
//		{ "08b509030d0900", "EHP00 Vorlauftemperatur        ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Wärmepumpenkreis T6
//	{ "08b509030d0a00", "EHP00 Rücklauftemperatur      ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK Wärmepumpenkreis T5
//		{ "08b509030d1200", "EHP00 Heizanlagedruck          ", "bar", ebusfsm::Type::data2c, 1, 2 },
//		{ "50b509030d4600", "EHP00 KG Vorlauftemperatur Soll  ", "°C", ebusfsm::Type::data1c, 1, 1 }, // OK KG
//		{ "08b509030d0300", "EHP00 KG Vorlauftemperatur Ist   ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK KG VF2
		/* MC2   Mischermodul */
//		{ "52b509030d4600", "MC2   OG Vorlauftemperatur Soll  ", "°C", ebusfsm::Type::data1c, 1, 1 }, // OK OG
//		{ "52b509030d0100", "MC2   OG Vorlauftemperatur Ist   ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK OG
//		{ "53b509030d4600", "MC2   EG Vorlauftemperatur Soll  ", "°C", ebusfsm::Type::data1c, 1, 1 }, // OK EG
//		{ "53b509030d0300", "MC2   EG Vorlauftemperatur Ist   ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK EG
		/* PMW00 Trinkwasserstation */
//	{ "0ab509030d0000", "PMW00 vom Speicher           ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK
//	{ "0ab509030d0100", "PMW00 zum Speicher           ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK
//	{ "0ab509030d0200", "PMW00 Warmwassertemperatur   ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK
		/* PMS00 Solarladestation */
//	{ "edb509030d0500", "PMS00 vom Kollektor          ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK
//	{ "edb509030d0600", "PMS00 zum Kollektor          ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK
//	{ "edb509030d0800", "PMS00 vom Speicher           ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK
//	{ "edb509030d0700", "PMS00 zum Speicher           ", "°C", ebusfsm::Type::data2c, 1, 2 }, // OK
		};

	while (true)
	{
//		for (const command cmd : commands)
//		{

//			eSeq.createMaster(0xff, cmd.hex);
//			int state = fsm.transmit(eSeq);

//			if (state == SEQ_OK)
//				std::cout << cmd.name << " " << std::fixed << std::setprecision(2)
//					<< ebusfsm::decode(cmd.type, eSeq.getSlave().range(cmd.pos, cmd.len)) << " " << cmd.unit
//					<< " ==> " << eSeq.toString().c_str() << std::endl;
//			else
//				std::cout << fsm.errorText(state) << std::endl;

//			eSeq.clear();
			sleep(2);
//		}

	}

	return (0);

}
