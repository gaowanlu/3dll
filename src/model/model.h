#pragma once
#ifndef __MODEL_H__
#define __MODEL_H__
#include<vector>
#include <Eigen/Dense>
#include <iostream>

class Model {
private:
	std::vector<Eigen::Matrix<double, 3, 1>> _vecs;
public:
	Model(std::vector<Eigen::Matrix<double, 3, 1>> vecs,const char ch);
	Model(std::vector<std::vector<double>> vecs);
	std::vector<Eigen::Matrix<double, 3, 1>> get_matrix();
	Model resize(double resize);
	Model move(double x,double y,double z);
};

#endif // !__MODEL_H__

