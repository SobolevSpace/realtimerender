#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourNorm;
out vec3 fragPos;
out vec2 ourCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 norm_model;

void main()
{
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	fragPos = aPos;
	ourNorm = normalize(norm_model*aNorm);
	ourCoord = aTexCoord;
}
