/**
 * @file Model.h
 *
 * Contains everything necessary to draw an item
 * - Shader
 * - Mesh
 * TODO: Add uniforms to Model
 * TODO: Add textures to Model (maybe encapsulate textures and Shader under Material)
 *
 * @author Lonnie L. Souder II
 * @date 12/01/19
 */

#include "SceneNode.h"
#include "Mesh.h"
#include "Shader.h"

#include <memory>

class Model : public SceneNode
{
public:
	/// Shorthand for uniform data needed by Model
	typedef std::pair<std::string, std::shared_ptr<const void>> UniformData;

	Model() = delete;

	/**
   * Makes a copy of another Model
   */
	Model(const Model &other);

	/**
   * Creates a model with the given mesh and shader program
   */
	Model(const std::shared_ptr<Mesh> pMesh,
		const std::shared_ptr<Shader> pShader,
		const std::vector<UniformData> Uniforms = {});

	/**
   * Releases shared pointers to data
   */
	~Model();

	/**
   * Sets all of the necessary uniforms
   */
	virtual void Update() override;

	/**
   * Draws mpMesh using mpShader
   */
	virtual void Draw() const override;

private:

	const std::shared_ptr<Mesh> mpMesh;
	const std::shared_ptr<Shader> mpShader;
	const std::vector<UniformData> mUniforms;
};
