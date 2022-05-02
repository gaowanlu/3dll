#include"model.h"
Model::Model(const std::vector<std::vector<double>> vecs) {
	for (auto& vec : vecs) {
		_vecs.push_back(Eigen::Matrix<double, 3, 1>(vec[0], vec[1], vec[2]));
	}
}

Model::Model(std::vector<Eigen::Matrix<double, 3, 1>> vecs, const char ch) {
	_vecs = vecs;
}

std::vector<Eigen::Matrix<double, 3, 1>> Model::get_matrix() {
	return _vecs;
}

Model Model::resize(double resize) {
	std::vector<Eigen::Matrix<double, 3, 1>> result = _vecs;
	for (auto& matrix : result) {
		matrix(0) *= resize;
		matrix(1) *= resize;
		matrix(2) *= resize;
	}
	Model model(result,' ');
	return model;
}

Model Model::move(double x, double y, double z) {
	std::vector<std::vector<double>> new_vecs;
	for (Eigen::Matrix<double, 3, 1> &v : _vecs) {
		new_vecs.push_back({v(0)+x,v(1)+y,v(2)+z});
	}
	return Model(new_vecs);
}