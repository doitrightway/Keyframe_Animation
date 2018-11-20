#include "hierarchy_node.hpp"
#include "texture.hpp"
#include <iostream>
#include <string>

extern GLuint vPosition,vColor,texCoord, uModelViewMatrix;
extern GLuint vid;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, 
		glm::vec4* a_vertices, glm::vec4* a_colours,int* id, 
		std::size_t v_size, std::size_t c_size, std::size_t id_size){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		vertex_buffer_size = num_v*16;
		color_buffer_size = c_size;
		color_buffer_size = num_v*16;
		id_size = num_v*4;
		// initialize vao and vbo of the object;


		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);
		glm::vec2 *tex_coord=new glm::vec2[color_buffer_size/2];
		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size +color_buffer_size/2+color_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size/2, tex_coord );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+color_buffer_size/2, color_buffer_size, a_colours );
		// glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+color_buffer_size*3/(float)2,id_size,id );
		
		std::cout<<a_colours[0][0]<<" ";
		delete[] tex_coord;
		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );


		glEnableVertexAttribArray( texCoord );
  		glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size+color_buffer_size/2));

		// glEnableVertexAttribArray( vid );
		// glVertexAttribPointer( vid, 1 , GL_FLOAT, GL_FALSE, 0, 
		// 	BUFFER_OFFSET(vertex_buffer_size + color_buffer_size+color_buffer_size/2) );

		// set parent
		if_tex=1;
		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}

	HNode::HNode(HNode* a_parent, GLuint num_v){

		num_vertices = num_v;


		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		// //setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );


		glEnableVertexAttribArray( texCoord );
  		glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		// glEnableVertexAttribArray( vid );
		// glVertexAttribPointer( vid, 1 , GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;
		if_tex=1;
		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices,glm::vec4* a_colours, 
		glm::vec2* tex_coord, int* id, std::size_t v_size, 
		std::size_t col_size, std::size_t tex_size, std::size_t id_size, std::string texture_file, int tex_x,int tex_y){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size= col_size;
		texture_buffer_size= tex_size;
		// initialize vao and vbo of the object;


		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + texture_buffer_size+color_buffer_size, 
			NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, texture_buffer_size, tex_coord );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+texture_buffer_size, color_buffer_size,a_colours);
		// glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + texture_buffer_size+color_buffer_size,
		// 	id_size,id);

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( texCoord );
  		glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size) );

  		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, 
			BUFFER_OFFSET(vertex_buffer_size+texture_buffer_size) );

		// glEnableVertexAttribArray( vid );
		// glVertexAttribPointer( vid, 1 , GL_FLOAT, GL_FALSE, 0, 
		// 	BUFFER_OFFSET(vertex_buffer_size+texture_buffer_size + color_buffer_size) );

		tex=texture_file;
		// strcpy(tex,texture_file);
		texx=tex_x;
		texy=tex_y;
		// tex=LoadTexture("images/all1.bmp",256,256);
		if_tex=id[0];

		//initial parameters are set to 0;
		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}

	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::render(){
		
    	
  		if(!if_tex){
  			GLuint temp= LoadTexture(tex.c_str(),texx,texy);
  			glBindTexture(GL_TEXTURE_2D, temp);
  		}
		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glUniform1i(vid,if_tex);
		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		rx++;
		update_matrices();
	}


	void HNode::inc_ry(){
		ry++;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz++;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx--;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry--;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz--;
		update_matrices();
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}
