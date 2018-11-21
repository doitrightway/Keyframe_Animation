#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"


namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz;

		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;
		std::size_t texture_buffer_size;
		std::size_t normal_buffer_size;

		GLuint num_vertices;
		GLuint vao,vbo;
		std::string tex;
		int texx,texy;

		uint if_tex;

		// glm::mat4 rotation;
		// glm::mat4 translation;
		
		std::vector<HNode*> children;
		HNode* parent;

		void update_matrices();

	  public:
	  	int islight;
	  	int state;
	  	glm::mat4 rotation;
		glm::mat4 translation;
		HNode (HNode*, GLuint, glm::vec4*,  glm::vec4*, glm::vec3*);
		HNode (HNode*, GLuint);
		HNode(HNode*, GLuint, glm::vec4*, glm::vec4* , 
		glm::vec2*,glm::vec3*,std::string,int,int);

		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void render_tree();
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
		void get_rotation(GLfloat [3]);
		void set_rotation(GLfloat [3]);
	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif