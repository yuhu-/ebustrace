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

#include "logger.h"

#include <iostream>

void logger::error(const std::string& message)
{
	std::cout << "ERROR:    " << message << std::endl;
}

void logger::warn(const std::string& message)
{
	//std::cout << "WARN:     " << message << std::endl;
}

void logger::info(const std::string& message)
{
	std::cout << "INFO:     " << message << std::endl;
}

void logger::debug(const std::string& message)
{
	//std::cout << "DEBUG:    " << message << std::endl;
}

void logger::trace(const std::string& message)
{
	//std::cout << "TRACE: " << message << std::endl;
}


