/*
  CSX75 Tutorial 3

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by - 
               Harshavardhan Kode
*/


#include "shapes.cpp"
#include <iostream>
#include <cmath>
#include "hierarchical_modelling.hpp"
#include "texture.hpp"


GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 view_matrix;
GLuint vao,vbo;

glm::mat4 ModelViewMatrix;

GLuint normalMatrix;
GLuint viewMatrix;
GLuint uModelViewMatrix;

int filenumber=0;

bool mylight1;
bool mylight2;

void createman(float,float);
glm::vec3 get_Bezier(double);
void change_state(double);
void capture_frame(unsigned int);

//-----------------------------------------------------------------


void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("vshader.glsl");
  std::string fragment_shader_file("fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  vNormal = glGetAttribLocation( shaderProgram, "vNormal" );
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" ); 

  vid= glGetUniformLocation( shaderProgram, "vid" ); 
  light1= glGetUniformLocation( shaderProgram, "light1" ); 
  light2= glGetUniformLocation( shaderProgram, "light2" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
  normalMatrix = glGetUniformLocation( shaderProgram, "normalMatrix");


  glm::vec4 skincol=glm::vec4(255.0/255,205.0/255,148.0/255,1);
  glm::vec4 red=glm::vec4(1,0.05,0.05,1);
  glm::vec4 yellow=glm::vec4(1,215.0/255,0,1);
  glm::vec4 blue=glm::vec4(0.05,0.05,1,1);
  glm::vec4 white=glm::vec4(0.5,0.3,0.7,1);



  center = new csX75::HNode(NULL,0);

  int scale=20;

  int shift=scale/2;
  rectangle rect(scale,0,glm::vec4(1,0,1,1));

  front = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.normals,"images/walldoor.bmp",256,148);

  front->change_parameters(-shift,-shift,shift,0,0,0);

  back = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.normals,"images/wallwin2.bmp",256,223);

  back->change_parameters(-shift,-shift,-shift,0,0,0);

  left = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.normals,"images/wall.bmp",256,174);

  left->change_parameters(-shift,-shift,-shift,0,-90,0);

  right = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.normals,"images/wall.bmp",256,174);

  right->change_parameters(shift,-shift,-shift,0,-90,0);

  bottom = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.normals,"images/floor.bmp",256,170);

  bottom->change_parameters(-shift,-shift,-shift,90,0,0);

  top = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.normals,"images/roof.bmp",256,158);

  top->change_parameters(-shift,shift,-shift,90,0,0);


/////////////////////Chair1///////////////////

  cuboid mychair(2,2,2,0);
  cylinder chairlegs(10,20,1,1,5,red);
  chairbase1= new csX75::HNode(center,36,mychair.positions,mychair.colors,mychair.normals);
  chairbase1->change_parameters(6,-5,-4,0,0,0);

  chairsupport1 = new csX75::HNode(chairbase1,36,mychair.positions,mychair.colors,mychair.normals);
  chairsupport1->change_parameters(0,0,0,90,0,0);
  chleg11= new csX75::HNode(chairbase1,chairlegs.siz,chairlegs.positions,chairlegs.colors,
    chairlegs.normals);

  chleg11->change_parameters(0,-4.8,0,0,0,0);

  chleg12=new csX75::HNode(chairbase1,chairlegs.siz,chairlegs.positions,chairlegs.colors,
    chairlegs.normals);

  chleg12->change_parameters(2,-4.8,0,0,0,0);

  chleg13=new csX75::HNode(chairbase1,chairlegs.siz,chairlegs.positions,chairlegs.colors,
    chairlegs.normals);

  chleg13->change_parameters(0,-4.8,2,0,0,0);

  chleg14=new csX75::HNode(chairbase1,chairlegs.siz,chairlegs.positions,chairlegs.colors,
    chairlegs.normals);

  chleg14->change_parameters(2,-4.8,2,0,0,0);


/////////////////////Chair2////////////

  chairbase2= new csX75::HNode(center,36,mychair.positions,mychair.colors,mychair.normals);
  chairbase2->change_parameters(-8,-5,-4,0,0,0);

  chairsupport2 = new csX75::HNode(chairbase2,36,mychair.positions,mychair.colors,mychair.normals);
  chairsupport2->change_parameters(0,0,0,90,0,0);
  chleg21= new csX75::HNode(chairbase2,chairlegs.siz,chairlegs.positions,chairlegs.colors,
    chairlegs.normals);

  chleg21->change_parameters(0,-4.8,0,0,0,0);

  chleg22=new csX75::HNode(chairbase2,chairlegs.siz,chairlegs.positions,chairlegs.colors,
    chairlegs.normals);

  chleg22->change_parameters(2,-4.8,0,0,0,0);

  chleg23=new csX75::HNode(chairbase2,chairlegs.siz,chairlegs.positions,chairlegs.colors,
    chairlegs.normals);

  chleg23->change_parameters(0,-4.8,2,0,0,0);

  chleg24=new csX75::HNode(chairbase2,chairlegs.siz,chairlegs.positions,chairlegs.colors,
    chairlegs.normals);

  chleg24->change_parameters(2,-4.8,2,0,0,0);

////////////////////////////////////////////////


//////////////////Random box///////////////////
  cuboid smallbox(2,2,2,0);
  cuboid largebox(4,4,4,0);  

  smbox1= new csX75::HNode(center,36,smallbox.positions,smallbox.colors,smallbox.normals);
  smbox1->change_parameters(4,-10,-10,0,0,0);

  smbox2= new csX75::HNode(center,36,largebox.positions,largebox.colors,largebox.normals);
  smbox2->change_parameters(-6,-10,-10,0,0,0);

///////////////////Lighting////////////////

  float lightscale=1;
  cylinder fix(10,20,0.3*lightscale,0.3*lightscale,2*lightscale,skincol);
  ellipsoid light(10,20,0.5*lightscale,0.5*lightscale,0.5*lightscale,skincol);

  fixture= new csX75::HNode(center,fix.siz,fix.positions,fix.colors,fix.normals);
  fixture->change_parameters(shift,0.5*shift,0*shift,0,0,90);

  wall_light= new csX75::HNode(fixture,light.siz,light.positions,light.colors,
    light.tex_coords,light.normals,"images/all.bmp",256,256);
  wall_light->islight=1;
  wall_light->change_parameters(0*lightscale,2*lightscale,0*lightscale,0,0,0);


///////////////////////////////////////////


  int table_sc=scale/10;

  cuboid tab_top(4*table_sc,0.2*table_sc,4*table_sc,1);
  table_top= new csX75::HNode(center,36,tab_top.positions,tab_top.colors,
  	tab_top.tex_coords,tab_top.normals,"images/table_top.bmp",256,162);
  table_top->change_parameters(-2*table_sc,-2*table_sc,-2*table_sc,0,0,0);

  cylinder tab_legs(20,20,0.3*table_sc,0.2*table_sc,3.2*table_sc,0);
  
  tab_leg1=new csX75::HNode(table_top,tab_legs.siz,tab_legs.positions,tab_legs.colors,
  	tab_legs.tex_coords,tab_legs.normals,"images/furniture.bmp",256,192);
  tab_leg1->change_parameters(0,-3*table_sc,0,-0,0,0);

  tab_leg2=new csX75::HNode(table_top,tab_legs.siz,tab_legs.positions,tab_legs.colors,
  	tab_legs.tex_coords,tab_legs.normals,"images/furniture.bmp",256,192);
  tab_leg2->change_parameters(4*table_sc,-3*table_sc,0*table_sc,0,0,0);

  tab_leg3=new csX75::HNode(table_top,tab_legs.siz,tab_legs.positions,tab_legs.colors,
  	tab_legs.tex_coords,tab_legs.normals,"images/furniture.bmp",256,192);
  tab_leg3->change_parameters(0*table_sc,-3*table_sc,4*table_sc,0,0,0);

  tab_leg4=new csX75::HNode(table_top,tab_legs.siz,tab_legs.positions,tab_legs.colors,
  	tab_legs.tex_coords,tab_legs.normals,"images/furniture.bmp",256,192);
  tab_leg4->change_parameters(4*table_sc,-3*table_sc,4*table_sc,0,0,0);


//////////////////////Lighting////////////////

  lampstand= new csX75::HNode(table_top,fix.siz,fix.positions,fix.colors,fix.normals);
  lampstand->change_parameters(0.5*table_sc,0.2*table_sc,2*table_sc,0,0,0);

  lamp_light= new csX75::HNode(lampstand,light.siz,light.positions,light.colors,
    light.tex_coords,light.normals,"images/all.bmp",256,256);
  lamp_light->islight=2;
  lamp_light->change_parameters(0*lightscale,2*lightscale,0*lightscale,0,0,0);
/////////////////////////////////////////////

  glm::vec4 arr[5]={skincol,red,blue,yellow,white};


  int scalebox= 1;

  openbox box(4*scalebox,2*scalebox,4*scalebox,arr);
  openbox lid(4*scalebox,0.3*scalebox,4*scalebox,arr);

  box1 = new csX75::HNode(table_top,box.siz,box.positions,box.colors
  	,box.normals);
  box1->change_parameters(1.0*table_sc,2.0*scalebox+0.2*table_sc,4.0*scalebox+1.0*table_sc,0.0,180.0,180.0);
  box2 = new csX75::HNode(box1,lid.siz,lid.positions,lid.colors,lid.normals);

  box2->change_parameters(4.0*scalebox,0.0,0.0,0.0,0.0,180.0);


  float body_sc=0.2*scalebox;
  cylinder torso(10,20,1.05*body_sc,1.2*body_sc,2.3*body_sc,yellow);
  // //note that the buffers are initialized in the respective constructors
 
  node1_torso = new csX75::HNode(box1,torso.siz,torso.positions,torso.colors,torso.normals);
  node1_torso->change_parameters(1*scalebox,0.65*scalebox,2.0*scalebox,0.0,-180.0,-180.0);

  cylinder neck(10,20,0.4*body_sc,0.3*body_sc,0.7*body_sc,skincol);

  node2_neck = new csX75::HNode(node1_torso,neck.siz,neck.positions,neck.colors,
  	neck.normals);
  node2_neck->change_parameters(0.0,2.3*body_sc,0.0,0.0,0.0,0.0);
  
  ellipsoid head(10,20,1*body_sc,1*body_sc,1*body_sc,skincol);

  node3_head = new csX75::HNode(node2_neck,head.siz,head.positions,head.colors,
  	head.normals);
  node3_head->change_parameters(0.0*body_sc,1.4*body_sc,0.0*body_sc,0.0,0.0,0.0);

  cylinder limb(10,20,0.25*body_sc,0.2*body_sc,2*body_sc,skincol);
  cylinder limblower(10,20,0.2*body_sc,0.15*body_sc,2*body_sc,skincol);
  cylinder thigh(10,20,0.35*body_sc,0.25*body_sc,2.5*body_sc,red);
  cylinder leglower(10,20,0.28*body_sc,0.2*body_sc,2.5*body_sc,skincol);
  cylinder tummy(10,20,1.05*body_sc,1.1*body_sc,0.7*body_sc,skincol);

  node4_leftarmu = new csX75::HNode(node1_torso,limb.siz,limb.positions,limb.colors,
  	limb.normals);
  node4_leftarmu->change_parameters((1.1-0.1*0.25/(2*2.3))*body_sc,
  	(2.3-0.25/2)*body_sc,0.0*body_sc,0.0,0.0,-90.0);

  node5_leftarml = new csX75::HNode(node4_leftarmu,limblower.siz,limblower.positions,limblower.colors,
  	limblower.normals);
  node5_leftarml->change_parameters(0.0*body_sc,2.0*body_sc,0.0*body_sc,0.0,0.0,90.0);

  node6_rightarmu = new csX75::HNode(node1_torso,limb.siz,limb.positions,limb.colors,
  	limb.normals);
  node6_rightarmu->change_parameters((-1.1+0.1*0.25/(2*2.3))*body_sc,(2.3-0.25/2)*body_sc,0.0*body_sc,0.0,0.0,90.0);

  node7_rightarml = new csX75::HNode(node6_rightarmu,limblower.siz,limblower.positions,limblower.colors,
  	limblower.normals);
  node7_rightarml->change_parameters(0.0*body_sc,2.0*body_sc,0.0*body_sc,0.0,0.0,90.0);

  node12_tummy = new csX75::HNode(node1_torso,tummy.siz,tummy.positions,tummy.colors,
  	tummy.normals);
  node12_tummy->change_parameters(0.0*body_sc,0.0*body_sc,0.0*body_sc,0.0,0.0,180.0);

  node8_leftthigh = new csX75::HNode(node12_tummy,thigh.siz,thigh.positions,thigh.colors,
  	thigh.normals);
  node8_leftthigh->change_parameters((-1.1+0.35/2)*body_sc,0.7*body_sc,0.0*body_sc,0.0,0.0,0.0);

  node9_leftfoot = new csX75::HNode(node8_leftthigh,leglower.siz,leglower.positions,leglower.colors,
  	leglower.normals);
  node9_leftfoot->change_parameters(0.0*body_sc,2.5*body_sc,0.0*body_sc,0.0,0.0,0.0);

  node10_rightthigh = new csX75::HNode(node12_tummy,thigh.siz,thigh.positions,thigh.colors,
  	thigh.normals);
  node10_rightthigh->change_parameters((1.1-0.35/2)*body_sc,0.7*body_sc,0.0*body_sc,0.0,0.0,0.0);

  node11_rightfoot = new csX75::HNode(node10_rightthigh,leglower.siz,leglower.positions,leglower.colors,
  	leglower.normals);
  node11_rightfoot->change_parameters(0.0*body_sc,2.5*body_sc,0.0*body_sc,0.0,0.0,0.0);

  ellipsoid skirt(10,20,3*body_sc,4.8*body_sc,3*body_sc,blue,1);

  node13_skirt = new csX75::HNode(node12_tummy,skirt.siz,skirt.positions,skirt.colors,
  	skirt.normals);
  node13_skirt->change_parameters(0.0*body_sc,5.2*body_sc,0.0*body_sc,0.0,0.0,180.0);

  glm::vec4 brown=glm::vec4(139.0/255,69.0/255,19.0/255,1);
  cylinder shoe=cylinder(10,20,0.3*body_sc,0.2*body_sc,1*body_sc,brown);
  node14_shoe=new csX75::HNode(node9_leftfoot,shoe.siz,shoe.positions,shoe.colors,
  	shoe.normals);
  node14_shoe->change_parameters(0.0*body_sc,(2.5+0.1)*body_sc,-0.23*body_sc,-90.0,0.0,180.0);

  node15_shoe=new csX75::HNode(node11_rightfoot,shoe.siz,shoe.positions,shoe.colors,
  	shoe.normals);
  node15_shoe->change_parameters(0.0*body_sc,(2.5+0.1)*body_sc,-0.23*body_sc,-90.0,0.0,180.0);

  // createman(0.8);
  createman(body_sc,scalebox);
  curr_node=box2;

  // curr_node = node1_torso;

}

void createman(float body_sc,float scalebox)
{
	glm::vec4 skincol=glm::vec4(255.0/255,205.0/255,148.0/255,1);
	glm::vec4 red=glm::vec4(1,0.05,0.05,1);
	glm::vec4 yellow=glm::vec4(1,215.0/255,0,1);
	glm::vec4 blue=glm::vec4(0.05,0.05,1,1);
	glm::vec4 brown=glm::vec4(139.0/255,69.0/255,19.0/255,1);
  	

  cylinder shoe=cylinder(10,20,0.3*body_sc,0.2*body_sc,1*body_sc,brown);

	cylinder mtorso(10,20,1.05*body_sc,1.2*body_sc,2.3*body_sc,yellow);
  //note that the buffers are initialized in the respective constructors
 
  man1_mtorso = new csX75::HNode(box1,mtorso.siz,mtorso.positions,mtorso.colors,
  	mtorso.normals);
  man1_mtorso->change_parameters(3*scalebox,0.65*scalebox,2.0*scalebox,0.0,-180.0,-180.0);

  cylinder mneck(10,20,0.4*body_sc,0.3*body_sc,0.7*body_sc,skincol);

  man2_mneck = new csX75::HNode(man1_mtorso,mneck.siz,mneck.positions,mneck.colors,
  	mneck.normals);
  man2_mneck->change_parameters(0.0*body_sc,2.3*body_sc,0.0*body_sc,0.0,0.0,0.0);
  
  ellipsoid mhead(10,20,1*body_sc,1*body_sc,1*body_sc,skincol);

  man3_mhead = new csX75::HNode(man2_mneck,mhead.siz,mhead.positions,mhead.colors,
  	mhead.normals);
  man3_mhead->change_parameters(0.0*body_sc,1.4*body_sc,0.0*body_sc,0.0,0.0,0.0);

  cylinder mlimb(10,20,0.25*body_sc,0.2*body_sc,2*body_sc,skincol);
  cylinder mlimblower(10,20*body_sc,0.2,0.15*body_sc,2*body_sc,skincol);
  cylinder mthigh(10,20,0.35*body_sc,0.25*body_sc,2.5*body_sc,red);
  cylinder mleglower(10,20,0.28*body_sc,0.2*body_sc,2.5*body_sc,skincol);
  cylinder mtummy(10,20,1.05*body_sc,1.1*body_sc,0.7*body_sc,yellow);

  man4_leftarmu = new csX75::HNode(man1_mtorso,mlimb.siz,mlimb.positions,mlimb.colors,
  	mlimb.normals);
  man4_leftarmu->change_parameters((1.1-0.1*0.25/(2*2.3))*body_sc,(2.3-0.25/2)*body_sc,0.0*body_sc,0.0,0.0,-90.0);

  man5_leftarml = new csX75::HNode(man4_leftarmu,mlimblower.siz,mlimblower.positions,mlimblower.colors,
  	mlimblower.normals);
  man5_leftarml->change_parameters(0.0*body_sc,2.0*body_sc,0.0*body_sc,0.0,0.0,-90.0);

  man6_rightarmu = new csX75::HNode(man1_mtorso,mlimb.siz,mlimb.positions,mlimb.colors,
  	mlimb.normals);
  man6_rightarmu->change_parameters((-1.1+0.1*0.25/(2*2.3))*body_sc,(2.3-0.25/2)*body_sc,0.0*body_sc,0.0,0.0,90.0);

  man7_rightarml = new csX75::HNode(man6_rightarmu,mlimblower.siz,mlimblower.positions,mlimblower.colors,
  	mlimblower.normals);
  man7_rightarml->change_parameters(0.0*body_sc,2.0*body_sc,0.0*body_sc,0.0,0.0,-90.0);

  man12_mtummy = new csX75::HNode(man1_mtorso,mtummy.siz,mtummy.positions,mtummy.colors,
  	mtummy.normals);
  man12_mtummy->change_parameters(0.0*body_sc,0.0*body_sc,0.0*body_sc,0.0,0.0,180.0);

  man8_leftmthigh = new csX75::HNode(man12_mtummy,mthigh.siz,mthigh.positions,mthigh.colors,
  	mthigh.normals);
  man8_leftmthigh->change_parameters((-1.1+0.35/2)*body_sc,0.7*body_sc,0.0*body_sc,0.0,0.0,0.0);

  man9_leftfoot = new csX75::HNode(man8_leftmthigh,mleglower.siz,mleglower.positions,mleglower.colors,
  	mleglower.normals);
  man9_leftfoot->change_parameters(0.0*body_sc,2.5*body_sc,0.0*body_sc,0.0,0.0,0.0);

  man10_rightmthigh = new csX75::HNode(man12_mtummy,mthigh.siz,mthigh.positions,mthigh.colors,
  	mthigh.normals);
  man10_rightmthigh->change_parameters((1.1-0.35/2)*body_sc,0.7*body_sc,0.0*body_sc,0.0,0.0,0.0);

  man11_rightfoot = new csX75::HNode(man10_rightmthigh,mleglower.siz,mleglower.positions,mleglower.colors,
  	mleglower.normals);
  man11_rightfoot->change_parameters(0.0*body_sc,2.5*body_sc,0.0*body_sc,0.0,0.0,0.0);

  man14_shoe=new csX75::HNode(man9_leftfoot,shoe.siz,shoe.positions,shoe.colors,
  	shoe.normals);
  man14_shoe->change_parameters(0.0*body_sc,(2.5+0.1)*body_sc,-0.23*body_sc,-90.0,0.0,180.0);

  man15_shoe=new csX75::HNode(man11_rightfoot,shoe.siz,shoe.positions,shoe.colors,
  	shoe.normals);
  man15_shoe->change_parameters(0.0*body_sc,(2.5+0.1)*body_sc,-0.23*body_sc,-90.0,0.0,180.0);

}

void capture_frame(unsigned int framenum)
{
  //global pointer float *pRGB
  unsigned char *pRGB = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];


  // set the framebuffer to read
  //default for double buffered
  glReadBuffer(GL_BACK);

  glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment

  glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
  char filename[200];
  sprintf(filename,"frame_%04d.ppm",framenum);
  std::ofstream out(filename, std::ios::out);
  out<<"P6"<<std::endl;
  out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
  out.write(reinterpret_cast<char const *>(pRGB), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
  out.close();

  //function to store pRGB in a file named count
  delete pRGB;
}


void renderGL(void)
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  // //Creating the lookat and the up vectors for the camera
  glm::vec3 nor=glm::vec3(0.0);

  if(start==1){
    start=2;
    last_time=glfwGetTime();
    cam_pos=get_Bezier(counter);
  }
  if(start==2 && counter>=1){
  	start=0;
  	counter=0;
  	for(int i=0;i<number;i++){
  		delete display_points[i];
  	}
  	number=0;
  }
  else if(start==2 && counter<1){
  	double tim=glfwGetTime();
  	if(tim-last_time>fps_cam_time){
	  	counter+=delta_t;
      cam_pos=get_Bezier(counter);
	  	c_xpos=cam_pos[0];
	  	c_ypos=cam_pos[1];
	  	c_zpos=cam_pos[2];
	  	
	  	last_time=tim;
	  }
	  nor=glm::vec3(c_box)-cam_pos;
  }
  if(start==3){
  	start=4;
  	key_file.open("keyframes.txt",std::ios::in | std::ios::binary);
  	last_time=glfwGetTime();
  	if(key_file.read((char*)&prev_state,sizeof(prev_state))){
  		if(key_file.read((char*)&fut_state,sizeof(fut_state))){
  			// std::cout<<"helo";
  			counter=1;
  			change_state(counter);
        capture_frame(filenumber);
        filenumber++;
  			counter++;
  		}
  		else{
  			start=0;
  			key_file.close();
  		}
  	}
  	else{
  		start=0;
  		key_file.close();
  	}
  }
  else if(start==4){
  	double tim=glfwGetTime();
  	if(tim-last_time>fps_time){
  		if(counter<num_frames+1){
  			change_state(counter);
        capture_frame(filenumber);
        filenumber++;
  			last_time=tim;
  			counter++;
  		}
  		else{
  			prev_state=fut_state;
	  		if(key_file.read((char*)&fut_state,sizeof(fut_state))){
	  			counter=1;
 	 			  change_state(counter);
          capture_frame(counter);
          filenumber++;
	  			counter++;
	  			last_time=tim;
	  		}
	  		else{
	  			key_file.close();
          filenumber=0;
	  			counter=0;
	  			start=0;
	  		}
  		}
  	}
  }

  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  

  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),nor,glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    projection_matrix = glm::frustum(-5.0, 5.0, -5.0, 5.0, 2.0, 40.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-5.0, 5.0, -5.0, 5.0, 0.0, 40.0);

  view_matrix = projection_matrix*lookat_matrix;

  ModelViewMatrix = (glm::inverse(lookat_matrix));

  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  matrixStack.push_back(view_matrix);
  center->render_tree();

}


void change_state(double counter){
	// std::cout<<mylight1<<" "<<mylight2<<std::endl;
	mylight2=fut_state.light2;
	mylight1=fut_state.light1;
	csX75::state a;
	for(int i=0;i<3;i++){
		a.man.torso[i]=prev_state.man.torso[i]*(num_frames-counter)/(float)num_frames+fut_state.man.torso[i]*counter/(float)num_frames;
		a.man.neck[i]=prev_state.man.neck[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.man.neck[i];
		a.man.leftlowerarm[i]=prev_state.man.leftlowerarm[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.man.leftlowerarm[i];
		a.man.leftlowerleg[i]=prev_state.man.leftlowerleg[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.man.leftlowerleg[i];
		a.man.rightlowerarm[i]=prev_state.man.rightlowerarm[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.man.rightlowerarm[i];
		a.man.rightlowerleg[i]=prev_state.man.rightlowerleg[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.man.rightlowerleg[i];
		a.woman.torso[i]=prev_state.woman.torso[i]*(num_frames-counter)/(float)num_frames+fut_state.woman.torso[i]*counter/(float)num_frames;
		a.woman.neck[i]=prev_state.woman.neck[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.woman.neck[i];
		a.woman.leftlowerarm[i]=prev_state.woman.leftlowerarm[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.woman.leftlowerarm[i];
		a.woman.leftlowerleg[i]=prev_state.woman.leftlowerleg[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.woman.leftlowerleg[i];
		a.woman.rightlowerarm[i]=prev_state.woman.rightlowerarm[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.woman.rightlowerarm[i];
		a.woman.rightlowerleg[i]=prev_state.woman.rightlowerleg[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.woman.rightlowerleg[i];
		
		a.box_lid[i]=prev_state.box_lid[i]*(num_frames-counter)/(float)num_frames+counter/(float)num_frames*fut_state.box_lid[i];
	}

	man1_mtorso->set_rotation(a.man.torso);
  	man2_mneck->set_rotation(a.man.neck);
  	man5_leftarml->set_rotation(a.man.leftlowerarm);
  	man7_rightarml->set_rotation(a.man.rightlowerarm);
  	man9_leftfoot->set_rotation(a.man.leftlowerleg);
  	man11_rightfoot->set_rotation(a.man.rightlowerleg);

  	node1_torso->set_rotation(a.woman.torso);
  	node2_neck->set_rotation(a.woman.neck);
  	node5_leftarml->set_rotation(a.woman.leftlowerarm);
  	node7_rightarml->set_rotation(a.woman.rightlowerarm);
  	node9_leftfoot->set_rotation(a.woman.leftlowerleg);
  	node11_rightfoot->set_rotation(a.woman.rightlowerleg);

  	box2->set_rotation(a.box_lid);
}


glm::vec3 get_Bezier(double x){
	glm::vec3 res=glm::vec3(0,0,0);
	int n=number+2;
	double tot=pow(x,n-1);
	res=glm::vec3(c_box_look)*glm::vec3(tot);
	for(int i=0;i<number;i++){
		tot=(tot/x)*(1-x)*(n-1-(float)i)/(i+1);
		res+=control_points[i]*glm::vec3(tot);
	}
	tot=(tot/x)*(1-x)/(n-1);
	res+=glm::vec3(c_door)*glm::vec3(tot);
	
	return res;
}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();  

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

