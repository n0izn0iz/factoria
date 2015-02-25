#version 330

layout(location = 0) in vec4	position;
out vec2						texCoord;
uniform float					rotation;
uniform vec2					modelpos;
uniform vec2					campos;
uniform vec2					screensize;
uniform float					scale;
void main()
{
	vec2 rotpos;

	rotpos.x = (position.x * cos(rotation)) - (position.y * sin(rotation));
	rotpos.y = (position.y * cos(rotation)) + (position.x * sin(rotation));
	vec2 screenpos = rotpos + modelpos - campos;
	vec2 clipPos;
	clipPos.y = screenpos.y * scale;
	clipPos.x = screenpos.x * (scale / (screensize.x / screensize.y));

	gl_Position = vec4(clipPos.x, clipPos.y, 0.0, 1.0);
	texCoord = position.zw;
}
