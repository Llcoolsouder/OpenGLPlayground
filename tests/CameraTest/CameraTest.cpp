#include <glm/glm.hpp>
#include <../include/Camera.h>

int main()
{
	const glm::mat4 IdentityMatrix = glm::mat4(1.0f);
	Camera camera;

	if (*camera.GetViewMatrix() != IdentityMatrix)
		return 1;
	if (*camera.GetProjMatrix() != IdentityMatrix)
		return 1;

	return 0;
}
