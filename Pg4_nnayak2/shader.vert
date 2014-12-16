uniform float time, type;
varying vec4 ecPos, refPos1;
varying float myType, myTime;

void main()
{  
	myType = type;
	myTime = time;
	
	//calculate the eye space position
    ecPos = gl_ModelViewMatrix * gl_Vertex;
	
    //pass tex coord to fragment shader     
	gl_TexCoord[0] = gl_MultiTexCoord0;

    gl_Position = ftransform();
	
	//storing the position transformed by ftransform also
	refPos1 = gl_Position;
} 