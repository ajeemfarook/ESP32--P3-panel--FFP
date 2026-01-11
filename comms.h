#ifndef COMMS_H
#define COMMS_H

#include <Arduino.h>   //  REQUIRED

// The maximum number of characters that can be read from Serial.
const size_t CHAR_LIMIT = 30; // Increased slightly for color input

// The line terminator character for Serial input.
const char LINE_TERMINATOR = '\n';

// The set of possible commands that can be sent to the LED matrix.
enum class Command {
    draw,
    fill,
    brightfield,
    darkfield,
    phaseTop,
    phaseBottom,
    phaseRight,
    phaseLeft,
    help
};

// Message data after parsing the serial input.
// Each LED matrix command uses a non-exclusive subset of the fields.
struct Message {
    Command cmd;
    int x;        // X-coordinate (0-100 for scaling)
    int y;        // Y-coordinate (0-100 for scaling)
    int r;        // radius
    int state;    // percentage or brightness
    char color;   // 'R', 'G', 'B'
    bool is_valid;
    String error_msg;
};

// Initialize a Message struct with default values.
void messageInit(Message& msg);

// Serial input
bool readStringUntil(String& input, char until_c, size_t char_limit);

// Message parsing
void parseMessage(const String& input, Message& msg);

// Argument parsers
void parseDrawArgs(const String& args, Message& msg);
void parseFillArgs(const String& args, Message& msg);
void parseBrightfieldArgs(const String& args, Message& msg);
void parseDarkfieldArgs(const String& args, Message& msg);
void parsePhaseTopArgs(const String& args, Message& msg);
void parsePhaseBottomArgs(const String& args, Message& msg);
void parsePhaseRightArgs(const String& args, Message& msg);
void parsePhaseLeftArgs(const String& args, Message& msg);

#endif // COMMS_H
