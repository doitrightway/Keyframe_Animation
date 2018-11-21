#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include "shapes.cpp"
#include <iostream>
#include <fstream>

extern GLfloat c_xrot,c_yrot,c_zrot, c_xpos, c_ypos, c_zpos;
extern bool enable_perspective;
extern csX75::HNode* center, *curr_node;
extern csX75::HNode* box1,* box2,*node1_torso, *node2_neck, *node3_head,
*node4_leftarmu,*node5_leftarml,*node6_rightarmu,*node7_rightarml,*node8_leftthigh,*node9_leftfoot,
*node10_rightthigh,*node11_rightfoot,*curr_node, *node12_tummy,*node13_skirt,
*man1_mtorso,* man2_mneck,* man3_mhead,* man4_leftarmu,* man5_leftarml,
* man6_rightarmu,* man7_rightarml,* man8_leftmthigh,* man9_leftfoot,
* man10_rightmthigh,* man11_rightfoot,* man12_mtummy,* man13_mskirt;

char degree='x';
int person=0;


extern glm::mat4 projection_matrix, uModelViewMatrix;
extern csX75::HNode* display_points[100];
extern glm::mat4 ModelViewMatrix;
extern int number,start;
extern glm::vec3 control_points[100];

extern bool mylight1;
extern bool mylight2;

namespace csX75
{

	void Save_Frame();


  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }

  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {

    double xpos, ypos, zpos;
    glfwGetCursorPos(window, &xpos, &ypos);

    switch(button)
    {
      case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS)
        {
           // std::cout<<xpos<<","<<ypos<<" ";
        	xpos=xpos+0.5f;
        	ypos=ypos+0.5f;
            // std::cout<<xpos<<","<<ypos<<" ";
    		// glReadPixels(xpos, 512-1-ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zpos);
            // std::cout<<xpos<<","<<ypos<<","<<zpos<<" ";
            glm::vec4 tresult= ModelViewMatrix*glm::vec4((float)xpos/512*10-5,(float)(512-1-ypos)/512*10-5,
              -(float)2,1);
            glm::vec3 result = glm::vec3(tresult[0]/tresult[3],tresult[1]/tresult[3],tresult[2]/tresult[3]);
            control_points[number]=result;
            ellipsoid sp(10,10,0.06,0.06,0.06,glm::vec4(0.9,0.3,0.4,1));
        	display_points[number]=new csX75::HNode(center,sp.siz,sp.positions,sp.colors,sp.normals);
            display_points[number]->change_parameters(result[0],result[1],result[2],0,0,0);
            std::cout<<result[0]<<","<<result[1]<<","<<result[2]<<" ";
            number++;
        }
          break;
      default:
          break;
    }
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
  	
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if(key == GLFW_KEY_F1){
      mylight1=!mylight1;
    }
    else if(key == GLFW_KEY_F2){
      mylight2=!mylight2;
    }
    else if (key == GLFW_KEY_1){
      if(person==0){
      	curr_node = node1_torso;
      }
      else{
      	curr_node=man1_mtorso;
      }
      degree='a';
    }
    else if (key == GLFW_KEY_2){
      if(person==0){
      	curr_node = node2_neck;
      }
      else{
      	curr_node=man2_mneck;
      }
      degree='a';
    }
    else if (key == GLFW_KEY_3){
      if(person==0){
      	curr_node = node5_leftarml; 
      }
      else{
      	curr_node=man5_leftarml;
      }
      degree='z';
    }
    
    else if (key == GLFW_KEY_4){
      if(person==0){
      	curr_node = node7_rightarml;
      }
      else{
      	curr_node=man7_rightarml;
      }
      degree='z';
    }
    else if (key == GLFW_KEY_5){
      if(person==0){
      	curr_node = node8_leftthigh;
      }
      else{
      	curr_node=man8_leftmthigh;
      }
      degree='a';
    }
    else if (key == GLFW_KEY_6){
      if(person==0){
      	curr_node = node10_rightthigh;
      }
      else{
      	curr_node=man10_rightmthigh;
      }
      degree='a';
    }
    else if (key == GLFW_KEY_L){
      curr_node = box2;
      degree='z';
    }
    else if (key == GLFW_KEY_LEFT && (degree=='a' || degree=='y')){
      curr_node->dec_ry();
    }
    else if (key == GLFW_KEY_RIGHT && (degree=='a' || degree=='y')){
      curr_node->inc_ry();
    }
    else if (key == GLFW_KEY_UP && (degree=='a' || degree=='x')){
      curr_node->dec_rx();
    }
    else if (key == GLFW_KEY_DOWN && (degree=='a' || degree=='x')){
      curr_node->inc_rx();
    }
    else if (key == GLFW_KEY_PAGE_UP && (degree=='a' || degree=='z')){
      curr_node->inc_rz();
    }
    else if (key == GLFW_KEY_PAGE_DOWN && (degree=='a' || degree=='z')){
      curr_node->dec_rz();
    }
    else if (key == GLFW_KEY_T){
      person=1-person;
      if(person==1){
      	curr_node=man1_mtorso;
      }
      else{
      	curr_node=node1_torso;
      }
    }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS){
      enable_perspective = !enable_perspective;   
    }
    else if (key == GLFW_KEY_A){
      c_yrot -= 1.0;
    }
    else if (key == GLFW_KEY_D){
      c_yrot += 1.0;
    }
    else if (key == GLFW_KEY_W){
      c_xrot -= 1.0;
    }
    else if (key == GLFW_KEY_S){
      c_xrot += 1.0;        
    }
    else if (key == GLFW_KEY_Q){
      c_zrot -= 1.0;
    }
    else if (key == GLFW_KEY_E){
      c_zrot += 1.0;   
    }

    else if (key == GLFW_KEY_H){
      c_ypos -= 0.1;
    }
    else if (key == GLFW_KEY_K){
      c_ypos += 0.1;
    }
    else if (key == GLFW_KEY_U){
      c_xpos -= 0.1;
    }
    else if (key == GLFW_KEY_J){
      c_xpos += 0.1;        
    }
    else if (key == GLFW_KEY_Y){
      c_zpos -= 0.1;
    }
    else if (key == GLFW_KEY_I){
      c_zpos += 0.1;   
    }
    else if (key == GLFW_KEY_O && action == GLFW_PRESS && number>0 && start==0){
    	start=1;
    }
    else if (key == GLFW_KEY_V && action == GLFW_PRESS){
    	Save_Frame();
    }
    else if (key == GLFW_KEY_M && action==GLFW_PRESS && start==0){
    	std::cout<<"starting player"<<std::endl;
    	start=3;
    }

  }

  void Save_Frame(){

  	state *a=new state;

  	a->light1=mylight1;
  	a->light2=mylight2;

  	man1_mtorso->get_rotation(a->man.torso);
  	man2_mneck->get_rotation(a->man.neck);
  	man5_leftarml->get_rotation(a->man.leftlowerarm);
  	man7_rightarml->get_rotation(a->man.rightlowerarm);
  	man8_leftmthigh->get_rotation(a->man.leftlowerleg);
  	man10_rightmthigh->get_rotation(a->man.rightlowerleg);

  	node1_torso->get_rotation(a->woman.torso);
  	node2_neck->get_rotation(a->woman.neck);
  	node5_leftarml->get_rotation(a->woman.leftlowerarm);
  	node7_rightarml->get_rotation(a->woman.rightlowerarm);
  	node8_leftthigh->get_rotation(a->woman.leftlowerleg);
  	node10_rightthigh->get_rotation(a->woman.rightlowerleg);

  	box2->get_rotation(a->box_lid);

  	std::ofstream f;
  	f.open("keyframes.txt",std::ios::app | std::ios::binary);
  	f.write((char*)a,sizeof(*a));
  	f.close();
  	delete a;
  }

};  
  


