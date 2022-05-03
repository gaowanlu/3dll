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
	/**
	 * @brief �������������ϵ�ĸ���ά���ƶ���ƫ�������ʼĬ���ڣ�0��0��0��
	*/
	double dx = 0, dy = 0, dz=0;
	camera();
	/**
	 * @brief �����������������ϵԭ����ת
	 * @param x_angle 
	 * @param y_angle 
	 * @param z_angle 
	 * @return �µ��������ϵ
	*/
	Eigen::Matrix<double, 3, 3> trans(double x_angle,double y_angle,double z_angle);
	void move(double dx, double dy, double dz);
	void clear_move();
};
#endif // !__CAMERA_H__
