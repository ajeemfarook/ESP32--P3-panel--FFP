#include <Arduino.h>
#include "comms.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Serial communications
///////////////////////////////////////////////////////////////////////////////////////////////////
void messageInit(Message& msg) {
    msg.cmd = Command::draw;
    msg.x = 0;
    msg.y = 0;
    msg.r = 0;
    msg.state = 0;
    msg.color = 'G';     // Default color is Green
    msg.is_valid = false;
    msg.error_msg = "";
}

bool readStringUntil(String& input, char until_c, size_t char_limit) {
    static bool timerRunning = false;
    static unsigned long timerStart = 0;
    static const unsigned long timeout_ms = 1000;

    while (Serial.available()) {
        timerRunning = false;

        char c = Serial.read();
        input += c;

        if (c == until_c) return true;
        if (char_limit && input.length() >= char_limit) return true;

        if (timeout_ms > 0) {
            timerRunning = true;
            timerStart = millis();
        }
    }

    if (timerRunning && (millis() - timerStart > timeout_ms)) {
        timerRunning = false;
        return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Message parsing
///////////////////////////////////////////////////////////////////////////////////////////////////
void parseMessage(const String& input, Message& msg) {
    if (input.length() == 0 || input.charAt(input.length() - 1) != LINE_TERMINATOR) {
        msg.is_valid = false;
        msg.error_msg = "No line terminator found";
        return;
    }

    int verbEnd = input.indexOf(' ');
    String verbStr;
    String argStr;

    if (verbEnd == -1) {
        verbStr = input.substring(0, input.length() - 1);
    } else {
        verbStr = input.substring(0, verbEnd);
        argStr = input.substring(verbEnd + 1);
    }

    msg.is_valid = true;

    if (verbStr.equalsIgnoreCase("draw")) {
        msg.cmd = Command::draw;
        parseDrawArgs(argStr, msg);
    } else if (verbStr.equalsIgnoreCase("fill")) {
        msg.cmd = Command::fill;
        parseFillArgs(argStr, msg);
    } else if (verbStr.equalsIgnoreCase("brightfield")) {
        msg.cmd = Command::brightfield;
        parseBrightfieldArgs(argStr, msg);
    } else if (verbStr.equalsIgnoreCase("darkfield")) {
        msg.cmd = Command::darkfield;
        parseDarkfieldArgs(argStr, msg);
    } else if (verbStr.equalsIgnoreCase("phaseTop")) {
        msg.cmd = Command::phaseTop;
        parsePhaseTopArgs(argStr, msg);
    } else if (verbStr.equalsIgnoreCase("phaseBottom")) {
        msg.cmd = Command::phaseBottom;
        parsePhaseBottomArgs(argStr, msg);
    } else if (verbStr.equalsIgnoreCase("phaseRight")) {
        msg.cmd = Command::phaseRight;
        parsePhaseRightArgs(argStr, msg);
    } else if (verbStr.equalsIgnoreCase("phaseLeft")) {
        msg.cmd = Command::phaseLeft;
        parsePhaseLeftArgs(argStr, msg);
    } else if (verbStr.equalsIgnoreCase("help")) {
        msg.cmd = Command::help;
    } else {
        msg.is_valid = false;
        msg.error_msg = "Unrecognized command: " + verbStr;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Argument parsers with optional color
///////////////////////////////////////////////////////////////////////////////////////////////////

void parseDrawArgs(const String& args, Message& msg) {
    int n = sscanf(args.c_str(), "%d %d %d %c", &msg.x, &msg.y, &msg.state, &msg.color);
    if (n < 3) {
        msg.is_valid = false;
        return;
    }
    if (n < 4) msg.color = 'G'; // default to green
}

void parseFillArgs(const String& args, Message& msg) {
    int n = sscanf(args.c_str(), "%d %c", &msg.state, &msg.color);
    if (n < 1) {
        msg.is_valid = false;
        return;
    }
    if (n < 2) msg.color = 'G'; // default to green
}

void parseBrightfieldArgs(const String& args, Message& msg) {
    int n = sscanf(args.c_str(), "%d %d %d %d %c", &msg.x, &msg.y, &msg.r, &msg.state, &msg.color);
    if (n < 4) msg.is_valid = false;
    if (n < 5) msg.color = 'G';
}

void parseDarkfieldArgs(const String& args, Message& msg) {
    parseBrightfieldArgs(args, msg);
}

void parsePhaseTopArgs(const String& args, Message& msg) {
    parseBrightfieldArgs(args, msg);
}

void parsePhaseBottomArgs(const String& args, Message& msg) {
    parseBrightfieldArgs(args, msg);
}

void parsePhaseRightArgs(const String& args, Message& msg) {
    parseBrightfieldArgs(args, msg);
}

void parsePhaseLeftArgs(const String& args, Message& msg) {
    parseBrightfieldArgs(args, msg);
}
