//uniform sampler2D tex;
uniform float zoom;
uniform vec2 origin;
uniform vec2 originUni;
uniform vec2 originUniUni;
uniform float cx;
uniform float cy;
void main()
{
float distance=1e20;
float distance2=1e20;
vec2 point=vec2(-0.5,2.0);
float di =  1.0;
float m2 = 0.0;
dvec2 dz = dvec2(0.0);
double x=(double)(gl_FragCoord.x-500)/(250*zoom)+origin.x+0.00000001*originUni.x+0.000000000001*originUniUni.x;;
double y=(double)(gl_FragCoord.y-500)/(250*zoom)+origin.y+0.00000001*originUni.y+0.000000000001*originUniUni.y;
double xtemp;
int i=0;
vec3 col;
for(;i<400;i++){
	if( m2>1024.0 ) { di=0.0; break; }
	dz = 2.0*vec2(x*dz.x-y*dz.y, x*dz.y + y*dz.x) + vec2(1.0,0.0);
	xtemp=x;
	x=x*x-y*y+cx;
	y=2*xtemp*y+cy;
	m2 = x*x+y*y;

	
	//col=max(col,texture2D(tex,vec2((x+2)/4,(y+2)/4)).xyz);

	
}
vec2 z=vec2(x,y);
vec2 dzf=dz;
float d = 0.5*sqrt(dot(z,z)/dot(dzf,dzf))*log(dot(z,z));
if(di>0.5)
d=0;
d = clamp( pow(50.0*d*zoom/2,0.2), 0.0, 1.0 );
//col.x=clamp(pow(2*col.x*(0.1*log10(zoom)+1),2),0.0,1.0);

gl_FragColor=vec4(d,d,d,1);

}