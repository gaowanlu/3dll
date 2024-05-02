////#include <iostream>
////#include <graphics.h>
////#include <easyx.h>
////#include <cmath>
////#include <vector>
////#include <conio.h>
////#include <Eigen/Dense>
////#include "utils/utils.h"
////#include "camera/camera.h"
////#include "utils/window.h"
////#include "model/model.h"
////#include "camera/camera.h"
////#include "model/cuboid.h"
//
///**
// * @brief ȫ�ִ���
//*/
////window m_window(1920, 1000, 1);
//
////int main(int argc, char** argv) {
//	//m_window.set_linecolor(0,255,0);
//	//cuboid model_1({
//	//	Model({//����
//	//		{3, 3, 0 },
//	//		{3, 6, 0},
//	//		{6, 6, 0},
//	//		{6, 3, 0}
//	//	}),
//	//	Model({//����
//	//		{3, 3, 10 },
//	//		{3, 6, 10},
//	//		{6, 6, 10},
//	//		{6, 3, 10}
//	//	}),
//	//	Model({//ǰ��
//	//		{3, 3, 0 },
//	//		{6, 3, 0},
//	//		{6, 3, 10},
//	//		{3, 3, 10}
//	//	}),
//	//	Model({//����
//	//		{3, 6, 0 },
//	//		{6, 6, 0},
//	//		{6, 6, 10},
//	//		{3, 6, 10}
//	//	}),
//	//	Model({//����
//	//		{3, 3, 0 },
//	//		{3, 6, 0},
//	//		{3, 6, 10},
//	//		{3, 3, 10}
//	//	}),
//	//	Model({//����
//	//		{6, 3, 0 },
//	//		{6, 6, 0},
//	//		{6, 6, 10},
//	//		{6, 3, 10}
//	//	})
//	//});
//	////����ģ��
//	//std::vector<cuboid>models;
//	//models.push_back(model_1);
//	//for (int i = 3; i <= 99; i+=3) {
//	//	models.push_back(model_1.move(i, 0, 0));
//	//	models.push_back(model_1.move(0, i, 0));
//	//}
//	//models.push_back(model_1.move(-10, -10, 10));
//
//	//Model model_z({
//	//	{0, 0, 0},
//	//	{0, 0, 70} }, 'z');
//	//Model model_x({
//	//	{0, 0, 0},
//	//	{30, 0, 0} }, 'x');
//	//Model model_y({
//	//	{0, 0, 0},
//	//	{0, 30, 0} }, 'y');
//	//
//	//cuboid grid;//�ص�����
//	//for (int x = -100; x <= 100; x+=20) {
//	//	for (int y = -100; y <= 100; y+=20) {
//	//		Eigen::Matrix<double, 3, 1> v1(
//	//			 x,y ,0);
//	//		Eigen::Matrix<double, 3, 1> v2(
//	//			x+20,y,0 );
//	//		Eigen::Matrix<double, 3, 1> v3(
//	//			x+20,y+20,0 );
//	//		Eigen::Matrix<double, 3, 1> v4(
//	//			x,y+20,0);
//	//		std::vector<Eigen::Matrix<double, 3, 1>> ves{v1, v2, v3, v4};
//	//		Model block(ves, ' ');
//	//		grid.push_back(block);
//	//	}
//	//}
//
//	//camera m_camera;
//
//	////��¼��һ������λ��
//	//int last_x = 0, last_y = 0;//�������Ʋ���
//	//double last_resize = 1.0;//�����ͷ���Ų���
//	//double x_angle = 0., y_angle = 0., z_angle = 0.;//�������ϵʵʱ��ת�Ƕ�
//
//	//Eigen::Matrix<double, 3, 3> camera_realtime=m_camera.trans(0,0,0);//��ʱ��ʵʱ�������
//
//	//while (1) {
//	//	m_window.start_frame();//��ʼ�����µ�֡
//	//	camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);
//	//	//��Ⱦ����
//	//	m_window.set_fillcolor(200, 200, 200);
//	//	m_window.set_linecolor(155,155,155);
//	//	m_window.render_cuboid(grid,last_resize, m_camera, camera_realtime);
//	//	//��Ⱦx y z��
//	//	m_window.set_linecolor(255, 0, 0);
//	//	m_window.render_model(model_x, last_resize, m_camera, camera_realtime);
//	//	m_window.render_model(model_y, last_resize, m_camera, camera_realtime);
//	//	m_window.render_model(model_z, last_resize, m_camera, camera_realtime);
//
//	//	//ģ����Ⱦ
//	//	m_window.set_linecolor(200, 134, 45);
//	//	m_window.set_fillcolor(124, 23, 124);
//	//	for (std::size_t k = 0; k < models.size();k++) {
//	//		m_window.render_cuboid(models[k],last_resize,m_camera,camera_realtime);
//	//	}
//
//	//	//�ٿز���
//	//	ExMessage message;
//	//	if (m_window.get_message(&message)) {
//	//		if (message.message == WM_KEYDOWN) {
//	//			if (message.vkcode == 'A') {
//	//				m_camera.move(1, 0, 0);
//	//			}
//	//			else if (message.vkcode == 'S') {
//	//				m_camera.move(0, 1, 0);
//	//			}
//	//			else if (message.vkcode == 'D') {
//	//				m_camera.move(-1, 0, 0);
//	//			}
//	//			else if (message.vkcode == 'W') {
//	//				m_camera.move(0, -1, 0);
//	//			}
//	//		}
//	//		if (message.mbutton) {//����м�����
//	//			x_angle = 0, y_angle = 0, z_angle = 0;
//	//			camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//�����λ
//	//			last_resize = 1.;//���Ź�λ
//	//			m_camera.clear_move();//ƫ��������
//	//		}
//	//		if (message.lbutton) {//����������
//	//			int dx = -(message.x - last_x);//������ x y��ƫ����
//	//			int dy = -(message.y - last_y);
//	//			last_x = message.x;
//	//			last_y = message.y;
//	//			if (fabs(dx) < 10 && fabs(dy) < 10) {
//	//				if (((int)x_angle - dy) % 360 < 88 && ((int)x_angle - dy) % 360 >-10) {
//	//					x_angle = ((int)x_angle - dy) % 360;
//	//				}
//	//				if (((int)y_angle - dx) % 360<66 && ((int)y_angle - dx) % 360>-66) {
//	//					y_angle = ((int)y_angle - dx) % 360;
//	//				}
//	//			}
//	//			//������б任
//	//			camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//�����������
//	//		}
//	//		if (message.wheel) {
//	//			if (message.ctrl) {//z����ת
//	//				double dz = message.wheel / 20.;
//	//				z_angle = ((int)z_angle + (int)dz) % 360;
//	//			}
//	//			else {//�������Ų�������
//	//				double dz = message.wheel / 4.;//һ�ι���120
//	//				m_camera.dz += dz;//��ȵ���
//	//				dz = fabs(message.wheel / 960.);
//	//				if (message.wheel < 0 && (last_resize - dz)>0.01) {//��С
//	//					last_resize = last_resize - dz;//����ϵ������
//	//				}
//	//				else if (last_resize + dz < 15) {//���
//	//					last_resize = last_resize + dz;//����ϵ������
//	//				}
//	//			}
//	//			//������б任
//	//			camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//�����������
//	//		}
//	//		//��������
//	//		RECT r = { 0, 0, 639, 479 };
//	//		TCHAR s[512];
//	//		_stprintf_s(s, _T("x_angle %.3lf y_angle %.3lf z_angle %.3lf resize %.3lf "),x_angle,y_angle,z_angle,last_resize);
//	//		drawtext(s, & r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//	//	}
//	//	m_window.show_frame();//���µ�֡��Ⱦ����Ļ
//	//}
////	return 0;
////}
//
///*This source code copyrighted by Lazy Foo' Productions 2004-2023
// and may not be redistributed without written permission.*/
//
////Using SDL and standard IO
// #include <SDL2/SDL.h>
// #include <stdio.h>
//
////Screen dimension constants
// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 480;
//
////Starts up SDL and creates window
// bool init();
//
////Loads media
// bool loadMedia();
//
////Frees media and shuts down SDL
// void close();
//
////The window we'll be rendering to
// SDL_Window* gWindow = NULL;
//
////The surface contained by the window
// SDL_Surface* gScreenSurface = NULL;
//
////The image we will load and show on the screen
// SDL_Surface* gHelloWorld = NULL;
//
// bool init()
//{
//	//Initialization flag
//	bool success = true;
//
//	//Initialize SDL
//	if (SDL_Init(SDL_INIT_VIDEO) < 0)
//	{
//		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//		success = false;
//	}
//	else
//	{
//		//Create window
//		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//		if (gWindow == NULL)
//		{
//			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//			success = false;
//		}
//		else
//		{
//			//Get window surface
//			gScreenSurface = SDL_GetWindowSurface(gWindow);
//		}
//	}
//
//	return success;
// }
//
// bool loadMedia()
//{
//	//Loading success flag
//	bool success = true;
//
//	//Load splash image
//	gHelloWorld = SDL_LoadBMP("hello_world.bmp");
//	if (gHelloWorld == NULL)
//	{
//		printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
//		success = false;
//	}
//
//	return success;
// }
//
// void close()
//{
//	//Deallocate surface
//	SDL_FreeSurface(gHelloWorld);
//	gHelloWorld = NULL;
//
//	//Destroy window
//	SDL_DestroyWindow(gWindow);
//	gWindow = NULL;
//
//	//Quit SDL subsystems
//	SDL_Quit();
// }
//
// int main(int argc, char* args[])
//{
//	//Start up SDL and create window
//	if (!init())
//	{
//		printf("Failed to initialize!\n");
//	}
//	else
//	{
//		//Load media
//		if (!loadMedia())
//		{
//			printf("Failed to load media!\n");
//		}
//		else
//		{
//			//Apply the image
//			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
//
//			//Update the surface
//			SDL_UpdateWindowSurface(gWindow);
//
//			//Hack to get window to stay up
//			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
//		}
//	}
//
//	//Free resources and close SDL
//	close();
//
//	return 0;
// }
//
