#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <Eigen/Dense>
#include "../utils/utils.h"
class camera {
private:
	//摄像机 正交基 人在(0,0,0) 不动摄像机进行转动
	Eigen::Matrix<double, 3, 3> _camera;
public:
	/**
	 * @brief 相对与世界坐标系的各个维度移动的偏移量，最开始默认在（0，0，0）
	*/
	double dx = 0, dy = 0, dz=0;
	camera();
	/**
	 * @brief 将相机绕着世界坐标系原点旋转
	 * @param x_angle 
	 * @param y_angle 
	 * @param z_angle 
	 * @return 新的相机坐标系
	*/
	Eigen::Matrix<double, 3, 3> trans(double x_angle,double y_angle,double z_angle);
	void move(double dx, double dy, double dz);
	void clear_move();
};
#endif // !__CAMERA_H__
