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

glm::mat4 model_matrix;
glm::mat4 view_matrix;
GLuint vao,vbo;

glm::mat3 ModelViewMatrix;


GLuint uModelViewMatrix;
int scale=10;
void createman(float,float);

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
  vid= glGetUniformLocation( shaderProgram, "vid" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" ); 

  glm::vec4 skincol=glm::vec4(255.0/255,205.0/255,148.0/255,1);
  glm::vec4 red=glm::vec4(1,0.05,0.05,1);
  glm::vec4 yellow=glm::vec4(1,215.0/255,0,1);
  glm::vec4 blue=glm::vec4(0.05,0.05,1,1);
  glm::vec4 white=glm::vec4(0.5,0.3,0.7,1);


  // GLuint tex=LoadTexture("images/all1.bmp",256,256);
  // glBindTexture(GL_TEXTURE_2D, tex);


  center = new csX75::HNode(NULL,0);

  cuboid room(10,10,10,1);

  // cuboid room(10,10,10,1);
  int shift=scale/2;
  rectangle rect(scale,0,glm::vec4(1,0,1,1));

  front = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.id,6*16,6*16,6*8,6*4,"images/walldoor.bmp",1300,752);

  front->change_parameters(-shift,-shift,shift,0,0,0);

  back = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.id,6*16,6*16,6*8,6*4,"images/wallwin2.bmp",1156,1006);

  back->change_parameters(-shift,-shift,-shift,0,0,0);

  left = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.id,6*16,6*16,6*8,6*4,"images/all.bmp",256,256);

  left->change_parameters(-shift,-shift,-shift,0,-90,0);

  right = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.id,6*16,6*16,6*8,6*4,"images/all.bmp",256,256);

  right->change_parameters(shift,-shift,-shift,0,-90,0);

  bottom = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.id,6*16,6*16,6*8,6*4,"images/all1.bmp",256,256);

  bottom->change_parameters(-shift,-shift,-shift,90,0,0);

  top = new csX75::HNode(center,6,rect.positions,
    rect.colors,rect.tex_coords,rect.id,6*16,6*16,6*8,6*4,"images/all1.bmp",256,256);

  top->change_parameters(-shift,shift,-shift,90,0,0);

  // myroom = new csX75::HNode(center, 36,room.positions,room.colors,
  //   room.tex_coords,room.id,36*16,36*16,36*8,36*4);
  // myroom->change_parameters(-5,-5,-5,0,0,0);
  // curr_node=myroom;
  curr_node = center;

  int table_sc=1;

  cuboid tab_top(2*table_sc,0.2*table_sc,4*table_sc,0);
  table_top= new csX75::HNode(center,36,tab_top.positions,tab_top.colors,
  	tab_top.tex_coords,tab_top.id,tab_top.retsiz(),tab_top.retsiz(),tab_top.retsiz()/2,
  	tab_top.retsiz()/4,"images/all1.bmp",256,256);
  table_top->change_parameters(0*table_sc,-2*table_sc,0*table_sc,0,0,0);

  cylinder tab_legs(20,20,0.3*table_sc,0.2*table_sc,3.2*table_sc,0);
  
  tab_leg1=new csX75::HNode(table_top,tab_legs.siz,tab_legs.positions,tab_legs.colors,
  	tab_legs.tex_coords,tab_legs.id,tab_legs.retsiz(),tab_legs.retsiz(),tab_legs.retsiz()/2,
  	tab_legs.retsiz()/4,"images/all1.bmp",256,256);
  tab_leg1->change_parameters(0,-3*table_sc,0,-0,0,0);

  tab_leg2=new csX75::HNode(table_top,tab_legs.siz,tab_legs.positions,tab_legs.colors,
  	tab_legs.tex_coords,tab_legs.id,tab_legs.retsiz(),tab_legs.retsiz(),tab_legs.retsiz()/2,
  	tab_legs.retsiz()/4,"images/all1.bmp",256,256);
  tab_leg2->change_parameters(2*table_sc,-3*table_sc,0*table_sc,0,0,0);

  tab_leg3=new csX75::HNode(table_top,tab_legs.siz,tab_legs.positions,tab_legs.colors,
  	tab_legs.tex_coords,tab_legs.id,tab_legs.retsiz(),tab_legs.retsiz(),tab_legs.retsiz()/2,
  	tab_legs.retsiz()/4,"images/all1.bmp",256,256);
  tab_leg3->change_parameters(0*table_sc,-3*table_sc,4*table_sc,0,0,0);

  tab_leg4=new csX75::HNode(table_top,tab_legs.siz,tab_legs.positions,tab_legs.colors,
  	tab_legs.tex_coords,tab_legs.id,tab_legs.retsiz(),tab_legs.retsiz(),tab_legs.retsiz()/2,
  	tab_legs.retsiz()/4,"images/all1.bmp",256,256);
  tab_leg4->change_parameters(2*table_sc,-3*table_sc,4*table_sc,0,0,0);


  // cylinder legs(20,20,2,2,10,skincol);



  // glEnableVertexAttribArray( vColor );
  // glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(36*16));

  glm::vec4 arr[5]={skincol,red,blue,yellow,white};


  int scalebox= 1;

  openbox box(4*scalebox,2*scalebox,4*scalebox,arr);
  openbox lid(4*scalebox,0.3*scalebox,4*scalebox,arr);

  // centroid_box = new csX75::HNode(table_top,0);
  // centroid_box->change_parameters(0.6*scalebox,0.2*table_sc+5*scalebox,0,0,0,0);
  box1 = new csX75::HNode(table_top,box.siz,box.positions,box.colors
  	,box.id, box.retsiz(),box.retsiz(), box.retsiz()/4);
  box1->change_parameters(-2.0*scalebox,2.0*scalebox+0.2*table_sc,2.0*scalebox,0.0,180.0,180.0);
  box2 = new csX75::HNode(box1,lid.siz,lid.positions,lid.colors,lid.id,lid.retsiz(),
  	lid.retsiz(),lid.retsiz()/4);

  box2->change_parameters(4.0*scalebox,0.0,0.0,0.0,0.0,180.0);


  float body_sc=0.2*scalebox;
  cylinder torso(10,20,1.05*body_sc,1.2*body_sc,2.3*body_sc,yellow);
  // //note that the buffers are initialized in the respective constructors
 
  node1_torso = new csX75::HNode(box1,torso.siz,torso.positions,torso.colors,torso.id,
  	torso.retsiz(),torso.retsiz(),torso.retsiz()/4);
  node1_torso->change_parameters(1*scalebox,0.65*scalebox,2.0*scalebox,0.0,-180.0,-180.0);

  cylinder neck(10,20,0.4*body_sc,0.3*body_sc,0.7*body_sc,skincol);

  node2_neck = new csX75::HNode(node1_torso,neck.siz,neck.positions,neck.colors,
  	neck.id,neck.retsiz(),neck.retsiz(),neck.retsiz()/4);
  node2_neck->change_parameters(0.0,2.3*body_sc,0.0,0.0,0.0,0.0);
  
  ellipsoid head(10,20,1*body_sc,1*body_sc,1*body_sc,skincol);

  node3_head = new csX75::HNode(node2_neck,head.siz,head.positions,head.colors,
  	head.id,head.retsiz(),head.retsiz(),head.retsiz()/4);
  node3_head->change_parameters(0.0*body_sc,1.4*body_sc,0.0*body_sc,0.0,0.0,0.0);

  cylinder limb(10,20,0.25*body_sc,0.2*body_sc,2*body_sc,skincol);
  cylinder limblower(10,20,0.2*body_sc,0.15*body_sc,2*body_sc,skincol);
  cylinder thigh(10,20,0.35*body_sc,0.25*body_sc,2.5*body_sc,red);
  cylinder leglower(10,20,0.28*body_sc,0.2*body_sc,2.5*body_sc,skincol);
  cylinder tummy(10,20,1.05*body_sc,1.1*body_sc,0.7*body_sc,skincol);

  node4_leftarmu = new csX75::HNode(node1_torso,limb.siz,limb.positions,limb.colors,
  	limb.id,limb.retsiz(),limb.retsiz(),limb.retsiz()/4);
  node4_leftarmu->change_parameters((1.1-0.1*0.25/(2*2.3))*body_sc,
  	(2.3-0.25/2)*body_sc,0.0*body_sc,0.0,0.0,-90.0);

  node5_leftarml = new csX75::HNode(node4_leftarmu,limblower.siz,limblower.positions,limblower.colors,
  	limblower.id,limblower.retsiz(),limblower.retsiz(),limblower.retsiz()/4);
  node5_leftarml->change_parameters(0.0*body_sc,2.0*body_sc,0.0*body_sc,0.0,0.0,90.0);

  node6_rightarmu = new csX75::HNode(node1_torso,limb.siz,limb.positions,limb.colors,
  	limb.id,limb.retsiz(),limb.retsiz(),limb.retsiz()/4);
  node6_rightarmu->change_parameters((-1.1+0.1*0.25/(2*2.3))*body_sc,(2.3-0.25/2)*body_sc,0.0*body_sc,0.0,0.0,90.0);

  node7_rightarml = new csX75::HNode(node6_rightarmu,limblower.siz,limblower.positions,limblower.colors,
  	limblower.id,limblower.retsiz(),limblower.retsiz(),limblower.retsiz()/4);
  node7_rightarml->change_parameters(0.0*body_sc,2.0*body_sc,0.0*body_sc,0.0,0.0,90.0);

  node12_tummy = new csX75::HNode(node1_torso,tummy.siz,tummy.positions,tummy.colors,
  	tummy.id,tummy.retsiz(),tummy.retsiz(),tummy.retsiz()/4);
  node12_tummy->change_parameters(0.0*body_sc,0.0*body_sc,0.0*body_sc,0.0,0.0,180.0);

  node8_leftthigh = new csX75::HNode(node12_tummy,thigh.siz,thigh.positions,thigh.colors,
  	thigh.id,thigh.retsiz(),thigh.retsiz(),thigh.retsiz()/4);
  node8_leftthigh->change_parameters((-1.1+0.35/2)*body_sc,0.7*body_sc,0.0*body_sc,0.0,0.0,0.0);

  node9_leftfoot = new csX75::HNode(node8_leftthigh,leglower.siz,leglower.positions,leglower.colors,
  	leglower.id,leglower.retsiz(),leglower.retsiz(),leglower.retsiz()/4);
  node9_leftfoot->change_parameters(0.0*body_sc,2.5*body_sc,0.0*body_sc,0.0,0.0,0.0);

  node10_rightthigh = new csX75::HNode(node12_tummy,thigh.siz,thigh.positions,thigh.colors,
  	thigh.id,thigh.retsiz(),thigh.retsiz(),thigh.retsiz()/4);
  node10_rightthigh->change_parameters((1.1-0.35/2)*body_sc,0.7*body_sc,0.0*body_sc,0.0,0.0,0.0);

  node11_rightfoot = new csX75::HNode(node10_rightthigh,leglower.siz,leglower.positions,leglower.colors,
  	leglower.id,leglower.retsiz(),leglower.retsiz(),leglower.retsiz()/4);
  node11_rightfoot->change_parameters(0.0*body_sc,2.5*body_sc,0.0*body_sc,0.0,0.0,0.0);

  ellipsoid skirt(10,20,3*body_sc,4.8*body_sc,3*body_sc,blue,1);

  node13_skirt = new csX75::HNode(node12_tummy,skirt.siz,skirt.positions,skirt.colors,
  	skirt.id,skirt.retsiz(),skirt.retsiz(),skirt.retsiz()/4);
  node13_skirt->change_parameters(0.0*body_sc,5.2*body_sc,0.0*body_sc,0.0,0.0,180.0);

  glm::vec4 brown=glm::vec4(139.0/255,69.0/255,19.0/255,1);
  cylinder shoe=cylinder(10,20,0.3*body_sc,0.2*body_sc,1*body_sc,brown);
  node14_shoe=new csX75::HNode(node9_leftfoot,shoe.siz,shoe.positions,shoe.colors,
  	shoe.id,shoe.retsiz(),shoe.retsiz(),shoe.retsiz()/4);
  node14_shoe->change_parameters(0.0*body_sc,(2.5+0.1)*body_sc,-0.23*body_sc,-90.0,0.0,180.0);

  node15_shoe=new csX75::HNode(node11_rightfoot,shoe.siz,shoe.positions,shoe.colors,
  	shoe.id,shoe.retsiz(),shoe.retsiz(),shoe.retsiz()/4);
  node15_shoe->change_parameters(0.0*body_sc,(2.5+0.1)*body_sc,-0.23*body_sc,-90.0,0.0,180.0);

  // createman(0.8);
  createman(body_sc,scalebox);

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
  	mtorso.id,mtorso.retsiz(),mtorso.retsiz(),mtorso.retsiz()/4);
  man1_mtorso->change_parameters(3*scalebox,0.65*scalebox,2.0*scalebox,0.0,-180.0,-180.0);

  cylinder mneck(10,20,0.4*body_sc,0.3*body_sc,0.7*body_sc,skincol);

  man2_mneck = new csX75::HNode(man1_mtorso,mneck.siz,mneck.positions,mneck.colors,
  	mneck.id,mneck.retsiz(),mneck.retsiz(),mneck.retsiz()/4);
  man2_mneck->change_parameters(0.0*body_sc,2.3*body_sc,0.0*body_sc,0.0,0.0,0.0);
  
  ellipsoid mhead(10,20,1*body_sc,1*body_sc,1*body_sc,skincol);

  man3_mhead = new csX75::HNode(man2_mneck,mhead.siz,mhead.positions,mhead.colors,
  	mhead.id,mhead.retsiz(),mhead.retsiz(),mhead.retsiz()/4);
  man3_mhead->change_parameters(0.0*body_sc,1.4*body_sc,0.0*body_sc,0.0,0.0,0.0);

  cylinder mlimb(10,20,0.25*body_sc,0.2*body_sc,2*body_sc,skincol);
  cylinder mlimblower(10,20*body_sc,0.2,0.15*body_sc,2*body_sc,skincol);
  cylinder mthigh(10,20,0.35*body_sc,0.25*body_sc,2.5*body_sc,red);
  cylinder mleglower(10,20,0.28*body_sc,0.2*body_sc,2.5*body_sc,skincol);
  cylinder mtummy(10,20,1.05*body_sc,1.1*body_sc,0.7*body_sc,yellow);

  man4_leftarmu = new csX75::HNode(man1_mtorso,mlimb.siz,mlimb.positions,mlimb.colors,
  	mlimb.id,mlimb.retsiz(),mlimb.retsiz(),mlimb.retsiz()/4);
  man4_leftarmu->change_parameters((1.1-0.1*0.25/(2*2.3))*body_sc,(2.3-0.25/2)*body_sc,0.0*body_sc,0.0,0.0,-90.0);

  man5_leftarml = new csX75::HNode(man4_leftarmu,mlimblower.siz,mlimblower.positions,mlimblower.colors,
  	mlimblower.id,mlimblower.retsiz(),mlimblower.retsiz(),mlimblower.retsiz()/4);
  man5_leftarml->change_parameters(0.0*body_sc,2.0*body_sc,0.0*body_sc,0.0,0.0,-90.0);

  man6_rightarmu = new csX75::HNode(man1_mtorso,mlimb.siz,mlimb.positions,mlimb.colors,
  	mlimb.id,mlimb.retsiz(),mlimb.retsiz(),mlimb.retsiz()/4);
  man6_rightarmu->change_parameters((-1.1+0.1*0.25/(2*2.3))*body_sc,(2.3-0.25/2)*body_sc,0.0*body_sc,0.0,0.0,90.0);

  man7_rightarml = new csX75::HNode(man6_rightarmu,mlimblower.siz,mlimblower.positions,mlimblower.colors,
  	mlimblower.id,mlimblower.retsiz(),mlimblower.retsiz(),mlimblower.retsiz()/4);
  man7_rightarml->change_parameters(0.0*body_sc,2.0*body_sc,0.0*body_sc,0.0,0.0,-90.0);

  man12_mtummy = new csX75::HNode(man1_mtorso,mtummy.siz,mtummy.positions,mtummy.colors,
  	mtummy.id,mtummy.retsiz(),mtummy.retsiz(),mtummy.retsiz()/4);
  man12_mtummy->change_parameters(0.0*body_sc,0.0*body_sc,0.0*body_sc,0.0,0.0,180.0);

  man8_leftmthigh = new csX75::HNode(man12_mtummy,mthigh.siz,mthigh.positions,mthigh.colors,
  	mthigh.id,mthigh.retsiz(),mthigh.retsiz(),mthigh.retsiz()/4);
  man8_leftmthigh->change_parameters((-1.1+0.35/2)*body_sc,0.7*body_sc,0.0*body_sc,0.0,0.0,0.0);

  man9_leftfoot = new csX75::HNode(man8_leftmthigh,mleglower.siz,mleglower.positions,mleglower.colors,
  	mleglower.id,mleglower.retsiz(),mleglower.retsiz(),mleglower.retsiz()/4);
  man9_leftfoot->change_parameters(0.0*body_sc,2.5*body_sc,0.0*body_sc,0.0,0.0,0.0);

  man10_rightmthigh = new csX75::HNode(man12_mtummy,mthigh.siz,mthigh.positions,mthigh.colors,
  	mthigh.id,mthigh.retsiz(),mthigh.retsiz(),mthigh.retsiz()/4);
  man10_rightmthigh->change_parameters((1.1-0.35/2)*body_sc,0.7*body_sc,0.0*body_sc,0.0,0.0,0.0);

  man11_rightfoot = new csX75::HNode(man10_rightmthigh,mleglower.siz,mleglower.positions,mleglower.colors,
  	mleglower.id,mleglower.retsiz(),mleglower.retsiz(),mleglower.retsiz()/4);
  man11_rightfoot->change_parameters(0.0*body_sc,2.5*body_sc,0.0*body_sc,0.0,0.0,0.0);

  man14_shoe=new csX75::HNode(man9_leftfoot,shoe.siz,shoe.positions,shoe.colors,
  	shoe.id,shoe.retsiz(),shoe.retsiz(),shoe.retsiz()/4);
  man14_shoe->change_parameters(0.0*body_sc,(2.5+0.1)*body_sc,-0.23*body_sc,-90.0,0.0,180.0);

  man15_shoe=new csX75::HNode(man11_rightfoot,shoe.siz,shoe.positions,shoe.colors,
  	shoe.id,shoe.retsiz(),shoe.retsiz(),shoe.retsiz()/4);
  man15_shoe->change_parameters(0.0*body_sc,(2.5+0.1)*body_sc,-0.23*body_sc,-90.0,0.0,180.0);

}

void renderGL(void)
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  // //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    projection_matrix = glm::frustum(-5.0, 5.0, -5.0, 5.0, 2.0, 40.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-5.0, 5.0, -5.0, 5.0, 0.0, 10.0);

  view_matrix = projection_matrix*lookat_matrix;

  ModelViewMatrix = (glm::inverse(glm::mat3(view_matrix)));

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

 
  // matrixStack.push_back(view_matrix);
  // matrixStack.push_back(myroom->translation);
  // matrixStack.push_back(myroom->rotation);
  // myroom->render();
  // front->render();

  matrixStack.push_back(view_matrix);
  center->render_tree();

  // node1_torso->render_tree();
  // man1_mtorso->render_tree();
  // centroid_box->render_tree();

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

