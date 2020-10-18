#shader vertex
#version 330 core

layout(location = 0) in vec4 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec4 v_tangent;
layout(location = 3) in vec2 v_texCoord;
layout(location = 4) in vec4 v_color;

uniform mat4 u_MVP;

out vec2 v_TexCoord;
out vec4 v_Color;

void main(){
   gl_Position = u_MVP * v_position;
   v_TexCoord = v_texCoord;
   v_Color = v_color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;

uniform vec4 m_MainColor;
uniform vec2 m_MainTextureOffset;
uniform vec2 m_MainTextureScale;
uniform sampler2D u_Texture;

vec2 ScaleUV(vec2 uv, vec2 _scale){
   uv.x = uv.x * _scale.x;
   uv.y = uv.y * _scale.y;
   return uv;
}

vec2 OffsetUV(vec2 uv, vec2 _offset){
   uv = uv + _offset;
   
   int x = int(uv.x);
   if (uv.x < 0){
      uv.x = uv.x - x + 1;
   }
   else{
      uv.x = uv.x - x;
   }
   int y = int(uv.y);
   if (uv.y <= 0){
      uv.y = uv.y - y + 1;
   }
   else{
      uv.y = uv.y - y;
   }
   return uv;
}

void main()
{
   vec2 uv = v_TexCoord;

   uv = ScaleUV(uv, m_MainTextureScale);
   uv = OffsetUV(uv, m_MainTextureOffset);
   color = texture(u_Texture, uv) * m_MainColor;
}
