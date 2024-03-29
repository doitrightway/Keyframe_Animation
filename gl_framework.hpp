#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

namespace csX75
{
  //! Initialize GL State
  void initGL(void);
 
  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


struct state_person{
	GLfloat torso[3];
	GLfloat neck[3];
	GLfloat leftlowerarm[3];
	GLfloat rightlowerarm[3];
	GLfloat leftlowerleg[3];
	GLfloat rightlowerleg[3];
};
struct state{
	int light1,light2;
	state_person man,woman;
	GLfloat box_lid[3];
};
};

#endif
