/**
 * @file PrimitiveGenerator.h
 *
 * Contains a set of functions used to generate vertex arrays
 * for various simple geometric shapes
 *
 * @author Lonnie L. Souder II
 * @date 08/01/2019
 */
#pragma once

#include "Mesh.h"
#include <memory>

/**
 * Contains a set of functions used to generate vertex arrays
 * for various simple geometric shapes
 */
namespace LSPrimitiveGenerator
{

    /**
     * @brief Generates a triangle that fits in a 1x1 square centered about the origin
     * 
     * @return Mesh 
     */
    std::shared_ptr<Mesh> Triangle();

}
