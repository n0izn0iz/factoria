#version 330

uniform sampler3D tex;
uniform float frame;
in vec2 texCoord;
out vec4 outputColor;
void main()
{
	outputColor = texture(tex, vec3(texCoord.x, texCoord.y, frame));
}
