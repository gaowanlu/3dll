#include "window.h"
window::window(int width,int height,int console) {
	if (width <= 0 || height <= 0) {
		throw "window can not width or height equals 0";
	}
	_width = width;
	_height = height;
	_world_base << 1., 0., 0., 0., 1., 0., 0., 0., 1.;
	init_window(console);
}


void window::init_window(int console) {
	//建立窗口
	initgraph(_width, _height,console);
}


int window::get_width() {
	return _width;
}


int window::get_height() {
	return _height;
}


void window::set_linecolor(unsigned char r, unsigned char g, unsigned char  b) {
	setlinecolor(RGB(r,g,b));
}


Eigen::Matrix<double, 3, 3> window::get_world_base() {
	return this->_world_base;
}


Eigen::Matrix<double, 3, 1> window::to_xy(double x, double y, double z,camera m_camera) {
		//计算相机到目标的举例
		double distance = sqrt(fabs(x) * fabs(x) + fabs(y) * fabs(y) + fabs(z) * fabs(z));
		//std::cout << distance << std::endl;
		double dot_size = 5;
		double resize = 40;//400/fabs(z)
		x += m_camera.dx;
		y += m_camera.dy;
		z += m_camera.dz;
		x *= resize;//缩放因数
		y *= resize;
		z *= resize;
		if (y < 0) {
			y = -y + (_height / 2.);
		}
		else {
			y = (_height / 2.) - y;
		}
		if (x > 0) {
			x += _width / 2;
		}
		else {
			x = _width / 2 + x;
		}
		return Eigen::Matrix<double, 3, 1>(x, y, z);
}

void window::draw_t_line(Eigen::Matrix<double, 3, 1> dot1, Eigen::Matrix<double, 3, 1> dot2) {
	//if (dot1(2) > 0 || dot2(2) > 0) {//向有一个向量在相机前面时才进行显示此连线
		line(dot1(0), dot1(1), dot2(0), dot2(1));
	//}
}

void window::clear() {
	cleardevice();
}

void window::sleep(int mseconds) {
	Sleep(mseconds);
}

bool window::get_message(ExMessage *message) {
	bool result= peekmessage(message);
	flushmessage();
	return result;
}

void window::render_model(Model m_model,double resize,camera m_camera, Eigen::Matrix<double, 3, 3> camera_realtime) {
	auto model = m_model.resize(resize).get_matrix();
	//渲染物品
	for (std::size_t i = 0; i < model.size(); i++) {
		Eigen::Matrix<double, 3, 1> dot = model[i];//获得模型的向量1
		//变换到相机坐标系内
		Eigen::Matrix<double, 3, 1> dot1_realtime = this->get_world_base() * camera_realtime.inverse() * dot;
		//获取模型向量2
		for (std::size_t j = 0; j < model.size(); j++) {
			Eigen::Matrix<double, 3, 1> dot = model[j];
			//变换到相机坐标系内
			Eigen::Matrix<double, 3, 1> dot2_realtime = this->get_world_base() * camera_realtime.inverse() * dot;
			//将x y投到屏幕上，变换到图像坐标系
			Eigen::Matrix<double, 3, 1> window_dot1 = this->to_xy(dot1_realtime(0), dot1_realtime(1), dot1_realtime(2), m_camera);
			Eigen::Matrix<double, 3, 1> window_dot2 = this->to_xy(dot2_realtime(0), dot2_realtime(1), dot2_realtime(2), m_camera);
			//画出向量1到向量2的连线
			this->draw_t_line(window_dot1, window_dot2);
		}
	}
}