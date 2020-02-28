#include <windows.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include "stb_image.h"
#include "myLib.h"
#include <iostream>
GLfloat eye[3] = { -80,80,-80 };//摄像机坐标
GLfloat center[3] = { 0,80,0 };//摄像机视线中心坐标
GLfloat aspect;//窗口宽高比

GLuint wallTex, floorTex, doorTex, grassTex, roofTex, ironTex, zishaTex, cubeTex[6];//各种纹理
GLfloat light_position[] = { 1,1,1,0 };//光源位置 平行光
GLfloat light_ambient[] = { 1,1,1,1.0 };//光源属性
GLfloat light_diffuse[] = { 5,5,5,1.0 };//光源属性
GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };//光源属性
GLfloat mat_specular[] = { 1, 1, 1, 1.0 };//材质属性
GLfloat mat_diffuse[] = { 1,1,1,1.0 };//材质属性
GLfloat mat_shininess[] = { 90.0 };//材质属性
GLboolean displayInside = (false);//是否显示屋内结构

void Drawing()
{

	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CW);

	//设置光源属性
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	//设置材质属性
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);

	//绘制浮空岛
	drawSphere(grassTex,ironTex);

	//天空包围盒
	glPushMatrix();
	glTranslatef(eye[0], eye[1], eye[2]);//设置原点为视点，使天空包围盒与视点相对静止
	glEnable(GL_TEXTURE_2D);//开启二维纹理效果
	glBindTexture(GL_TEXTURE_2D, cubeTex[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5000, -5000, 5000);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5000, 5000, 5000);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(5000, 5000, 5000);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(5000, -5000, 5000);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, cubeTex[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5000, -5000, -5000);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5000, 5000, -5000);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-5000, 5000, 5000);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5000, -5000, 5000);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, cubeTex[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(5000, -5000, -5000);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(5000, 5000, -5000);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-5000, 5000, -5000);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5000, -5000, -5000);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, cubeTex[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(5000, -5000, 5000);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(5000, 5000, 5000);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(5000, 5000, -5000);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(5000, -5000, -5000);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, cubeTex[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5000, 5000, 5000);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(5000, 5000, 5000);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(5000, 5000, -5000);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5000, 5000, -5000);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, cubeTex[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(5000, -5000, 5000);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(5000, -5000, -5000);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-5000, -5000, -5000);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5000, -5000, 5000);
	glEnd();
	glPopMatrix();

	//门侧墙面
	glBindTexture(GL_TEXTURE_2D, wallTex);//绑定纹理
	glNormal3f(1, 0, 0);//设置法向量
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-35.0, 0.0, -20.0);
	glTexCoord2f(0.0f, 1.5f); glVertex3f(-35.0, 30.0, -20.0);
	glTexCoord2f(1.0f, 1.5f); glVertex3f(-35.0, 30.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-35.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-35.0, 20.0, 0.0);
	glTexCoord2f(1.0f, 1.5f); glVertex3f(-35.0, 30.0, 0.0);
	glTexCoord2f(1.5f, 1.5f); glVertex3f(-35.0, 30.0, 10.0);
	glTexCoord2f(1.5f, 1.0f); glVertex3f(-35.0, 20.0, 10.0);
	glTexCoord2f(1.5f, 0.0f); glVertex3f(-35.0, 0.0, 10.0);
	glTexCoord2f(1.5f, 1.5f); glVertex3f(-35.0, 30.0, 10.0);
	glTexCoord2f(2.0f, 1.5f); glVertex3f(-35.0, 30.0, 20.0);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(-35.0, 0.0, 20.0);

	glNormal3f(-1, 0, 0);//设置法向量
	glTexCoord2f(-0.1f, 0.0f); glVertex3f(-37.0, 0.0, -22.0);
	glTexCoord2f(-0.1f, 1.5f); glVertex3f(-37.0, 30.0, -22.0);
	glTexCoord2f(1.0f, 1.5f); glVertex3f(-37.0, 30.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-37.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-37.0, 20.0, 0.0);
	glTexCoord2f(1.0f, 1.5f); glVertex3f(-37.0, 30.0, 0.0);
	glTexCoord2f(1.5f, 1.5f); glVertex3f(-37.0, 30.0, 10.0);
	glTexCoord2f(1.5f, 1.0f); glVertex3f(-37.0, 20.0, 10.0);
	glTexCoord2f(1.5f, 0.0f); glVertex3f(-37.0, 0.0, 10.0);
	glTexCoord2f(1.5f, 1.5f); glVertex3f(-37.0, 30.0, 10.0);
	glTexCoord2f(2.0f, 1.5f); glVertex3f(-37.0, 30.0, 20.0);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(-37.0, 0.0, 20.0);

	glNormal3f(0, 0, 1);//设置法向量
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-37.0, 0.0, 20.0);
	glTexCoord2f(0.0f, 1.5f); glVertex3f(-37.0, 30.0, 20.0);
	glTexCoord2f(0.1f, 1.5f); glVertex3f(-35.0, 30.0, 20.0);
	glTexCoord2f(0.1f, 0.0f); glVertex3f(-35.0, 0.0, 20.0);

	glNormal3f(0, 1, 0);//设置法向量
	glTexCoord2f(-0.1f, -0.1f); glVertex3f(-37.0, 30.0, -22.0);
	glTexCoord2f(-0.1f, 2.0f); glVertex3f(-37.0, 30.0, 20.0);
	glTexCoord2f(0.0f, 2.0f); glVertex3f(-35.0, 30.0, 20.0);
	glTexCoord2f(0.0f, -0.1f); glVertex3f(-35.0, 30.0, -22.0);

	//窗侧墙面
	glNormal3f(0, 0, 1);//设置法向量
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-35.0, 0.0, -20.0);
	glTexCoord2f(0.0f, 0.6f); glVertex3f(-35.0, 12.0, -20.0);
	glTexCoord2f(3.5f, 0.6f); glVertex3f(35.0, 12.0, -20.0);
	glTexCoord2f(3.5f, 0.0f); glVertex3f(35.0, 0.0, -20.0);
	glTexCoord2f(0.0f, 0.6f); glVertex3f(-35.0, 12.0, -20.0);
	glTexCoord2f(1.0f, 0.6f); glVertex3f(-15.0, 12.0, -20.0);
	glTexCoord2f(1.0f, 1.25f); glVertex3f(-15.0, 25.0, -20.0);
	glTexCoord2f(0.0f, 1.25f); glVertex3f(-35.0, 25.0, -20.0);
	glTexCoord2f(0.0f, 1.5f); glVertex3f(-35.0, 30.0, -20.0);
	glTexCoord2f(0.0f, 1.25f); glVertex3f(-35.0, 25.0, -20.0);
	glTexCoord2f(3.5f, 1.25f); glVertex3f(35.0, 25.0, -20.0);
	glTexCoord2f(3.5f, 1.5f); glVertex3f(35.0, 30.0, -20.0);
	glTexCoord2f(2.5f, 0.6f); glVertex3f(15.0, 12.0, -20.0);
	glTexCoord2f(2.5f, 1.25f); glVertex3f(15.0, 25.0, -20.0);
	glTexCoord2f(3.5f, 1.25f); glVertex3f(35.0, 25.0, -20.0);
	glTexCoord2f(3.5f, 0.6f); glVertex3f(35.0, 12.0, -20.0);

	glNormal3f(0, 0, -1);//设置法向量
	glTexCoord2f(-0.1f, 0.0f); glVertex3f(-37.0, 0.0, -22.0);
	glTexCoord2f(-0.1f, 0.6f); glVertex3f(-37.0, 12.0, -22.0);
	glTexCoord2f(3.5f, 0.6f); glVertex3f(35.0, 12.0, -22.0);
	glTexCoord2f(3.5f, 0.0f); glVertex3f(35.0, 0.0, -22.0);
	glTexCoord2f(-0.1f, 0.6f); glVertex3f(-37.0, 12.0, -22.0);
	glTexCoord2f(1.0f, 0.6f); glVertex3f(-15.0, 12.0, -22.0);
	glTexCoord2f(1.0f, 1.25f); glVertex3f(-15.0, 25.0, -22.0);
	glTexCoord2f(-0.1f, 1.25f); glVertex3f(-37.0, 25.0, -22.0);
	glTexCoord2f(-0.1f, 1.5f); glVertex3f(-37.0, 30.0, -22.0);
	glTexCoord2f(-0.1f, 1.25f); glVertex3f(-37.0, 25.0, -22.0);
	glTexCoord2f(3.5f, 1.25f); glVertex3f(35.0, 25.0, -22.0);
	glTexCoord2f(3.5f, 1.5f); glVertex3f(35.0, 30.0, -22.0);
	glTexCoord2f(2.5f, 0.6f); glVertex3f(15.0, 12.0, -22.0);
	glTexCoord2f(2.5f, 1.25f); glVertex3f(15.0, 25.0, -22.0);
	glTexCoord2f(3.5f, 1.25f); glVertex3f(35.0, 25.0, -22.0);
	glTexCoord2f(3.5f, 0.6f); glVertex3f(35.0, 12.0, -22.0);

	glNormal3f(0, 1, 0);//设置法向量
	glTexCoord2f(0.0f, 0.0f); glVertex3f(35.0, 30.0, -20.0);
	glTexCoord2f(0.0f, 0.1f); glVertex3f(35.0, 30.0, -22.0);
	glTexCoord2f(3.5f, 0.1f); glVertex3f(-35.0, 30.0, -22.0);
	glTexCoord2f(3.5f, 0.0f); glVertex3f(-35.0, 30.0, -20.0);

	glNormal3f(1, 0, 0);//设置法向量
	glTexCoord2f(-0.1f, 1.5f); glVertex3f(35.0, 30.0, -22.0);
	glTexCoord2f(0.0f, 1.5f); glVertex3f(35.0, 30.0, -20.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(35.0, 0.0, -20.0);
	glTexCoord2f(-0.1f, 0.0f); glVertex3f(35.0, 0.0, -22.0);

	glNormal3f(0, 1, 0);//设置法向量
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15.0, 12.0, -20.0);
	glTexCoord2f(0.0f, 0.1f); glVertex3f(-15.0, 12.0, -22.0);
	glTexCoord2f(1.5f, 0.1f); glVertex3f(15.0, 12.0, -22.0);
	glTexCoord2f(1.5f, 0.0f); glVertex3f(15.0, 12.0, -20.0);

	glNormal3f(0, -1, 0);//设置法向量
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15.0, 25.0, -22.0);
	glTexCoord2f(0.0f, 0.1f); glVertex3f(-15.0, 25.0, -20.0);
	glTexCoord2f(1.5f, 0.1f); glVertex3f(15.0, 25.0, -20.0);
	glTexCoord2f(1.5f, 0.0f); glVertex3f(15.0, 25.0, -22.0);

	glNormal3f(1, 0, 0);//设置法向量
	glTexCoord2f(0.6f, 0.0f); glVertex3f(-15.0, 12.0, -20.0);
	glTexCoord2f(1.25f, 0.0f); glVertex3f(-15.0, 25.0, -20.0);
	glTexCoord2f(1.25f, 0.1f); glVertex3f(-15.0, 25.0, -22.0);
	glTexCoord2f(0.6f, 0.1f); glVertex3f(-15.0, 12.0, -22.0);

	glNormal3f(-1, 0, 0);//设置法向量
	glTexCoord2f(0.0f, 0.6f); glVertex3f(15.0, 12.0, -20.0);
	glTexCoord2f(0.0f, 1.25f); glVertex3f(15.0, 25.0, -20.0);
	glTexCoord2f(0.1f, 1.25f); glVertex3f(15.0, 25.0, -22.0);
	glTexCoord2f(0.1f, 0.6f); glVertex3f(15.0, 12.0, -22.0);


	if (!displayInside)
	{
		//其他墙面
		glNormal3f(0, 0, 1);//设置法向量
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-37.0, 0.0, 20.0);
		glTexCoord2f(0.0f, 1.5f); glVertex3f(-37.0, 30.0, 20.0);
		glTexCoord2f(3.6f, 1.5f); glVertex3f(35.0, 30.0, 20.0);
		glTexCoord2f(3.6f, 0.0f); glVertex3f(35.0, 0.0, 20.0);

		glNormal3f(0, 0, -1);//设置法向量
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-37.0, 0.0, 19.0);
		glTexCoord2f(0.0f, 1.5f); glVertex3f(-37.0, 30.0, 19.0);
		glTexCoord2f(3.6f, 1.5f); glVertex3f(35.0, 30.0, 19.0);
		glTexCoord2f(3.6f, 0.0f); glVertex3f(35.0, 0.0, 19.0);

		glNormal3f(1, 0, 0);//设置法向量
		glTexCoord2f(-0.1f, 1.5f); glVertex3f(35.0, 30.0, -22.0);
		glTexCoord2f(2.0f, 1.5f); glVertex3f(35.0, 30.0, 20.0);
		glTexCoord2f(2.0f, 0.0f); glVertex3f(35.0, 0.0, 20.0);
		glTexCoord2f(-0.1f, 0.0f); glVertex3f(35.0, 0.0, -22.0);

		glNormal3f(-1, 0, 0);//设置法向量
		glTexCoord2f(-0.1f, 1.5f); glVertex3f(34.0, 30.0, -22.0);
		glTexCoord2f(2.0f, 1.5f); glVertex3f(34.0, 30.0, 20.0);
		glTexCoord2f(2.0f, 0.0f); glVertex3f(34.0, 0.0, 20.0);
		glTexCoord2f(-0.1f, 0.0f); glVertex3f(34.0, 0.0, -22.0);

		glEnd();
		glBegin(GL_TRIANGLES);

		glNormal3f(-1, 0, 0);//设置法向量
		glTexCoord2f(2.0f, 1.5f); glVertex3f(-37.0, 30.0, 20.0);
		glTexCoord2f(-0.1f, 1.5f); glVertex3f(-37.0, 30.0, -22.0);
		glTexCoord2f(0.95f, 2.0f); glVertex3f(-37.0, 40.0, -1.0);

		glNormal3f(1, 0, 0);//设置法向量
		glTexCoord2f(2.0f, 1.5f); glVertex3f(-35.0, 30.0, 20.0);
		glTexCoord2f(-0.1f, 1.5f); glVertex3f(-35.0, 30.0, -22.0);
		glTexCoord2f(0.95f, 2.0f); glVertex3f(-35.0, 40.0, -1.0);

		glNormal3f(1, 0, 0);//设置法向量
		glTexCoord2f(2.0f, 1.5f); glVertex3f(35.0, 30.0, 20.0);
		glTexCoord2f(-0.1f, 1.5f); glVertex3f(35.0, 30.0, -22.0);
		glTexCoord2f(0.95f, 2.0f); glVertex3f(35.0, 40.0, -1.0);

		glNormal3f(-1, 0, 0);//设置法向量
		glTexCoord2f(2.0f, 1.5f); glVertex3f(34.0, 30.0, 20.0);
		glTexCoord2f(-0.1f, 1.5f); glVertex3f(34.0, 30.0, -22.0);
		glTexCoord2f(0.95f, 2.0f); glVertex3f(34.0, 40.0, -1.0);
		glEnd();

		//房顶
		glBindTexture(GL_TEXTURE_2D, roofTex);//绑定纹理
		glBegin(GL_QUADS);

		glNormal3f(0, 0.9028605, 0.4299335);//设置法向量
		glTexCoord2f(0.0f, 0.322916666f); glVertex3f(-37.0, 30.0, 20.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-37.0, 40.0, -1.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(35.0, 40.0, -1.0);
		glTexCoord2f(1.0f, 0.322916666f); glVertex3f(35.0, 30.0, 20.0);

		glNormal3f(0, 0.9028605, -0.4299335);//设置法向量
		glTexCoord2f(0.0f, 0.322916666f); glVertex3f(-37.0, 30.0, -22.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-37.0, 40.0, -1.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(35.0, 40.0, -1.0);
		glTexCoord2f(1.0f, 0.322916666f); glVertex3f(35.0, 30.0, -22.0);

	}
	glEnd();

	//门
	glBindTexture(GL_TEXTURE_2D, doorTex);//绑定纹理
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);//设置法向量
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-35.0, 0.0, 10.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-35.0, 20.0, 10.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-35.0, 20.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-35.0, 0.0, 0.0);

	glNormal3f(-1, 0, 0);//设置法向量
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-37.0, 0.0, 10.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-37.0, 20.0, 10.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-37.0, 20.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-37.0, 0.0, 0.0);
	glEnd();

	//地板
	glBindTexture(GL_TEXTURE_2D, floorTex);//绑定纹理
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);//设置法向量
	glTexCoord2f(0.0f, 2.0f); glVertex3f(-35.0, 0.2, 20.0);
	glTexCoord2f(3.5f, 2.0f); glVertex3f(35.0, 0.2, 20.0);
	glTexCoord2f(3.5f, 0.0f); glVertex3f(35.0, 0.2, -20.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-35.0, 0.2, -20.0);
	glEnd();

	//桌子
	mat_diffuse[0] = 1, mat_diffuse[1] = 0.5, mat_diffuse[2] = 0;//换个材质
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	drawNGon(0.0, 1.0, 0.0, -27.5, 10.0, -12.5, 7.5, 30);
	glDisable(GL_TEXTURE_2D);
	drawNGon(0.0, -1.0, 0.0, -27.5, 9.0, -12.5, 7.5, 30);
	drawCylinder(0.0, 1.0, 0.0, -27.5, 10.0, -12.5, -1.0, 7.5, 30);
	mat_diffuse[0] = 0.7, mat_diffuse[1] = 0.7, mat_diffuse[2] = 0.7;//换个材质
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	drawCylinder(0.0, 1.0, 0.0, -27.5, 1.0, -12.5, -1.0, 3.5, 30);
	drawCylinder(0.0, 1.0, 0.0, -27.5, 9.0, -12.5, -8.0, 1.0, 30);
	drawNGon(0.0, 1.0, 0.0, -27.5, 1.0, -12.5, 3.5, 30);
	drawNGon(0.0, -1.0, 0.0, -27.5, 0.0, -12.5, 3.5, 30);

	//茶壶
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, zishaTex);//绑定纹理
	glPushMatrix();
	glTranslatef(-30, 11.5, -15);
	glutSolidTeapot(2);
	glPopMatrix();
	
	//沙漏（两个圆锥）
	mat_diffuse[0] = 1, mat_diffuse[1] = 0.7, mat_diffuse[2] = 0.5;//换个材质
	glPushMatrix();
	glTranslatef(-25, 10, -10);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.5, 1, 40, 40);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 11.9, -10);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(0.5, 1, 40, 40);
	glPopMatrix();
	glEnd();
	mat_diffuse[0] = 0.8, mat_diffuse[1] = 0.8, mat_diffuse[2] = 0.8;//材质换回去


	glPopMatrix();
}

void OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空缓冲区
	Drawing();
	glutSwapBuffers();//切换绘图缓冲区
}

void OnReshape(int w, int h)
{
	aspect = (float)w / h;//获取新的宽高比
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, aspect, 1.0, 10000.0);//改变宽高比
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 500, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyPress(unsigned char c,int x,int y)
{
	if (c == ' ')//视点上移
	{
		eye[1] += 5;
		center[1] += 5;
	}
	else if (c == 'x')//视点下移
	{
		eye[1] -= 5;
		center[1] -= 5;
	}
	else if (c == 'w')//视点前移
	{
		float dir[3] = { eye[0] - center[0],eye[1] - center[1] ,eye[2] - center[2] };
		for (int i = 0; i < 3; i++)
		{
			eye[i] -= 0.1 * dir[i];
			center[i] -= 0.1 * dir[i];
		}
	}
	else if (c == 's')//视点后移
	{
		float dir[3] = { eye[0] - center[0],eye[1] - center[1] ,eye[2] - center[2] };
		for (int i = 0; i < 3; i++)
		{
			eye[i] += 0.1 * dir[i];
			center[i] += 0.1 * dir[i];
		}
	}
	else if (c == 'd')//视点右移
	{
		float dir[] = { eye[2] - center[2] , center[0] - eye[0] };
		float m = sqrt(dir[0] * dir[0] + dir[1] * dir[1]);
		dir[0] = dir[0] / m;
		dir[1] = dir[1] / m;
		eye[0] += 5 * dir[0];
		eye[2] += 5 * dir[1];
		center[0] += 5 * dir[0];
		center[2] += 5 * dir[1];
	}
	else if (c == 'a')//视点左移
	{
		float dir[] = { eye[2] - center[2] , center[0] - eye[0] };
		float m = sqrt(dir[0] * dir[0] + dir[1] * dir[1]);
		dir[0] = dir[0] / m;
		dir[1] = dir[1] / m;
		eye[0] -= 5 * dir[0];
		eye[2] -= 5 * dir[1];
		center[0] -= 5 * dir[0];
		center[2] -= 5 * dir[1];
	}
	else if (c == 'q')//切换显示模式（透视两面墙）
	{
		displayInside = !displayInside;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, aspect, 1.0, 10000.0);
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

void MouseMove(int x, int y)
{
	static bool first = false;
	static int xLast=750, yLast=450;
	int xtemp=x, ytemp=y;
	x = x - xLast;
	y = y - yLast;//求鼠标移动的距离
	float dir[3] = { center[0] - eye[0],center[1] - eye[1],center[2] - eye[2] };//求视线方向
	dir[1] = dir[1] * cos((float)y / 90) - sqrt(dir[0] * dir[0] + dir[2] * dir[2]) * sin((float)y / 90);
	dir[0] = dir[0] * cos((float)x / 90) - dir[2] * sin((float)x / 90);
	dir[2] = dir[2] * cos((float)x / 90) + dir[0] * sin((float)x / 90);//求更改后的视线方向
	float m = sqrt(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
	dir[0] = dir[0] / m * 113.137084;
	dir[1] = dir[1] / m * 113.137084;
	dir[2] = dir[2] / m * 113.137084;
	//视线方向正规化，保证视点与视野中心点的距离不变

	center[0] = eye[0] + dir[0];
	center[1] = eye[1] + dir[1];
	center[2] = eye[2] + dir[2];//求更改后的视野中心点位置
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, aspect, 1.0, 10000.0);
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
	xLast = xtemp, yLast = ytemp;
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	//双缓冲模式
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(1500, 900);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("opengl");
	//设置视点视向
	gluPerspective(60, 1, 1, 2000);
	gluLookAt(100, 100, 100, 0, 0, 0, 0, 200, 0);
	//加载纹理
	wallTex = loadTexture("wall.bmp",GL_MODULATE);
	floorTex = loadTexture("floor.bmp", GL_MODULATE);
	doorTex = loadTexture("door.bmp", GL_MODULATE);
	grassTex = loadTexture("grass.bmp", GL_MODULATE);
	roofTex = loadTexture("roof.bmp", GL_MODULATE);
	ironTex = loadTexture("iron.bmp", GL_MODULATE);
	zishaTex = loadTexture("zisha.bmp", GL_MODULATE);
	cubeTex[0] = loadTexture("front.bmp", GL_MODULATE);
	cubeTex[1] = loadTexture("right.bmp", GL_MODULATE);
	cubeTex[2] = loadTexture("back.bmp", GL_MODULATE);
	cubeTex[3] = loadTexture("left.bmp", GL_MODULATE);
	cubeTex[4] = loadTexture("top.bmp", GL_MODULATE);
	cubeTex[5] = loadTexture("bottom.bmp", GL_MODULATE);
	//注册显示回调函数
	glutDisplayFunc(OnDisplay);
	//注册缩放回调函数
	glutReshapeFunc(OnReshape);
	//注册键盘响应函数
	glutKeyboardFunc(keyPress);
	//注册鼠标响应函数
	glutPassiveMotionFunc(MouseMove);
	//开启深度测试
	glEnable(GL_DEPTH_TEST);
	//开启光照效果
	glEnable(GL_LIGHTING);
	//打开0号光源
	glEnable(GL_LIGHT0);
	//进入主事件循环
	glutMainLoop();
}
