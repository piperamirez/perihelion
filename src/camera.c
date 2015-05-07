#include "camera.h"

void initCamera(struct Camera *camera) {
    camera->x = 40;
    camera->y = 20;
    camera->z = -40;
    camera->direction = 0;
    camera->yPoint = 0;
    setPoint(camera);
}

void setPoint(struct Camera *camera) {
    camera->xPoint = camera->x + sin(camera->direction) * POINT_DISTANCE;
    camera->zPoint = camera->z + cos(camera->direction) * POINT_DISTANCE;
}

void updateCamara(struct Camera *camera, int *keys, int mouseX, int mouseY) {
	
	if (camera->x >= 100)  camera->x = 100;
	if (camera->x <= -100) camera->x = -100;
	if (camera->y >= 100)  camera->y = 100;
	if (camera->y <= -100) camera->y = -100;
	if (camera->z >= 100)  camera->z = 100;
	if (camera->z <= -100) camera->z = -100;

    if (keys['w']) {
        camera->x += sin(camera->direction) * CAM_LINEAR_SPEED;
        camera->z += cos(camera->direction) * CAM_LINEAR_SPEED;
    }
    if (keys['d']) {
        camera->x += sin(camera->direction - PI_HALF) * CAM_LINEAR_SPEED;
        camera->z += cos(camera->direction - PI_HALF) * CAM_LINEAR_SPEED;
    }
    if (keys['a']) {
        camera->x += sin(camera->direction + PI_HALF) * CAM_LINEAR_SPEED;
        camera->z += cos(camera->direction + PI_HALF) * CAM_LINEAR_SPEED;
    }
    if (keys['s']) {
        camera->x -= sin(camera->direction) * CAM_LINEAR_SPEED;
        camera->z -= cos(camera->direction) * CAM_LINEAR_SPEED;
    }
    if (keys['z']) {
        camera->y += CAM_LINEAR_SPEED;
    }
    if (keys['x']){
        camera->y -= CAM_LINEAR_SPEED;
    }

    setPoint(camera);

    camera->yPoint = (camera->screenHeight + 400 - mouseY) / 200.0;
    camera->xPoint = (camera->screenWidth - 500 - mouseX) / 200.0;

}

void reshapeCamara(struct Camera *camera, int width, int height) {
    camera->screenHeight = height;
	camera->screenWidth = width;
}