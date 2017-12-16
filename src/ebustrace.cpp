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

struct command
{
	const char* hex;
	const char* name;
	const char* unit;
	int type;
	int pos;
	int len;
};

int main()
{
	ebusfsm::EbusFSM fsm(0xff, "/dev/ttyUSB0", false, std::make_shared<logger>(), std::bind(&identify, std::placeholders::_1),
		std::bind(&publish, std::placeholders::_1));

	fsm.setReceiveTimeout(15000);

	ebusfsm::EbusSequence eSeq;

	std::vector<command> commands =
	{
	{ "0ab509030d0000", "t1", "°C", 22, 1, 2 },
	{ "0ab509030d0100", "t2", "°C", 22, 1, 2 },
	{ "0ab509030d0200", "t3", "°C", 22, 1, 2 },
	{ "0ab509030d0300", "Vdot1", "Hz", 23, 1, 2 },
	{ "0ab509030d0500", "PumpED  ", "%", 13, 1, 2 },
	{ "0ab509030d0600", "MixerPos", "-", 23, 1, 2} };

	while (true)
	{
		for (const command cmd : commands)
		{


			eSeq.createMaster(0xff, cmd.hex);
			int state = fsm.transmit(eSeq);

			if (state == SEQ_OK)
				std::cout << cmd.name << " " << ebusfsm::decode(cmd.type, eSeq.getSlave().range(cmd.pos, cmd.len)) << " " << cmd.unit
					<< std::endl;
			else
				std::cout << fsm.errorText(state) << std::endl;

			eSeq.clear();
			sleep(2);
		}

	}

	return (0);

}
