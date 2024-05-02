#include <iostream>
#include <graphics.h>
#include <easyx.h>
#include <cmath>
#include <vector>
#include <conio.h>
#include <Eigen/Dense>
#include "utils/utils.h"
#include "camera/camera.h"
#include "utils/window.h"
#include "model/model.h"
#include "camera/camera.h"
#include "model/cuboid.h"

/**
 * @brief 全局窗口
 */
window m_window(800, 600, 1);

int main(int argc, char **argv)
{
	// 设置画的线条颜色
	m_window.set_linecolor(0, 255, 0);
	// 长方体定义
	cuboid model_1({Model({// 底面
						   {30, 30, 0},
						   {30, 60, 0},
						   {60, 60, 0},
						   {60, 30, 0}}),
					Model({// 顶面
						   {30, 30, 100},
						   {30, 60, 100},
						   {60, 60, 100},
						   {60, 30, 100}}),
					Model({// 前面
						   {30, 30, 0},
						   {60, 30, 0},
						   {60, 30, 100},
						   {30, 30, 100}}),
					Model({// 后面
						   {30, 60, 0},
						   {60, 60, 0},
						   {60, 60, 100},
						   {30, 60, 100}}),
					Model({// 左面
						   {30, 30, 0},
						   {30, 60, 0},
						   {30, 60, 100},
						   {30, 30, 100}}),
					Model({// 右面
						   {60, 30, 0},
						   {60, 60, 0},
						   {60, 60, 100},
						   {60, 30, 100}})});

	// 建立新的长方体 确定其放置的位置
	std::vector<cuboid> models;
	models.push_back(model_1);
	for (int i = 0; i <= 990; i += 30)
	{
		models.push_back(model_1.move(i, 0, 0));
		// models.push_back(model_1.move(0, i, 0));
	}
	// models.push_back(model_1.move(-10, -10, 10));

	// 用线显示下世界坐标系原点的X-Y-Z轴
	Model model_z({{0, 0, 0},
				   {0, 0, 70}},
				  'z');
	Model model_x({{0, 0, 0},
				   {30, 0, 0}},
				  'x');
	Model model_y({{0, 0, 0},
				   {0, 30, 0}},
				  'y');

	// 将世界坐标系的X-Y平面画出网格，以便于能够看到平面
	cuboid grid; // 地的网格
	constexpr int GRID_X = 1000, GRID_Y = 1000, GRID_SIZE = 100;
	for (int x = -GRID_X; x <= GRID_X; x += GRID_SIZE)
	{
		for (int y = -GRID_Y; y <= GRID_Y; y += GRID_SIZE)
		{
			Eigen::Matrix<double, 3, 1> v1(
				x, y, 0);
			Eigen::Matrix<double, 3, 1> v2(
				x + GRID_SIZE, y, 0);
			Eigen::Matrix<double, 3, 1> v3(
				x + GRID_SIZE, y + GRID_SIZE, 0);
			Eigen::Matrix<double, 3, 1> v4(
				x, y + GRID_SIZE, 0);
			std::vector<Eigen::Matrix<double, 3, 1>> ves{v1, v2, v3, v4};
			Model block(ves, ' ');
			grid.push_back(block);
		}
	}

	camera m_camera;

	// 记录上一次鼠标的位置
	int last_x = 0, last_y = 0;						 // 用于手势操作
	double last_resize = 1.0;						 // 相机镜头缩放参数
	double x_angle = 0., y_angle = 0., z_angle = 0.; // 相机坐标系实时旋转角度

	Eigen::Matrix<double, 3, 3> camera_realtime = m_camera.trans(0, 0, 0); // 此时的实时相机参数

	while (1)
	{
		m_window.start_frame();										 // 开始制作新的帧
		camera_realtime = m_camera.trans(x_angle, y_angle, z_angle); // 调整相机角度
		// 渲染世界坐标系x-y平面
		m_window.set_fillcolor(200, 200, 200);
		m_window.set_linecolor(155, 155, 155);
		m_window.render_cuboid(grid, last_resize, m_camera, camera_realtime);

		// 渲染x y z轴
		m_window.set_linecolor(255, 0, 0);
		m_window.render_model(model_x, last_resize, m_camera, camera_realtime);
		m_window.render_model(model_y, last_resize, m_camera, camera_realtime);
		m_window.render_model(model_z, last_resize, m_camera, camera_realtime);

		// 相机
		{
			m_window.set_linecolor(0, 255, 0);
			std::vector<Eigen::Vector3d> camera_local_point;
			Eigen::Vector3d camera_x{200, 0, 0};
			camera_x = m_camera.trans(m_camera.angle_x, m_camera.angle_y, m_camera.angle_z) * camera_x;
			camera_x += Eigen::Vector3d{m_camera.dx, m_camera.dy, m_camera.dz};
			camera_local_point.push_back(camera_x);

			// Eigen::Vector3d camera_y{ 0,200,0 };
			// camera_y = m_camera.trans(m_camera.angle_x, m_camera.angle_y, m_camera.angle_z) * camera_y;
			// camera_y += Eigen::Vector3d{ m_camera.dx, m_camera.dy, m_camera.dz };
			// camera_local_point.push_back(camera_y);

			Eigen::Vector3d camera_z{0, 0, 200};
			camera_z = m_camera.trans(m_camera.angle_x, m_camera.angle_y, m_camera.angle_z) * camera_z;
			camera_z += Eigen::Vector3d{m_camera.dx, m_camera.dy, m_camera.dz};
			camera_local_point.push_back(camera_z);

			for (int i = 0; i < camera_local_point.size(); i++)
			{
				Model model_camera_local({camera_local_point[i], {m_camera.dx, m_camera.dy, m_camera.dz}}, ' ');
				m_window.render_model(model_camera_local, last_resize, m_camera, camera_realtime);
			}
		}

		// 渲染提前准备好的许多立方体
		m_window.set_linecolor(200, 134, 45);
		m_window.set_fillcolor(124, 23, 124);
		for (std::size_t k = 0; k < models.size(); k++)
		{
			m_window.render_cuboid(models[k], last_resize, m_camera, camera_realtime);
		}

		// 操控部分
		ExMessage message;
		if (m_window.get_message(&message))
		{
			if (message.message == WM_KEYDOWN)
			{
				if (message.vkcode == 'Q')
				{
					m_camera.move(-10, 0, 0);
				}
				else if (message.vkcode == 'A')
				{
					m_camera.move(10, 0, 0);
				}
				else if (message.vkcode == 'W')
				{
					m_camera.move(0, -10, 0);
				}
				else if (message.vkcode == 'S')
				{
					m_camera.move(0, 10, 0);
				}
				else if (message.vkcode == 'E')
				{
					m_camera.move(0, 0, -10);
				}
				else if (message.vkcode == 'D')
				{
					m_camera.move(0, 0, 10);
				}
				else if (message.vkcode == 'R')
				{
					x_angle = ((int)x_angle - 1) % 360;
				}
				else if (message.vkcode == 'F')
				{
					x_angle = ((int)x_angle + 1) % 360;
				}
				else if (message.vkcode == 'T')
				{
					y_angle = ((int)y_angle - 1) % 360;
				}
				else if (message.vkcode == 'G')
				{
					y_angle = ((int)y_angle + 1) % 360;
				}
				else if (message.vkcode == 'Y')
				{
					z_angle = ((int)z_angle - 1) % 360;
				}
				else if (message.vkcode == 'H')
				{
					z_angle = ((int)z_angle + 1) % 360;
				}
			}

			camera_realtime = m_camera.trans(x_angle, y_angle, z_angle); // 调整相机角度

			// if (message.mbutton) {//鼠标中键按下
			//	x_angle = 0, y_angle = 0, z_angle = 0;
			//	camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//相机归位
			//	last_resize = 1.;//缩放归位
			//	m_camera.clear_move();//偏移量归零
			// }
			// if (message.lbutton) {//鼠标左键按下
			//	int dx = -(message.x - last_x);//求出鼠标 x y轴偏移量
			//	int dy = -(message.y - last_y);
			//	last_x = message.x;
			//	last_y = message.y;
			//	if (fabs(dx) < 10 && fabs(dy) < 10) {
			//		if (((int)x_angle - dy) % 360 < 181 && ((int)x_angle - dy) % 360 >-181) {
			//			x_angle = ((int)x_angle - dy) % 360;
			//		}
			//		if (((int)y_angle - dx) % 360<181 && ((int)y_angle - dx) % 360>-181) {
			//			y_angle = ((int)y_angle - dx) % 360;
			//		}
			//	}
			//	//相机进行变换
			//	camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//调整相机参数
			// }
			// if (message.wheel) {
			//	if (message.ctrl) {//z轴旋转
			//		double dz = message.wheel / 20.;
			//		z_angle = ((int)z_angle + (int)dz) % 360;
			//	}
			//	else {//调整缩放参数缩放
			//		double dz = message.wheel / 4.;//一次滚轮120
			//		m_camera.dz += dz;//深度调整
			//		dz = fabs(message.wheel / 960.);
			//		if (message.wheel < 0 && (last_resize - dz)>0.01) {//变小
			//			last_resize = last_resize - dz;//缩放系数调整
			//		}
			//		else if (last_resize + dz < 15) {//变大
			//			last_resize = last_resize + dz;//缩放系数调整
			//		}
			//	}
			//	//相机进行变换
			//	camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//调整相机参数
			// }

			// 画出文字
			RECT r = {0, 0, 639, 479};
			TCHAR s[512];
			_stprintf_s(s, _T("x_angle %.3lf y_angle %.3lf z_angle %.3lf local(%.3lf,%.3lf,%.3lf) resize %.3lf "), x_angle, y_angle, z_angle, m_camera.dx, m_camera.dy, m_camera.dz, last_resize);
			std::wcout << s << std::endl;
			drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

		m_window.show_frame(); // 将新的帧渲染到屏幕
	}
	return 0;
}
