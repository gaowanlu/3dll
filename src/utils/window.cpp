#include "window.h"
window::window(int width,int height,int console) {
	_frame = new IMAGE(width,height);
	if (width <= 0 || height <= 0) {
		throw "window can not width or height equals 0";
	}
	_width = width;
	_height = height;
	_world_base << 1., 0., 0., 0., 1., 0., 0., 0., 1.;
	init_window(console);
}
window::~window() {
	if (this->_frame) {
		delete _frame;
	}
}

void window::start_frame() {
	SetWorkingImage(this->_frame);
	this->clear();//画布
}

void window::show_frame() {
	SetWorkingImage();
	if (_frame) {
		putimage(0, 0, _frame);
	}
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
		double resize = 10;//400/fabs(z)
		x += m_camera.dx;
		y += m_camera.dy;
		//z += m_camera.dz;
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
	//if (dot1(2) > 0 && dot2(2) > 0) {//向有一个向量在相机前面时才进行显示此连线
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
		//变换到相机坐标系内s
		Eigen::Matrix<double, 3, 1> dot1_realtime =  camera_realtime.inverse() * this->get_world_base() * dot;//
		//获取模型向量2
		for (std::size_t j = 0; j < model.size(); j++) {
			Eigen::Matrix<double, 3, 1> dot = model[j];
			//变换到相机坐标系内
			Eigen::Matrix<double, 3, 1> dot2_realtime =camera_realtime.inverse() * this->get_world_base() * dot;//
			//将x y投到屏幕上，变换到图像坐标系
			Eigen::Matrix<double, 3, 1> window_dot1 = this->to_xy(dot1_realtime(0), dot1_realtime(1), dot1_realtime(2), m_camera);
			Eigen::Matrix<double, 3, 1> window_dot2 = this->to_xy(dot2_realtime(0), dot2_realtime(1), dot2_realtime(2), m_camera);
			//if (window_dot1(2)>=m_camera.dz||window_dot2(2)>=m_camera.dz) {
			//画出向量1到向量2的连线
			this->draw_t_line(window_dot1, window_dot2);
			//}
		}
	}
}

void window::render_cuboid(cuboid& _cuboid, double resize, camera m_camera, Eigen::Matrix<double, 3, 3> camera_realtime) {
	for (size_t j = 0; j < _cuboid._vecs.size(); j++) {
		std::vector<std::vector<int>> dots;
		std::vector<Eigen::Matrix<double, 3, 1>> block = _cuboid._vecs[j].get_matrix();
		//判断是否渲染，当模型全部点在相机后面则不进行渲染
		bool render = false;//默认全部点在相机后面
		for (int i = 0; i <= block.size(); i++) {
			Eigen::Matrix<double, 3, 1> dot_realtime = camera_realtime.inverse() * this->get_world_base() * block[i % block.size()];//
			//相机角度的进行缩放,缩放要在相机坐标系下缩放，在不同基下的缩放变换是不等价的，要从相似矩阵原理触发
			dot_realtime = dot_realtime * resize;
			Eigen::Matrix<double, 3, 1> window_dot = this->to_xy(dot_realtime(0), dot_realtime(1), dot_realtime(2), m_camera);
			//if (window_dot(2) > m_camera.dz) {//此点在相机背后
			render = true;
			//}
			dots.push_back(std::vector<int>{ (int)window_dot(0), (int)window_dot(1) });
		}
		//不全部在相机后则渲染
		if (render) {
			POINT pts[5] = {
				{dots[0][0],dots[0][1]},
				{dots[1][0],dots[1][1]},
				{dots[2][0],dots[2][1]},
				{dots[3][0],dots[3][1]},
				{dots[4][0],dots[4][1]} };
			polygon(pts, 5);
		}
	}
}

void window::set_fillcolor(unsigned char r, unsigned char g, unsigned char  b) {
	setfillcolor(RGB(r,g,b));
}

Eigen::Matrix<double, 3, 3> window::trans(Eigen::Matrix<double, 3, 3> camera_realtime,double x_angle, double y_angle, double z_angle) {
	Eigen::Matrix<double, 3, 3> new_world_base;
	new_world_base << 1., 0., 0., 0., 1., 0., 0., 0., 1.;
	_world_base = camera_realtime.inverse() * utils::roate_x(x_angle) * utils::roate_y(y_angle) * utils::roate_z(z_angle) * camera_realtime * new_world_base;
	return new_world_base;
}