uniform float zoom;
uniform vec2 origin;
uniform vec2 originUni;
uniform vec2 originUniUni;
void main()
{
float distance=1e20;
float distance2=1e20;
vec2 point=vec2(-0.5,2.0);
float di =  1.0;
float m2 = 0.0;
dvec2 dz = dvec2(0.0);
double x=0;
double y=0;
double cx=(double)(gl_FragCoord.x-500)/(250*zoom)+origin.x+0.00000001*originUni.x+0.000000000001*originUniUni.x;
double cy=(double)(gl_FragCoord.y-500)/(250*zoom)+origin.y+0.00000001*originUni.y+0.000000000001*originUniUni.y;
double xtemp;
int i=0;
vec3 col;
vec4 pc=vec4(0,0,0,1);
for(;i<400;i++){
if( m2>1024.0 ) { di=0.0; break; }
dz = 2.0*vec2(x*dz.x-y*dz.y, x*dz.y + y*dz.x) + vec2(1.0,0.0);
xtemp=x;
x=x*x-y*y+cx;
y=2*xtemp*y+cy;
 m2 = x*x+y*y;
 //distance=min(distance,abs((float)y));//line trap
 //distance2=min(distance2,dot(vec2(x,y)-point,vec2(x,y)-point));//point trap
}
//distance2=sqrt(distance2);//point trap
vec2 z=vec2(x,y);
vec2 dzf=dz;
float d = 0.5*sqrt(dot(z,z)/dot(dzf,dzf))*log(dot(z,z));

if(di>0.5)
d=0;
d = clamp( pow(4.0*d*zoom/2,0.2), 0.0, 1.0 );
//d*=clamp(distance*10*(log10(zoom)+10),0,0.5);//line trap
//d*=clamp(distance2*(log10(zoom)+1),0,1);//point trap
gl_FragColor=vec4(d,d,d,1);

}