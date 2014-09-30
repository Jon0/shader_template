namespace std {

struct VertexData {
	glm::vec4 pos;
	glm::vec4 norm;
};

VertexData makeVert(glm::vec4 p) {
	VertexData v;
	v.pos = p;
	return v;
}

};
