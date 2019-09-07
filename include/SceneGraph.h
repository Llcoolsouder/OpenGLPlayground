/**
 * @file SceneGraph.h
 *
 * Describes an interface for any scene graph used by the engine
 *
 * @author Lonnie L. Souder II
 * @date 09/07/2019
 */
#pragma once

#include "SceneNode.h"

class SceneGraph : SceneNode
{
public:

	virtual void Update() = 0;

	virtual void Draw() = 0;

	// TODO: This currently doesn't do anything different from SceneNode. If it doesn't need to be different soon, get rid of this.
};