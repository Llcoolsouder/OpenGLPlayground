#include "Model.h"

#include "Mesh.h"
#include "Shader.h"

#include <algorithm>
#include <memory>

//=============================================================================
//=============================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Model::Model(const Model &other) :
		mpMesh(other.mpMesh),
		mpShader(other.mpShader),
		mUniforms(other.mUniforms)
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Model::Model(
	const std::shared_ptr<Mesh> pMesh,
	const std::shared_ptr<Shader> pShader,
	const std::vector<UniformData> Uniforms) :
		mpMesh(pMesh),
		mpShader(pShader),
		mUniforms(Uniforms)
{
	// TODO: Discard uniforms that are not in the shader
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Model::~Model()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Model::Update()
{
	mpShader->Use();
	for_each(
		mUniforms.begin(),
		mUniforms.end(),
		[&](const UniformData uniform) { mpShader->SetUniform(uniform.first, uniform.second.get()); });

	for_each(
		mChildren.begin(),
		mChildren.end(),
		[&](std::shared_ptr<SceneNode> child) { child->Update(); });
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Model::Draw() const
{
	mpMesh->Bind();
	mpShader->SetAllVertexAttribPointers();
	mpShader->Use();
	mpMesh->Draw();

	for_each(
		mChildren.begin(),
		mChildren.end(),
		[&](std::shared_ptr<SceneNode> child) { child->Draw(); });
}
