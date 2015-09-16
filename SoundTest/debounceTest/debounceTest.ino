/*
  debounce test on 9.16.2015
  hardware + state change 
  cat sound + led 

*/



#include <PCM.h>

#define BUTTON_2 4

int LED = A0;
boolean goOn = false;

boolean wasPressed = false;
int buttonState = 0;
const unsigned char cat[] PROGMEM = {
  126, 125, 126, 128, 128, 128, 128, 128, 128, 127, 127, 128, 127, 127, 127, 128, 128, 128, 129, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 129, 129, 128, 127, 126, 127, 128, 128, 127, 127, 128, 128, 128, 127, 126, 127, 128, 128, 128, 129, 129, 127, 126, 126, 127, 128, 128, 127, 127, 127, 127, 127, 128, 127, 126, 126, 127, 128, 128, 128, 129, 128, 127, 127, 128, 127, 126, 126, 128, 127, 127, 127, 128, 127, 127, 128, 128, 128, 128, 128, 129, 129, 128, 127, 126, 126, 127, 126, 127, 128, 128, 128, 127, 127, 127, 128, 128, 127, 127, 126, 126, 127, 128, 129, 128, 128, 128, 128, 128, 129, 129, 128, 127, 127, 128, 129, 129, 127, 125, 126, 128, 129, 127, 127, 128, 127, 126, 127, 129, 129, 128, 128, 127, 127, 127, 128, 129, 129, 129, 128, 127, 126, 125, 126, 127, 127, 128, 128, 127, 126, 127, 129, 129, 127, 126, 127, 128, 127, 127, 126, 126, 127, 129, 128, 125, 124, 127, 128, 127, 126, 128, 130, 130, 129, 128, 127, 127, 125, 123, 124, 128, 130, 129, 127, 127, 127, 127, 128, 128, 127, 126, 127, 128, 128, 128, 129, 130, 128, 127, 129, 131, 128, 123, 123, 127, 128, 126, 127, 129, 128, 125, 125, 129, 130, 129, 129, 128, 129, 132, 131, 127, 126, 129, 130, 128, 129, 132, 130, 124, 123, 127, 130, 128, 126, 127, 129, 129, 129, 130, 130, 128, 126, 127, 129, 129, 128, 128, 127, 127, 129, 133, 131, 127, 125, 126, 126, 125, 125, 127, 129, 130, 129, 127, 128, 131, 129, 126, 126, 129, 130, 128, 128, 128, 128, 128, 128, 126, 124, 125, 128, 129, 128, 126, 127, 128, 129, 129, 128, 127, 126, 124, 124, 126, 128, 129, 128, 127, 126, 125, 126, 126, 126, 128, 129, 127, 125, 125, 127, 127, 130, 134, 135, 131, 128, 129, 133, 135, 133, 131, 131, 134, 136, 137, 136, 136, 134, 133, 136, 139, 137, 134, 131, 127, 124, 126, 129, 129, 125, 124, 124, 125, 125, 125, 122, 121, 123, 127, 126, 123, 123, 124, 123, 120, 120, 121, 121, 118, 117, 119, 117, 112, 108, 110, 112, 112, 113, 115, 114, 113, 116, 122, 124, 125, 130, 132, 128, 124, 126, 131, 133, 135, 135, 136, 138, 143, 144, 140, 135, 132, 132, 134, 137, 139, 138, 139, 141, 140, 135, 133, 136, 137, 136, 136, 140, 145, 144, 139, 138, 139, 138, 134, 131, 131, 132, 134, 134, 131, 125, 124, 124, 122, 122, 127, 130, 125, 119, 121, 123, 120, 116, 115, 118, 124, 129, 127, 119, 117, 124, 128, 123, 117, 117, 120, 121, 119, 120, 122, 122, 122, 123, 127, 130, 133, 135, 135, 131, 129, 131, 133, 131, 131, 135, 136, 134, 133, 136, 139, 140, 143, 144, 140, 134, 131, 133, 138, 140, 138, 133, 133, 134, 134, 135, 138, 138, 134, 129, 126, 124, 122, 125, 128, 127, 124, 123, 124, 126, 128, 129, 129, 127, 123, 120, 120, 122, 121, 117, 117, 121, 122, 119, 116, 117, 119, 117, 114, 112, 115, 119, 118, 116, 119, 121, 118, 114, 117, 121, 119, 117, 117, 119, 122, 127, 132, 132, 127, 126, 126, 131, 135, 133, 131, 131, 135, 135, 131, 135, 139, 139, 140, 142, 143, 133, 125, 129, 133, 135, 133, 134, 138, 135, 132, 134, 137, 138, 132, 127, 129, 128, 127, 128, 133, 137, 136, 136, 135, 127, 121, 119, 122, 126, 127, 129, 128, 125, 126, 124, 122, 124, 123, 119, 115, 118, 124, 122, 121, 129, 134, 132, 122, 117, 118, 117, 119, 122, 124, 129, 130, 128, 125, 120, 120, 119, 120, 125, 126, 127, 128, 129, 135, 138, 137, 133, 127, 127, 127, 127, 131, 132, 136, 142, 140, 137, 128, 125, 130, 126, 127, 130, 133, 140, 138, 136, 132, 122, 124, 124, 126, 126, 124, 135, 141, 139, 134, 128, 129, 124, 118, 121, 124, 128, 130, 134, 132, 121, 113, 117, 123, 123, 116, 114, 119, 128, 128, 120, 114, 116, 121, 117, 113, 116, 121, 129, 133, 132, 130, 119, 114, 109, 109, 117, 118, 120, 122, 124, 124, 113, 113, 123, 128, 127, 123, 127, 133, 135, 134, 128, 125, 128, 132, 126, 119, 124, 132, 139, 137, 138, 137, 125, 120, 115, 117, 124, 131, 147, 145, 134, 128, 126, 132, 126, 127, 138, 138, 134, 125, 125, 126, 123, 129, 128, 123, 120, 128, 130, 119, 115, 120, 130, 123, 117, 122, 121, 127, 123, 122, 122, 113, 121, 120, 124, 126, 116, 125, 128, 130, 127, 119, 132, 129, 121, 118, 116, 123, 124, 131, 133, 124, 123, 128, 133, 127, 123, 128, 132, 136, 132, 134, 137, 140, 140, 128, 128, 134, 140, 136, 128, 136, 138, 134, 130, 130, 135, 136, 139, 133, 127, 130, 137, 139, 122, 126, 141, 145, 139, 122, 133, 136, 128, 128, 120, 129, 128, 125, 132, 120, 127, 129, 127, 127, 115, 125, 127, 120, 120, 118, 131, 130, 120, 121, 129, 133, 116, 106, 122, 140, 134, 118, 125, 136, 136, 121, 115, 129, 132, 137, 128, 117, 125, 132, 138, 123, 117, 141, 145, 131, 114, 125, 153, 149, 134, 129, 137, 143, 129, 121, 132, 153, 156, 137, 123, 126, 136, 128, 123, 137, 150, 148, 125, 122, 134, 132, 126, 121, 137, 149, 138, 130, 128, 138, 140, 122, 117, 122, 134, 132, 115, 116, 132, 137, 126, 115, 127, 136, 124, 111, 116, 132, 132, 118, 117, 135, 144, 124, 108, 116, 136, 134, 111, 116, 134, 141, 131, 115, 127, 134, 126, 121, 112, 133, 145, 133, 128, 123, 136, 129, 109, 129, 144, 147, 133, 120, 136, 127, 114, 122, 136, 152, 138, 121, 128, 129, 123, 115, 123, 148, 143, 115, 112, 127, 134, 117, 108, 139, 152, 127, 108, 110, 133, 128, 106, 118, 135, 142, 125, 103, 121, 132, 116, 104, 108, 137, 137, 109, 112, 124, 128, 113, 99, 125, 138, 123, 110, 106, 124, 121, 102, 116, 136, 141, 120, 101, 117, 123, 105, 106, 124, 140, 132, 109, 119, 126, 114, 114, 113, 132, 133, 111, 124, 121, 122, 119, 111, 141, 130, 116, 126, 122, 131, 104, 105, 139, 131, 130, 120, 128, 140, 108, 105, 114, 129, 141, 119, 118, 128, 129, 117, 99, 122, 146, 132, 112, 115, 129, 116, 103, 116, 139, 135, 119, 122, 121, 116, 106, 112, 131, 124, 123, 119, 123, 127, 104, 112, 125, 132, 122, 106, 128, 126, 108, 104, 121, 142, 122, 117, 128, 127, 112, 99, 119, 133, 129, 121, 128, 133, 117, 106, 114, 140, 136, 121, 124, 129, 128, 103, 116, 143, 144, 135, 121, 135, 126, 109, 119, 136, 148, 135, 131, 139, 131, 116, 120, 143, 146, 135, 125, 141, 136, 113, 124, 137, 154, 139, 126, 143, 127, 124, 117, 128, 151, 132, 137, 136, 131, 125, 113, 138, 141, 126, 126, 132, 134, 114, 112, 141, 146, 127, 119, 130, 137, 114, 112, 134, 140, 127, 116, 132, 136, 123, 122, 134, 142, 124, 112, 129, 140, 128, 121, 137, 155, 128, 111, 139, 145, 132, 118, 143, 155, 120, 129, 146, 143, 132, 132, 157, 143, 121, 140, 146, 138, 131, 132, 160, 147, 129, 145, 139, 146, 130, 124, 155, 137, 139, 141, 133, 151, 123, 135, 149, 131, 142, 125, 140, 139, 112, 136, 144, 139, 128, 128, 145, 128, 109, 134, 142, 121, 124, 131, 139, 117, 113, 151, 133, 117, 124, 126, 132, 110, 122, 149, 128, 127, 126, 123, 131, 115, 137, 143, 121, 130, 125, 129, 124, 122, 152, 147, 125, 130, 132, 131, 123, 123, 153, 143, 126, 142, 135, 139, 125, 129, 161, 129, 128, 141, 136, 141, 110, 143, 159, 122, 140, 135, 141, 124, 112, 154, 127, 121, 141, 134, 131, 112, 134, 145, 114, 126, 127, 118, 123, 113, 134, 127, 120, 133, 111, 118, 114, 117, 137, 113, 115, 120, 120, 119, 98, 135, 143, 107, 118, 118, 123, 104, 110, 149, 112, 120, 134, 123, 119, 109, 144, 127, 107, 132, 128, 125, 120, 127, 146, 123, 121, 135, 126, 136, 113, 137, 148, 109, 127, 125, 149, 121, 118, 169, 120, 117, 117, 137, 128, 100, 162, 140, 116, 121, 127, 133, 103, 134, 146, 116, 119, 119, 118, 117, 116, 144, 131, 113, 121, 112, 126, 105, 110, 144, 119, 111, 107, 127, 132, 96, 134, 135, 101, 112, 112, 133, 100, 115, 164, 100, 111, 120, 131, 125, 85, 161, 126, 99, 129, 115, 145, 97, 133, 164, 101, 131, 120, 135, 125, 94, 166, 131, 120, 137, 124, 152, 100, 138, 157, 112, 136, 123, 146, 117, 117, 169, 125, 130, 129, 140, 127, 103, 163, 132, 116, 130, 131, 141, 93, 154, 156, 107, 130, 110, 141, 97, 119, 173, 106, 130, 115, 128, 118, 90, 171, 129, 106, 117, 116, 131, 86, 140, 165, 110, 114, 116, 134, 98, 105, 172, 125, 107, 114, 136, 124, 94, 169, 145, 116, 117, 119, 138, 92, 154, 159, 123, 139, 112, 142, 113, 134, 165, 120, 151, 120, 121, 129, 126, 171, 127, 146, 142, 118, 129, 112, 161, 135, 134, 144, 124, 134, 107, 156, 147, 127, 135, 124, 134, 97, 136, 153, 128, 131, 125, 134, 105, 122, 150, 123, 124, 125, 122, 107, 113, 152, 127, 120, 135, 118, 109, 100, 148, 131, 106, 135, 120, 124, 95, 141, 150, 107, 129, 115, 130, 98, 123, 159, 116, 128, 120, 138, 112, 115, 162, 123, 125, 120, 134, 119, 111, 169, 131, 128, 131, 137, 125, 101, 168, 133, 121, 132, 136, 138, 98, 168, 141, 121, 133, 127, 142, 91, 155, 141, 118, 136, 122, 148, 95, 147, 144, 109, 130, 112, 142, 92, 133, 152, 108, 128, 112, 142, 95, 115, 152, 107, 117, 107, 137, 101, 109, 154, 115, 119, 109, 132, 99, 105, 146, 114, 120, 113, 137, 102, 115, 150, 115, 125, 112, 137, 97, 115, 154, 112, 136, 119, 144, 105, 118, 162, 106, 137, 120, 139, 108, 116, 173, 107, 141, 130, 139, 113, 111, 174, 102, 134, 130, 138, 115, 113, 178, 105, 132, 128, 137, 107, 108, 174, 98, 129, 122, 143, 104, 112, 178, 92, 127, 113, 141, 94, 106, 181, 87, 128, 114, 145, 95, 105, 185, 81, 120, 112, 140, 95, 105, 191, 87, 121, 119, 140, 96, 106, 189, 88, 119, 120, 143, 99, 117, 194, 95, 127, 121, 146, 95, 121, 192, 93, 136, 121, 156, 96, 133, 195, 92, 143, 114, 159, 88, 138, 192, 93, 152, 116, 169, 84, 146, 184, 91, 149, 109, 170, 77, 155, 176, 97, 151, 110, 171, 69, 160, 160, 95, 145, 110, 167, 69, 172, 151, 99, 142, 114, 156, 64, 175, 138, 98, 137, 125, 149, 68, 187, 131, 101, 128, 132, 138, 65, 195, 123, 110, 124, 145, 137, 68, 204, 114, 116, 115, 148, 133, 71, 213, 110, 130, 114, 156, 130, 78, 213, 100, 138, 108, 160, 123, 93, 216, 97, 151, 104, 167, 108, 106, 207, 90, 158, 100, 179, 95, 128, 201, 90, 161, 93, 183, 76, 144, 184, 93, 161, 95, 191, 65, 164, 164, 98, 150, 92, 186, 53, 183, 142, 112, 143, 101, 181, 48, 198, 114, 121, 127, 109, 168, 51, 213, 96, 135, 115, 123, 149, 58, 215, 77, 144, 101, 141, 129, 81, 214, 72, 155, 86, 157, 103, 105, 198, 71, 165, 78, 176, 86, 140, 177, 78, 168, 71, 182, 68, 172, 149, 94, 169, 78, 183, 63, 201, 114, 112, 157, 87, 170, 66, 223, 86, 138, 143, 106, 149, 79, 227, 58, 156, 123, 127, 124, 106, 220, 49, 171, 106, 144, 95, 134, 192, 50, 174, 95, 157, 77, 169, 157, 67, 167, 88, 155, 65, 191, 118, 92, 155, 96, 148, 74, 203, 85, 118, 133, 105, 127, 96, 197, 68, 143, 118, 123, 106, 128, 173, 66, 154, 103, 134, 90, 162, 142, 85, 157, 101, 138, 86, 185, 104, 111, 145, 108, 132, 100, 196, 77, 144, 128, 121, 115, 124, 184, 62, 167, 110, 138, 100, 159, 158, 68, 176, 96, 144, 87, 186, 119, 91, 171, 95, 144, 90, 204, 80, 122, 149, 101, 129, 106, 203, 54, 155, 126, 114, 110, 134, 181, 45, 173, 106, 125, 93, 167, 148, 61, 177, 99, 129, 84, 192, 106, 90, 163, 104, 126, 92, 205, 74, 128, 139, 116, 112, 112, 195, 57, 158, 117, 133, 98, 144, 169, 61, 171, 102, 141, 86, 173, 131, 84, 169, 102, 142, 89, 193, 94, 114, 151, 110, 130, 104, 195, 72, 145, 131, 126, 113, 131, 176, 66, 162, 113, 138, 98, 162, 146, 82, 167, 107, 142, 92, 183, 111, 106, 155, 113, 135, 101, 192, 86, 135, 138, 126, 119, 122, 180, 75, 155, 122, 140, 104, 150, 156, 81, 163, 112, 145, 94, 174, 124, 100, 158, 115, 142, 98, 186, 96, 123, 142, 125, 128, 114, 183, 80, 144, 126, 138, 111, 138, 164, 78, 154, 113, 147, 97, 164, 136, 90, 154, 109, 148, 91, 184, 106, 111, 144, 114, 141, 97, 195, 81, 134, 129, 125, 129, 112, 193, 67, 154, 116, 138, 115, 134, 182, 64, 167, 106, 147, 104, 157, 164, 72, 172, 102, 153, 98, 178, 142, 85, 170, 102, 152, 97, 193, 121, 100, 164, 106, 147, 99, 200, 104, 114, 153, 112, 139, 105, 201, 91, 127, 140, 117, 130, 112, 194, 81, 139, 126, 120, 122, 124, 181, 75, 149, 115, 120, 112, 138, 166, 70, 157, 109, 120, 103, 154, 151, 69, 161, 108, 121, 95, 169, 138, 74, 161, 109, 123, 92, 180, 126, 83, 158, 111, 124, 95, 188, 115, 97, 157, 113, 125, 102, 193, 103, 111, 156, 115, 125, 112, 195, 93, 123, 153, 116, 123, 122, 195, 83, 134, 148, 117, 120, 132, 191, 75, 146, 140, 117, 117, 141, 184, 68, 157, 131, 118, 113, 151, 172, 61, 164, 120, 115, 106, 161, 157, 57, 167, 112, 113, 98, 171, 140, 58, 166, 107, 112, 93, 181, 124, 66, 165, 105, 112, 92, 189, 108, 76, 163, 108, 111, 97, 196, 96, 86, 161, 112, 107, 106, 200, 91, 98, 161, 121, 106, 117, 201, 88, 107, 159, 127, 105, 126, 198, 88, 116, 156, 131, 106, 133, 191, 84, 123, 151, 131, 110, 141, 186, 84, 132, 147, 129, 110, 146, 179, 81, 140, 142, 129, 109, 151, 170, 78, 145, 132, 127, 104, 152, 157, 74, 150, 123, 128, 100, 157, 143, 73, 153, 114, 126, 95, 165, 131, 76, 157, 113, 125, 89, 173, 117, 79, 156, 115, 124, 86, 183, 107, 88, 156, 121, 126, 87, 191, 99, 98, 155, 127, 129, 95, 200, 93, 109, 155, 129, 125, 102, 203, 86, 119, 158, 133, 120, 110, 205, 77, 123, 157, 138, 113, 117, 208, 75, 127, 154, 144, 110, 121, 204, 73, 130, 142, 142, 109, 124, 193, 74, 138, 129, 131, 107, 126, 172, 67, 147, 120, 117, 109, 138, 155, 58, 158, 119, 101, 105, 154, 146, 47, 164, 127, 93, 99, 169, 147, 40, 164, 135, 90, 91, 176, 155, 43, 164, 147, 100, 91, 179, 160, 50, 161, 150, 111, 98, 183, 162, 60, 161, 146, 114, 102, 183, 156, 63, 161, 141, 111, 106, 186, 152, 62, 163, 139, 103, 106, 187, 148, 59, 165, 142, 101, 107, 188, 145, 53, 158, 139, 94, 105, 186, 143, 51, 153, 134, 89, 103, 182, 137, 51, 152, 127, 86, 105, 182, 133, 55, 158, 124, 83, 106, 181, 125, 53, 163, 124, 83, 112, 186, 124, 54, 167, 124, 81, 116, 190, 125, 61, 175, 131, 84, 125, 197, 127, 67, 183, 136, 84, 130, 200, 126, 69, 190, 140, 83, 133, 201, 121, 61, 191, 140, 79, 134, 206, 125, 57, 193, 141, 75, 130, 205, 126, 53, 192, 142, 74, 125, 204, 124, 50, 186, 137, 70, 117, 199, 116, 47, 183, 133, 68, 115, 202, 111, 42, 180, 129, 61, 111, 207, 114, 42, 184, 134, 57, 105, 207, 118, 38, 183, 141, 57, 103, 208, 129, 42, 183, 150, 64, 105, 206, 138, 50, 185, 157, 76, 113, 209, 146, 59, 187, 153, 80, 111, 205, 145, 63, 192, 149, 83, 108, 199, 138, 60, 191, 143, 86, 104, 196, 137, 60, 189, 142, 93, 103, 189, 134, 63, 180, 132, 101, 106, 182, 129, 76, 177, 117, 101, 112, 174, 110, 84, 187, 109, 95, 126, 185, 94, 80, 200, 112, 81, 126, 204, 90, 65, 203, 130, 73, 112, 219, 101, 50, 187, 147, 76, 91, 224, 125, 54, 169, 164, 96, 76, 215, 145, 66, 149, 170, 124, 73, 201, 161, 88, 130, 158, 144, 77, 176, 159, 111, 122, 138, 148, 96, 166, 142, 123, 133, 130, 126, 102, 177, 134, 112, 140, 157, 116, 80, 183, 152, 95, 106, 177, 136, 55, 157, 179, 115, 68, 162, 167, 62, 117, 175, 149, 62, 131, 174, 93, 104, 159, 168, 81, 119, 158, 105, 104, 149, 165, 90, 126, 155, 108, 100, 153, 170, 86, 123, 161, 119, 91, 153, 189, 101, 118, 164, 141, 92, 144, 194, 122, 118, 153, 149, 97, 138, 185, 133, 124, 144, 144, 91, 132, 170, 128, 126, 144, 144, 85, 131, 167, 122, 118, 144, 147, 76, 121, 172, 126, 104, 141, 158, 73, 101, 168, 140, 87, 123, 166, 82, 79, 152, 166, 91, 102, 171, 107, 72, 121, 182, 113, 84, 161, 137, 89, 96, 180, 142, 80, 135, 145, 109, 81, 161, 161, 92, 115, 144, 126, 81, 144, 170, 112, 105, 139, 140, 91, 138, 174, 138, 111, 140, 149, 97, 135, 171, 145, 112, 140, 157, 95, 127, 173, 152, 103, 129, 165, 96, 106, 167, 167, 104, 115, 170, 110, 92, 155, 179, 112, 101, 165, 123, 79, 131, 187, 125, 86, 154, 138, 73, 95, 177, 142, 74, 131, 152, 89, 72, 159, 167, 84, 110, 158, 113, 66, 133, 185, 109, 95, 155, 140, 74, 105, 184, 140, 87, 135, 153, 89, 86, 166, 166, 100, 123, 164, 106, 82, 151, 181, 118, 111, 180, 134, 80, 139, 197, 148, 89, 174, 168, 80, 108, 189, 183, 77, 135, 192, 99, 78, 158, 211, 93, 85, 188, 133, 63, 116, 222, 140, 57, 159, 172, 76, 73, 197, 184, 63, 107, 186, 108, 52, 156, 202, 95, 64, 173, 139, 46, 118, 200, 138, 45, 145, 177, 63, 88, 184, 186, 57, 100, 195, 101, 70, 149, 212, 101, 66, 179, 139, 68, 108, 204, 143, 54, 144, 171, 87, 74, 182, 185, 71, 97, 186, 132, 58, 141, 210, 124, 65, 161, 184, 79, 95, 192, 179, 67, 104, 194, 117, 68, 145, 206, 105, 59, 168, 156, 70, 91, 197, 159, 48, 120, 181, 105, 58, 160, 201, 79, 71, 171, 147, 51, 108, 209, 127, 43, 133, 182, 71, 56, 186, 183, 46, 70, 193, 125, 29, 129, 226, 109, 24, 155, 189, 59, 62, 210, 194, 36, 84, 205, 129, 34, 139, 238, 103, 31, 159, 188, 62, 59, 215, 187, 40, 85, 202, 139, 30, 138, 232, 113, 37, 152, 204, 74, 65, 205, 195, 56, 77, 204, 143, 39, 125, 226, 119, 31, 147, 196, 72, 45, 193, 197, 47, 64, 196, 155, 21, 105, 231, 137, 26, 125, 217, 84, 30, 173, 220, 73, 42, 193, 172, 37, 77, 223, 165, 23, 110, 207, 108, 21, 154, 232, 84, 43, 173, 191, 47, 66, 225, 181, 43, 92, 214, 131, 26, 142, 237, 117, 34, 154, 200, 67, 47, 198, 205, 57, 65, 195, 161, 28, 100, 234, 153, 31, 114, 221, 105, 26, 164, 237, 99, 30, 177, 203, 54, 52, 211, 208, 40, 66, 209, 157, 21, 94, 240, 150, 19, 110, 218, 111, 15, 150, 240, 106, 24, 155, 215, 72, 34, 193, 227, 68, 41, 188, 193, 42, 60, 219, 196, 41, 62, 208, 162, 28, 91, 230, 170, 26, 95, 217, 143, 30, 118, 243, 142, 27, 119, 227, 128, 23, 147, 244, 120, 16, 139, 235, 97, 18, 164, 245, 89, 7, 168, 235, 72, 15, 190, 244, 62, 15, 196, 231, 50, 25, 215, 233, 42, 32, 213, 214, 30, 40, 225, 207, 33, 46, 216, 190, 23, 57, 218, 195, 34, 59, 213, 181, 32, 60, 223, 199, 38, 61, 215, 192, 29, 59, 231, 200, 30, 56, 227, 191, 16, 63, 237, 193, 19, 65, 235, 178, 18, 77, 238, 184, 27, 82, 226, 176, 37, 83, 225, 183, 51, 81, 209, 183, 48, 73, 208, 197, 58, 60, 202, 194, 50, 54, 208, 212, 52, 49, 202, 200, 45, 52, 220, 213, 50, 52, 202, 193, 41, 64, 219, 202, 52, 56, 193, 175, 48, 76, 206, 190, 57, 65, 176, 161, 62, 85, 198, 181, 71, 75, 166, 161, 73, 93, 190, 178, 81, 75, 162, 161, 82, 95, 180, 175, 82, 81, 162, 155, 83, 99, 183, 166, 80, 96, 169, 152, 83, 113, 187, 153, 84, 109, 173, 143, 87, 128, 179, 142, 86, 119, 169, 131, 89, 126, 173, 139, 88, 121, 161, 131, 92, 129, 173, 131, 87, 121, 163, 129, 93, 138, 170, 124, 87, 125, 157, 117, 99, 143, 160, 116, 87, 123, 142, 119, 110, 136, 152, 119, 94, 110, 135, 133, 114, 131, 152, 128, 91, 105, 152, 140, 104, 125, 161, 132, 80, 109, 157, 132, 100, 136, 171, 121, 79, 120, 154, 124, 99, 142, 167, 122, 94, 124, 155, 129, 107, 136, 159, 136, 101, 114, 147, 138, 117, 129, 159, 140, 99, 107, 139, 138, 114, 129, 157, 135, 101, 110, 144, 137, 109, 124, 152, 143, 106, 105, 134, 136, 119, 120, 143, 140, 109, 107, 128, 136, 118, 114, 133, 131, 116, 110, 121, 129, 124, 126, 127, 127, 122, 112, 115, 125, 133, 122, 120, 139, 138, 113, 106, 135, 141, 109, 111, 145, 145, 106, 107, 146, 139, 106, 116, 152, 143, 104, 114, 141, 133, 109, 123, 155, 146, 119, 116, 135, 138, 118, 118, 139, 150, 130, 109, 125, 144, 134, 116, 128, 148, 129, 106, 118, 143, 134, 110, 126, 150, 137, 106, 111, 142, 135, 112, 119, 146, 138, 103, 110, 144, 140, 105, 105, 147, 151, 115, 101, 126, 137, 111, 104, 130, 146, 129, 106, 117, 134, 129, 111, 115, 137, 133, 112, 112, 133, 135, 114, 120, 143, 140, 114, 109, 130, 128, 115, 121, 138, 140, 125, 122, 124, 127, 127, 120, 119, 130, 145, 135, 112, 118, 135, 133, 119, 131, 151, 136, 111, 115, 135, 132, 116, 125, 145, 145, 123, 112, 124, 133, 125, 114, 127, 146, 136, 111, 108, 129, 133, 117, 123, 145, 144, 115, 104, 124, 133, 120, 115, 134, 147, 131, 114, 115, 125, 124, 118, 126, 135, 130, 114, 112, 125, 129, 124, 120, 128, 134, 128, 119, 114, 122, 129, 125, 123, 133, 145, 133, 112, 115, 132, 133, 118, 125, 144, 138, 113, 112, 133, 134, 115, 119, 145, 148, 118, 104, 125, 139, 125, 112, 131, 153, 143, 119, 117, 133, 132, 115, 119, 142, 151, 132, 118, 125, 130, 121, 117, 132, 145, 140, 126, 116, 116, 121, 127, 130, 134, 143, 142, 124, 110, 121, 136, 130, 122, 135, 150, 139, 116, 117, 132, 134, 124, 124, 138, 143, 132, 117, 117, 128, 133, 130, 130, 139, 139, 126, 119, 127, 134, 127, 126, 141, 150, 138, 121, 120, 129, 134, 132, 132, 136, 139, 138, 130, 122, 121, 125, 128, 129, 139, 149, 142, 121, 112, 123, 134, 130, 128, 140, 147, 136, 123, 126, 132, 126, 120, 132, 148, 143, 124, 119, 129, 135, 127, 123, 132, 140, 134, 124, 123, 128, 131, 128, 129, 136, 142, 139, 127, 118, 122, 132, 138, 136, 135, 138, 140, 134, 126, 124, 127, 128, 129, 134, 142, 144, 135, 123, 120, 126, 132, 130, 130, 139, 147, 140, 123, 116, 127, 138, 137, 134, 140, 145, 137, 123, 119, 126, 132, 132, 135, 141, 140, 128, 118, 119, 127, 129, 126, 130, 140, 143, 130, 114, 112, 125, 135, 132, 127, 130, 137, 133, 122, 118, 125, 131, 128, 123, 127, 134, 133, 124, 119, 124, 128, 122, 114, 119, 133, 139, 130, 120, 124, 133, 131, 118, 113, 126, 140, 139, 127, 122, 129, 134, 130, 123, 122, 128, 134, 136, 133, 128, 123, 124, 127, 127, 128, 133, 136, 129, 120, 124, 134, 133, 123, 125, 140, 146, 131, 119, 124, 133, 127, 119, 126, 141, 145, 134, 123, 120, 120, 121, 125, 128, 130, 132, 130, 121, 112, 116, 128, 128, 117, 115, 130, 142, 135, 119, 112, 119, 128, 132, 127, 120, 123, 135, 136, 121, 107, 115, 130, 129, 116, 116, 129, 136, 127, 118, 120, 124, 125, 123, 123, 125, 132, 137, 132, 118, 115, 126, 136, 129, 122, 130, 143, 138, 122, 115, 124, 132, 129, 123, 125, 136, 145, 140, 126, 116, 121, 128, 125, 120, 127, 141, 144, 133, 123, 124, 128, 127, 124, 124, 125, 131, 140, 142, 131, 119, 118, 124, 121, 113, 114, 126, 137, 135, 122, 112, 111, 118, 125, 123, 118, 121, 132, 137, 127, 113, 110, 119, 128, 127, 121, 119, 127, 136, 131, 113, 103, 113, 131, 131, 117, 111, 122, 135, 135, 125, 118, 120, 123, 123, 120, 119, 125, 136, 142, 138, 127, 122, 126, 129, 124, 116, 117, 131, 145, 146, 133, 121, 121, 128, 130, 122, 115, 117, 130, 142, 142, 129, 117, 118, 129, 135, 127, 116, 116, 128, 141, 142, 131, 116, 112, 122, 134, 133, 121, 114, 121, 136, 138, 124, 107, 106, 119, 130, 125, 110, 106, 121, 140, 141, 123, 105, 103, 117, 132, 133, 121, 113, 121, 137, 142, 128, 111, 107, 115, 124, 126, 120, 113, 115, 127, 139, 138, 124, 111, 111, 123, 133, 132, 122, 117, 124, 137, 143, 135, 123, 117, 122, 130, 134, 129, 122, 119, 126, 134, 137, 131, 124, 120, 121, 126, 132, 133, 126, 118, 120, 130, 136, 130, 122, 121, 125, 129, 130, 129, 127, 124, 122, 126, 134, 137, 132, 124, 123, 127, 129, 127, 123, 121, 118, 116, 118, 127, 132, 128, 121, 122, 129, 130, 125, 122, 125, 130, 131, 129, 131, 134, 133, 127, 124, 127, 130, 129, 129, 130, 131, 128, 127, 133, 139, 137, 127, 123, 128, 132, 128, 124, 125, 130, 133, 138, 146, 147, 136, 123, 120, 125, 131, 132, 132, 131, 128, 127, 130, 133, 133, 132, 129, 127, 126, 128, 130, 127, 125, 127, 131, 128, 124, 128, 136, 136, 127, 122, 128, 136, 137, 133, 128, 125, 125, 129, 132, 129, 122, 120, 125, 131, 131, 128, 124, 122, 125, 132, 135, 132, 128, 128, 130, 128, 124, 124, 127, 130, 134, 139, 141, 140, 140, 143, 143, 136, 127, 125, 126, 127, 129, 133, 138, 141, 141, 140, 137, 132, 129, 128, 127, 127, 131, 139, 144, 141, 135, 134, 133, 130, 128, 130, 131, 130, 129, 132, 137, 138, 134, 130, 127, 125, 125, 128, 130, 129, 128, 129, 131, 131, 133, 133, 131, 128, 128, 131, 131, 129, 128, 128, 129, 129, 130, 131, 129, 127, 127, 128, 127, 126, 128, 131, 128, 123, 121, 126, 130, 130, 129, 130, 130, 130, 130, 131, 130, 130, 134, 139, 138, 133, 130, 131, 132, 130, 128, 127, 129, 132, 134, 134, 132, 131, 131, 131, 129, 129, 129, 128, 125, 124, 127, 130, 129, 127, 129, 131, 130, 128, 126, 125, 125, 125, 129, 131, 130, 128, 127, 128, 125, 122, 121, 123, 125, 127, 128, 128, 126, 124, 124, 126, 127, 125, 121, 119, 122, 128, 130, 129, 127, 128, 128, 124, 118, 115, 119, 124, 126, 125, 124, 124, 126, 129, 131, 127, 121, 119, 124, 128, 128, 126, 126, 127, 127, 124, 124, 128, 130, 129, 126, 123, 123, 125, 128, 130, 130, 127, 122, 120, 123, 128, 131, 128, 124, 123, 123, 123, 121, 122, 124, 127, 129, 127, 121, 117, 119, 124, 129, 130, 129, 129, 130, 129, 125, 122, 122, 124, 124, 126, 128, 127, 125, 123, 125, 130, 131, 129, 126, 126, 125, 121, 119, 124, 130, 131, 128, 126, 128, 131, 131, 129, 126, 127, 129, 130, 128, 128, 130, 130, 127, 125, 128, 130, 127, 126, 128, 130, 128, 125, 127, 130, 131, 127, 124, 126, 129, 130, 128, 126, 124, 126, 130, 130, 125, 121, 122, 125, 125, 124, 124, 124, 124, 124, 124, 122, 121, 121, 122, 122, 120, 119, 120, 124, 125, 122, 121, 123, 124, 124, 124, 126, 129, 130, 129, 127, 125, 125, 124, 122, 121, 122, 124, 124, 124, 126, 127, 126, 124, 125, 128, 131, 129, 127, 127, 128, 128, 127, 128, 130, 130, 129, 129, 127, 125, 123, 123, 123, 124, 125, 126, 127, 127, 128, 128, 128, 129, 131, 129, 126, 124, 125, 125, 126, 127, 129, 129, 127, 124, 126, 130, 131, 128, 125, 126, 127, 126, 125, 124, 125, 126, 128, 129, 128, 126, 125, 126, 127, 127, 127, 128, 131, 133, 131, 130, 129, 129, 130, 130, 127, 124, 123, 122, 122, 123, 126, 127, 127, 127, 126, 122, 119, 120, 125, 129, 132, 130, 125, 123, 126, 129, 129, 128, 130, 132, 131, 128, 125, 125, 126, 125, 126, 126, 125, 123, 123, 122, 121, 121, 124, 127, 126, 126, 128, 130, 130, 130, 131, 132, 130, 128, 129, 128, 125, 124, 126, 127, 126, 128, 129, 128, 125, 122, 121, 121, 124, 125, 125, 126, 127, 127, 128, 130, 132, 133, 131, 129, 128, 130, 131, 127, 125, 126, 127, 128, 129, 129, 127, 126, 129, 128, 126, 127, 130, 130, 130, 129, 128, 128, 129, 131, 132, 133, 133, 133, 134, 135, 135, 134, 132, 130, 130, 132, 132, 131, 130, 130, 129, 128, 127, 127, 128, 128, 127, 125, 125, 127, 128, 130, 132, 132, 133, 134, 135, 138, 138, 134, 130, 131, 132, 127, 124, 128, 133, 133, 132, 131, 129, 129, 130, 129, 127, 129, 131, 129, 128, 130, 133, 134, 135, 136, 139, 142, 140, 135, 132, 130, 127, 126, 128, 131, 133, 136, 137, 133, 129, 129, 130, 130, 130, 132, 132, 131, 132, 135, 138, 137, 134, 133, 133, 132, 132, 134, 135, 133, 134, 135, 132, 128, 128, 130, 129, 127, 124, 123, 125, 127, 127, 129, 132, 131, 127

};


void setup() {

  pinMode(BUTTON_2, INPUT);

  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  buttonCheck();
  lightCheck(goOn);

}


void buttonCheck(){
  buttonState = digitalRead(BUTTON_2);
  if (buttonState != wasPressed) {
    if (!buttonState) {
      Serial.println("cat 2 is pressed");
      //analogWrite(LED, 1024);
      goOn = true;
    } else {
      Serial.println("released");
      //analogWrite(LED, 0);
      goOn=false;
    }
  }
  wasPressed = buttonState;
}

void lightCheck(boolean goOn){
  if (goOn){
    analogWrite(LED, 1024);
    startPlayback(cat, sizeof(cat));
    delay(500);
  }
  analogWrite(LED,0);
  
}
