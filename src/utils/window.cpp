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
	this->clear();//����
}

void window::show_frame() {
	SetWorkingImage();
	if (_frame) {
		putimage(0, 0, _frame);
	}
}

void window::init_window(int console) {
	//��������
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
		//���������Ŀ��ľ���
		double distance = sqrt(fabs(x) * fabs(x) + fabs(y) * fabs(y) + fabs(z) * fabs(z));
		//std::cout << distance << std::endl;
		double dot_size = 5;
		double resize = 10;//400/fabs(z)
		x += m_camera.dx;
		y += m_camera.dy;
		//z += m_camera.dz;
		x *= resize;//��������
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
	//if (dot1(2) > 0 && dot2(2) > 0) {//����һ�����������ǰ��ʱ�Ž�����ʾ������
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
	//��Ⱦ��Ʒ
	for (std::size_t i = 0; i < model.size(); i++) {
		Eigen::Matrix<double, 3, 1> dot = model[i];//���ģ�͵�����1
		//�任���������ϵ��s
		Eigen::Matrix<double, 3, 1> dot1_realtime =  camera_realtime.inverse() * this->get_world_base() * dot;//
		//��ȡģ������2
		for (std::size_t j = 0; j < model.size(); j++) {
			Eigen::Matrix<double, 3, 1> dot = model[j];
			//�任���������ϵ��
			Eigen::Matrix<double, 3, 1> dot2_realtime =camera_realtime.inverse() * this->get_world_base() * dot;//
			//��x yͶ����Ļ�ϣ��任��ͼ������ϵ
			Eigen::Matrix<double, 3, 1> window_dot1 = this->to_xy(dot1_realtime(0), dot1_realtime(1), dot1_realtime(2), m_camera);
			Eigen::Matrix<double, 3, 1> window_dot2 = this->to_xy(dot2_realtime(0), dot2_realtime(1), dot2_realtime(2), m_camera);
			//if (window_dot1(2)>=m_camera.dz||window_dot2(2)>=m_camera.dz) {
			//��������1������2������
			this->draw_t_line(window_dot1, window_dot2);
			//}
		}
	}
}

void window::render_cuboid(cuboid& _cuboid, double resize, camera m_camera, Eigen::Matrix<double, 3, 3> camera_realtime) {
	for (size_t j = 0; j < _cuboid._vecs.size(); j++) {
		std::vector<std::vector<int>> dots;
		std::vector<Eigen::Matrix<double, 3, 1>> block = _cuboid._vecs[j].get_matrix();
		//�ж��Ƿ���Ⱦ����ģ��ȫ��������������򲻽�����Ⱦ
		bool render = false;//Ĭ��ȫ�������������
		for (int i = 0; i <= block.size(); i++) {
			Eigen::Matrix<double, 3, 1> dot_realtime = camera_realtime.inverse() * this->get_world_base() * block[i % block.size()];//
			//����ǶȵĽ�������,����Ҫ���������ϵ�����ţ��ڲ�ͬ���µ����ű任�ǲ��ȼ۵ģ�Ҫ�����ƾ���ԭ����
			dot_realtime = dot_realtime * resize;
			Eigen::Matrix<double, 3, 1> window_dot = this->to_xy(dot_realtime(0), dot_realtime(1), dot_realtime(2), m_camera);
			//if (window_dot(2) > m_camera.dz) {//�˵����������
			render = true;
			//}
			dots.push_back(std::vector<int>{ (int)window_dot(0), (int)window_dot(1) });
		}
		//��ȫ�������������Ⱦ
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