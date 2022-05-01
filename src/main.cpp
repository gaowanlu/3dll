#include <iostream>
#include <graphics.h>
#include <easyx.h>
#include <cmath>
#include <vector>
#include <conio.h>
#include <Eigen/Dense>
#include "camera/camera.h"
#define PI 3.14159265
#define WINDOW_WITH 640
#define WINDOW_HEIGHT 480

Eigen::Matrix<double, 3, 3> roate_x(double angle) {
	angle = angle * PI / 180.;
	Eigen::Matrix<double, 3, 3> m;
	m << 1. , 0. , 0. , 0. , cos(angle) , -sin(angle) , 0. , sin(angle) , cos(angle);
	return m;
}

Eigen::Matrix<double, 3, 3> roate_y(double angle) {
	angle = angle * PI / 180.;
	Eigen::Matrix<double, 3, 3> m;
	m << cos(angle) , 0. , sin(angle) , 0. , 1. , 0. , -sin(angle) , 0. , cos(angle);
	return m;
}

Eigen::Matrix<double, 3, 3> roate_z(double angle) {
	angle = angle * PI / 180.;
	Eigen::Matrix<double, 3, 3> m;
	m << cos(angle), -sin(angle), 0., sin(angle), cos(angle), 0., 0., 0., 1.;
	return m;
}

std::vector<Eigen::Matrix<double, 3, 1>>  resize_model(std::vector<Eigen::Matrix<double, 3, 1>> model,double resize) {
	for (auto& matrix : model) {
		matrix(0) *= resize;
		matrix(1) *= resize;
		matrix(2) *= resize;
	}
	return model;
}


/*
	�˴���x��yΪ�������ϵ��ԭ������Ļ���ģ���Ϊx����Ϊy
	esayx ����ԭ�����豸�����Ͻǣ�X ������Ϊ����Y ������Ϊ����������λ������
	�������ϵ��ͼ������ϵ
*/
Eigen::Matrix<double,3,1> to_xy(double x,double y,double z) {
	//���������Ŀ��ľ���
	double distance = sqrt(fabs(x) * fabs(x) + fabs(y) * fabs(y) + fabs(z) * fabs(z));
	//std::cout << distance << std::endl;
	double dot_size = 5;
	double resize = 40;//400/fabs(z)
	x *= resize;//��������
	y *= resize;
	z *= resize;
	if (y < 0) {
		y = -y + (WINDOW_HEIGHT / 2);
	}
	else {
		y = (WINDOW_HEIGHT / 2) - y;
	}
	if (x > 0) {
		x += WINDOW_WITH / 2;
	}
	else {
		x = WINDOW_WITH / 2 + x;
	}
	return Eigen::Matrix<double, 3, 1>(x,y,z);
}

void draw_t_line(Eigen::Matrix<double, 3, 1> dot1, Eigen::Matrix<double, 3, 1> dot2) {
	//if (dot1(2) > 0 && dot2(2) > 0) {
		line(dot1(0),dot1(1),dot2(0),dot2(1));
	//}
}

//�����ǵ�
void create_model_1(std::vector<Eigen::Matrix<double, 3, 1>>& model) {
	model.push_back(Eigen::Matrix<double, 3, 1>(2, 3, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(2, 5, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(4, 3, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(4, 5, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(2, 3, 2));
	model.push_back(Eigen::Matrix<double, 3, 1>(2, 5, 2));
	model.push_back(Eigen::Matrix<double, 3, 1>(4, 3, 2));
	model.push_back(Eigen::Matrix<double, 3, 1>(4, 5, 2));
}

void create_model_2(std::vector<Eigen::Matrix<double, 3, 1>>& model) {
	model.push_back(Eigen::Matrix<double, 3, 1>(7, -11, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(7, -5, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(9, -15, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(9, -5, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(7, -31, 2));
	model.push_back(Eigen::Matrix<double, 3, 1>(7, -5, 2));
	model.push_back(Eigen::Matrix<double, 3, 1>(9, -33, 2));
	model.push_back(Eigen::Matrix<double, 3, 1>(17, -5, 2));
}

void create_model_3(std::vector<Eigen::Matrix<double, 3, 1>>& model) {
	model.push_back(Eigen::Matrix<double, 3, 1>(-2, -3, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(-2, -5, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(-4, -3, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(-4, -5, 0));
	model.push_back(Eigen::Matrix<double, 3, 1>(-2, -3, 2));
	model.push_back(Eigen::Matrix<double, 3, 1>(-2, -5, 2));
	model.push_back(Eigen::Matrix<double, 3, 1>(-4, -3, 2));
	model.push_back(Eigen::Matrix<double, 3, 1>(-4, -5, 2));
}

int main(int argc, char** argv) {
	//��������
	initgraph(1000, 700);	// ������ͼ���ڣ���СΪ 640x480 ����
	setlinecolor(RED);
	//��������ϵ��
	Eigen::Matrix<double, 3, 3> world_base;
	world_base << 1., 0., 0., 0., 1., 0., 0., 0., 1.;

	//��Ʒ1
	Eigen::Matrix<double, 3, 1> m1;
	m1 << 0, 0, 5;
	//��Ʒ2
	Eigen::Matrix<double, 3, 1> m2;
	m2 << 2, 2, 2;
	//����ģ��
	std::vector<Eigen::Matrix<double, 3, 1>>model1;
	create_model_1(model1);//����ģ��1
	std::vector<Eigen::Matrix<double, 3, 1>>model2;
	create_model_2(model2);//����ģ��2
	std::vector<Eigen::Matrix<double, 3, 1>>model3;
	create_model_3(model3);//����ģ��3
	std::vector<std::vector<Eigen::Matrix<double, 3, 1>>>models{ model1,model2 };

	//����� ������ ����(0,0,0) �������������ת��
	Eigen::Matrix<double, 3, 3> camera;
	camera << 1., 0., 0., 0., 1., 0., 0., 0., 1.;

	//����������ϵ�µ����������������ϵ��ʾ����ʽ ���任
	//�� m*x=carama*y �� y ����y=carama��*m*x 
	std::cout << "[" << camera.inverse() * world_base * m1 << "]" << std::endl;
	std::cout << "[" << camera.inverse() * world_base * m2 << "]" << std::endl;

	//�������Ƕȱ�ʾ�������(0,0,0) x y z��ת�ĽǶ�
	double x_angle = 0, y_angle = 0, z_angle = 0;
	std::cout << camera * roate_x(x_angle) * roate_y(y_angle) * roate_z(z_angle) << std::endl;
	//��¼��һ������λ��
	int last_x = 0, last_y = 0;
	double last_resize = 1.0;

	Eigen::Matrix<double, 3, 3> camera_realtime;

	while (1) {
		//ȡ��������������л��任
		camera_realtime = roate_x(x_angle) * roate_y(y_angle) * roate_z(z_angle) * camera;//ʵʱ���
		for (auto model : models) {
			//��Ⱦmodel
			model=resize_model(model, last_resize);
			for (std::size_t i = 0; i < model.size(); i++) {
				Eigen::Matrix<double, 3, 1> dot = model[i];
				Eigen::Matrix<double, 3, 1> dot1_realtime = camera_realtime.inverse() * world_base * dot;
				for (std::size_t j = 0; j < model.size(); j++) {
					Eigen::Matrix<double, 3, 1> dot = model[j];
					Eigen::Matrix<double, 3, 1> dot2_realtime = camera_realtime.inverse() * world_base * dot;
					Eigen::Matrix<double, 3, 1> window_dot1 = to_xy(dot1_realtime(0), dot1_realtime(1), dot1_realtime(2));
					Eigen::Matrix<double, 3, 1> window_dot2 = to_xy(dot2_realtime(0), dot2_realtime(1), dot2_realtime(2));
					draw_t_line(window_dot1, window_dot2);
				}
			}
		}
		ExMessage message;
		if (peekmessage(&message)) {
			if (message.lbutton) {//����갴��
				int dx = message.x - last_x;
				int dy = message.y - last_y;
				last_x = message.x;
				last_y = message.y;
				if (fabs(dx) < 10 && fabs(dy) < 10) {
					x_angle =((int)x_angle+ dy)%360, y_angle =((int)y_angle+ dx)%360, z_angle += 0;
				}
			}
			if (message.wheel) {
				if(message.ctrl){//����
					double dz = fabs(message.wheel) / 600.;//һ�ι���120
					if (message.wheel < 0&&(last_resize - dz)>0.1) {//��С
						last_resize = last_resize - dz;
					}
					else if(last_resize + dz<5) {//���
						last_resize = last_resize + dz;
					}
				}
				else {//z����ת
					double dz = message.wheel / 10.;
					z_angle = ((int)z_angle + (int)dz) % 360;
				}
			}
			//��������
			RECT r = { 0, 0, 639, 479 };
			TCHAR s[512];
			_stprintf_s(s, _T("x_angle %.3lf y_angle %.3lf z_angle %.3lf resize %.3lf "),x_angle,y_angle,z_angle,last_resize);
			drawtext(s, & r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		flushmessage();
		Sleep(20);
		//����Ļ�������Զ����Ļ�м䣬���������ϵ��Ļ����ˮƽ����Ϊx����Ļ���﷽��Ϊz����Ļ���Ϸ�Ϊy
		cleardevice();
	}
	return 0;
}