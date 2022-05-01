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

int main(int argc, char** argv) {
	window m_window(1000,700,1);
	m_window.set_linecolor(0,255,0);
	Model model_1({
		{2, 3, 0},
		{2, 5, 0},
		{4, 3, 0},
		{4, 5, 0},
		{2,	3, 2},
		{2, 5, 2},
		{4, 3, 2},
		{4, 5, 2}},'1');
	Model model_2({
		{7, -11, 0},
		{7, -5, 0},
		{9, -15, 0},
		{27, -5, 0},
		{7, -31, 2},
		{7, -5, 2},
		{9, -33, 2},
		{17, -5, 2} }, '2');

	Model model_3({
		{-2, -3, 0},
		{-2, -5, 0},
		{-4, -3, 0},
		{-4, -5, 0},
		{-2, -3, 2},
		{-2, -5, 2},
		{-4, -3, 2},
		{-4, -5, 2} }, '3');
	
	std::vector<Model>grid;//地的网格
	for (int x = -30; x <= 30; x+=5) {
		for (int y = -30; y <= 30; y+=5) {
			Eigen::Matrix<double, 3, 1> v1(
				 x,y ,0);
			Eigen::Matrix<double, 3, 1> v2(
				x+2,y,0 );
			Eigen::Matrix<double, 3, 1> v3(
				x+2,y+2,0 );
			Eigen::Matrix<double, 3, 1> v4(
				x,y+2,0);
			std::vector<Eigen::Matrix<double, 3, 1>> ves{v1, v2, v3, v4};
			Model block(ves, ' ');
			grid.push_back(block);
		}
	}
	//建立模型
	std::vector<Model>models{model_1,model_2,model_3};
	camera m_camera;

	//记录上一次鼠标的位置
	int last_x = 0, last_y = 0;
	double last_resize = 1.0;//缩放参数
	double x_angle = 0., y_angle = 0., z_angle = 0.;//相机坐标系实时旋转角度

	Eigen::Matrix<double, 3, 3> camera_realtime=m_camera.trans(0,0,0);

	while (1) {
		//渲染地面
		m_window.set_linecolor(155,155,155);
		for (size_t j = 0; j < grid.size(); j++) {
			std::vector<std::vector<int>> dots;
			std::vector<Eigen::Matrix<double, 3, 1>> block = grid[j].resize(last_resize).get_matrix();
	/*		std::cout << block[0](1) << std::endl;
			std::cout << block[0](0) << std::endl;*/
			for (int i = 0; i <= block.size(); i++) {
				//std::cout << block[i % block.size()](0) << std::endl;
				Eigen::Matrix<double, 3, 1> dot_realtime = camera_realtime.inverse() * m_window.get_world_base() * block[i % block.size()];
				Eigen::Matrix<double, 3, 1> window_dot = m_window.to_xy(dot_realtime(0), dot_realtime(1), dot_realtime(2),m_camera);
				dots.push_back(std::vector<int>{ (int)window_dot(0), (int)window_dot(1) });
			}
			POINT pts[5] = {
				{dots[0][0],dots[0][1]},
				{dots[1][0],dots[1][1]},
				{dots[2][0],dots[2][1]},
				{dots[3][0],dots[3][1]},
				{dots[4][0],dots[4][1]} };
			polygon(pts, 5);
		}
		//Sleep(1000);
		//continue;
		//取出相机的向量进行基变换
		m_window.set_linecolor(0, 255, 0);
		for (std::size_t k = 0; k < models.size();k++) {
			auto model = models[k].resize(last_resize).get_matrix();
			//渲染物品
			for (std::size_t i = 0; i < model.size(); i++) {
				Eigen::Matrix<double, 3, 1> dot = model[i];//获得模型的向量1
				//变换到相机坐标系内
				Eigen::Matrix<double, 3, 1> dot1_realtime = camera_realtime.inverse() * m_window.get_world_base() * dot;
				//获取模型向量2
				for (std::size_t j = 0; j < model.size(); j++) {
					Eigen::Matrix<double, 3, 1> dot = model[j];
					//变换到相机坐标系内
					Eigen::Matrix<double, 3, 1> dot2_realtime = camera_realtime.inverse() * m_window.get_world_base() * dot;
					//将x y投到屏幕上，变换到图像坐标系
					Eigen::Matrix<double, 3, 1> window_dot1 = m_window.to_xy(dot1_realtime(0), dot1_realtime(1), dot1_realtime(2),m_camera);
					Eigen::Matrix<double, 3, 1> window_dot2 = m_window.to_xy(dot2_realtime(0), dot2_realtime(1), dot2_realtime(2),m_camera);
					//画出向量1到向量2的连线
					m_window.draw_t_line(window_dot1, window_dot2);
				}
			}
		}

		//操控部分
		ExMessage message;
		if (m_window.get_message(&message)) {
			if (message.message == WM_KEYDOWN) {
				if (message.vkcode == 'A') {
					m_camera.move(1, 0, 0);
				}
				else if (message.vkcode == 'S') {
					m_camera.move(0, 1, 0);
				}
				else if (message.vkcode == 'D') {
					m_camera.move(-1, 0, 0);
				}
				else if (message.vkcode == 'W') {
					m_camera.move(0, -1, 0);
				}
			}
			if (message.mbutton) {//鼠标中键按下
				x_angle = 0, y_angle = 0, z_angle = 0;
				camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//相机归位
				last_resize = 1.;//缩放归位
				m_camera.clear_move();//偏移量归零
			}
			if (message.lbutton) {//鼠标左键按下
				int dx = message.x - last_x;//求出鼠标 x y轴偏移量
				int dy = message.y - last_y;
				last_x = message.x;
				last_y = message.y;
				if (fabs(dx) < 10 && fabs(dy) < 10) {
					x_angle = ((int)x_angle + dy) % 360, y_angle = ((int)y_angle + dx) % 360, z_angle += 0;
				}
				//相机进行变换
				camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//调整相机参数
			}
			if (message.wheel) {
				if (message.ctrl) {//调整缩放参数缩放
					double dz = message.wheel / 10.;
					z_angle = ((int)z_angle + (int)dz) % 360;
				}
				else {//z轴旋转
					double dz = fabs(message.wheel) / 300.;//一次滚轮120
					if (message.wheel < 0 && (last_resize - dz)>0.1) {//变小
						last_resize = last_resize - dz;
					}
					else if (last_resize + dz < 15) {//变大
						last_resize = last_resize + dz;
					}
				}
				//相机进行变换
				camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//调整相机参数
			}
			//画出文字
			RECT r = { 0, 0, 639, 479 };
			TCHAR s[512];
			_stprintf_s(s, _T("x_angle %.3lf y_angle %.3lf z_angle %.3lf resize %.3lf "),x_angle,y_angle,z_angle,last_resize);
			drawtext(s, & r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

		m_window.sleep(50);//睡眠
		m_window.clear();//清屏
	}
	return 0;
}