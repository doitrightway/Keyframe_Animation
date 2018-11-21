/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include <iostream>
#include <fstream>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
GLfloat c_xpos = 0, c_ypos = 0, c_zpos = 5.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

// Coordinates of box
const glm::vec4 c_box=glm::vec4(0,0,0,1);
const glm::vec4 c_box_look=glm::vec4(-2,3,0,1);
const glm::vec4 c_door=glm::vec4(-8,-8,-8,1);

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;
//Shader program attribs
GLuint vPosition,vColor,texCoord, vNormal;
GLuint vid;
GLuint light1,light2;

// //global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

csX75::HNode* curr_node;
csX75::HNode* center;
csX75::HNode* front;
csX75::HNode* back;
csX75::HNode* left;
csX75::HNode* right;
csX75::HNode* bottom;
csX75::HNode* top;
csX75::HNode* table_top;
csX75::HNode* tab_leg1;
csX75::HNode* tab_leg2;
csX75::HNode* tab_leg3;
csX75::HNode* tab_leg4;
csX75::HNode* node1_torso;
csX75::HNode* node2_neck;
csX75::HNode* node3_head;
csX75::HNode* node4_leftarmu;
csX75::HNode* node5_leftarml;
csX75::HNode* node6_rightarmu;
csX75::HNode* node7_rightarml;
csX75::HNode* node8_leftthigh;
csX75::HNode* node9_leftfoot;
csX75::HNode* node10_rightthigh;
csX75::HNode* node11_rightfoot;
csX75::HNode* node12_tummy;
csX75::HNode* node13_skirt;
csX75::HNode* node14_shoe;
csX75::HNode* node15_shoe;
csX75::HNode* man1_mtorso;
csX75::HNode* man2_mneck;
csX75::HNode* man3_mhead;
csX75::HNode* man4_leftarmu;
csX75::HNode* man5_leftarml;
csX75::HNode* man6_rightarmu;
csX75::HNode* man7_rightarml;
csX75::HNode* man8_leftmthigh;
csX75::HNode* man9_leftfoot;
csX75::HNode* man10_rightmthigh;
csX75::HNode* man11_rightfoot;
csX75::HNode* man12_mtummy;
csX75::HNode* man13_mskirt;
csX75::HNode* man14_shoe;
csX75::HNode* man15_shoe;
csX75::HNode* box1;
csX75::HNode* box2;
csX75::HNode* fixture;
csX75::HNode* wall_light;
csX75::HNode* lampstand;
csX75::HNode* lamp_light;
csX75::HNode* chairbase1;
csX75::HNode* chairbase2;
csX75::HNode* chairsupport1;
csX75::HNode* chairsupport2;
csX75::HNode* chleg11;
csX75::HNode* chleg12;
csX75::HNode* chleg13;
csX75::HNode* chleg14;
csX75::HNode* chleg21;
csX75::HNode* chleg22;
csX75::HNode* chleg23;
csX75::HNode* chleg24;
csX75::HNode* smbox1;
csX75::HNode* smbox2;
// csX75::HNode* centroid_box;

csX75::HNode* display_points[100];
int number=0,start=0;
double counter=0;
double delta_t=0.04;
glm::vec3 control_points[100];
double last_time=0;
double fps_time=0.001;
double fps_cam_time = 0.001; 
std::ifstream key_file;
glm::vec3 cam_pos;
csX75::state prev_state, fut_state;
int num_frames=5;
int SCREEN_WIDTH= 512;
int SCREEN_HEIGHT= 512;

//-------------------------------------------------------------------------

#endif
