/**
 * Despayre License
 *
 * Copyright © 2016-2017 Michał "Griwes" Dominiak
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation is required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 **/

#include <fstream>
#include <string>

#include "despayre.h"

int main(int argc, char ** argv) try
{
    auto context = reaver::despayre::despayre{ "./buildfile" };
    context.build(argv[1], argv[2]);
}
catch (reaver::exception & ex)
{
    ex.print(reaver::logger::default_logger());
    return 2;
}
catch (std::exception & ex)
{
    reaver::logger::dlog(reaver::logger::fatal) << ex.what();
    return 1;
}

