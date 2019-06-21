

float hash (in vec2 st) {
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*13758.5453123);
}


void main()
{
float iTime=13;
	vec2 iResolution=vec2(1000,1000);
	float t = 0.1*iTime - 1.0;

	mat2 am = mat2( cos(t*1.71+0.18), cos(t*1.31+3.18), cos(t*1.13+3.29), cos(t*1.44+4.21) );
	mat2 bm = mat2( cos(t*2.57+1.66), cos(t*1.08+0.74), cos(t*2.25+2.78), cos(t*1.23+1.29) );
	mat2 cm = mat2( cos(t*1.15+6.33), cos(t*2.94+2.92), cos(t*1.78+0.82), cos(t*2.58+2.36) );
	mat2 dm = mat2( cos(t*1.42+4.89), cos(t*2.73+6.34), cos(t*1.82+5.91), cos(t*1.21+3.84) );
	vec2 at = vec2( cos(t*2.13+0.94), cos(t*1.19+0.29) )*0.8;
	vec2 bt = vec2( cos(t*1.09+5.25), cos(t*1.27+1.77) )*0.8;
	vec2 ct = vec2( cos(t*2.76+4.39), cos(t*2.35+2.04) )*0.8;
	vec2 dt = vec2( cos(t*1.42+4.71), cos(t*2.81+3.51) )*0.8;

	

	
	vec3  cola = vec3(0.0);

	
	float cad = 0.0;

	for(int z=0;z<2;z++){
	for(int y=0;y<2;y++){
		vec2 of =  vec2( float(y), float(z) )/float(2);
	    vec2 uv = -1.0 + 2.0*(gl_FragCoord.xy+of)/iResolution.xy;
		uv *= 2.0;
		float p = hash(vec2(gl_FragCoord.x+y,gl_FragCoord.y+z));
		vec2 z = vec2( 0.0 );
	for( int i=0; i<2048; i++ ) 
    {
		p = fract( p*8.1 );

    
             if( p < 0.25 ) { z = am*z + at; cad = 0.10; }
        else if( p < 0.50 ) { z = bm*z + bt; cad = 0.25; }
        else if( p < 0.75 ) { z = cm*z + ct; cad = 0.20; }
        else                { z = dm*z + dt; cad = 0.15; }

        // non linear transform
	    float zr = length(z);
		float ar = atan( z.y, z.x ) + zr*0.5;
		z = 2.0*vec2( cos(ar), sin(ar) )/zr;

        if( i>20 )
		{
         if( dot(uv-z,uv-z)<1e-3)
		 cola+=cad/2;

		}
	}
	
	}}
	gl_FragColor = vec4( cola/4, 1.0 );
}