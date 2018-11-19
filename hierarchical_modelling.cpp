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
// #include "texture.hpp"


GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;
GLuint vao,vbo;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
// void createman();

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
  vid= glGetAttribLocation( shaderProgram, "vid" ); 
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

  cuboid room(10,10,10,0);

  myroom = new csX75::HNode(center,36,room.positions,room.colors,room.tex_coords,room.id,36*16,36*16,36*8,36*4,"images/all.bmp",512,512);
  myroom->change_parameters(-5,-5,-5,0,0,0);
  curr_node = myroom;
  
  cuboid ro(2,2,2,0);
  troom = new csX75::HNode(center,36,ro.positions,ro.colors,ro.tex_coords,ro.id,36*16,36*16,36*8,36*4,"images/all1.bmp",256,256);
  troom->change_parameters(-1,-1,-1,0,0,0);

  // curr_node = troom;

  // cylinder legs(20,20,2,2,10,skincol);



  // glEnableVertexAttribArray( vColor );
  // glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(36*16));

  // glm::vec4 arr[5]={skincol,red,blue,yellow,white};

  // openbox box(4,2,4,arr);
  // openbox lid(4,0.3,4,arr);

  // centroid_box = new csX75::HNode(NULL,0);
  // centroid_box->change_parameters(0.6,5,0,0,0,0);
  // box1 = new csX75::HNode(centroid_box,box.siz,box.positions,box.colors,box.retsiz(),box.retsiz());
  // box1->change_parameters(-2.0,1.0,2.0,0.0,180.0,180.0);
  // box2 = new csX75::HNode(box1,lid.siz,lid.positions,lid.colors,lid.retsiz(),lid.retsiz());

  // box2->change_parameters(4.0,0.0,0.0,0.0,0.0,180.0);


  // cylinder torso(10,20,1.05,1.2,2.3,yellow);
  // //note that the buffers are initialized in the respective constructors
 
  // node1_torso = new csX75::HNode(NULL,torso.siz,torso.positions,torso.colors,torso.retsiz(),torso.retsiz());
  // node1_torso->change_parameters(3.7,0,-1.0,0.0,0.0,0.0);

  // cylinder neck(10,20,0.4,0.3,0.7,skincol);

  // node2_neck = new csX75::HNode(node1_torso,neck.siz,neck.positions,neck.colors,neck.retsiz(),neck.retsiz());
  // node2_neck->change_parameters(0.0,2.3,0.0,0.0,0.0,0.0);
  
  // ellipsoid head(10,20,1,1,1,skincol);

  // node3_head = new csX75::HNode(node2_neck,head.siz,head.positions,head.colors,head.retsiz(),head.retsiz());
  // node3_head->change_parameters(0.0,1.4,0.0,0.0,0.0,0.0);

  // cylinder limb(10,20,0.25,0.2,2,skincol);
  // cylinder limblower(10,20,0.2,0.15,2,skincol);
  // cylinder thigh(10,20,0.35,0.25,2.5,red);
  // cylinder leglower(10,20,0.28,0.2,2.5,skincol);
  // cylinder tummy(10,20,1.05,1.1,0.7,skincol);

  // node4_leftarmu = new csX75::HNode(node1_torso,limb.siz,limb.positions,limb.colors,limb.retsiz(),limb.retsiz());
  // node4_leftarmu->change_parameters(1.1-0.1*0.25/(2*2.3),2.3-0.25/2,0.0,0.0,0.0,-90.0);

  // node5_leftarml = new csX75::HNode(node4_leftarmu,limblower.siz,limblower.positions,limblower.colors,limblower.retsiz(),limblower.retsiz());
  // node5_leftarml->change_parameters(0.0,2.0,0.0,0.0,0.0,90.0);

  // node6_rightarmu = new csX75::HNode(node1_torso,limb.siz,limb.positions,limb.colors,limb.retsiz(),limb.retsiz());
  // node6_rightarmu->change_parameters(-1.1+0.1*0.25/(2*2.3),2.3-0.25/2,0.0,0.0,0.0,90.0);

  // node7_rightarml = new csX75::HNode(node6_rightarmu,limblower.siz,limblower.positions,limblower.colors,limblower.retsiz(),limblower.retsiz());
  // node7_rightarml->change_parameters(0.0,2.0,0.0,0.0,0.0,90.0);

  // node12_tummy = new csX75::HNode(node1_torso,tummy.siz,tummy.positions,tummy.colors,tummy.retsiz(),tummy.retsiz());
  // node12_tummy->change_parameters(0.0,0.0,0.0,0.0,0.0,180.0);

  // node8_leftthigh = new csX75::HNode(node12_tummy,thigh.siz,thigh.positions,thigh.colors,thigh.retsiz(),thigh.retsiz());
  // node8_leftthigh->change_parameters(-1.1+0.35/2,0.7,0.0,0.0,0.0,0.0);

  // node9_leftfoot = new csX75::HNode(node8_leftthigh,leglower.siz,leglower.positions,leglower.colors,leglower.retsiz(),leglower.retsiz());
  // node9_leftfoot->change_parameters(0.0,2.5,0.0,0.0,0.0,0.0);

  // node10_rightthigh = new csX75::HNode(node12_tummy,thigh.siz,thigh.positions,thigh.colors,thigh.retsiz(),thigh.retsiz());
  // node10_rightthigh->change_parameters(1.1-0.35/2,0.7,0.0,0.0,0.0,0.0);

  // node11_rightfoot = new csX75::HNode(node10_rightthigh,leglower.siz,leglower.positions,leglower.colors,leglower.retsiz(),leglower.retsiz());
  // node11_rightfoot->change_parameters(0.0,2.5,0.0,0.0,0.0,0.0);

  // ellipsoid skirt(10,20,3,4.8,3,blue,1);

  // node13_skirt = new csX75::HNode(node12_tummy,skirt.siz,skirt.positions,skirt.colors,skirt.retsiz(),skirt.retsiz());
  // node13_skirt->change_parameters(0.0,5.2,0.0,0.0,0.0,180.0);

  // glm::vec4 brown=glm::vec4(139.0/255,69.0/255,19.0/255,1);
  // cylinder shoe=cylinder(10,20,0.3,0.2,1,brown);
  // node14_shoe=new csX75::HNode(node9_leftfoot,shoe.siz,shoe.positions,shoe.colors,shoe.retsiz(),shoe.retsiz());
  // node14_shoe->change_parameters(0.0,2.5+0.1,-0.23,-90.0,0.0,180.0);

  // node15_shoe=new csX75::HNode(node11_rightfoot,shoe.siz,shoe.positions,shoe.colors,shoe.retsiz(),shoe.retsiz());
  // node15_shoe->change_parameters(0.0,2.5+0.1,-0.23,-90.0,0.0,180.0);

  // createman();

  // curr_node = node1_torso;

}

// void createman()
// {
// 	glm::vec4 skincol=glm::vec4(255.0/255,205.0/255,148.0/255,1);
// 	glm::vec4 red=glm::vec4(1,0.05,0.05,1);
// 	glm::vec4 yellow=glm::vec4(1,215.0/255,0,1);
// 	glm::vec4 blue=glm::vec4(0.05,0.05,1,1);
// 	glm::vec4 brown=glm::vec4(139.0/255,69.0/255,19.0/255,1);
  	

//   	cylinder shoe=cylinder(10,20,0.3,0.2,1,brown);

// 	cylinder mtorso(10,20,1.05,1.2,2.3,yellow);
//   //note that the buffers are initialized in the respective constructors
 
//   man1_mtorso = new csX75::HNode(NULL,mtorso.siz,mtorso.positions,mtorso.colors,mtorso.retsiz(),mtorso.retsiz());
//   man1_mtorso->change_parameters(-3.7,0.0,0.0,0.0,0.0,0.0);

//   cylinder mneck(10,20,0.4,0.3,0.7,skincol);

//   man2_mneck = new csX75::HNode(man1_mtorso,mneck.siz,mneck.positions,mneck.colors,mneck.retsiz(),mneck.retsiz());
//   man2_mneck->change_parameters(0.0,2.3,0.0,0.0,0.0,0.0);
  
//   ellipsoid mhead(10,20,1,1,1,skincol);

//   man3_mhead = new csX75::HNode(man2_mneck,mhead.siz,mhead.positions,mhead.colors,mhead.retsiz(),mhead.retsiz());
//   man3_mhead->change_parameters(0.0,1.4,0.0,0.0,0.0,0.0);

//   cylinder mlimb(10,20,0.25,0.2,2,skincol);
//   cylinder mlimblower(10,20,0.2,0.15,2,skincol);
//   cylinder mthigh(10,20,0.35,0.25,2.5,red);
//   cylinder mleglower(10,20,0.28,0.2,2.5,skincol);
//   cylinder mtummy(10,20,1.05,1.1,0.7,yellow);

//   man4_leftarmu = new csX75::HNode(man1_mtorso,mlimb.siz,mlimb.positions,mlimb.colors,mlimb.retsiz(),mlimb.retsiz());
//   man4_leftarmu->change_parameters(1.1-0.1*0.25/(2*2.3),2.3-0.25/2,0.0,0.0,0.0,-90.0);

//   man5_leftarml = new csX75::HNode(man4_leftarmu,mlimblower.siz,mlimblower.positions,mlimblower.colors,mlimblower.retsiz(),mlimblower.retsiz());
//   man5_leftarml->change_parameters(0.0,2.0,0.0,0.0,0.0,-90.0);

//   man6_rightarmu = new csX75::HNode(man1_mtorso,mlimb.siz,mlimb.positions,mlimb.colors,mlimb.retsiz(),mlimb.retsiz());
//   man6_rightarmu->change_parameters(-1.1+0.1*0.25/(2*2.3),2.3-0.25/2,0.0,0.0,0.0,90.0);

//   man7_rightarml = new csX75::HNode(man6_rightarmu,mlimblower.siz,mlimblower.positions,mlimblower.colors,mlimblower.retsiz(),mlimblower.retsiz());
//   man7_rightarml->change_parameters(0.0,2.0,0.0,0.0,0.0,-90.0);

//   man12_mtummy = new csX75::HNode(man1_mtorso,mtummy.siz,mtummy.positions,mtummy.colors,mtummy.retsiz(),mtummy.retsiz());
//   man12_mtummy->change_parameters(0.0,0.0,0.0,0.0,0.0,180.0);

//   man8_leftmthigh = new csX75::HNode(man12_mtummy,mthigh.siz,mthigh.positions,mthigh.colors,mthigh.retsiz(),mthigh.retsiz());
//   man8_leftmthigh->change_parameters(-1.1+0.35/2,0.7,0.0,0.0,0.0,0.0);

//   man9_leftfoot = new csX75::HNode(man8_leftmthigh,mleglower.siz,mleglower.positions,mleglower.colors,mleglower.retsiz(),mleglower.retsiz());
//   man9_leftfoot->change_parameters(0.0,2.5,0.0,0.0,0.0,0.0);

//   man10_rightmthigh = new csX75::HNode(man12_mtummy,mthigh.siz,mthigh.positions,mthigh.colors,mthigh.retsiz(),mthigh.retsiz());
//   man10_rightmthigh->change_parameters(1.1-0.35/2,0.7,0.0,0.0,0.0,0.0);

//   man11_rightfoot = new csX75::HNode(man10_rightmthigh,mleglower.siz,mleglower.positions,mleglower.colors,mleglower.retsiz(),mleglower.retsiz());
//   man11_rightfoot->change_parameters(0.0,2.5,0.0,0.0,0.0,0.0);

//   man14_shoe=new csX75::HNode(man9_leftfoot,shoe.siz,shoe.positions,shoe.colors,shoe.retsiz(),shoe.retsiz());
//   man14_shoe->change_parameters(0.0,2.5+0.1,-0.23,-90.0,0.0,180.0);

//   man15_shoe=new csX75::HNode(man11_rightfoot,shoe.siz,shoe.positions,shoe.colors,shoe.retsiz(),shoe.retsiz());
//   man15_shoe->change_parameters(0.0,2.5+0.1,-0.23,-90.0,0.0,180.0);

// }

void renderGL(void)
{
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
    projection_matrix = glm::frustum(-5.0, 5.0, -5.0, 5.0, 1.0, 200.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-5.0, 5.0, -5.0, 5.0, -10.0, 10.0);

  view_matrix = projection_matrix*lookat_matrix;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

 
  matrixStack.push_back(view_matrix);
  // matrixStack.push_back(myroom->translation);
  // matrixStack.push_back(myroom->rotation);
  center->render_tree();

  // matrixStack.push_back(view_matrix);

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

