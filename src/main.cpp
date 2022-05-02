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

int main(int argc, char** argv) {
	window m_window(1000,700,1);
	m_window.set_linecolor(0,255,0);
	cuboid model_1({
		Model({//底面
			{3, 3, 0 },
			{3, 6, 0},
			{6, 6, 0},
			{6, 3, 0}
		}),
		Model({//顶面
			{3, 3, 10 },
			{3, 6, 10},
			{6, 6, 10},
			{6, 3, 10}
		}),
		Model({//前面
			{3, 3, 0 },
			{6, 3, 0},
			{6, 3, 10},
			{3, 3, 10}
		}),
		Model({//后面
			{3, 6, 0 },
			{6, 6, 0},
			{6, 6, 10},
			{3, 6, 10}
		}),
		Model({//左面
			{3, 3, 0 },
			{3, 6, 0},
			{3, 6, 10},
			{3, 3, 10}
		}),
		Model({//右面
			{6, 3, 0 },
			{6, 6, 0},
			{6, 6, 10},
			{6, 3, 10}
		})
	});
	//建立模型
	std::vector<cuboid>models;
	models.push_back(model_1);
	for (int i = 3; i <= 99; i+=3) {
		models.push_back(model_1.move(i, 0, 0));
		models.push_back(model_1.move(0, i, 0));
	}
	models.push_back(model_1.move(-10, -10, 10));

	Model model_z({
		{0, 0, 0},
		{0, 0, 70} }, 'z');
	Model model_x({
		{0, 0, 0},
		{30, 0, 0} }, 'x');
	Model model_y({
		{0, 0, 0},
		{0, 30, 0} }, 'y');
	
	cuboid grid;//地的网格
	for (int x = -30; x <= 30; x+=5) {
		for (int y = -30; y <= 30; y+=5) {
			Eigen::Matrix<double, 3, 1> v1(
				 x,y ,0);
			Eigen::Matrix<double, 3, 1> v2(
				x+5,y,0 );
			Eigen::Matrix<double, 3, 1> v3(
				x+5,y+5,0 );
			Eigen::Matrix<double, 3, 1> v4(
				x,y+5,0);
			std::vector<Eigen::Matrix<double, 3, 1>> ves{v1, v2, v3, v4};
			Model block(ves, ' ');
			grid.push_back(block);
		}
	}

	camera m_camera;

	//记录上一次鼠标的位置
	int last_x = 0, last_y = 0;
	double last_resize = 1.0;//缩放参数
	double x_angle = 0., y_angle = 0., z_angle = 0.;//相机坐标系实时旋转角度

	Eigen::Matrix<double, 3, 3> camera_realtime=m_camera.trans(0,0,0);

	while (1) {
		//渲染地面
		m_window.set_fillcolor(200, 200, 200);
		m_window.set_linecolor(155,155,155);
		m_window.render_cuboid(grid,last_resize, m_camera, camera_realtime);
		m_window.set_linecolor(255, 0, 0);
		m_window.render_model(model_x, last_resize, m_camera, camera_realtime);
		m_window.render_model(model_y, last_resize, m_camera, camera_realtime);
		m_window.render_model(model_z, last_resize, m_camera, camera_realtime);

		//模型渲染
		m_window.set_linecolor(200, 134, 45);
		m_window.set_fillcolor(124, 23, 124);
		for (std::size_t k = 0; k < models.size();k++) {
			m_window.render_cuboid(models[k],last_resize,m_camera,camera_realtime);
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
				int dx = -(message.x - last_x);//求出鼠标 x y轴偏移量
				int dy = -(message.y - last_y);
				last_x = message.x;
				last_y = message.y;
				if (fabs(dx) < 10 && fabs(dy) < 10) {
					x_angle = ((int)x_angle + dy) % 360, y_angle = ((int)y_angle + dx) % 360, z_angle += 0;
				}
				//相机进行变换
				camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//调整相机参数
			}
			if (message.wheel) {
				if (message.ctrl) {//z轴旋转
					double dz = message.wheel / 20.;
					z_angle = ((int)z_angle + (int)dz) % 360;
				}
				else {//调整缩放参数缩放
					double dz = fabs(message.wheel) / 950.;//一次滚轮120
					if (message.wheel < 0 && (last_resize - dz)>0.1) {//变小
						last_resize = last_resize - dz;
						m_camera.dz=last_resize;
					}
					else if (last_resize + dz < 15) {//变大
						last_resize = last_resize + dz;
						m_camera.dz = last_resize;
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