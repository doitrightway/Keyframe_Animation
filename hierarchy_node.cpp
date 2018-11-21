#include "hierarchy_node.hpp"
#include "texture.hpp"
#include <iostream>
#include <string>

extern GLuint vPosition,vColor,texCoord, uModelViewMatrix, normalMatrix, vNormal;
extern GLuint vid, light1, light2;
extern bool mylight1, mylight2;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, 
		glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec3* normals){

		num_vertices = num_v;
		islight=0;
		vertex_buffer_size = num_v*16;
		texture_buffer_size = num_v*8;
		color_buffer_size = num_v*16;
		normal_buffer_size= num_v*12;
		// initialize vao and vbo of the object;


		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		glm::vec2 *tex_coord=new glm::vec2[texture_buffer_size];
		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size+
			texture_buffer_size + normal_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, texture_buffer_size, tex_coord );

		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+ texture_buffer_size, 
			color_buffer_size, a_colours );

		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+ texture_buffer_size+color_buffer_size, 
			normal_buffer_size, normals );

		delete[] tex_coord;
		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );


		glEnableVertexAttribArray( texCoord );
  		glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, 
			BUFFER_OFFSET(vertex_buffer_size + texture_buffer_size));

		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, 
			BUFFER_OFFSET(vertex_buffer_size + texture_buffer_size+ color_buffer_size));

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
		islight=0;

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

		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

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
		glm::vec2* tex_coord, glm::vec3* normals, std::string texture_file, int tex_x,int tex_y){

		num_vertices = num_v;
		islight=0;
		vertex_buffer_size = num_v*16;
		texture_buffer_size = num_v*8;
		color_buffer_size = num_v*16;
		normal_buffer_size= num_v*12;
		// initialize vao and vbo of the object;


		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + texture_buffer_size+color_buffer_size+
			normal_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, texture_buffer_size, tex_coord );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+texture_buffer_size, 
			color_buffer_size, a_colours );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+texture_buffer_size+color_buffer_size, 
			normal_buffer_size,normals);

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( texCoord );
  		glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size) );

  		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, 
			BUFFER_OFFSET(vertex_buffer_size+texture_buffer_size) );

		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, 
			BUFFER_OFFSET(vertex_buffer_size+texture_buffer_size+color_buffer_size) );


		tex=texture_file;
		texx=tex_x;
		texy=tex_y;
		if_tex=0;

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
  			if(islight==1 && mylight1)
  			{
  				GLuint temp= LoadTexture("images/glow.bmp",64,48);
  				glBindTexture(GL_TEXTURE_2D, temp);
  			}
  			else if(islight==2 && mylight2)
  			{
  				GLuint temp= LoadTexture("images/glow.bmp",64,48);
  				glBindTexture(GL_TEXTURE_2D, temp);
  			}
  			else
  			{
  				GLuint temp= LoadTexture(tex.c_str(),texx,texy);
  				glBindTexture(GL_TEXTURE_2D, temp);
  			}
  		}
		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glm::mat3 normal_matrix= glm::transpose(glm::inverse(glm::mat3(*ms_mult)));
		glUniformMatrix3fv(normalMatrix,1, GL_FALSE, glm::value_ptr(normal_matrix));
		glUniform1i(vid,if_tex);
		glUniform1i(light1,mylight1);
		glUniform1i(light2,mylight2	);
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

	void HNode::get_rotation(GLfloat t[3]){
		t[0]=rx;
		t[1]=ry;
		t[2]=rz;
	}
	void HNode::set_rotation(GLfloat t[3]){
		rx=t[0];
		ry=t[1];
		rz=t[2];
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
