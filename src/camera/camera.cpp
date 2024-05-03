#include"camera.h"
#include<iostream>

camera::camera() {
	_camera << 1., 0., 0., 0., 1., 0., 0., 0., 1.;
}

Eigen::Matrix<double, 3, 3> camera::trans(double x_angle, double y_angle, double z_angle) {
	angle_x = x_angle;
	angle_y = y_angle;
	angle_z = z_angle;
	return utils::roate_x(x_angle) * utils::roate_y(y_angle) * utils::roate_z(z_angle) * _camera;
}

void camera::move(double dx,double dy,double dz) {
	this->dx += dx;
	this->dy += dy;
	this->dz += dz;
}

void camera::clear_move() {
	this->dx = 0;
	this->dy = 0;
	this->dz = 0;
}