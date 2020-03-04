#include "SceneNode.h"

#include <algorithm>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
SceneNode::SceneNode() :
		mpParent(nullptr),
		mChildren({})
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
SceneNode::~SceneNode()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SceneNode::Update()
{
	std::for_each(
		mChildren.begin(),
		mChildren.end(),
		[&](std::shared_ptr<SceneNode> pChild) { pChild->Update(); });
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SceneNode::Draw() const
{
	std::for_each(
		mChildren.begin(),
		mChildren.end(),
		[&](std::shared_ptr<SceneNode> pChild) { pChild->Draw(); });
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SceneNode::SetParentNode(std::shared_ptr<SceneNode> pNewParentNode)
{
	mpParent = pNewParentNode;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool SceneNode::AddChildNode(std::shared_ptr<SceneNode> pNewChildNode)
{
	for (auto it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		if (*it == pNewChildNode)
			return false;
	}
	mChildren.push_back(pNewChildNode);
	return true;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool SceneNode::RemoveChildNode(std::shared_ptr<SceneNode> pChildNode)
{
	for (auto it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		if (*it == pChildNode)
		{
			mChildren.erase(it);
			return true;
		}
	}
	return false;
}