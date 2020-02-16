/**
 * @file SceneNode.h
 *
 * Describes interface for a node in the Scene Graph
 *
 * @author Lonnie L. Souder II
 * @date 09/07/2019
 */
#pragma once

#include <list>
#include <memory>

class SceneNode
{
public:
	/**
	 * Should handle all updates of the node
	 * from one frame to the next
	 */
	virtual void Update() = 0;

	/**
	 * Should handle how the node is drawn
	 */
	virtual void Draw() const = 0;

protected:

	std::shared_ptr<SceneNode> mpParent;
	std::list<std::shared_ptr<SceneNode>> mChildren;

};
