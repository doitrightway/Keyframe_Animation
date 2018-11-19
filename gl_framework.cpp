#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern csX75::HNode* myroom, *curr_node;
// extern csX75::HNode* box1,* box2,*centroid_box,*node1_torso, *node2_neck, *node3_head,
// *node4_leftarmu,*node5_leftarml,*node6_rightarmu,*node7_rightarml,*node8_leftthigh,*node9_leftfoot,
// *node10_rightthigh,*node11_rightfoot,*curr_node, *node12_tummy,*node13_skirt,
// *man1_mtorso,* man2_mneck,* man3_mhead,* man4_leftarmu,* man5_leftarml,
// * man6_rightarmu,* man7_rightarml,* man8_leftmthigh,* man9_leftfoot,
// * man10_rightmthigh,* man11_rightfoot,* man12_mtummy,* man13_mskirt;
// char degree='a';
// int person=0;
namespace csX75
{
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
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
  	
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    // else if (key == GLFW_KEY_1){
    //   if(person==0){
    //   	curr_node = node1_torso;
    //   }
    //   else{
    //   	curr_node=man1_mtorso;
    //   }
    //   degree='a';
    // }
    // else if (key == GLFW_KEY_2){
    //   if(person==0){
    //   	curr_node = node2_neck;
    //   }
    //   else{
    //   	curr_node=man2_mneck;
    //   }
    //   degree='a';
    // }
    // else if (key == GLFW_KEY_3){
    //   if(person==0){
    //   	curr_node = node3_head;	
    //   }
    //   else{
    //   	curr_node=man3_mhead;
    //   }
    //   degree='a';
    // }
    // else if (key == GLFW_KEY_4){
    //   if(person==0){
    //   	curr_node = node4_leftarmu;
    //   }
    //   else{
    //   	curr_node=man4_leftarmu;
    //   }
    //   degree='a';
    // }
    // else if (key == GLFW_KEY_5){
    //   if(person==0){
    //   	curr_node = node5_leftarml; 
    //   }
    //   else{
    //   	curr_node=man5_leftarml;
    //   }
    //   degree='z';
    // }
    // else if (key == GLFW_KEY_6){
    //   if(person==0){
    //   	curr_node = node6_rightarmu; 
    //   }
    //   else{
    //   	curr_node=man6_rightarmu;
    //   }
    //   degree='a';
    // }
    // else if (key == GLFW_KEY_7){
    //   if(person==0){
    //   	curr_node = node7_rightarml;
    //   }
    //   else{
    //   	curr_node=man7_rightarml;
    //   }
    //   degree='z';
    // }
    // else if (key == GLFW_KEY_8){
    //   if(person==0){
    //   	curr_node = node8_leftthigh;
    //   }
    //   else{
    //   	curr_node=man8_leftmthigh;
    //   }
    //   degree='a';
    // }
    // else if (key == GLFW_KEY_9){
    //   if(person==0){
    //   	curr_node = node9_leftfoot;
    //   }
    //   else{
    //   	curr_node=man9_leftfoot;
    //   }
    //   degree='x';
    // }
    // else if (key == GLFW_KEY_0){
    //   if(person==0){
    //   	curr_node = node10_rightthigh;
    //   }
    //   else{
    //   	curr_node=man10_rightmthigh;
    //   }
    //   degree='a';
    // }
    // else if (key == GLFW_KEY_EQUAL){
    //   if(person==0){
    //   	curr_node = node11_rightfoot;
    //   }
    //   else{
    //   	curr_node=man11_rightfoot;
    //   }
    //   degree='x';
    // }
    // else if (key == GLFW_KEY_B){
    //   curr_node = centroid_box;
    //   degree='a';
    // }
    // else if (key == GLFW_KEY_L){
    //   curr_node = box2;
    //   degree='z';
    // }
    // else if (key == GLFW_KEY_LEFT && (degree=='a' || degree=='y')){
    //   curr_node->dec_ry();
    // }
    // else if (key == GLFW_KEY_RIGHT && (degree=='a' || degree=='y')){
    //   curr_node->inc_ry();
    // }
    // else if (key == GLFW_KEY_UP && (degree=='a' || degree=='x')){
    //   curr_node->dec_rx();
    // }
    // else if (key == GLFW_KEY_DOWN && (degree=='a' || degree=='x')){
    //   curr_node->inc_rx();
    // }
    // else if (key == GLFW_KEY_PAGE_UP && (degree=='a' || degree=='z')){
    //   curr_node->inc_rz();
    // }
    // else if (key == GLFW_KEY_PAGE_DOWN && (degree=='a' || degree=='z')){
    //   curr_node->dec_rz();
    // }
    else if (key == GLFW_KEY_LEFT){
      curr_node->dec_ry();
    }
    else if (key == GLFW_KEY_RIGHT){
      curr_node->inc_ry();
    }
    else if (key == GLFW_KEY_UP){
      curr_node->dec_rx();
    }
    else if (key == GLFW_KEY_DOWN){
      curr_node->inc_rx();
    }
    else if (key == GLFW_KEY_PAGE_UP){
      curr_node->inc_rz();
    }
    else if (key == GLFW_KEY_PAGE_DOWN){
      curr_node->dec_rz();
    }
    // else if (key == GLFW_KEY_T){
    //   person=1-person;
    //   if(person==1){
    //   	curr_node=man1_mtorso;
    //   }
    //   else{
    //   	curr_node=node1_torso;
    //   }
    // }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS){
      enable_perspective = !enable_perspective;   
    }
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS){
      c_yrot -= 1.0;
    }
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS){
      c_yrot += 1.0;
    }
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS){
      c_xrot -= 1.0;
    }
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS){
      c_xrot += 1.0;        
    }
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS){
      c_zrot -= 1.0;
    }
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS){
      c_zrot += 1.0;   
    }
  }

  

};  
  


