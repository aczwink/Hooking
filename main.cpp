/*
 * Copyright (c) 2019 Amir Czwink (amir130@hotmail.de)
 *
 * This file is part of Hooking.
 *
 * Hooking is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hooking is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hooking.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <Std++.hpp>
using namespace StdXX;
using namespace StdXX::Debugging;

void hookVictim()
{
	stdOut << u8"victim" << endl;
}

FunctionHook hook((void*)hookVictim);

void hookTarget()
{
	stdOut << u8"hey from hook" << endl;
}

void hookTargetAndContinue()
{
	stdOut << u8"hey from hook! Now continuing with original function..." << endl;
	hook.Trampoline();
}

int32 Main(const String& programName, const FixedArray<String>& args)
{
	hookVictim();
	hook.Hook((void*)hookTarget);
	hookVictim();
	hook.UnHook();
	hookVictim();

	hook.Hook((void*)hookTargetAndContinue);
	hookVictim();
	hook.UnHook();
	hookVictim();

	stdOut << u8"Done with hooking" << endl;

	return EXIT_SUCCESS;
}