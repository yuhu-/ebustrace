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

#ifndef EBUSTRACE_LOGGER_H
#define EBUSTRACE_LOGGER_H

#include <ebusfsm/IEbusLogger.h>

class logger : public ebusfsm::IEbusLogger
{

public:
	void error(const std::string& message);
	void warn(const std::string& message);
	void info(const std::string& message);
	void debug(const std::string& message);
	void trace(const std::string& message);

};

#endif // EBUSTRACE_LOGGER_H
