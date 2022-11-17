#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <vector_matrix.h>

using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
	float normal[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3


Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f }, { 0, 0, 1, 0} },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f }, { 0, 0, 1, 0} },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f }, { 0, 0, 1, 0} },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f }, { 0, 0, 1, 0} },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f }, { 0, 0, 1, 0} },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f }, { 0, 0, 1, 0} },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f }, { 1, 0, 0, 0} },
	{ { 0.5f,	-0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f }, { 1, 0, 0, 0} },
	{ { 0.5f,	-0.5f,  -0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f }, { 1, 0, 0, 0} },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f }, { 1, 0, 0, 0} },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f }, { 1, 0, 0, 0} },
	{ { 0.5f,	 0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f }, { 1, 0, 0, 0} },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f }, { 0, 1, 0, 0} },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f }, { 0, 1, 0, 0} },
	{ { -0.5f,	0.5f,	 -0.5f, 1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f }, { 0, 1, 0, 0} },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f }, { 0, 1, 0, 0} },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f }, { 0, 1, 0, 0} },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f }, { 0, 1, 0, 0} },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f }, {-1, 0, 0, 0} },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f }, {-1, 0, 0, 0} } ,
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f }, {-1, 0, 0, 0} },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	 -0.5f, 1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f }, {-1, 0, 0, 0} },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f }, {-1, 0, 0, 0} },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f }, {-1, 0, 0, 0} },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 1.0f,	1.0f,	0.0f,	1.0f }, { 0, -1, 0, 0} },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 1.0f,	1.0f,	0.0f,	1.0f }, { 0, -1, 0, 0} },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 1.0f,	1.0f,	0.0f,	1.0f }, { 0, -1, 0, 0} },
	// v3-v2-v7
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	1.0f,	0.0f,	1.0f }, { 0, -1, 0, 0} },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	1.0f,	0.0f,	1.0f }, { 0, -1, 0, 0} },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 1.0f,	1.0f,	0.0f,	1.0f }, { 0, -1, 0, 0} },

	// v4-v7-v6 (back)
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	1.0f,	1.0f }, { 0, 0, -1, 0} },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	1.0f,	1.0f }, { 0, 0, -1, 0} },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	1.0f,	1.0f }, { 0, 0, -1, 0} },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.0f,	1.0f,	1.0f,	1.0f }, { 0, 0, -1, 0} },
	{ { 0.5f,	0.5f,	 -0.5f,1.0f },{ 0.0f,	1.0f,	1.0f,	1.0f }, { 0, 0, -1, 0} },
	{ { 0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.0f,	1.0f,	1.0f,	1.0f }, { 0, 0, -1, 0} }
};


const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);
const size_t NormalOffset = sizeof(Vertices[0].XYZW) + sizeof(Vertices[1].RGBA);

int
CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
ColorBufferId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4 instance;

// biến của camera
GLfloat l = -1.0, r = 1.0;
GLfloat bottom = -1.0, top = 1.0;
GLfloat zNear = 2.5, zFar = 5;

//GLfloat radius = 1, theta2 = 0, phi = 0;

//const GLfloat dr = 5.0 * degrees_to_radians;

mat4
model_mat_cpp,
view_mat_cpp,			//Ma trận view
projection_mat_cpp,		//Ma trận projection
model_mat_cpp1;

int
model_location,
model_view_loc,
projection_loc;

//GLfloat theta[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
GLfloat R[] = { 0, 0, 0 }; // xoay ô tô
GLfloat cancau[] = {0, 0, 0}; // điều khiển cần cẩu 0: trục, 1: con lăn, 2: dây
GLfloat thungxe = 0.0;
GLfloat T = 0.0f;
// kích thước ô tô
GLdouble x_thung = 0.8, y_thung = 0.01, z_thung = 0.3, x_dau = 0.4, y_dau = 0.5,
z_dau = 0.3, banh_xe = 0.05, y_khung = 0.03, x_khung = 0.1;

// ------------------------------------------
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

bool CompileShader(GLuint shaderID) {
	cout << "Compiling shader" << shaderID << "..." << endl;
	glCompileShader(shaderID);
	int result = -1;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		cout << "Shader " << shaderID << " compile failed" << endl;
		int maxLength = 2048;
		int realLength = 0;
		char log[2048];
		glGetShaderInfoLog(shaderID, maxLength, &realLength, log);
		cout << log << endl;
		return false;
	}
	cout << "Shader " << shaderID << " compile successful" << endl;
	return true;
}


// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

void dauxe()
{
	instance = translate(vec3(x_thung / 2 + x_dau / 2, y_dau / 2 - y_thung / 2, 0.0)) * scale(vec3(x_dau, y_dau, z_dau));
	mat4 model_dau_xe = model_mat_cpp * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_dau_xe.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void khung(GLfloat a, GLfloat b, GLfloat c)
{
	instance = translate(vec3(a, b, c)) * scale(vec3(x_thung, y_khung, z_thung));
	mat4 model_khung = model_mat_cpp * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_khung.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thung1()
{
	instance = scale(vec3(x_thung, y_thung, z_thung));
	mat4 model_thung_day = model_mat_cpp * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_thung_day.m);
	glDrawArrays(GL_TRIANGLES, 0, 36); //thung day

	instance = translate(vec3(0, y_dau / 2 - y_dau / 5, z_thung / 2)) * rotate_x(90) * instance;
	mat4 model_thung_trai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_thung_trai.m);
	glDrawArrays(GL_TRIANGLES, 0, 36); //thung mat trai

	instance = translate(vec3(0, y_dau - z_thung / 1.5, 0)) * rotate_x(180) * instance;
	mat4 model_thung_phai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_thung_phai.m);
	glDrawArrays(GL_TRIANGLES, 0, 36); // thung mat phai

	instance = scale(vec3(x_thung * 1.5, 1, z_thung * 1.3)) * translate(vec3(x_thung / 1.65, 0, 0)) * rotate_y(90) * instance;
	mat4 model_thung_trc = model_mat_cpp * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_thung_trc.m);
	glDrawArrays(GL_TRIANGLES, 0, 36); // thung mat truoc
}

void cuaxetrai()
{
	instance = translate(vec3(x_thung / 1.4, y_dau / 2, z_dau / 2)) * scale(vec3(0.2, 0.2, 0.01));
	mat4 model_cua_trai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_cua_trai.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cuaxephai()
{
	instance = translate(vec3(x_thung / 1.4, y_dau / 2, -z_dau / 2)) * scale(vec3(0.2, 0.2, 0.01));
	mat4 model_cua_phai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_cua_phai.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Banhxe(GLfloat a, GLfloat b, GLfloat c, int x)
{
	instance = translate(vec3(a, b, c)) * scale(vec3(0.1, 0.15, 0.1)) * rotate_z(x);
	mat4 model_banhxe = model_mat_cpp * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_banhxe.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void BongDen(GLfloat a, GLfloat b, GLfloat c, int x)
{
	instance = translate(vec3(a, b, c)) * scale(vec3(0.1, 0.15, 0.1)) * rotate_z(x);
	model_mat_cpp1 = identity_mat4() * scale(vec3(0.5, 0.5, 0.5));
	mat4 model_banhxe = model_mat_cpp1 * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_banhxe.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}
void Da(GLfloat a, GLfloat b, GLfloat c, int x)
{
	instance = translate(vec3(a, b, c)) * scale(vec3(0.015, 0.05, 1.4)) * rotate_z(x) * rotate_y(90);
	model_mat_cpp1 = identity_mat4() * scale(vec3(0.5, 0.5, 0.5));
	mat4 model_banhxe = model_mat_cpp1 * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_banhxe.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
// cần cẩu
GLfloat i = 0;
mat4 instance_ban;
mat4 Model;
//0.65f, -0.032f, 0.0f
GLfloat a = 0.65f;
GLfloat b = -0.032f;
GLfloat c = 0.0f;
void than(GLfloat w, GLfloat l, GLfloat h) 
{
	instance = scale(vec3(w, l, h));
	mat4 model_than = Model * instance_ban * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_than.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void dau(GLfloat w, GLfloat h)
{
	instance = scale(vec3(w, h, w));
	mat4 model_dau = Model * instance_ban * instance;
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_dau.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void than3() // đan chéo
{
	// 1
	instance_ban = translate(vec3(0.05f, 0.05f, -0.05f)) * rotate_z(45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.05f, 0.05f, -0.05f)) * rotate_z(-45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.05f, 0.05f, 0.06f)) * rotate_z(45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.05f, 0.05f, 0.06f)) * rotate_z(-45);
	than(0.13f, 0.02f, 0.02f);
	// 2
	instance_ban = translate(vec3(0.15f, 0.05f, -0.05f)) * rotate_z(45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.15f, 0.05f, -0.05f)) * rotate_z(-45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.15f, 0.05f, 0.06f)) * rotate_z(45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.15f, 0.05f, 0.06f)) * rotate_z(-45);
	than(0.13f, 0.02f, 0.02f);
	// 3
	instance_ban = translate(vec3(0.25f, 0.05f, -0.05f)) * rotate_z(45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.25f, 0.05f, -0.05f)) * rotate_z(-45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.25f, 0.05f, 0.06f)) * rotate_z(45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.25f, 0.05f, 0.06f)) * rotate_z(-45);
	than(0.13f, 0.02f, 0.02f);
	// 4
	instance_ban = translate(vec3(0.35f, 0.05f, -0.05f)) * rotate_z(45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.35f, 0.05f, -0.05f)) * rotate_z(-45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.35f, 0.05f, 0.06f)) * rotate_z(45);
	than(0.13f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.35f, 0.05f, 0.06f)) * rotate_z(-45);
	than(0.13f, 0.02f, 0.02f);
	// 5
	instance_ban = translate(vec3(0.45f, 0.04f, -0.05f)) * rotate_z(45);
	than(0.11f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.45f, 0.04f, -0.05f)) * rotate_z(-45);
	than(0.11f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.45f, 0.04f, 0.06f)) * rotate_z(45);
	than(0.11f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.45f, 0.04f, 0.06f)) * rotate_z(-45);
	than(0.11f, 0.02f, 0.02f);
	// 6
	instance_ban = translate(vec3(0.55f, 0.03f, -0.05f)) * rotate_z(45);
	than(0.09f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.55f, 0.03f, -0.05f)) * rotate_z(-45);
	than(0.09f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.55f, 0.03f, 0.06f)) * rotate_z(45);
	than(0.09f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.55f, 0.03f, 0.06f)) * rotate_z(-45);
	than(0.09f, 0.02f, 0.02f);
	// 7
	instance_ban = translate(vec3(0.65f, 0.03f, -0.05f)) * rotate_z(45);
	than(0.08f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.65f, 0.03f, -0.05f)) * rotate_z(-45);
	than(0.08f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.65f, 0.03f, 0.06f)) * rotate_z(45);
	than(0.08f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.65f, 0.03f, 0.06f)) * rotate_z(-45);
	than(0.08f, 0.02f, 0.02f);
	// 8
	instance_ban = translate(vec3(0.75f, 0.03f, -0.05f)) * rotate_z(45);
	than(0.07f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.75f, 0.03f, -0.05f)) * rotate_z(-45);
	than(0.07f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.75f, 0.03f, 0.06f)) * rotate_z(45);
	than(0.07f, 0.02f, 0.02f);
	instance_ban = translate(vec3(0.75f, 0.03f, 0.06f)) * rotate_z(-45);
	than(0.07f, 0.02f, 0.02f);
	//
}
void can()
{// dau
	instance_ban = translate(vec3(0.35f, 0.0f, -0.05f));
	than(1.3f, 0.01f, 0.02f);
	instance_ban = translate(vec3(0.35f, 0.0f, 0.05f));
	than(1.3f, 0.01f, 0.02f);
	//

	// vach ngan
	instance_ban = rotate_z(-5) * translate(vec3(0.5f, 0.122f, -0.05f));
	than(1.0f, 0.01f, 0.02f);
	instance_ban = rotate_z(-5) * translate(vec3(0.5f, 0.122f, 0.05f));
	than(1.0f, 0.01f, 0.02f);

	//
	instance_ban = rotate_z(15) * translate(vec3(-0.11f, 0.12f, -0.05f));
	than(0.3f, 0.01f, 0.02f);
	instance_ban = rotate_z(15) * translate(vec3(-0.11f, 0.12f, 0.05f));
	than(0.3f, 0.01f, 0.02f);
	instance_ban = translate(vec3(-0.25f, 0.05f, 0.0f));
	than(0.1f, 0.1f, 0.2f);
	instance_ban = translate(vec3(-0.35f, 0.05f, 0.0f));
	than(0.1f, 0.1f, 0.2f);
	instance_ban = translate(vec3(0.0f, 0.05f, 0.0f));
	than(0.05f, 0.05f, 0.1f);
	instance_ban = translate(vec3(0.0f, 0.2f, 0.0f));
	dau(0.03f, 0.3f);

	//
	instance_ban = translate(vec3(-0.2f, 0.18f, 0.0f)) * rotate_z(-50);
	than(0.01f, 0.5f, 0.01f);
	instance_ban = translate(vec3(0.48f, 0.18f, 0.0f)) * rotate_z(72);
	than(0.01f, 1.05f, 0.01f);
	//

	instance_ban = translate(vec3(0.5f, 0.04f, 0.0f));
	than(0.01f, 0.08f, 0.15f);

	instance_ban = translate(vec3(0.6f, 0.04f, 0.0f));
	than(0.01f, 0.07f, 0.15f);

	instance_ban = translate(vec3(0.7f, 0.036f, 0.0f));
	than(0.01f, 0.06f, 0.15f);

	instance_ban = translate(vec3(0.8f, 0.03f, 0.0f));
	than(0.01f, 0.05f, 0.15f);

	instance_ban = translate(vec3(0.9f, 0.028f, 0.0f));
	than(0.01f, 0.04f, 0.15f);
	//
	instance_ban = translate(vec3(0.1f, 0.06f, 0.0f));
	than(0.01f, 0.1f, 0.15f);

	instance_ban = translate(vec3(0.2f, 0.05f, 0.0f));
	than(0.01f, 0.1f, 0.15f);

	instance_ban = translate(vec3(0.3f, 0.05f, 0.0f));
	than(0.01f, 0.09f, 0.15f);

	instance_ban = translate(vec3(0.4f, 0.05f, 0.0f));
	than(0.01f, 0.085f, 0.15f);

	instance_ban = translate(vec3(0.01f, 0.062f, 0.0f));
	than(0.01f, 0.12f, 0.15f);

	// dau can
	instance_ban = translate(vec3(1.0f, 0.02f, 0.0f));
	than(0.05f, 0.04f, 0.1f);
	//
	instance_ban = translate(vec3(0.1f, 0.0f, 0.0f));
	dau(0.017f, 0.08f);
	instance_ban = translate(vec3(1.0f, 0.0f, 0.0f));
	dau(0.017f, 0.08f);
	instance_ban = translate(vec3(0.55f, -0.032f, 0.0f));
	than(0.9f, 0.017f, 0.017f);
}
void t1()
{
	// than 1: 
	instance_ban = identity_mat4();
	instance_ban = translate(vec3(0.0f, -0.1f, 0.0f));
	than(0.15f, 0.02f, 0.15f);
	instance_ban = translate(vec3(0.0f, -0.2f, 0.0f));
	dau(0.03f, 0.5f);
	instance_ban = translate(vec3(0.0f, -0.4f, 0.0f));
	dau(0.15f, 0.02f);
	//
	instance_ban = translate(vec3(0.07f, -0.25f, 0.05f));
	than(0.01f, 0.3f, 0.01f);
	instance_ban = rotate_z(-25) * translate(vec3(0.1f, -0.22f, 0.05f));
	than(0.01f, 0.32f, 0.01f);

	instance_ban = translate(vec3(-0.07f, -0.25f, 0.05f));
	than(0.01f, 0.3f, 0.01f);
	instance_ban = rotate_z(25) * translate(vec3(-0.1f, -0.22f, 0.05f));
	than(0.01f, 0.32f, 0.01f);

	instance_ban = translate(vec3(0.07f, -0.25f, -0.05f));
	than(0.01f, 0.3f, 0.01f);
	instance_ban = rotate_z(-25) * translate(vec3(0.1f, -0.22f, -0.05f));
	than(0.01f, 0.3f, 0.01f);

	instance_ban = translate(vec3(-0.07f, -0.25f, -0.05f));
	than(0.01f, 0.3f, 0.01f);
	instance_ban = rotate_z(25) * translate(vec3(-0.1f, -0.22f, -0.05f));
	than(0.01f, 0.3f, 0.01f);

	instance_ban = translate(vec3(0.0f, -0.8f, 0.0f));
	dau(0.17f, 0.8f);
	instance_ban = translate(vec3(0.0f, -1.2f, 0.0f));
	dau(0.3f, 0.05f);
}
void t2()
{
	instance_ban = identity_mat4();
	instance_ban = translate(vec3(-2.18999f, -0.7f, 0.15f)) * rotate_y(270);
	than(-0.09f, 1.0f, 0.015f);
	for (int i = 1; i <= 99; i++) {
		BongDen(-1.69f, 0.97f, 0.15f, i);
	}
}
void t3()
{
	for (GLfloat j = 1.36f; j <= 1.94f; j = j + 0.04f) {
		for (int i = 1; i <= 99; i++) {
			Da(j, -0.077f, 0.015f, i);
		}
	}
	for (GLfloat j = 1.40f; j <= 1.90f; j = j + 0.04f) {
		for (int i = 1; i <= 99; i++) {
			Da(j, -0.018f, 0.015f, i);
		}
	}
	for (GLfloat j = 1.44f; j <= 1.86f; j = j + 0.04f) {
		for (int i = 1; i <= 99; i++) {
			Da(j, 0.041f, 0.015f, i);
		}
	}
	for (GLfloat j = 1.47f; j <= 1.82f; j = j + 0.04f) {
		for (int i = 1; i <= 99; i++) {
			Da(j, 0.1f, 0.015f, i);
		}
	}
	for (GLfloat j = 1.51f; j <= 1.78f; j = j + 0.04f) {
		for (int i = 1; i <= 99; i++) {
			Da(j, 0.159f, 0.015f, i);
		}
	}
	for (GLfloat j = 1.55f; j <= 1.74f; j = j + 0.04f) {
		for (int i = 1; i <= 99; i++) {
			Da(j, 0.218f, 0.015f, i);
		}
	}
	for (GLfloat j = 1.59f; j <= 1.70f; j = j + 0.04f) {
		for (int i = 1; i <= 99; i++) {
			Da(j, 0.277f, 0.015f, i);
		}
	}
	for (GLfloat j = 1.63f; j <= 1.66f; j = j + 0.04f) {
		for (int i = 1; i <= 99; i++) {
			Da(j, 0.336f, 0.015f, i);
		}
	}
}
void truot(GLfloat a, GLfloat b, GLfloat c)
{
	instance_ban = translate(vec3(a, b, c)); //0.65f, -0.032f, 0.0f
	dau(0.05f, 0.05f);
}
void day()
{
	instance_ban = translate(vec3(0.65f, -0.45f, 0.0f));
	dau(0.012f, 0.8f);
}

void thunghang(vec3(tran))
{
	mat4 model_thung = identity_mat4() * translate(tran) * rotate_y(45) * scale(vec3(0.3, 0.15, 0.15));
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_thung.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


float
cam_speed = 0.05f,
cam_rot_speed = 1.0f,
cam_pos[] = { 0.0f, 0.0f, 3.0f },
cam_x = 0.0f,
cam_y = 0.0f,
cam_z = 0.0f;

void DisplayFunc(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	//xe
	model_mat_cpp = identity_mat4() * scale(vec3(0.5, 0.5, 0.5));
	model_mat_cpp = model_mat_cpp * rotate_x(R[0]) * rotate_y(R[1]) * rotate_z(R[2]);
	model_mat_cpp = model_mat_cpp * translate(vec3(T, 0, 0.3));
	dauxe();

	khung(0.2, -(y_thung) / 2, 0);
	for (int i = 1; i <= 90; i++) {
		Banhxe(-(x_thung / 3) + x_thung / 2 + banh_xe, -(y_thung + banh_xe) / 2, -z_thung / 2, i); //banh phai giua
		Banhxe(-(x_thung / 3) + x_thung / 2 + banh_xe, -(y_thung + banh_xe) / 2, z_thung / 2, i); //banh trai giua
		Banhxe(-(x_thung / 3) + x_thung + banh_xe, -(y_thung + banh_xe) / 2, -z_thung / 2, i);
		Banhxe(-(x_thung / 3) + x_thung + banh_xe, -(y_thung + banh_xe) / 2, z_thung / 2, i);
		Banhxe(-(x_thung / 3) + banh_xe, -(y_thung + banh_xe) / 2, z_thung / 2, i); //banh trai sau
		Banhxe(-(x_thung / 3) + banh_xe, -(y_thung + banh_xe) / 2, -z_thung / 2, i); //banh trai sau
	}
	cuaxetrai();
	cuaxephai();
	model_mat_cpp = model_mat_cpp * translate(vec3(-i / 2, 2 * i, 0)) * rotate_z(thungxe);
	thung1();


	//can cau
	Model = identity_mat4() * scale(vec3(0.5, 0.5, 0.5)) * translate(vec3(0.5f, 1.1f, 0.0f));
	t1();
	//Biển cảnh báo
	t2();
	Model = Model * rotate_y(cancau[0]);
	can();
	than3();
	Model = Model * translate(vec3(cancau[1], 0.0, 0.0));
	truot(0.65f, -0.032f, 0.0f);
	Model = Model * scale(vec3(1.0, cancau[2], 1.0));
	day();
	
	thunghang(vec3(-0.6, 0.0, 0.0));
	thunghang(vec3(-0.5, 0.0, 0.2));
	thunghang(vec3(-0.55, 0.15, 0.1));
	//Khối gỗ
	t3();
	// phép chiếu
	mat4 Tran = translate(vec3(-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	mat4 Rotate = rotate_x(-cam_x) * rotate_y(-cam_y) * rotate_z(-cam_z);

	view_mat_cpp = Rotate * Tran;
	model_view_loc = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(model_view_loc, 1, GL_FALSE, view_mat_cpp.m);

	projection_mat_cpp = frustum(l, r, bottom, top, zNear, zFar);
	projection_loc = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection_mat_cpp.m);

	glutSwapBuffers();
}

void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	// keyboard handler
	switch (key) {
	case 27: // Escape Key
		exit(EXIT_SUCCESS);
		break;

	case 'y': // xoay xe theo chiều y
		R[1] += 5;
		if (R[1] > 360) R[1] -= 360;
		glutPostRedisplay();
		break;
	case 'Y':
		// một số lệnh 
		R[1] -= 5;
		if (R[1] > 360) R[1] -= 360;
		glutPostRedisplay();
		break;
	case 'x': // xoay xe theo chiều x
		R[0] += 5;
		if (R[1] > 360) R[1] -= 360;
		glutPostRedisplay();
		break;
	case 'X':
		// một số lệnh 
		R[0] -= 5;
		if (R[1] > 360) R[1] -= 360;
		glutPostRedisplay();
		break;
	case 'z': // xoay xe theo chiều z
		R[2] += 5;
		if (R[1] > 360) R[1] -= 360;
		glutPostRedisplay();
		break;
	case 'Z':
		// một số lệnh 
		R[2] -= 5;
		if (R[1] > 360) R[1] -= 360;
		glutPostRedisplay();
		break;

	case 'd': // tịnh tiến xe
		T += 0.05;
		glutPostRedisplay();
		break;
	case 'D':
		// một số lệnh 
		T -= 0.05;

		glutPostRedisplay();
		break;

	case 'u': // lật thùng xe
		// một số lệnh 
		if (thungxe < 30)
		{
			thungxe += 5;
			i = i + 0.01;
		}
		else {}
		glutPostRedisplay();
		break;
	case 'U':
		// một số lệnh 

		if (thungxe > 0)
		{
			thungxe -= 5;
			i = i - 0.01;
		}
		glutPostRedisplay();
		break;

	// điều khiển quay camera theo các trục
		// quay theo trục x
	case 'r':
		cam_x += cam_rot_speed;
		break;
	case 'R':
		cam_x -= cam_rot_speed;
		break;

		// quay theo trục y
	case 't':
		cam_y += cam_rot_speed;
		break;
	case 'T':
		cam_y -= cam_rot_speed;
		break;

		// quay theo trục z
	case 'p':
		cam_z += cam_rot_speed;
		break;
	case 'P':
		cam_z -= cam_rot_speed;
		break;

	case ' ': // reset
		l = -1.0;
		r = 1.0;
		bottom = -1.0;
		top = 1.0;
		zNear = 2.5;
		zFar = 5.0;
		cam_pos[0] = 0.0f;
		cam_pos[1] = 0.0f;
		cam_pos[2] = 3.0f;
		cam_x = 0.0f;
		cam_y = 0.0f;
		cam_z = 0.0f;
		R[0] = 0;
		R[1] = 0;
		R[2] = 0;
		T = 0;
		cancau[0] = 0;
		cancau[1] = 0;
		cancau[2] = 0;
		thungxe = 0;
		i = 0;
		break;
		// dieu khien can cau
	case 'm': // điều khiển trục
		cancau[0] -= 0.5;
		if (cancau[0] > 360) cancau[0] -= 360;
		glutPostRedisplay();
		break;
	case 'M':
		// một số lệnh
		cancau[0] += 0.5;
		if (cancau[0] > 360) cancau[0] -= 360;
		glutPostRedisplay();
		break;
	case 'n': // điều khiển con trượt
		// một số lệnh
		cancau[1] += 0.005;
		if (cancau[1] > 0.35)
		{
			cancau[1] = 0;
		}
		glutPostRedisplay();
		break;
	case 'N':
		// một số lệnh
		cancau[1] -= 0.005;
		if (cancau[1] < -0.5)
		{
			cancau[1] = 0;
		}
		glutPostRedisplay();
		break;
	case 'k': // kéo thả dây
		// một số lệnh
		cancau[2] += 0.01;
		if (cancau[2] > 1.5) cancau[2] = 0;
		glutPostRedisplay();
		break;
	case 'K':
		// một số lệnh
		cancau[2] -= 0.01;
		if (cancau[2] < 0) cancau[2] = 0;
		glutPostRedisplay();
		break;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
 // dịch chuyển camera
void SpecialFunc(int key, int x, int y)
{
	switch (key)
	{
	// dịch theo trục x
	case GLUT_KEY_LEFT:
		cam_pos[0] -= cam_speed;
		break;
	case GLUT_KEY_RIGHT:
		cam_pos[0] += cam_speed;
		break;

	// dịch theo trục y
	case GLUT_KEY_UP:
		cam_pos[1] += cam_speed;
		break;
	case GLUT_KEY_DOWN:
		cam_pos[1] -= cam_speed;
		break;
	}

	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y)
{
	// dịch theo trục z
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:    cam_pos[2] += cam_speed;  break;
		case GLUT_RIGHT_BUTTON:   cam_pos[2] -= cam_speed;  break;
		}
	}
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Cong truong xay dung");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutMouseFunc(MouseFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}