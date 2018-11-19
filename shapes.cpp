#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/vec2.hpp"
#include <iostream>
#include <cmath>


class rectangle
{
	public:
		glm::vec4* positions;
		glm::vec4* colors;
		glm::vec2* tex_coords;
		int* id;
		rectangle(int scale, int iden)
		{
			positions=new glm::vec4[6];
			colors= new glm::vec4[6];
			tex_coords=new glm::vec2[6];
			id= new int[6];
			positions[0]=glm::vec4(0.0,0.0,0.0, 1.0);
			positions[1]=glm::vec4(scale,0.0,0.0, 1.0);
			positions[2]=glm::vec4(scale,scale,0.0, 1.0);
			positions[3]=glm::vec4(0.0,0.0,0.0, 1.0);
			positions[4]=glm::vec4(0.0,scale,0.0, 1.0);
			positions[5]=glm::vec4(scale,scale,0.0, 1.0);
			tex_coords[0]=glm::vec2(0.0,0.0);
			tex_coords[1]=glm::vec2(1.0,0.0);
			tex_coords[2]=glm::vec2(1.0,1.0);
			tex_coords[3]=glm::vec2(0.0,0.0);
			tex_coords[4]=glm::vec2(0.0,1.0);
			tex_coords[5]=glm::vec2(1.0,1.0);
			for(int i=0;i<6;i++)
			{
				id[i]=iden;
				colors[i]=glm::vec4(0.2,0.2,0.3,1.0);
			}
		}
};

class cuboid
{
public:
	float a,b,c;
	glm::vec4* pos;
	glm::vec4* col;
	int idx;
	int iden;
	uint siz;
	glm::vec4* positions;
	glm::vec4* colors;
	int* id;
	glm::vec2* tex_coords;
	glm::vec2* t_coords;

	cuboid(float a,float b,float c, int id)
	{
		this->a=a;
		this->b=b;
		this->c=c;
		siz=36;
		idx=0;
		iden=id;
		pos=new glm::vec4[8];
		col=new glm::vec4[8];
		positions=new glm::vec4[36];
		colors=new glm::vec4[36];
		tex_coords=new glm::vec2[36];
		this->id = new int[36];
		t_coords=new glm::vec2[4];
		initcoord();
		gen();
	}

	uint retsiz(void)
	{
		return 16*siz;
	}

	void quad(int a, int b, int c, int d)
	{
	 	colors[idx] = col[a]; positions[idx] = pos[a]; tex_coords[idx]=t_coords[0]; id[idx]= iden; idx++;
	  	colors[idx] = col[b]; positions[idx] = pos[b]; tex_coords[idx]=t_coords[1]; id[idx]= iden; idx++;
	  	colors[idx] = col[c]; positions[idx] = pos[c]; tex_coords[idx]=t_coords[2]; id[idx]= iden; idx++;
	  	colors[idx] = col[a]; positions[idx] = pos[a]; tex_coords[idx]=t_coords[0]; id[idx]= iden; idx++;
	  	colors[idx] = col[c]; positions[idx] = pos[c]; tex_coords[idx]=t_coords[2]; id[idx]= iden; idx++;
	  	colors[idx] = col[d]; positions[idx] = pos[d]; tex_coords[idx]=t_coords[3]; id[idx]= iden; idx++;
	}

	void initcoord()
	{
		pos[0]=glm::vec4(0.0,0.0,0.0, 1.0);
		pos[1]=glm::vec4(a, 0.0, 0.0, 1.0);
		pos[2]=glm::vec4(a, 0.0, c, 1.0);
		pos[3]=glm::vec4(0.0, 0.0, c, 1.0);
		pos[4]=glm::vec4(0.0, b, 0.0, 1.0);
		pos[5]=glm::vec4(a, b, 0.0, 1.0);
		pos[6]=glm::vec4(a, b, c, 1.0);
		pos[7]=glm::vec4(0.0, b, c, 1.0);
		t_coords[0] = glm::vec2( 0.0, 0.0);
		t_coords[1]=glm::vec2( 0.0, 1.0);
		t_coords[2]=glm::vec2( 1.0, 0.0);
		t_coords[3]=glm::vec2( 1.0, 1.0);

		for(int i=0;i<8;i++)
		{
			col[i]=glm::vec4(1,0,0,1.0);
		}
	}

	void gen()
	{
		quad(0,1,2,3);
		quad(5,6,2,1);
		quad(0,4,7,3);
		quad(0,1,5,4);
		quad(3,2,6,7);
		quad(4,5,6,7);
	}

};


class openbox
{
public:
	float a,b,c;
	glm::vec4* pos;
	int idx;
	uint siz;
	glm::vec4* positions;
	glm::vec4* colors;
	glm::vec4 mycol[5];
	int* id;
	int iden;
	glm::vec2* tex_coords;
	glm::vec2* t_coords;

	openbox(float a,float b,float c,glm::vec4 mycol[])
	{
		this->a=a;
		this->b=b;
		this->c=c;
		siz=30;
		idx=0;
		pos=new glm::vec4[8];
		positions=new glm::vec4[30];
		colors=new glm::vec4[30];
		tex_coords=new glm::vec2[30];
		this->id = new int[30];
		t_coords=new glm::vec2[4];
		for(int i=0;i<5;i++)
		{
			this->mycol[i]=mycol[i];
		}
		iden=1;
		initcoord();
		gen();
	}

	openbox(float a,float b,float c, int iden)
	{
		this->a=a;
		this->b=b;
		this->c=c;
		siz=30;
		idx=0;
		pos=new glm::vec4[8];
		positions=new glm::vec4[30];
		colors=new glm::vec4[30];
		tex_coords=new glm::vec2[30];
		this->id = new int[30];
		t_coords=new glm::vec2[4];
		for(int i=0;i<5;i++)
		{
			this->mycol[i]=glm::vec4(1,0,0,1);
		}
		this->iden=iden;
		initcoord();
		gen();
	}

	uint retsiz(void)
	{
		return 16*siz;
	}

	void quad(int a, int b, int c, int d,glm::vec4 col)
	{
	 	colors[idx] = col; positions[idx] = pos[a]; tex_coords[idx]=t_coords[0]; id[idx]= iden; idx++;
	  	colors[idx] = col; positions[idx] = pos[b]; tex_coords[idx]=t_coords[1]; id[idx]= iden; idx++;
	  	colors[idx] = col; positions[idx] = pos[c]; tex_coords[idx]=t_coords[2]; id[idx]= iden; idx++;
	  	colors[idx] = col; positions[idx] = pos[a]; tex_coords[idx]=t_coords[0]; id[idx]= iden; idx++;
	  	colors[idx] = col; positions[idx] = pos[c]; tex_coords[idx]=t_coords[2]; id[idx]= iden; idx++;
	  	colors[idx] = col; positions[idx] = pos[d]; tex_coords[idx]=t_coords[3]; id[idx]= iden; idx++;
	}

	void initcoord()
	{
		pos[4]=glm::vec4(0.0,0.0,0.0, 1.0);
		pos[5]=glm::vec4(a, 0.0, 0.0, 1.0);
		pos[6]=glm::vec4(a, 0.0, c, 1.0);
		pos[7]=glm::vec4(0.0, 0.0, c, 1.0);
		pos[0]=glm::vec4(0.0, b, 0.0, 1.0);
		pos[1]=glm::vec4(a, b, 0.0, 1.0);
		pos[2]=glm::vec4(a, b, c, 1.0);
		pos[3]=glm::vec4(0.0, b, c, 1.0);
		t_coords[0] = glm::vec2( 0.0, 0.0);
		t_coords[1]=glm::vec2( 0.0, 1.0);
		t_coords[2]=glm::vec2( 1.0, 0.0);
		t_coords[3]=glm::vec2( 1.0, 1.0);
	}

	void gen()
	{
		quad(0,1,2,3,mycol[0]);
		quad(5,6,2,1,mycol[1]);
		quad(0,4,7,3,mycol[2]);
		quad(0,1,5,4,mycol[3]);
		quad(3,2,6,7,mycol[4]);
	}

};


class ellipsoid{
public:
	int base,height;
	int points;
	uint siz;
	float a,b,c;
	glm::vec4* pos;
	glm::vec4* col;
	int idx;
	glm::vec4* positions;
	glm::vec4 mycol;
	glm::vec4* colors;
	int t;
	int* id;
	int iden;
	glm::vec2* tex_coords;
	glm::vec2* t_coords;

	ellipsoid(int spherebase,int sphereheight,float at,float bt,float ct, glm::vec4 col)
	{
		idx=0;
		t=2;
		mycol=col;
		base=spherebase;
		height=sphereheight;
		a=at;
		b=bt;
		c=ct;
		this->iden=1;
		points=base*(2*height);
		siz=6*base*(2*(height)-1);
		pos=new glm::vec4[points];
		this->col=new glm::vec4[points];
		positions=new glm::vec4[siz];
		colors=new glm::vec4[siz];
		t_coords=new glm::vec2[points];
		tex_coords=new glm::vec2[siz];
		this->id=new int[siz];
		initcoord();
		gen();
	}
	ellipsoid(int spherebase,int sphereheight,float at,float bt,float ct)
	{
		idx=0;
		t=2;
		mycol=glm::vec4(1,0,0,1);
		base=spherebase;
		height=sphereheight;
		a=at;
		b=bt;
		c=ct;
		this->iden=0;
		points=base*(2*height);
		siz=6*base*(2*(height)-1);
		pos=new glm::vec4[points];
		this->col=new glm::vec4[points];
		positions=new glm::vec4[siz];
		colors=new glm::vec4[siz];
		t_coords=new glm::vec2[points];
		tex_coords=new glm::vec2[siz];
		this->id=new int[siz];
		initcoord();
		gen();
	}
	ellipsoid(int spherebase,int sphereheight,float at,float bt,float ct,glm::vec4 col,int r)
	{
		idx=0;
		t=r;
		mycol=col;
		base=spherebase;
		height=sphereheight;
		a=at;
		b=bt;
		c=ct;
		points=base*(height);
		siz=6*base*(height-1);
		pos=new glm::vec4[points];
		this->col=new glm::vec4[points];
		positions=new glm::vec4[siz];
		colors=new glm::vec4[siz];
		t_coords=new glm::vec2[points];
		tex_coords=new glm::vec2[siz];
		this->iden=1 tex_coord[idx]=t_coordsen=; id[idx]=iden;;
		this->id=new int[siz];
		initcoord();
		gen();
	}
	ellipsoid(int spherebase,int sphereheight,float at,float bt,float ct,int r)
	{
		idx=0;
		t=r;
		mycol=glm::vec4(1,0,0,1);
		base=spherebase;
		height=sphereheight;
		a=at;
		b=bt;
		c=ct;
		points=base*(height);
		siz=6*base*(height-1);
		pos=new glm::vec4[points];
		this->col=new glm::vec4[points];
		positions=new glm::vec4[siz];
		colors=new glm::vec4[siz];
		t_coords=new glm::vec2[points];
		tex_coords=new glm::vec2[siz];
		this->iden=0;
		this->id=new int[siz];
		initcoord();
		gen();
	}

	uint retsiz(void)
	{
		return 16*siz;
	}

	void quad(int a, int b, int c, int d)
	{
		colors[idx] = col[a]; positions[idx] = pos[a]; tex_coord[idx]=t_coords[a]; id[idx]=iden; idx++;
		colors[idx] = col[b]; positions[idx] = pos[b]; tex_coord[idx]=t_coords[b]; id[idx]=iden; idx++;
		colors[idx] = col[c]; positions[idx] = pos[c]; tex_coord[idx]=t_coords[c]; id[idx]=iden; idx++;
		colors[idx] = col[a]; positions[idx] = pos[a]; tex_coord[idx]=t_coords[a]; id[idx]=iden; idx++;
		colors[idx] = col[c]; positions[idx] = pos[c]; tex_coord[idx]=t_coords[c]; id[idx]=iden; idx++;
		colors[idx] = col[d]; positions[idx] = pos[d]; tex_coord[idx]=t_coords[d]; id[idx]=iden; idx++;
	}

	void initcoord(){
		int counter=0;
		for(int i=0;i<t*height;i++){
			for(int j=0;j<base;j++){
				float t1=(height-1-i)/(float)height,t2=j/(float)base;
				
				pos[counter]=glm::vec4(sqrt(1-t1*t1)*sin(2*3.14*t2)*a,
					t1*b,
					sqrt(1-t1*t1)*cos(2*3.14*t2)*c,
					1.0);
				t_coords[counter]=glm::vec2((float)j/base,(float)i/(t*height))
				if(t!=2 && i==height-1){
					col[counter]=glm::vec4(0,0,0,1.0);
				}
				else{
					col[counter]=mycol;
				}
				counter++;
			}
		}
	}

	void gen(){
		for(int i=0;i<t*height-1;i++)
		{
			for(int j=0;j<base;j++)
			{
				int b=i*base+j;
				int a=b+base;
				int c=base*i+(b+1)%base;
				int d=c+base;
				quad(a,b,c,d);
			}
		}
	}

};

class cylinder
{
public:
	int base;
	int height;
	int points;
	glm::vec4* pos;
	glm::vec4* col;
	int idx;
	uint siz;
	float b1,b2;
	float h;
	glm::vec4* positions;
	glm::vec4* colors;
	glm::vec4 mycol;
	int* id;
	int iden;
	glm::vec2* tex_coords;
	glm::vec2* t_coords;
	
	cylinder(int cylinbase,int cylinheight,float base1,float base2,float ht, glm::vec4 col)
	{
		base=cylinbase;
		mycol=col;
		height=cylinheight;
		b1=base1;
		b2=base2;
		h=ht;
		points=base*(height+1)+2;
		pos=new glm::vec4[points];
		this->col=new glm::vec4[points];
		idx=0;
		siz=6*base*(height)+6*base;
		positions=new glm::vec4[siz];
		colors=new glm::vec4[siz];
		tex_coords=new glm::vec2[siz];
		t_coords=new glm::vec2[points];
		this->id=new int[siz];
		iden=1;
		initcoord();
		pos[base*(height+1)]=glm::vec4(0.0,0,0,1);
		this->col[base*(height+1)]=mycol;
		pos[base*(height+1)+1]=glm::vec4(0,h,0,1);
		this->col[base*(height+1)+1]=mycol;
		gen();
	}
	cylinder(int cylinbase,int cylinheight,float base1,float base2,float ht, int iden, glm::vec4 col=glm::vec4(1,0,0,1))
	{
		base=cylinbase;
		mycol=col;
		height=cylinheight;
		b1=base1;
		b2=base2;
		h=ht;
		points=base*(height+1)+2;
		pos=new glm::vec4[points];
		this->col=new glm::vec4[points];
		idx=0;
		siz=6*base*(height)+6*base;
		positions=new glm::vec4[siz];
		colors=new glm::vec4[siz];
		tex_coords=new glm::vec2[siz];
		t_coords=new glm::vec2[points];
		this->id=new int[siz];
		this->iden=iden;
		initcoord();
		pos[base*(height+1)]=glm::vec4(0.0,0,0,1);
		this->col[base*(height+1)]=mycol;
		pos[base*(height+1)+1]=glm::vec4(0,h,0,1);
		this->col[base*(height+1)+1]=mycol;
		gen();
	}

	uint retsiz(void)
	{
		return 16*siz;
	}

	void quad(int a, int b, int c, int d)
	{
		colors[idx] = col[a]; positions[idx] = pos[a]; tex_coords[idx] = t_coords[a]; id[idx]=iden; idx++;
		colors[idx] = col[b]; positions[idx] = pos[b]; tex_coords[idx] = t_coords[b]; id[idx]=iden; idx++;
		colors[idx] = col[c]; positions[idx] = pos[c]; tex_coords[idx] = t_coords[c]; id[idx]=iden; idx++;
		colors[idx] = col[a]; positions[idx] = pos[a]; tex_coords[idx] = t_coords[a]; id[idx]=iden; idx++;
		colors[idx] = col[c]; positions[idx] = pos[c]; tex_coords[idx] = t_coords[c]; id[idx]=iden; idx++;
		colors[idx] = col[d]; positions[idx] = pos[d]; tex_coords[idx] = t_coords[d]; id[idx]=iden; idx++;
	}

	void initcoord(void)
	{
		int counter=0;
		for(int i=0;i<height+1;i++){
			float t=(i*b2+(height-i)*b1)/(float)height;
			for(int j=0;j<base;j++){
				pos[counter]=glm::vec4(t*sin(2*3.14*j/(float)base),
					h*i/(float)height,
					t*cos(2*3.14*j/(float)base),
					1.0);
				t_coords[counter]=glm::vec2((float)j/base,(float)i/height);
				if(i==0 || i==height){
					col[counter]=glm::vec4(0,0,0,1);
				}else{
					col[counter]=mycol;
				}
				counter++;
			}
		}
	}

	void gen(void)
	{
		for(int i=0;i<height;i++){
			for(int j=0;j<base;j++)
			{
				int b=i*base+j;
				int a=b+base;
				int c= base*i + (b+1)%base;
				int d=c+base;
				quad(a,b,c,d);
			}
		}
		for(int j=0;j<base;j+=2){
			quad(j,(j+1)%base,(j+2)%base,base*(height+1));
			int t=height*base-1;
			quad(t+j,t+(j+1)%base,t+(j+2)%base,base*(height+1)+1);
		}
	}

};