#shader vertex
#version 330 core

layout(location = 0) in vec4 position; 

uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * position;
    gl_PointSize = 1.0;
};

#shader fragment    
#version 330 core

out vec4 color; 

uniform mat4 u_MVP;
uniform float u_time;
 
void main(){
    vec3 set = vec3(0, 0.635, 1);

    color = vec4(set, 1.0);
};