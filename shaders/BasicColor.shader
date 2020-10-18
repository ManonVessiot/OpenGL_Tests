#shader vertex
#version 330 core

layout(location = 0) in vec4 v_position;

void main(){
   gl_Position = v_position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main(){
   color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
