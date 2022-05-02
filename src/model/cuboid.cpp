#include"cuboid.h"
cuboid::cuboid() {

}
cuboid::cuboid(std::vector<Model> vecs) {
	_vecs = vecs;
}

void cuboid::push_back(Model model) {
	_vecs.push_back(model);
}

cuboid cuboid::move(double x,double y,double z) {
	std::vector<Model> new_vecs;
	for (auto model : _vecs) {
		new_vecs.push_back(model.move(x, y, z));
	}
	return cuboid(new_vecs);
}