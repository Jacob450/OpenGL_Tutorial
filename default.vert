#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

// outputs the color for the fragment shader
out vec3 color;

out vec2 texCoord;

//controls scale of vertices
uniform float scale;

void main()
{
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	// Assign the colors from the vertex data to "color" which will be used in the fragment shader"
	color = aColor;
	texCoord = vec2(aTex.x, aTex.y) ;
}