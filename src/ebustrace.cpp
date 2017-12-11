/*
 * Copyright (C) Roland Jax 2017 <roland.jax@liwest.at>
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

ebusfsm::Reaction identify(ebusfsm::EbusSequence& eSeq)
{
	//std::cout << "identify: " << eSeq.toString().c_str() << std::endl;

	return (ebusfsm::Reaction::undefined);
}

void publish(ebusfsm::EbusSequence& eSeq)
{
	//std::cout << "publish:  " << eSeq.toString().c_str() << std::endl;
}

int main()
{
	ebusfsm::EbusFSM fsm(0xff, "/dev/ttyUSB0", false, std::make_shared<logger>(), std::bind(&identify, std::placeholders::_1),
		std::bind(&publish, std::placeholders::_1));

	fsm.setReceiveTimeout(15000);

	ebusfsm::EbusSequence eSeq;
	std::string arr[8][3] =
	{
	{ "0ab509030d0000", "NTC1 - Sensor           ", "°C" },
	{ "0ab509030d0100", "NTC2 - Sensor           ", "°C" },
	{ "0ab509030d0200", "NTC3 - Sensor           ", "°C" },
	{ "0ab509030d0900", "Heizanforderung         ", "°C" },
	{ "0ab509030d0b00", "Zapfsollwert manuell    ", "°C" },
	{ "0ab509030d0c00", "Zapfsollwert automatisch", "°C" },
	{ "0ab509030d0e00", "Zapfsollwert aktuell    ", "°C" },
	{ "0ab509030d4600", "Volumenstrom            ", "l/min" } };

	while (true)
	{
		sleep(5);

		size_t i = 0;
		while (!arr[i][0].empty())
		{

			eSeq.createMaster(0xff, arr[i][0]);
			int state = fsm.transmit(eSeq);

			if (state == SEQ_OK)
				std::cout << arr[i][1] << " " << ebusfsm::decode(4, eSeq.getSlave().range(1, 2)) << " " << arr[i][2]
					<< std::endl;
			else
				std::cout << fsm.errorText(state) << std::endl;

			eSeq.clear();

			++i;
		}

	}

	return (0);

}
