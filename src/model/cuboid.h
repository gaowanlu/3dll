#pragma once
#ifndef __CUBOID_H__
#define __CUBOID_H__
#include <Eigen/Dense>
#include <vector>
#include "model.h"

class cuboid
{
private:
public:
	cuboid();
	cuboid(std::vector<Model> vecs);
	std::vector<Model> _vecs;
	void push_back(Model model);
	cuboid move(double x, double y, double z);
};
#endif // !__CUBOID_H__
