#version 120

void main(){
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	vec4 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	gl_Position = pos;
    
    vec4 col = gl_Color;
	gl_FrontColor =  col;	
}
