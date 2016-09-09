#version 120

uniform float timeValX = 1.0;
uniform float timeValY = 1.0;
uniform vec4 bands;
uniform ivec4 effect;
uniform vec3	colorIn;


vec4 rand(vec2 A,vec2 B,vec2 C,vec2 D){
    vec2 s=vec2(12.9898,78.233);
    vec4 tmp=vec4(dot(A,s),dot(B,s),dot(C,s),dot(D,s));
    return fract(sin(tmp) * 43758.5453)* 2.0 - 1.0;
} 


float noise(vec2 coord,float d){
    vec2 C[4];
    float d1 = 1.0/d;
    C[0]=floor(coord*d)*d1;
    C[1]=C[0]+vec2(d1,0.0);
    C[2]=C[0]+vec2(d1,d1);
    C[3]=C[0]+vec2(0.0,d1);
    vec2 p=fract(coord*d);
    vec2 q=1.0-p;
    vec4 w=vec4(q.x*q.y,p.x*q.y,p.x*p.y,q.x*p.y);
    return dot(vec4(rand(C[0],C[1],C[2],C[3])),w); 
} 


void main(){
	//this is the fragment shader
	//this is where the pixel level drawing happens
	//gl_FragCoord gives us the x and y of the current pixel its drawing
	
	//we grab the x and y and store them in an int
	float xVal = gl_FragCoord.x;
	float yVal = gl_FragCoord.y;
	
	//we use the mod function to only draw pixels if they are every 2 in x or every 4 in y
//
    vec4 color = vec4(colorIn,1);
    if (effect.x == 1) {
        color.xyz += bands.xyz * sin(xVal / 1024 * 100 + timeValX) + sin(yVal / 768 * 170 + timeValY);
    }
    
    if (effect.y == 1) {
        if( mod(xVal, 2.0) == 0.5 && mod(yVal, 4.0) == 0.5 ){
            color.xyz *= gl_Color.xyz;
        }else{
            color.a = 0.0;
        }

    }
    
    if (effect.z == 1) {
        color.xyz += noise(vec2(xVal, yVal), 1.) * vec3(1.0, 0., 0.);
    }
    
    if (effect.w == 1) {
        color.xyz += fract(xVal / 1024 * 60 * bands.y + timeValX * .33) * vec3(.8, .5, .2);// + fract(yVal / 768 * 170 + timeValY)
    }
                       
    gl_FragColor = color;
}