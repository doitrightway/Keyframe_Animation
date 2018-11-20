#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include "shapes.cpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern csX75::HNode* center, *curr_node;
extern csX75::HNode* box1,* box2,*node1_torso, *node2_neck, *node3_head,
*node4_leftarmu,*node5_leftarml,*node6_rightarmu,*node7_rightarml,*node8_leftthigh,*node9_leftfoot,
*node10_rightthigh,*node11_rightfoot,*curr_node, *node12_tummy,*node13_skirt,
*man1_mtorso,* man2_mneck,* man3_mhead,* man4_leftarmu,* man5_leftarml,
* man6_rightarmu,* man7_rightarml,* man8_leftmthigh,* man9_leftfoot,
* man10_rightmthigh,* man11_rightfoot,* man12_mtummy,* man13_mskirt;

char degree='a';
int person=0;

extern csX75::HNode* display_points[100];
extern glm::mat3 ModelViewMatrix;
extern int number;
extern glm::vec3 control_points[100];

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

  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {

    double xpos, ypos, zpos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glReadPixels(xpos, ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zpos);

    switch(button)
    {
      case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS)
        {
           // std::cout<<xpos<<","<<ypos<<" ";

           // glm::vec3 result = glm::vec3((float)xpos/512*2-1,(float)ypos/512*2-1,0.4)*ModelViewMatrix;
           // control_points[number]=result;
           // ellipsoid sp(10,10,0.1,0.1,0.1,glm::vec4(0.2,0.3,0.4,1));
        	glm::mat4 m_projection = glm::perspective(glm::radians(45.0f), (float)(1024/768), 0.1f, 1000.0f);

            glm::vec3 win(xpos,512 - 1 - ypos, zpos);
            glm::vec4 viewport(0.0f,0.0f,(float)512, (float)512);
            glm::vec3 world = glm::unProject(win, mesh.getView() * mesh.getTransform(),m_projection,viewport);

            std::cout << "screen " << xpos << " " << ypos << " " << zpos << std::endl;
            std::cout << "world " << world.x << " " << world.y << " " << world.z << std::endl;
           display_points[number]=new csX75::HNode(center,sp.siz,sp.positions,sp.colors,sp.id,
           	sp.retsiz(),sp.retsiz(),sp.retsiz()/4);
           display_points[number]->change_parameters(world[0],world[1],world[2],0,0,0);
           // std::cout<<result[0]<<","<<-result[1]<<","<<-result[2]<<" ";
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
      	curr_node = node3_head;	
      }
      else{
      	curr_node=man3_mhead;
      }
      degree='a';
    }
    else if (key == GLFW_KEY_4){
      if(person==0){
      	curr_node = node4_leftarmu;
      }
      else{
      	curr_node=man4_leftarmu;
      }
      degree='a';
    }
    else if (key == GLFW_KEY_5){
      if(person==0){
      	curr_node = node5_leftarml; 
      }
      else{
      	curr_node=man5_leftarml;
      }
      degree='z';
    }
    else if (key == GLFW_KEY_6){
      if(person==0){
      	curr_node = node6_rightarmu; 
      }
      else{
      	curr_node=man6_rightarmu;
      }
      degree='a';
    }
    else if (key == GLFW_KEY_7){
      if(person==0){
      	curr_node = node7_rightarml;
      }
      else{
      	curr_node=man7_rightarml;
      }
      degree='z';
    }
    else if (key == GLFW_KEY_8){
      if(person==0){
      	curr_node = node8_leftthigh;
      }
      else{
      	curr_node=man8_leftmthigh;
      }
      degree='a';
    }
    else if (key == GLFW_KEY_9){
      if(person==0){
      	curr_node = node9_leftfoot;
      }
      else{
      	curr_node=man9_leftfoot;
      }
      degree='x';
    }
    else if (key == GLFW_KEY_0){
      if(person==0){
      	curr_node = node10_rightthigh;
      }
      else{
      	curr_node=man10_rightmthigh;
      }
      degree='a';
    }
    else if (key == GLFW_KEY_EQUAL){
      if(person==0){
      	curr_node = node11_rightfoot;
      }
      else{
      	curr_node=man11_rightfoot;
      }
      degree='x';
    }
    else if (key == GLFW_KEY_B){
      curr_node = center;
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
  }

  

};  
  


