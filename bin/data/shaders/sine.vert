#version 120

uniform float time = 1.0;
uniform int waveDirection = 0;
uniform int waveFrequency = 1;

void main(){

	vec4 modVert = gl_Vertex;
	
	if(waveDirection == 0){
		modVert.z = sin(modVert.x * 200 + time * waveFrequency) * 10;
	} else {
		modVert.z = sin(modVert.y * 200 + time * waveFrequency) * 10;
    }

	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * modVert;
}
