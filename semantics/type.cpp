/**
 * Despayre License
 *
 * Copyright © 2016 Michał "Griwes" Dominiak
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

#include <unordered_map>

#include "despayre/semantics/type.h"
#include "despayre/semantics/variable.h"
#include "despayre/semantics/delayed_variable.h"
#include "despayre/semantics/namespace.h"

using type_identifier = reaver::despayre::_v1::type_identifier;
using type_descriptor = reaver::despayre::_v1::type_descriptor;
using variable_ptr = std::shared_ptr<reaver::despayre::_v1::variable>;

void reaver::despayre::_v1::_detail::_save_identifier(reaver::despayre::_v1::semantic_context & ctx, const std::vector<std::u32string> & name, type_identifier id)
{
    auto val = ctx.variables;
    for (auto i = 0ull; i < name.size() - 1; ++i)
    {
        auto nested = val->get_property(name[i]);
        if (nested)
        {
            val = nested;
            continue;
        }

        auto ns = std::make_shared<name_space>();
        val->add_property(name[i], ns);
        val = ns;
    }

    val->add_property(name.back(), std::make_shared<type_descriptor_variable>(id));
}

void reaver::despayre::_v1::_detail::_save_descriptor(semantic_context & ctx, type_identifier id, std::u32string name, std::string source_module, constructor type_constructor)
{
    ctx.type_descriptors.emplace(id, type_descriptor{ std::move(name), std::move(source_module), type_constructor });
}

variable_ptr reaver::despayre::_v1::instantiate(const semantic_context & ctx, const std::vector<std::u32string> & name, std::vector<variable_ptr> variables)
{
    auto val = ctx.variables;
    for (auto i = 0ull; i < name.size() && val; ++i)
    {
        val = val->get_property(name[i]);
    }

    if (!val)
    {
        return std::make_shared<delayed_variable>(name, std::move(variables));
    }

    if (val->type() != get_type_identifier<type_descriptor_variable>())
    {
        assert(!"fdsa");
    }

    return instantiate(ctx, val->as<type_descriptor_variable>()->identifier(), std::move(variables));
}

variable_ptr reaver::despayre::_v1::instantiate(const semantic_context & ctx, type_identifier id, std::vector<variable_ptr> variables)
{
    return ctx.type_descriptors.at(id).type_constructor(std::move(variables));
}

