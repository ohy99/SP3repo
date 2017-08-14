#ifndef _MOVINGTEXTUREMESH_H
#define _MOVINGTEXTUREMESH_H

#include "Mesh.h"
#include "Vertex.h"
#include <vector>

class MovingTextureMesh : public Mesh {

public:
	const std::vector<Vertex> defaultVDB;
	std::vector<Vertex> vertex_buffer_data;
	MovingTextureMesh(const std::string &meshName, std::vector<Vertex> vbd) : Mesh(meshName), vertex_buffer_data(vbd), defaultVDB(vbd){
		
	}
	~MovingTextureMesh() {
	}

	
};
#endif