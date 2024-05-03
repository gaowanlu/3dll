#include "window.h"

window::window(int width, int height, int console)
{
	_frame = new IMAGE(width, height);
	if (width <= 0 || height <= 0)
	{
		throw "window can not width or height equals 0";
	}
	_width = _last_width = width;
	_height = _last_height = height;
	_world_base << 1., 0., 0., 0., 1., 0., 0., 0., 1.;
	init_window(console);
	// ��ô��ھ��
	this->hWnd = GetHWnd();
	// �������ô��ڴ�С
	// MoveWindow(hWnd, rect.left, rect.top, 1920, height, true);
	DWORD dwStyle = GetWindowLong(this->hWnd, GWL_STYLE);
	// ����ȫ�������Ŵ��ڴ�С
	dwStyle |= WS_MAXIMIZE | WS_SIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
	SetWindowLong(this->hWnd, GWL_STYLE, dwStyle);
}
window::~window()
{
	if (this->_frame)
	{
		delete _frame;
	}
}

void window::start_frame()
{
	// ��ȡ��ʱ�Ĵ���ʵʱ��С
	//  ��ȡ����ԭʼ��С
	RECT rect;
	GetWindowRect(this->hWnd, &rect);
	int real_height = rect.bottom - rect.top;
	int real_width = rect.right - rect.left;
	if (_height != real_height || _width != real_width)
	{
		// �������ɻ���
		delete this->_frame;
		_frame = new IMAGE(real_width, real_height);
		_last_width = _width;
		_last_height = _height;
		_width = real_width;
		_height = real_height;
	}
	SetWorkingImage(this->_frame);
	this->clear(); // ����
}

void window::show_frame()
{
	SetWorkingImage();
	if (_last_height != _height || _last_width != _width)
	{
		// initgraph(_width, _height, 1);
		std::cout << "���ڴ�С�ı�" << std::endl;
		_last_height = _height;
		_last_width = _width;
	}
	if (_frame)
	{
		putimage(0, 0, _frame);
	}
}

void window::init_window(int console)
{
	// ��������
	initgraph(_width, _height, console);
}

int window::get_width()
{
	return _width;
}

int window::get_height()
{
	return _height;
}

void window::set_linecolor(unsigned char r, unsigned char g, unsigned char b)
{
	setlinecolor(RGB(r, g, b));
}

Eigen::Matrix<double, 3, 3> window::get_world_base()
{
	return this->_world_base;
}

Eigen::Matrix<double, 3, 1> window::to_xy(double x, double y, double z, camera m_camera)
{
	// ����x y z Ͷ����Ļ
	double real_x = x;
	double real_y = y; // �������y
	double real_z = z;
	real_x += get_width() / 2.;
	real_z = -real_z;
	real_z += get_height() / 2.;

	return Eigen::Matrix<double, 3, 1>(real_x, real_y, real_z);
}

void window::draw_t_line(Eigen::Matrix<double, 3, 1> dot1, Eigen::Matrix<double, 3, 1> dot2)
{
	line(dot1(0), dot1(2), dot2(0), dot2(2));
}

void window::clear()
{
	cleardevice();
}

void window::sleep(int mseconds)
{
	Sleep(mseconds);
}

bool window::get_message(ExMessage *message)
{
	bool result = peekmessage(message);
	flushmessage();
	return result;
}

void window::render_model(Model m_model, double resize, camera m_camera, Eigen::Matrix<double, 3, 3> camera_realtime)
{
	auto model = m_model.resize(resize).get_matrix();
	// ��Ⱦ��Ʒ
	for (std::size_t i = 0; i < model.size(); i++)
	{
		bool needShow = true;
		Eigen::Matrix<double, 3, 1> window_dot1;
		Eigen::Matrix<double, 3, 1> window_dot2;

		Eigen::Matrix<double, 3, 1> dot = model[i];												// ���ģ�͵�����1
		Eigen::Matrix<double, 3, 1> dot1_realtime = dot;
		// ��ת
		dot1_realtime = camera_realtime.inverse() * dot1_realtime;
		dot1_realtime -= Eigen::Matrix<double, 3, 1>{m_camera.dx, m_camera.dy, m_camera.dz}; // ��ƽ��

		// needShow = dot1_realtime(1) >= 0;

		if (needShow)
		{
			// ��ȡģ������2
			for (std::size_t j = 0; j < model.size(); j++)
			{
				Eigen::Matrix<double, 3, 1> dot = model[j];
				Eigen::Matrix<double, 3, 1> dot2_realtime = dot;

				dot2_realtime = camera_realtime.inverse() * dot2_realtime;
				dot2_realtime -= Eigen::Matrix<double, 3, 1>{m_camera.dx, m_camera.dy, m_camera.dz};
				// needShow = dot2_realtime(1) >= 0;
				if (needShow)
				{
					window_dot1 = this->to_xy(dot1_realtime(0), dot1_realtime(1), dot1_realtime(2), m_camera);
					window_dot2 = this->to_xy(dot2_realtime(0), dot2_realtime(1), dot2_realtime(2), m_camera);
					// ��������1������2������
					this->draw_t_line(window_dot1, window_dot2);
				}
			}
		}
	}
}

void window::render_cuboid(cuboid &_cuboid, double resize, camera m_camera, Eigen::Matrix<double, 3, 3> camera_realtime)
{
	// �����ݿ���һ��
	cuboid copyedCuboid = _cuboid;

	for (int i = 0; i < copyedCuboid._vecs.size(); i++)
	{
		std::vector<Eigen::Vector3d> vec = copyedCuboid._vecs[i].get_matrix(); // һ���õ�һ������������ά����
		std::vector<std::vector<int>> dots;
		bool needShow = true;
		// ����������ά��
		for (int j = 0; j <= vec.size(); j++)
		{
			// �����ֱ������ϵԭ�� �ƶ�����������ԭ�㴦 ͬʱ�������е���������ƶ�
			double dotx = vec[j % vec.size()].x();
			double doty = vec[j % vec.size()].y();
			double dotz = vec[j % vec.size()].z();

			Eigen::Vector3d vRes{dotx, doty, dotz};
			vRes = camera_realtime.inverse() * vRes;
			// ƽ��
			vRes = {vRes.x() - m_camera.dx, vRes.y() - m_camera.dy, vRes.z() - m_camera.dz}; // �����ֱ������ϵ�����Ƶ���������ϵ

			if (vRes.y() < 0)
			{
				// needShow = false;
				// break;
			}
			// ����
			vRes = vRes * resize;
			Eigen::Matrix<double, 3, 1> window_dot = this->to_xy(vRes(0), vRes(1), vRes(2), m_camera);
			dots.push_back(std::vector<int>{(int)window_dot(0),(int)window_dot(2)});
		}
		if (needShow)
		{
			POINT pts[5] = {
				{dots[0][0], dots[0][1]},
				{dots[1][0], dots[1][1]},
				{dots[2][0], dots[2][1]},
				{dots[3][0], dots[3][1]},
				{dots[4][0], dots[4][1]}};
			polygon(pts, 5);
		}
	}
}

void window::set_fillcolor(unsigned char r, unsigned char g, unsigned char b)
{
	setfillcolor(RGB(r, g, b));
}