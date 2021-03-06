#version 150

in vec3 position;
in vec3 color;

out vec3 ex_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{	
      gl_Position = proj * view * model * vec4(position, 1.0f);
      ex_color = color;
}
