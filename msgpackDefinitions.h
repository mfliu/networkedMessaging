#pragma once
#ifndef MSGPACK_DEFS_H
#define MSGPACK_DEFS_H
#include <msgpack.hpp>
#include <string>

using namespace std;
using namespace msgpack;

//#define DEFAULT_IP "localhost:10000"
#define MAX_PACKET_LENGTH 8192 // arbitrary 
#define MAX_STRING_LENGTH 128  // also arbitrary

// Experiment Control Messages 1-500 
// Sometimes 0 is poorly parsed as a truncation signal
enum struct MessageTypeID  {
  MODULE_ADD = 1,
  MODULE_SUBSCRIBE = 2,
  TEST_PACKET = 3,
  SESSION_START = 4,
  SESSION_END = 5,
  TRIAL_START = 6,
  TRIAL_END = 7,
  START_RECORDING = 8,
  STOP_RECORDING = 9,
  PAUSE_RECORDING = 10,
  RESUME_RECORDING = 11,
  REMOVE_OBJECT = 12,
  KEYPRESS = 13,
  RESET_WORLD = 14,

// Combined/Complex Object Messages 500-1000
  CST_CREATE = 500,
  CST_DESTRUCT = 501, 
  CST_START = 502,
  CST_STOP = 503,
  CST_SET_VISUAL = 504,
  CST_SET_HAPTIC = 505,
  CST_SET_LAMBDA = 506,
  CST_DATA = 507,
  CUPS_CREATE = 508,
  CUPS_DESTRUCT = 509,
  CUPS_START = 510,
  CUPS_STOP = 511,
  CUPS_DATA = 512, 

// Haptics Messages 1000-2000
  HAPTIC_DATA_STREAM = 1000,
  HAPTICS_SET_ENABLED = 1001,
  HAPTICS_SET_ENABLED_WORLD = 1002,
  HAPTICS_SET_STIFFNESS = 1008,
  HAPTICS_BOUNDING_PLANE = 1009, 
  HAPTICS_CONSTANT_FORCE_FIELD = 1010,
  HAPTICS_VISCOSITY_FIELD = 1011,
  HAPTICS_FREEZE_EFFECT = 1012,
  HAPTICS_REMOVE_WORLD_EFFECT = 1013,

// Graphics Messages are 2000-3000 
  GRAPHICS_SET_ENABLED = 2000,
  GRAPHICS_CHANGE_BG_COLOR = 2001,
  GRAPHICS_PIPE = 2002,
  GRAPHICS_ARROW = 2003,
  GRAPHICS_CHANGE_OBJECT_COLOR = 2004,
  GRAPHICS_MOVING_DOTS = 2014,
  GRAPHICS_SHAPE_BOX = 2046,
  GRAPHICS_SHAPE_SPHERE = 2050,
  GRAPHICS_SHAPE_TORUS = 2051,
};

/**
 * MSG_HEADER is included in all messages that are sent. It contains metadata about the time and
 * type of message
 */
class MSG_HEADER {
  public:
    int msg_num;
    double timestamp;
    int msg_type;
    int reserved;
    MSGPACK_DEFINE_MAP(msg_num, timestamp, msg_type, reserved);
};

class M_MODULE_ADD {
  public:
    MSG_HEADER header;
    string moduleName;
    string ipAddr;
    int port;
    MSGPACK_DEFINE_MAP(header, moduleName, ipAddr, port);
    /*M_MODULE_ADD(string mName, string ip, int p) {
      header.msg_type = static_cast<unsigned int>(MessageTypeID::MODULE_ADD);
      moduleName = mName;
      ipAddr = ip;
      port = p;
    }*/
};

class M_MODULE_SUBSCRIBE {
  public:
    MSG_HEADER header;
    string moduleName;
    int msgType;
    MSGPACK_DEFINE_MAP(header, moduleName, msgType);
    /*M_MODULE_SUBSCRIBE(string iA, int p, int mType) {
      header.msg_type = static_cast<int>(MessageTypeID::MODULE_SUBSCRIBE);
      ipAddr = iA;
      port = p;
      msgType = mType;
    }*/
};

class M_TEST_PACKET {
  public:
    MSG_HEADER header;
    int testData[64];
    MSGPACK_DEFINE_MAP(header, testData);
    /*M_TEST_PACKET(tD) {
      header.msg_type = static_cast<int>(MessageTypeID::TEST_PACKET);
      testData =  tD;
    }*/
};
class M_SESSION_START {
  public:
    MSG_HEADER header;
    MSGPACK_DEFINE_MAP(header);
    /*M_SESSION_START() {
      header.msg_type = static_cast<int>(MessageTypeID::SESSION_START);
    }*/
};

class M_SESSION_END {
  public:
    MSG_HEADER header;
    MSGPACK_DEFINE_MAP(header);
    /*M_SESSION_END() {
      header.msg_type = static_cast<int>(MessageTypeID::SESSION_END);
    }*/
};

class M_TRIAL_START {
  public:
    MSG_HEADER header;
    int trialNum;
    MSGPACK_DEFINE_MAP(header, trialNum);
    /*M_TRIAL_START(int tNum) {
      header.msg_type = static_cast<int>(MessageTypeID::TRIAL_START);
      trialNum = tNum;
    }*/
};

class M_TRIAL_END {
  public:
    MSG_HEADER header;
    int trialNum;
    MSGPACK_DEFINE_MAP(header, trialNum);
    /*M_TRIAL_END(int tNum) {
      header.msg_type = static_cast<int>(MessageTypeID::TRIAL_END);
      trialNum = tNum;
    }*/
};

class M_START_RECORDING {
  public:
    MSG_HEADER header;
    MSGPACK_DEFINE_MAP(header);
    /*M_START_RECORDING() {
      header.msg_type = static_cast<int>(MessageTypeID::START_RECORDING);
    }*/
};

class M_STOP_RECORDING {
  public:
    MSG_HEADER header;
    MSGPACK_DEFINE_MAP(header);
    /*M_STOP_RECORDING() {
      header.msg_type = static_cast<int>(MessageTypeID::STOP_RECORDING);
    }*/
};

class M_PAUSE_RECORDING {
  public:
    MSG_HEADER header;
    MSGPACK_DEFINE_MAP(header);
    /*M_PAUSE_RECORDING() {
      header.msg_type = static_cast<int>(MessageTypeID::PAUSE_RECORDING);
    }*/
};

class M_RESUME_RECORDING {
  public:
    MSG_HEADER header;
    MSGPACK_DEFINE_MAP(header);
    /*M_RESUME_RECORDING() {
      header.msg_type = static_cast<int>(MessageTypeID::RESUME_RECORDING);
    }*/
};

class M_REMOVE_OBJECT {
  public:
    MSG_HEADER header;
    string objectName;
    MSGPACK_DEFINE_MAP(header, objectName);
    /*M_REMOVE_OBJECT(string oName) {
      header.msg_type = static_cast<int>(MessageTypeID::REMOVE_OBJECT);
      objectName = oName;
    }*/
};

class M_KEYPRESS {
  public:
    MSG_HEADER header;
    string keyName;
    MSGPACK_DEFINE_MAP(header, keyName);
    /*M_KEYPRESS(string kName) {
      header.msg_type = static_cast<int>(MessageTypeID::KEYPRESS);
      keyName = kName;
    }*/
};

class M_RESET_WORLD {
  public:
    MSG_HEADER header;
    MSGPACK_DEFINE_MAP(header);
    /*M_RESET_WORLD() {
      header.msg_type = static_cast<int>(MessageTypeID::RESET_WORLD);
    }*/
};

class M_CST_CREATE {
  public:
    MSG_HEADER header;
    string cstName;
    MSGPACK_DEFINE_MAP(header, cstName);
    /*M_CST_CREATE(string cName){
      header.msg_type = static_cast<int>(MessageTypeID::CST_CREATE);
      cstName = cName;
    }*/
};

class M_CST_DESTRUCT {
  public:
    MSG_HEADER header;
    string cstName;
    MSGPACK_DEFINE_MAP(header, cstName);
    /*M_CST_DESTRUCT(string cName) {
      header.msg_type = static_cast<int>(MessageTypeID::CST_DESTRUCT);
      cstName = cName;
    }*/
};

class M_CST_START {
  public:
    MSG_HEADER header;
    string cstName;
    MSGPACK_DEFINE_MAP(header, cstName);
    /*M_CST_START(string cName) {
      header.msg_type = static_cast<int>(MessageTypeID::CST_START);
      cstName = cName;
    }*/
};

class M_CST_STOP {
  public:
    MSG_HEADER header;
    string cstName;
    MSGPACK_DEFINE_MAP(header, cstName);
    /*M_CST_STOP(string cName) {
      header.msg_type = static_cast<int>(MessageTypeID::CST_STOP);
      cstName = cName;
    }*/
};

class M_CST_SET_VISUAL {
  public:
    MSG_HEADER header;
    string cstName;
    int visionEnabled;
    MSGPACK_DEFINE_MAP(header, cstName, visionEnabled);
    /*M_CST_SET_VISUAL(string cName, int vEnabled) {
      header.msg_type = static_cast<int>(MessageTypeID::CST_SET_VISUAL);
      cstName = cName;
      visionEnabled = vEnabled;
    }*/
};

class M_CST_SET_HAPTIC {
  public:
    MSG_HEADER header;
    string cstName;
    int hapticEnabled;
    MSGPACK_DEFINE_MAP(header, cstName, hapticEnabled);
    /*M_CST_SET_HAPTIC(string cName, int hEnabled) {
      header.msg_type = static_cast<int>(MessageTypeID::CST_SET_HAPTIC);
      cstName = cName;
      hapticEnabled = hEnabled;
    }*/
};

class M_CST_SET_LAMBDA {
  public:
    MSG_HEADER header;
    string cstName;
    double lambdaVal;
    MSGPACK_DEFINE_MAP(header, cstName, lambdaVal);
    /*M_CST_SET_LAMBDA(string cName, double lVal) {
      header.msg_type = static_cast<int>(MessageTypeID::CST_SET_LAMBDA);
      cstName = cName;
      lambdaVal = lVal;
    }*/
};

class M_CST_DATA {
  public:
    MSG_HEADER header;
    double cursorX;
    double cursorY;
    double cursorZ;
    MSGPACK_DEFINE_MAP(header, cursorX, cursorY, cursorZ);
    /*M_CST_DATA(double cX, double cY, double cZ) {
      header.msg_type = static_cast<int>(MessageTypeID::CST_DATA);
      cursorX = cX;
      cursorY = cY;
      cursorZ = cZ;
    }*/
};

class M_CUPS_CREATE {
  public:
    MSG_HEADER header;
    string cupsName;
    double escapeAngle;
    double pendulumLength;
    double ballMass;
    double cartMass;
    MSGPACK_DEFINE_MAP(header, cupsName, escapeAngle, pendulumLength, ballMass, cartMass);
    /*M_CUPS_CREATE(string cName, double eAngle, double pLength, double bMass, double cMass) {
      header.msg_type = static_cast<int>(MessageTypeID::CUPS_CREATE);
      cupsName = cName;
      escapeAngle = eAngle;
      pendulumLength = pLength;
      ballMass = bMass;
      cartMass = cMass;
    }*/
};

class M_CUPS_DESTRUCT {
  public:
    MSG_HEADER header;
    string cupsName;
    MSGPACK_DEFINE_MAP(header, cupsName);
    /*M_CUPS_DESTRUCT(string cName) {
      header.msg_type = static_cast<int>(MessageTypeID::CUPS_DESTRUCT);
      cupsName = cName;
    }*/
};

class M_CUPS_START {
  public:
    MSG_HEADER header;
    string cupsName;
    MSGPACK_DEFINE_MAP(header, cupsName);
    /*M_CUPS_START(string cName) {
      header.msg_type = static_cast<int>(MessageTypeID::CUPS_START);
      cupsName = cName;
    }*/
};

class M_CUPS_STOP {
  public:
    MSG_HEADER header;
    string cupsName;
    MSGPACK_DEFINE_MAP(header, cupsName);
    /*M_CUPS_STOP(string cName) {
      header.msg_type = static_cast<int>(MessageTypeID::CUPS_STOP);
      cupsName = cName;
    }*/
};

class M_HAPTIC_DATA_STREAM {
  public:
    MSG_HEADER header;
    double posX;
    double posY;
    double posZ;
    double velX;
    double velY;
    double velZ;
    double forceX;
    double forceY;
    double forceZ;
    string collisions[4];
    MSGPACK_DEFINE_MAP(header, posX, posY, posZ, velX, velY, velZ,\
        forceX, forceY, forceZ, collisions);
    /*M_HAPTIC_DATA_STREAM(double pX, double pY, double pZ, double vX, double vY, double vZ, \
        double fX, double fY, double fZ, string c[4]) {
      header.msg_type = static_cast<int>(MessageTypeID::HAPTIC_DATA_STREAM);
      posX = pX;
      posY = pY;
      posZ = pZ;
      velX = vX;
      velY = vY;
      velZ = vZ;
      forceX = fX;
      forceY = fY;
      forceZ = fZ;
      collisions[0] = c[0];
      collisions[1] = c[1];
      collisions[2] = c[2];
      collisions[3] = c[3];
    }*/
};

class M_HAPTICS_SET_ENABLED {
  public:
    MSG_HEADER header;
    string objectName;
    int enabled;
    MSGPACK_DEFINE_MAP(header, objectName, enabled);
    /*M_HAPTICS_SET_ENABLED(string oName, int e) {
      header.msg_type = static_cast<int>(MessageTypeID::HAPTICS_SET_ENABLED);
      objectName = oName;
      enabled = e;
    }*/
};

class M_HAPTICS_SET_ENABLED_WORLD {
  public:
    MSG_HEADER header;
    string effectName;
    int enabled;
    MSGPACK_DEFINE_MAP(header, effectName, enabled);
    /*M_HAPTICS_SET_ENABLED_WORLD(string eName, int e) {
      header.msg_type = static_cast<int>(MessageTypeID::HAPTICS_SET_ENABLED_WORLD);
      effectName = eName;
      enabled = e;
    }*/
};

class M_HAPTICS_SET_STIFFNESS {
  public:
    MSG_HEADER header;
    string objectName;
    double stiffness;
    MSGPACK_DEFINE_MAP(header, objectName, stiffness);
    /*M_HAPTICS_SET_STIFFNESS(string oName, double s) {
      header.msg_type = static_cast<int>(MessageTypeID::HAPTICS_SET_STIFFNESS);
      objectName = oName;
      stiffness = s;
    }*/
};

class M_HAPTICS_BOUNDING_PLANE {
  public:
    MSG_HEADER header;
    double bWidth;
    double bHeight;
    MSGPACK_DEFINE_MAP(header, bWidth, bHeight);
    /*M_HAPTICS_BOUNDING_PLANE(double bW, double bH) {
      header.msg_type = static_cast<int>(MessageTypeID::HAPTICS_BOUNDING_PLANE);
      bWidth = bW;
      bHeight = bH;
    }*/
};

class M_HAPTICS_CONSTANT_FORCE_FIELD {
  public:
    MSG_HEADER header;
    string effectName;
    double direction;
    double magnitude;
    MSGPACK_DEFINE_MAP(header, effectName, direction, magnitude);
    /*M_HAPTICS_CONSTANT_FORCE_FIELD(string eName, double d, double m) {
      header.msg_type = static_cast<int>(MessageTypeID::HAPTICS_CONSTANT_FORCE_FIELD);
      effectName = eName;
      direction = d;
      magnitude = m;
    }*/
};

class M_HAPTICS_VISCOSITY_FIELD {
  public:
    MSG_HEADER header;
    string effectName;
    double viscosityMatrix[9];
    MSGPACK_DEFINE_MAP(header, effectName, viscosityMatrix);
    /*M_HAPTICS_VISCOSITY_FIELD(string eName, double vM[9]) {
      header.msg_type = static_cast<int>(MessageTypeID::HAPTICS_VISCOSITY_FIELD);
      effectName = eName;
      viscosityMatrix[0] = vM[0];
      viscosityMatrix[1] = vM[1];
      viscosityMatrix[2] = vM[2];
      viscosityMatrix[3] = vM[3];
      viscosityMatrix[4] = vM[4];
      viscosityMatrix[5] = vM[5];
      viscosityMatrix[6] = vM[6];
      viscosityMatrix[7] = vM[7];
      viscosityMatrix[8] = vM[8];
    }*/
};

class M_HAPTICS_FREEZE_EFFECT {
  public:
    MSG_HEADER header;
    string effectName;
    MSGPACK_DEFINE_MAP(header, effectName);
    /*M_HAPTICS_FREEZE_EFFECT(string eName) {
      header.msg_type = static_cast<int>(MessageTypeID::HAPTICS_FREEZE_EFFECT);
      effectName = eName;
    }*/
};

class M_HAPTICS_REMOVE_WORLD_EFFECT {
  public:
    MSG_HEADER header;
    string effectName;
    MSGPACK_DEFINE_MAP(header, effectName);
    /*M_HAPTICS_REMOVE_WORLD_EFFECT(string eName) {
      header.msg_type = static_cast<int>(MessageTypeID::HAPTICS_REMOVE_WORLD_EFFECT);
      effectName = eName;
    }*/
};

class M_GRAPHICS_SET_ENABLED {
  public:
    MSG_HEADER header;
    string objectName;
    int enabled;
    MSGPACK_DEFINE_MAP(header, objectName, enabled);
    /*M_GRAPHICS_SET_ENABLED(string oName, int e) {
      header.msg_type = static_cast<int>(MessageTypeID::GRAPHICS_SET_ENABLED);
      objectName = oName;
      enabled = e;
    }*/
};

class M_GRAPHICS_CHANGE_BG_COLOR {
  public:
    MSG_HEADER header;
    float color[4];
    MSGPACK_DEFINE_MAP(header, color);
    /*M_GRAPHICS_CHANGE_BG_COLOR(float c[4]) {
      header.msg_type = static_cast<int>(MessageTypeID::GRAPHICS_CHANGE_BG_COLOR);
      color[0] = c[0];
      color[1] = c[1];
      color[2] = c[2];
      color[3] = c[3];
    }*/
};

class M_GRAPHICS_PIPE {
  public:
    MSG_HEADER header;
    string objectName;
    double height;
    double innerRadius;
    double outerRadius;
    unsigned int numSides;
    unsigned int numHeightSegments;
    double position[3];
    double rotation[9];
    float color[4];
    MSGPACK_DEFINE_MAP(header, objectName, height, innerRadius, outerRadius, numSides,\
        numHeightSegments, position, rotation, color);
    /*M_GRAPHICS_PIPE(string oName, double h, double iR, double oR, unsigned int nS, \
        unsigned int nHS, double p[3], double r[9], double c[4]) {
      header.msg_type = static_cast<int>(MessageTypeID::GRAPHICS_PIPE);
      objectName = oName;
      height = h;
      innerRadius = iR;
      outerRadius = oR;
      numSides = nS;
      numHeightSegments = nHS;
      position[0] = p[0];
      position[1] = p[1];
      position[2] = p[2];
      rotation[0] = r[0];
      rotation[1] = r[1];
      rotation[2] = r[2];
      rotation[3] = r[3];
      rotation[4] = r[4];
      rotation[5] = r[5];
      rotation[6] = r[6];
      rotation[7] = r[7];
      rotation[8] = r[8];
      color[0] = c[0];
      color[1] = c[1];
      color[2] = c[2];
      color[3] = c[3];
    }*/
};

class M_GRAPHICS_ARROW {
  public:
    MSG_HEADER header;
    string objectName;
    double aLength;
    double shaftRadius;
    double lengthTip;
    double radiusTip;
    int bidirectional;
    unsigned int numSides;
    double direction[3];
    double position[3];
    float color[4];
    MSGPACK_DEFINE_MAP(header, objectName, aLength, shaftRadius, lengthTip, radiusTip,\
        bidirectional, numSides, direction, position, color);
    /*M_GRAPHICS_ARROW(string oName, double aL, double sR, double lT, double rT,\
        int b, unsigned int nS, double d[3], double p[3], float c[4]) {
      header.msg_type = static_cast<int>(MessageTypeID::GRAPHICS_ARROW);
      objectName = oName;
      aLength = aL;
      shaftRadius = sR;
      lengthTip = lT;
      radiusTip = rT;
      bidirectional = b;
      numSides = nS;
      direction[0] = d[0];
      direction[1] = d[1];
      direction[2] = d[2];
      position[0] = p[0];
      position[1] = p[1];
      position[2] = p[2];
      color[0] = c[0];
      color[1] = c[1];
      color[2] = c[2];
      color[3] = c[3];
    }*/
};

class M_GRAPHICS_CHANGE_OBJECT_COLOR {
  public:
    MSG_HEADER header;
    string objectName;
    float color[4];
    MSGPACK_DEFINE_MAP(header, objectName, color);
    /*M_GRAPHICS_CHANGE_OBJECT_COLOR(string oName, float c[4]) {
      header.msg_type = static_cast<int>(MessageTypeID::GRAPHICS_CHANGE_OBJECT_COLOR);
      objectName = oName;
      color[0] = c[0];
      color[1] = c[1];
      color[2] = c[2];
      color[3] = c[3];
    }*/
};

class M_GRAPHICS_MOVING_DOTS {
  public:
    MSG_HEADER header;
    string objectName;
    int numDots;
    double coherence;
    double direction;
    double magnitude;
    MSGPACK_DEFINE_MAP(header, objectName, numDots, coherence, direction, magnitude);
    /*M_GRAPHICS_MOVING_DOTS(string oName, int nDots, double c, double d, double m) {
      header.msg_type = static_cast<int>(MessageTypeID::GRAPHICS_MOVING_DOTS);
      objectName = oName;
      numDots = nDots;
      coherence = c;
      direction = d;
      magnitude = m;
    }*/
};

class M_GRAPHICS_SHAPE_BOX {
  public:
    MSG_HEADER header;
    string objectName;
    double sizeX;
    double sizeY;
    double sizeZ;
    double localPosition[3];
    float color[4];
    MSGPACK_DEFINE_MAP(header, objectName, sizeX, sizeY, localPosition, color);
    /*M_GRAPHICS_SHAPE_BOX(string oName, double sX, double sY, double sZ, double lP[3], float c[4]) {
      header.msg_type = static_cast<int>(MessageTypeID::GRAPHICS_SHAPE_BOX);
      objectName = oName;
      sizeX = sX;
      sizeY = sY;
      sizeZ = sZ;
      localPosition[0] = lP[0];
      localPosition[1] = lP[1];
      localPosition[2] = lP[2];
      color[0] = c[0];
      color[1] = c[1];
      color[2] = c[2];
      color[3] = c[3];
    }*/
};

class M_GRAPHICS_SHAPE_SPHERE {
  public:
    MSG_HEADER header;
    string objectName;
    double radius;
    double localPosition[3];
    float color[4];
    MSGPACK_DEFINE_MAP(header, objectName, radius, localPosition, color);
    /*M_GRAPHICS_SHAPE_SPHERE(string oName, double r, double lP[3], float c[4]) {
      header.msg_type = static_cast<int>(MessageTypeID::GRAPHICS_SHAPE_SPHERE);
      objectName = oName;
      radius = r;
      localPosition[0] = lP[0];
      localPosition[1] = lP[1];
      localPosition[2] = lP[2];
      color[0] = c[0];
      color[1] = c[1];
      color[2] = c[2];
      color[3] = c[3];
    }*/
};

class M_GRAPHICS_SHAPE_TORUS {
  public:
    MSG_HEADER header;
    string objectName;
    double innerRadius;
    double outerRadius;
    double localPosition[3];
    float color[4];
    MSGPACK_DEFINE_MAP(header, objectName, innerRadius, outerRadius, localPosition, color);
    /*M_GRAPHICS_SHAPE_TORUS(string oName, double iR, double oR, double lP[3], float c[4]) {
      header.msg_type = static_cast<int>(MessageTypeID::GRAPHICS_SHAPE_TORUS);
      objectName = oName;
      innerRadius = iR;
      outerRadius = oR;
      localPosition[0] = lP[0];
      localPosition[1] = lP[1];
      localPosition[2] = lP[2];
      color[0] = c[0];
      color[1] = c[1];
      color[2] = c[2];
      color[3] = c[3];
    }*/
};
#endif
