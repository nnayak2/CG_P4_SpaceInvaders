varying vec4 ecPos, refPos1;
varying float myType, myTime;
uniform sampler2D myTex;

void main()
{
	vec4 lightAmb;
	vec4 lightDif;
	vec4 lightSpc;
	
	if(myType == 0)
	{
		lightAmb = vec4( 0.6, 0.0, 0.0, 1.0);
		lightDif = vec4( 0.5, 0.5, 0.0, 1.0);
		lightSpc = vec4( 0.5, 0.5, 0.5, 1.0);
	}
	else if(myType == 1)
	{
		lightAmb = vec4( 0.0, 0.3, 0.2, 1.0);
		lightDif = vec4( 0.0, 0.5, 0.5, 1.0);
		lightSpc = vec4( 0.5, 0.5, 0.5, 1.0);
	}
	else
	{
		lightAmb = vec4( 0.0, 0.0, 0.6, 1.0);
		lightDif = vec4( 0.5, 0.0, 0.5, 1.0);
		lightSpc = vec4( 0.5, 0.5, 0.5, 1.0);
	}
	
	vec4 normal = -vec4( normalize(cross(dFdy(refPos1.xyz), dFdx(refPos1.xyz))) , 1.0);
	vec4 lightPos = vec4( normalize(vec3(gl_LightSource[0].position - ecPos.xyz)), 1.0);
	vec4 eye = vec4(0.0, 10.0, 0.0, 1.0);
	
	vec4 color;
	//Color is being calculated as Ambient   +   N.L * diffue   +  N.HV ^ 8 * specular
	
	color = lightAmb;

	float ndotl = dot(normal, normalize(lightPos - ecPos));
	if(ndotl > 0.0)
		color = color + ndotl*lightDif*sin(myTime);

	float ndoth = dot(normal, normalize( (lightPos - ecPos) + (eye - ecPos) ) );
	if(ndoth > 0.0)
		color = color +  (lightSpc * pow( ndoth , 8 ));

	gl_FragColor = color;
}