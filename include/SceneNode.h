/**
 * @file SceneNode.h
 *
 * Describes a node in the Scene Graph
 *
 * @author Lonnie L. Souder II
 * @date 02/29/2020
 */
#pragma once

#include <list>
#include <memory>

class SceneNode
{
public:
	
	SceneNode();

	~SceneNode();

	/**
	 * Should handle all updates of the node
	 * from one frame to the next
	 */
	virtual void Update();

	/**
	 * Should handle how the node is drawn
	 */
	virtual void Draw() const;

	/**
	 * Sets the pointer to the parent node
	 * @param pNewParentNode Pointer to the new parent node
	 */
	virtual void SetParentNode(std::shared_ptr<SceneNode> pNewParentNode);

	/**
	 * Adds a child node to this node
	 * @param pNewChildNode Pointer to the new child node to be added
	 * @return true if pNewChildNode is successfully added else false
	 */
	virtual bool AddChildNode(std::shared_ptr<SceneNode> pNewChildNode);

	/**
	 * Removes a child node from this node
	 * @param Pointer to the child node to be removed
	 * @return true if pChildNode is successfully removed else false
	 */
	virtual bool RemoveChildNode(std::shared_ptr<SceneNode> pChildNode);

protected:

	std::shared_ptr<SceneNode> mpParent;
	std::list<std::shared_ptr<SceneNode>> mChildren;

};
