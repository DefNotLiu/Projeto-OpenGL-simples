
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL\glut.h>
#include <Windows.h>
#include "RgbImage.h"

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		1.0, 0.0, 0.0, 1.0
#define YELLOW  1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define ORANGE  0.8, 0.6, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.9, 0.92, 0.29, 1.0
#define GRAY1    0.2, 0.2, 0.2, 1.0
#define GRAY2    0.9, 0.9, 0.9, 1.0
#define PI		 3.14159

//================================================================================
//===========================================================Variaveis e constantes

float centrox = 0;
float rotacao = 0, rotacao_abre;

GLfloat tam = 0.5;
float abre_escala[] = { 1.5, 1.5, 2.0 };
float abre_origem[] = {(-tam / 2) * abre_escala[0] - 0.125, 0, (-tam/2) * abre_escala[2]};  //inf esq
float alt_bot = 0.2;
float alt_bot_step = 0;
float transparencia = 1.0;
int carrega = 0, down = 0, roda_tempo = 0, tempo = 0, luzbotao = 0, dim = 64;
static GLfloat vertices[] = {
//…………………………………………………… Esquerda
		-tam,  -tam,  tam,	// 0 
		-tam,   tam,  tam,	// 1 
		-tam,   tam, -tam,	// 2 
		-tam,  -tam, -tam,	// 3 
//…………………………………………………… Direita abre
		 tam,  -tam,  tam,	// 4 
		 tam,   tam,  tam,	// 5 
		 tam,   tam, -tam,	// 6 
		 tam,  -tam, -tam,	// 7 
//……………………………………………………… Cima
		-tam,  tam,  tam,	// 8 
		-tam,  tam, -tam,	// 9 
		 tam,  tam, -tam,	// 10 
		 tam,  tam,  tam,	// 11 
//……………………………………………………… Baixo
		-tam,  -tam, tam,	// 12
		-tam,  -tam, -tam,	// 13
		tam, -tam, -tam,	// 14 
		tam, -tam, tam,	// 15
//…………………………………………………… Frente
		tam,  -tam,  tam,	// 16 
		-tam,  -tam, tam,	// 17 
		-tam,  tam, tam,	// 18 
		tam,  tam, tam,		// 19 
//…………………………………………………… Tras
		 tam,  -tam,  -tam,	// 20 
		 -tam,  -tam,  -tam,// 21 
		-tam,  tam, -tam,	// 22 
		 tam,  tam, -tam	// 23 
};

static GLfloat normais[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  //…………………………………………………………………………………………………… x=tam (Direita)
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		 //…………………………………………………………………………………………………… y=tam (Cima)
			0.0,  1.0,  0.0,
			0.0,  1.0,  0.0,
			0.0,  1.0,  0.0,
			0.0,  1.0,  0.0,
		//…………………………………………………………………………………………………… y=tam (Cima)
			0.0, -1.0, 0.0,
			0.0, -1.0, 0.0,
			0.0, -1.0, 0.0,
			0.0, -1.0, 0.0,

			0.0,  0.0,  1.0,
			0.0,  0.0,  1.0,
			0.0,  0.0,  1.0,
			0.0,  0.0,  1.0,

			0.0,  0.0,  -1.0,
			0.0,  0.0,  -1.0,
			0.0,  0.0,  -1.0,
			0.0,  0.0,  -1.0
};

static GLfloat cor[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda) - Red
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	//…………………………………………………………………………………………………… y=tam (Cima) - Blue
	  0.5, 0.5, 0.5,
	  0.5, 0.5, 0.5,
	  0.5, 0.5, 0.5,
	  0.5, 0.5, 0.5,
	//…………………………………………………………………………………………………… x=2*tam (Direita) - Green
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,

	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,

	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,

	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8,
	  0.8, 0.8, 0.8
};

static GLfloat texturas[] = {
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1 };

static GLuint esquerda[] = { 0, 1,  2,  3 };
static GLuint  direita[] = { 4, 7,  6,  5 };
static GLuint     cima[] = { 8, 11, 10, 9 };
static GLuint	 baixo[] = { 12, 13, 14, 15};
static GLuint   frente[] = { 16, 19, 18, 17 };
static GLuint	  tras[] = { 20, 21, 22, 23 };
static GLuint cima_inv[] = { 8, 9, 10, 11 };
static GLuint esquerda_inv[] = { 0, 3,  2,  1 };

//------------------------------------------------------------ Sistema Coordenadas + objectos
GLint		wScreen = 800, hScreen = 600;		//.. janela
GLfloat		xC = 20.0, yC = 20.0, zC = 20.0;	//.. Mundo
GLboolean   frenteVisivel = 1;
RgbImage imag;
GLuint   texture[5];
GLUquadricObj* esfera = gluNewQuadric();

//------------------------------------------------------------ Observador 
GLfloat  rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao-PI/2), 3.0, rVisao * sin(aVisao-PI/2) };
GLfloat  angZoom = 45;
GLfloat  incZoom = 3;


//------------------------------------------------------------ Rotacao
GLint     msec = 10;
GLint     sempreRodar = 0;
GLfloat   altura = 0;
GLfloat   incALT = 0.03;
GLfloat anguloLuz = 0;
GLfloat intensidadeDia = 0.0;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia, intensidadeDia, 1 };
GLint   ligaTeto = 1;		 //:::   'T'  
GLfloat intensidadeT = 0.3;  //:::   'I'  
GLint   luzR = 1;		 	 //:::   'R'  
GLint   luzG = 1;			 //:::   'G'  
GLint   luzB = 1;			 //:::   'B'  
GLfloat localPos[4] = { 0, 20, 0, 1.0 };
GLfloat localCorAmb[4] = { 1, 1, 1, 1.0 };
GLfloat localCorDif[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localCorEsp[4] = { luzR, luzG, luzB, 1.0 };
GLfloat DirPos[4] = { 1, 0, 0, .0 };
GLfloat DirCorAmb[4] = { 1, 0.5, 0.5, 1.0 };
GLfloat DirCorDif[4] = { luzR, luzG, luzB, 1.0 };
GLfloat DirCorEsp[4] = { luzR, luzG, luzB, 1.0 };
GLint   Dia = 1;
void initMaterials(int material);

//================================================================================
//=========================================================================== INIT

void initTexturas()
{
	//----------------------------------------- Chao - tapete
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("tapete.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- Esfera - skybox envolvente
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("unnamed.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//-----------------------------------------  Acrilico
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("acrilico.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//-----------------------------------------  prato
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("prato.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- Lados Microondas
	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("marmore.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

}

void iluminacao() {
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	GLfloat Foco_direccao[] = { 0, -1, 0, 0 };	//……… -Z
	GLfloat Foco1_cor[] = { 1, 1,  1, 1 };	//……… Cor da luz 1
	GLfloat Foco_ak = 1.0;
	GLfloat Foco_al = 0.05f;
	GLfloat Foco_aq = 0.0f;
	GLfloat Foco_Expon = 2.0;		// Foco, SPOT_Exponent

	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Foco_Expon);

	glLightfv(GL_LIGHT1, GL_POSITION, DirPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, DirCorAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DirCorDif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, DirCorEsp);
}

void initLights(void) {
	//…………………………………………………………………………………………………………………………………………… Ambiente
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	
	//…………………………………………………………………………………………………………………………………………… Teto
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}

void init(void)
{
	glClearColor(WHITE);		//………………………………………………………………………………Apagar
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	
	initTexturas();
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glEnable(GL_NORMALIZE);
	

	glEnable(GL_CULL_FACE);		//………………………………………………………………………………Faces visiveis
	glCullFace(GL_BACK);		//………………………………………………………………………………Mostrar so as da frente

	//…………………………………………………………………………………………………………………………… ILUMINACAO / MAteriais
	

	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………Vertex arrays
	glNormalPointer(GL_FLOAT, 0, normais);
	glColorPointer(3, GL_FLOAT, 0, cor);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas);   // coordenadas textura

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	initLights();

}

GLvoid resize(GLsizei width, GLsizei height)
{
	wScreen = width;
	hScreen = height;
	glViewport(0, 0, wScreen, hScreen);
	glutPostRedisplay();
}

void drawEsfera()
{
	//------------------------- Esfera
	//initMaterials(16);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluQuadricDrawStyle(esfera, GLU_FILL);
	gluQuadricNormals(esfera, GLU_SMOOTH);
	gluQuadricTexture(esfera, GL_TRUE);
	gluSphere(esfera, 60.0, 100, 100);
	gluQuadricOrientation(esfera, GLU_INSIDE);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo
	glColor4f(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(20, 0, 0);
	glEnd();
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 20, 0);
	glEnd();
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 20);
	glEnd();

}


void desenhaContorno() {

	initMaterials(12);
	glBegin(GL_LINES);
		glVertex3f(tam, tam, tam);
		glVertex3f(tam, tam, -tam);
		glVertex3f(tam, tam, tam);
		glVertex3f(tam, -tam, tam);
		glVertex3f(tam, tam, tam);
		glVertex3f(-tam, tam, tam);
		glVertex3f(-tam, tam, tam);
		glVertex3f(-tam, tam, -tam);
		glVertex3f(-tam, tam, tam);
		glVertex3f(-tam, -tam, tam);
		glVertex3f(-tam, -tam, tam);
		glVertex3f(-tam, -tam, -tam);
		glVertex3f(-tam, -tam, tam);
		glVertex3f(tam, -tam, tam);
		glVertex3f(tam, -tam, tam);
		glVertex3f(tam, -tam, -tam);
		glVertex3f(tam, -tam, -tam);
		glVertex3f(-tam, -tam, -tam);
		glVertex3f(tam, -tam, -tam);
		glVertex3f(tam, tam, -tam);
		glVertex3f(-tam, -tam, -tam);
		glVertex3f(-tam, tam, -tam);
		glVertex3f(-tam, tam, -tam);
		glVertex3f(tam, tam, -tam);
	glEnd();

}

void desenhaBotao(){

	GLfloat x = 0, z = 0;
	GLfloat ang = 0, step = 0.1;
	GLfloat raio = 0.2;

	/*Coluna*/
	initMaterials(15);
	glBegin(GL_QUAD_STRIP);
		ang = 2 * PI;
		while (ang > 0) {
			x = raio * cos(ang);
			z = raio * sin(ang);
			glVertex3f(x, alt_bot, z);
			glVertex3f(x, 0, z);
			ang = ang - step;
		}
		glVertex3f(raio, alt_bot, 0);
		glVertex3f(raio, 0, 0);
	glEnd();

	/*Circunferencia sup*/
	initMaterials(5);
	glBegin(GL_POLYGON);
		ang = 2 * PI;
		while (ang > 0) {
			x = raio * cos(ang);
			z = raio * sin(ang);
			glVertex3f(x, alt_bot, z);
			ang = ang - step;
		}
	glEnd();
}

void desenhaPrato() {

	GLfloat x = 0, z = 0;
	GLfloat ang = 0, step = 0.1;
	GLfloat raio = 0.5;

	glTranslatef(0, -0.7, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_POLYGON);
	ang = 2*PI;
	while (ang > 0) {
		x = raio * cos(ang);
		z = raio * sin(ang);
		glTexCoord2f((cos(ang)+1)*0.5, (sin(ang)+1)*0.5);
		glVertex3f(x, alt_bot, z);
		ang = ang - step;
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void desenhaFrente() {

	initMaterials(2);
	glBegin(GL_QUADS);
	    glColor3f(0.1, 0.1, 0.1);
		glVertex3f(tam, tam, tam); //esquerda pa baixo
		glVertex3f(tam, 5 * -tam / 6, tam);
		glVertex3f(tam, 5 * -tam / 6, 5 * tam / 6);
		glVertex3f(tam, tam, 5 * tam / 6);
		glVertex3f(tam, -tam, tam);//baixo pa direita
		glVertex3f(tam, -tam, 5 * -tam / 6);
		glVertex3f(tam, 5 * -tam / 6, 5 * -tam / 6);
		glVertex3f(tam, 5 * -tam / 6, tam);
		glVertex3f(tam, -tam, -tam); //direita pa cima
		glVertex3f(tam, 5 * tam / 6, -tam);
		glVertex3f(tam, 5 * tam / 6, -5 * tam / 6);
		glVertex3f(tam, -tam, -5 * tam / 6);
		glVertex3f(tam, tam, -tam); //cima pa esquerda
		glVertex3f(tam, tam, 5 * tam / 6);
		glVertex3f(tam, 5 * tam / 6, 5 * tam / 6);
		glVertex3f(tam, 5 * tam / 6, -tam);
	glEnd();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();
	initMaterials(16);
	glMaterialf(GL_FRONT, GL_DIFFUSE, transparencia);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);    glVertex3f(tam, 5*tam/6, 5*-tam/6); //C
		glTexCoord2f(1.0f, 1.0f); 	 glVertex3f(tam, 5*tam/6, 5*tam/6);  //B
		glTexCoord2f(1.0f, 0.0f);    glVertex3f(tam, 5*-tam/6, 5*tam/6); //A
		glTexCoord2f(0.0f, 0.0f);  	 glVertex3f(tam, 5*-tam/6, 5*-tam/6); //D
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	


}

void drawScene() {

	//=================================================== BULE
	if (frenteVisivel == 0)
		glDisable(GL_CULL_FACE);		//………………………………………………………………………………Faces visiveis
	else
		glEnable(GL_CULL_FACE);		//………………………………………………………………………………Faces visiveis
	if (frenteVisivel == 1)
		glCullFace(GL_BACK);  //glFrontFace(GL_CW);
	if (frenteVisivel == 2)
		glCullFace(GL_FRONT);  //glFrontFace(GL_CCW);


	//==================================== MESA	


	if (sempreRodar) {
		rotacao = rotacao + 1;
		altura = altura + incALT;
		if (altura > 3) incALT = -incALT;
		if (altura < -1) incALT = -incALT;
	}

	glTranslatef(centrox, altura, 0.0);
	glRotatef(rotacao, 0.0, 1.0, 0.0);
	//botao && prato
	glPushMatrix();
	if (roda_tempo > 0) {
		glRotatef(36 * tempo, 0, 1, 0);
	}
		desenhaPrato();
	glPopMatrix();
	glPushMatrix();
		if (carrega)
			glTranslatef(0, -alt_bot_step, 0);
		glTranslatef(0, tam * abre_escala[1], 0);
		desenhaBotao();
	glPopMatrix();
	glScalef(abre_escala[0], abre_escala[1], abre_escala[2]);
	
	
	glPushMatrix();
	initMaterials(17);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glEnable(GL_TEXTURE_2D);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, cima);

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, tras);
	glPushMatrix();
	glTranslatef(-tam, -tam, -tam);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.5, 0.5, 0);
	glNormal3f(-1, 0, 0);
	glBegin(GL_QUADS);
	int med_dim = dim / 2;
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
		}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	//desenhaContorno();
	//abre
	glPushMatrix();
	glTranslatef(-abre_origem[0], -abre_origem[1], -abre_origem[2]);
	glRotatef(rotacao_abre, 0, 1, 0);
	glTranslatef(abre_origem[0], abre_origem[1], abre_origem[2]);
	desenhaFrente();
	glPopMatrix();
}

void display(void) {

	//================================================================= APaga 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= Não modificar
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)wScreen / hScreen, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//================================================================= Não modificar

	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	
	//…………………………………………………………………………………………………………………………………………………………Objectos
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	iluminacao();
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	drawEsfera();
	drawEixos();
	drawScene();
	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}


void Timer(int value)
{
	if (carrega) {

		if (alt_bot_step < alt_bot && down == 0) {
			alt_bot_step += 0.01;
			if (alt_bot_step >= alt_bot)
				down = 1;
		}

		if (alt_bot_step > 0 && down == 1) {
			alt_bot_step -= 0.01;
			if (alt_bot_step == 0)
				carrega = 0;
		}

	}
	if(roda_tempo > tempo)
		tempo += 1;
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {
	case 'f':
	case 'F':
		frenteVisivel = (frenteVisivel + 1) % 3;
		glutPostRedisplay();
		break;

	case 'W':
	case 'w':
		centrox = centrox + 0.25;
		glutPostRedisplay();
		break;

	case 'S':
	case 's':
		centrox = centrox - 0.25;
		glutPostRedisplay();
		break;

	case 'e':
	case 'E':
		rotacao = rotacao + 2.5;
		glutPostRedisplay();
		break;

	case 'Q':
	case 'q':
		rotacao = rotacao - 2.5;
		glutPostRedisplay();
		break;

	case 'D':
	case 'd':
		if (rotacao_abre >= 0){}
		else
			rotacao_abre += 2.5;
		glutPostRedisplay();
		break;

	case 'A':
	case 'a':
		if (rotacao_abre <= -90) {}
		else
			rotacao_abre -= 2.5;
		glutPostRedisplay();
		break;

	case 'R':
	case 'r':
		rVisao = rVisao++;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
		glutPostRedisplay();
		break;

	case 'T':
	case 't':
		rVisao = rVisao--;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
		glutPostRedisplay();
		break;

	case 'b':
	case 'B':
		carrega = 1;
		down = 0;
		roda_tempo += 10;
		glutPostRedisplay();
		break;

	case 'C':
	case 'c':
		if (transparencia + 0.05 <= 1)
			transparencia += 0.05;
		glutPostRedisplay();
		break;

	case 'V':
	case 'v':
		if (transparencia - 0.05 >= 0)
			transparencia -= 0.05;
		glutPostRedisplay();
		break;

	case 'L':
	case 'l':
		Dia = !Dia;
		if (Dia) {
			luzGlobalCorAmb[0] = 1;
			luzGlobalCorAmb[1] = 1;
			luzGlobalCorAmb[2] = 1;
		}
		else {
			luzGlobalCorAmb[0] = 0.0;
			luzGlobalCorAmb[1] = 0.0;
			luzGlobalCorAmb[2] = 0.0;
		}
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
		glutPostRedisplay();
		break;

	case 'K':
	case 'k':
		luzbotao += 1;
		if (luzbotao % 4 == 0) {
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
		}
		else if (luzbotao % 4 == 1) {
			glEnable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
		}
		else if (luzbotao % 4 == 2) {
			glEnable(GL_LIGHT1);
			glDisable(GL_LIGHT0);
		}
		else {
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT0);
		}
		glutPostRedisplay();
		break;

	case 'H':
	case 'h':
		dim = 2 * dim;
		if (dim > 256) dim = 256;
		glutPostRedisplay();
		break;

	case 'G':
	case 'g':
		dim = 0.5 * dim;
		if (dim < 1) dim = 1;
		glutPostRedisplay();
		break;

	case 'M':
	case 'm':
		printf("ola %f", anguloLuz);
		anguloLuz += 36;
		if (anguloLuz == 360)
			anguloLuz = 0;
		glLightfv(GL_LIGHT0, GL_POSITION, localPos);
		glutPostRedisplay();
		break;
		//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}

}



void teclasNotAscii(int key, int x, int y) {

	if (key == GLUT_KEY_UP)
		obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN)
		obsP[1] = (obsP[1] - 0.1);


	if (key == GLUT_KEY_LEFT)
		aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT)
		aVisao = (aVisao - 0.1);

	obsP[0] = rVisao * cos(aVisao - PI/2);
	obsP[2] = rVisao * sin(aVisao - PI/2);


	glutPostRedisplay();

}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("|Abrir porta:'a/d'|    |Botão:'b'|    |FaceVisivel:'f'|    |Observador:'SETAS'|    |Andar:'w/s'|    |Rodar:'q/e'|    |Luzes dir e foco:k, ambiente:l|");
	init();
	glutSpecialFunc(teclasNotAscii);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}



