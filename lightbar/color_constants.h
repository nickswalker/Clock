//Colors are three byte values, RGB. Structs are a C level feature; byte is not a valid type, so we have to use char
struct color {
  char r;
  char g;
  char b;
};
//Shorthand that makes "RGB" the equivalent of "struct color"
typedef struct color RGB;
//Some of the perceptual problems seem to stem from the fact that the Green LED is much brighter than the red or the blue. Red is very dim.

//No indigo but you can spot it in the fade
static RGB RED = {255, 0, 0};
static RGB ORANGE  = {255, 13, 0}; // I know this seems ridiculous, but this is through trial and error
static RGB YELLOW = {255, 53, 0}; //At full red and green, the result is still strongly green. Have to turn down the green
static RGB GREEN = {0, 128, 0};
static RGB BLUE = {0, 0, 255};
static RGB VIOLET = {255, 0, 255}; //Red is too weak, has to be pulled up. Closer to a magenta

static RGB CYAN = {0, 255, 255}; //This works as you would expect because blue and green are pretty close in strength
static RGB MAGENTA = {0, 255, 32}; //Hottish pink

static RGB PINK = {255, 13, 14}; //Hottish pink

static RGB BLACK = {0, 0, 0};
static RGB WHITE = {255, 94, 68}; //Neutral white. This sums up the red-brightness problems.
static RGB COOLWHITE = {255, 255, 255}; //Pretty blue-green. Brightest color that can be displayed

static RGB rainbow[] = {
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  VIOLET
};

//static RGB wake[] = {
  //(RGB){1,0,0}, //Very dim red
  //(RGB){10,1,0}, //Dim orangish
  //(RGB){65,18,0} //Brighter yellow

//};
//static float wakeTimes[] = {
 // 3,
//  10,
//  20
//}
