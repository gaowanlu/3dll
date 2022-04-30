#include <iostream>
#include <graphics.h>
#include <easyx.h>
#include <cmath>
#include <vector>
#include <conio.h>
#include <Eigen\Dense>
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

/*
	此处的x，y为相机坐标系，原点在屏幕中心，右为x，上为y
	esayx 坐标原点在设备的左上角，X 轴向右为正，Y 轴向下为正，度量单位是像素
	相机坐标系到图像坐标系
*/
Eigen::Matrix<double,3,1> to_xy(double x,double y,double z) {
	//计算相机到目标的举例
	double distance = sqrt(fabs(x) * fabs(x) + fabs(y) * fabs(y) + fabs(z) * fabs(z));
	double dot_size = 5;
	double resize = 40;
	x *= resize;//缩放因数
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

//创建角点
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
	//建立窗口
	initgraph(640, 480);	// 创建绘图窗口，大小为 640x480 像素
	setlinecolor(RED);
	//世界坐标系基
	Eigen::Matrix<double, 3, 3> world_base;
	world_base << 1., 0., 0., 0., 1., 0., 0., 0., 1.;
	
	//物品1
	Eigen::Matrix<double, 3, 1> m1;
	m1 << 0, 0, 5;
	//物品2
	Eigen::Matrix<double, 3, 1> m2;
	m2 << 2, 2, 2;
	//建立模型
	std::vector<Eigen::Matrix<double, 3, 1>>model1;
	create_model_1(model1);//创建模型1
	std::vector<Eigen::Matrix<double, 3, 1>>model2;
	create_model_2(model2);//创建模型2
	std::vector<Eigen::Matrix<double, 3, 1>>model3;
	create_model_3(model3);//创建模型3
	std::vector<std::vector<Eigen::Matrix<double, 3, 1>>>models{model1,model2};

	//摄像机 正交基 人在(0,0,0) 不动摄像机进行转动
	Eigen::Matrix<double, 3, 3> camera;
	camera << 1., 0., 0., 0., 1., 0., 0., 0., 1.;

	//求世界坐标系下的坐标在摄像机坐标系表示的形式 基变换
	//有 m*x=carama*y 求 y ，则y=carama逆*m*x 
	std::cout <<"["<< camera.inverse() * world_base * m1 <<"]"<< std::endl;
	std::cout <<"["<< camera.inverse() * world_base * m2 <<"]"<< std::endl;

	//用三个角度表示摄像机在(0,0,0) x y z旋转的角度
	double x_angle = 0, y_angle = 0, z_angle = 0;
	std::cout << camera * roate_x(x_angle)* roate_y(y_angle) * roate_z(z_angle) << std::endl;
	//尝试连续旋转
	int count = 0;
	double a = 0, b = 0, c = 0;
	//for (; a < 180; a+=0.5) {
	//	for (; b < 180; b+=0.5) {
			Eigen::Matrix<double, 3, 3> camera_realtime;
			for (c=0,b=74,a=-30; c < 360; c+=0.1,b+=0.1,b+=0.1) {
				count++;
				//x_angle = a, y_angle = b, z_angle = c;
				x_angle = c, y_angle = b, z_angle = 0;
				//取出相机的向量进行基变换
				camera_realtime = roate_x(x_angle)* roate_y(y_angle)* roate_z(z_angle)*camera;//实时相机
				for (auto& model : models) {
					//渲染model
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
				Sleep(10);
				//在屏幕中相机永远在屏幕中间，且相机坐标系屏幕右手水平方向为x，屏幕向里方向为z，屏幕向上方为y
				cleardevice();
			}
	//	}
	//}
	std::cout << "NOW NOTHING RUN"<<count << std::endl;
	_getch();
	return 0;
}