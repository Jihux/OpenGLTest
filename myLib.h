#pragma once
#define pi 3.1415926535898
#define myabs(X) ((X>0)?X:-X)
#include <math.h>
#include <GL/glut.h>

void drawNGon(float nx, float ny, float nz, float x, float y, float z, float r, int edge)
{
	glNormal3f(nx, ny, nz);//设置法向�?
	float dAlpha = 2 * pi / edge;
	if (myabs(ny) - 0.0 > 0.01 || myabs(nx) - 0.0 > 0.01)//圆不与xOy平面平行的情�?
	{
		float u[3] = { ny,-nx,0 };
		float v[3] = { nx * nz,ny * nz,-nx * nx - ny * ny };//圆所在平面的两个互相垂直的向�?
		float umod = sqrtf(-v[2]), vmod = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);//求两个向量的�?
		for (int i = 0; i < 3; i++)
		{
			u[i] /= umod;
			v[i] /= vmod;
		}//将该两个向量正规�?
		glBegin(GL_POLYGON);
		for (float alpha = 0; alpha > -2*pi; alpha-=dAlpha)
		{
			float s = sin(alpha), c = cos(alpha);
			glTexCoord2f(s / 2 + 0.5, c / 2 + 0.5);//设置纹理坐标
			glVertex3f(x + (u[0] * c + v[0] * s) * r, y + (u[1] * c + v[1] * s) * r, z + (u[2] * c + v[2] * s) * r);//绘制顶点
		}
		glEnd();
	}
	else if (myabs(nz) - 0.0 > 0.01)//圆与xOy平面平行的情�?
	{
		float u[3] = { nz,0,-nx };
		float v[3] = { nx * ny,-nx * nx - nz * nz,nz * ny };//圆所在平面的两个互相垂直的向�?
		float umod = sqrtf(-v[1]), vmod = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);//求两个向量的�?
		for (int i = 0; i < 3; i++)
		{
			u[i] /= umod;
			v[i] /= vmod;
		}//将该两个向量正规�?
		glBegin(GL_POLYGON);
		for (float alpha = 0; alpha < 2 * pi; alpha += dAlpha)
		{
			float s = sin(alpha), c = cos(alpha);
			glTexCoord2f(s / 2 + 0.5, c / 2 + 0.5);//设置纹理坐标
			glVertex3f(x + (u[0] * c + v[0] * s) * r, y + (u[1] * c + v[1] * s) * r, z + (u[2] * c + v[2] * s) * r);//绘制顶点
		}
		glEnd();
	}
}

void drawCylinder(float nx, float ny, float nz, float x, float y, float z, float h, float r, int edge)
{
	float dAlpha = 2 * pi / edge;
	if (myabs(ny) - 0.0 > 0.01 || myabs(nx) - 0.0 > 0.01)//底面不与xOy平面平行的情�?
	{
		float u[3] = { ny,-nx,0 };
		float v[3] = { nx * nz,ny * nz,-nx * nx - ny * ny };//底面所在平面的两个互相垂直的向�?
		float umod = sqrtf(-v[2]), vmod = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]),nmod=sqrtf(-v[2]+nz*nz);//求两个向量的�?
		for (int i = 0; i < 3; i++)
		{
			u[i] /= umod;
			v[i] /= vmod;
		}//将该两个向量正规�?
		float hv[3] = { h * nx / nmod,h * ny / nmod,h * nz / nmod };
		glBegin(GL_QUAD_STRIP);
		for (float alpha = 0; alpha < 2 * pi; alpha += dAlpha)
		{
			float s = sin(alpha), c = cos(alpha);
			float x0 = x + (u[0] * c + v[0] * s) * r, y0 = y + (u[1] * c + v[1] * s) * r, z0 = z + (u[2] * c + v[2] * s) * r;
			glNormal3f((x0 - x) / r, (y0 - y) / r, (z0 - z) / r);//设置顶点法向�?
			glTexCoord2f(r * alpha / 10, h/10); glVertex3f(x0 + hv[0], y0 + hv[1], z0 + hv[2]);
			glTexCoord2f(r * alpha / 10, 0); glVertex3f(x0, y0, z0);//绑定纹理坐标并绘制顶�?
		}
		glEnd();
	}
	else if (myabs(nz) - 0.0 > 0.01)//底面与xOy平面平行的情�?
	{
		float u[3] = { nz,0,-nx };
		float v[3] = { nx * ny,-nx * nx - nz * nz,nz * ny };
		float umod = sqrtf(-v[1]), vmod = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]), nmod = sqrtf(-v[1] + ny * ny);
		for (int i = 0; i < 3; i++)
		{
			u[i] /= umod;
			v[i] /= vmod;
		}//将该两个向量正规�?
		float hv[3] = { h * nx / nmod,h * ny / nmod,h * nz / nmod };
		glBegin(GL_POLYGON);
		for (float alpha = 0; alpha < 2 * pi; alpha += dAlpha)
		{
			float s = sin(alpha), c = cos(alpha);
			float x0 = x + (u[0] * c + v[0] * s) * r, y0 = y + (u[1] * c + v[1] * s) * r, z0 = z + (u[2] * c + v[2] * s) * r;
			glNormal3f((x0 - x) / r, (y0 - y) / r, (z0 - z) / r);//设置顶点法向�?
			glVertex3f(x0 + hv[0], y0 + hv[1], z0 + hv[2]);
			glVertex3f(x0, y0, z0);//绑定纹理坐标并绘制顶�?
		}
		glEnd();
	}
}

void drawmobius(float x, float y, float z, float nx, float ny, float nz, float r, float r1)
{
	if (myabs(ny) - 0.0 > 0.01 || myabs(nx) - 0.0 > 0.01)
	{
		float u[3] = { ny,-nx,0 };
		float v[3] = { nx * nz,ny * nz,-nx * nx - ny * ny };
		float umod = sqrtf(-v[2]), vmod = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]), nmod = sqrtf(nz * nz - v[2]);
		for (int i = 0; i < 3; i++)
		{
			u[i] /= umod;
			v[i] /= vmod;
		}
		nz /= nmod;
		ny /= nmod;
		ny /= nmod;
		glBegin(GL_QUADS);
		glNormal3f(1, 1, 1);
		for (float alpha = 0; alpha < 2 * pi;)
		{
			float s = sin(alpha), c = cos(alpha);
			float x1 = (u[0] * c + v[0] * s), y1 = (u[1] * c + v[1] * s), z1 = (u[2] * c + v[2] * s);
			float x2 = r1 * x1 * cos(alpha / 2) + r1 * nx * sin(alpha / 2), y2 = r1 * y1 * cos(alpha / 2) + r1 * ny * sin(alpha / 2), z2 = r1 * z1 * cos(alpha / 2) + r1 * nz * sin(alpha / 2);
			glVertex3f(x + x1 * r + x2, y + y1 * r + y2, z + z1 * r + z2);
			glVertex3f(x + x1 * r - x2, y + y1 * r - y2, z + z1 * r - z2);
			alpha += pi / 18;
			s = sin(alpha), c = cos(alpha);
			x1 = (u[0] * c + v[0] * s), y1 = (u[1] * c + v[1] * s), z1 = (u[2] * c + v[2] * s);
			x2 = r1 * x1 * cos(alpha / 2) + r1 * nx * sin(alpha / 2), y2 = r1 * y1 * cos(alpha / 2) + r1 * ny * sin(alpha / 2), z2 = r1 * z1 * cos(alpha / 2) + r1 * nz * sin(alpha / 2);
			glVertex3f(x + x1 * r - x2, y + y1 * r - y2, z + z1 * r - z2);
			glVertex3f(x + x1 * r + x2, y + y1 * r + y2, z + z1 * r + z2);
		}
		glEnd();
	}
}

void drawSphere(unsigned int groundTex,unsigned int  bottomTex)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTex);
	drawNGon(0, 1, 0, 0, 0, 0, 86.60254, 1000);//绘制地面
	glBindTexture(GL_TEXTURE_2D, bottomTex);
	glBegin(GL_QUADS);
	for (float a1 = 0; a1 < pi / 3; a1 += pi / 180)//绘制弧面
	{
		float a2 = a1 + pi / 180;
		for (float b1 = 0; b1 < 43 * pi / 21; b1 += pi / 500)
		{
			float b2 = b1 + pi / 18;
			glNormal3f(sin(a1) * cos(b1), -cos(a1), sin(a1) * sin(b1));
			glTexCoord2f(b1, a1); glVertex3f(100 * sin(a1) * cos(b1), 50 - 100 * cos(a1), 100 * sin(a1) * sin(b1));
			glNormal3f(sin(a1) * cos(b2), -cos(a1), sin(a1) * sin(b2));
			glTexCoord2f(b2, a1); glVertex3f(100 * sin(a1) * cos(b2), 50 - 100 * cos(a1), 100 * sin(a1) * sin(b2));
			glNormal3f(sin(a2) * cos(b2), -cos(a2), sin(a2) * sin(b2));
			glTexCoord2f(b2, a2); glVertex3f(100 * sin(a2) * cos(b2), 50 - 100 * cos(a2), 100 * sin(a2) * sin(b2));
			glNormal3f(sin(a2) * cos(b1), -cos(a2), sin(a2) * sin(b1));
			glTexCoord2f(b1, a2); glVertex3f(100 * sin(a2) * cos(b1), 50 - 100 * cos(a2), 100 * sin(a2) * sin(b1));
		}
	}
	glDisable(GL_TEXTURE_2D);
	glEnd();
}