#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <Eigen/Dense>
#include "../utils/utils.h"
class camera {
private:
	//����� ������ ����(0,0,0) �������������ת��
	Eigen::Matrix<double, 3, 3> _camera;
public:
	double dx = 0, dy = 0, dz=0;
	camera();
	Eigen::Matrix<double, 3, 3> trans(double x_angle,double y_angle,double z_angle);
	void move(double dx, double dy, double dz);
	void clear_move();
};
#endif // !__CAMERA_H__
