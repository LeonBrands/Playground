#pragma once

//Number of bounces before a ray stops recursively casting
#define NBOUNCES 50

//Number of horizontal pixels in the generated image
#define NX 1920
//Number of vertical pixels in the generated image
#define NY 1080

//Number of samples per pixel
#define NS 100

//Camera's position in the world
#define LOOK_FROM vec3{ 13, 2, 3 }
//Position the camera looks at
#define LOOK_AT vec3{ 0, 0, 0 }
//The up vector for the camera, defines the camera's roll
#define CAM_UP vec3{ 0, 1, 0 }
//The distance to the focused object, used for depth of field
#define DIST_TO_FOCUS (LOOK_AT - LOOK_FROM).length()
//The camera's aperture, modifies how much/what gets affected by dof
#define APERTURE 0.1
//The camera's (vertical) field of view
#define VFOV 20