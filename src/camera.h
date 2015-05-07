#include <math.h>

#define POINT_DISTANCE (10)

#define CAM_LINEAR_SPEED (0.07)
#define CAM_ANGULAR_SPEED (0.002)
#define PI_HALF (3.14159/2.0)

struct Camera {
    float x, y, z;
    float xPoint, yPoint, zPoint;
    float direction;
    int screenWidth, screenHeight;
};

void initCamera(struct Camera *camera);
void reshapeCamara(struct Camera *camera, int width, int height);
void setPoint(struct Camera *camera);
void updateCamara(struct Camera *camera, int *keys, int mouseX, int mouseY);