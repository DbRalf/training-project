#include "udp_messages.h"

#include <iostream>


DRIVE_CMD::DRIVE_CMD()
{
    message = {};
}


DRIVE_CMD::~DRIVE_CMD()
{
}

// you know nothing john snow
void DRIVE_CMD::init()
{
    message = {};
}

// print the entire message struct
void DRIVE_CMD::print()
{
    std::cout << "throttle_vector: " << message.throttle_vector << '\n';
    std::cout << "steer_vector: " << message.steer_vector << '\n';
    std::cout << "brake_vector: " << static_cast<int>(message.brake_vector) << '\n';
    std::cout << "required_engine_state: " << message.required_engine_state << '\n';
    std::cout << "open_rear_ramp: " << message.open_rear_ramp << '\n';
    std::cout << "close_rear_ramp: " << message.close_rear_ramp << '\n';
    std::cout << "required_horn_state: " << message.required_horn_state << '\n';
    std::cout << "required_smoke_state: " << message.required_smoke_state << '\n';
    std::cout << "lights_low_beams: " << message.lights_low_beams << '\n';
    std::cout << "lights_high_beams: " << message.lights_high_beams << '\n';
    std::cout << "lights_cat_eyes: " << message.lights_cat_eyes << '\n';
    std::cout << "brake_light_allowed: " << message.brake_light_allowed << '\n';
    std::cout << "fnr_forward_cmd: " << message.fnr_forward_cmd << '\n';
    std::cout << "fnr_neutral_cmd: " << message.fnr_neutral_cmd << '\n';
    std::cout << "fnr_reverse_cmd: " << message.fnr_reverse_cmd << '\n';
    std::cout << "engine_on_override: " << message.engine_on_override << '\n';
    std::cout << "spare: " << message.spare << '\n';
    std::cout << "message_counter: " << static_cast<int>(message.message_counter) << '\n';
}

// set a sew value in the struct based on keyboard input
bool DRIVE_CMD::set(){

    keyboard_input ter1;

    char key = ter1.get_input();
    switch (key)
    {
    case 'w':
        message.throttle_vector = 500;
        message.brake_vector = 0;
        break;
    case 's':
        message.brake_vector = 255;
        message.throttle_vector = 0;
        break;
    case 'd':
        message.steer_vector = 500;
        break;
    case 'a':
        message.steer_vector = -500;
        break;

    case '1':
        message.lights_low_beams = !message.lights_low_beams;
        break;
    case '2':
        message.lights_high_beams = !message.lights_high_beams;
        break;
    case '3':
        message.lights_cat_eyes = !message.lights_cat_eyes;
        break;
    case '4':
        message.required_horn_state = !message.required_horn_state;
        break;
    case '5':
        message.required_smoke_state = !message.required_smoke_state;
        break;
    case 'o':
        message.open_rear_ramp = !message.open_rear_ramp;
        break;

    case 'c':
        message.close_rear_ramp = !message.close_rear_ramp;
        break;
    case 'f':
        message.fnr_forward_cmd = 1;
        message.fnr_neutral_cmd = 0;
        message.fnr_reverse_cmd = 0;
        break;
    case 'n':
        message.fnr_forward_cmd = 0;
        message.fnr_neutral_cmd = 1;
        message.fnr_reverse_cmd = 0;
        break;
    case 'r':
        message.fnr_forward_cmd = 0;
        message.fnr_neutral_cmd = 0;
        message.fnr_reverse_cmd = 1;
        break;
    case 'u':
        message.engine_on_override = !message.engine_on_override;
        break;
    case '0':
        message.required_engine_state = !message.required_engine_state;
    case '6':
        message.brake_light_allowed = !message.brake_light_allowed;
        break;
    case '\e':
        return false;
    }


    return true;

}

// get the value from the relevant requesrt
int DRIVE_CMD::get(int request){

    switch (request)
    {
    case THROTTLE_VECTOR: return message.throttle_vector;
    case STEER_VECTOR: return message.steer_vector;
    case BRAKE_VECTOR: return message.brake_vector;
    case REQ_ENGINE_STATE: return message.required_engine_state;
    case OP_RAMP: return message.open_rear_ramp;
    case CL_RAMP: return message.close_rear_ramp;
    case HORN_STATE: return message.required_horn_state;
    case SMOKE_STATE: return message.required_smoke_state;
    case LOW_BEAM: return message.lights_low_beams;
    case HIGH_BEAM: return message.lights_high_beams;
    case CAT_EYES: return message.lights_cat_eyes;
    case FORWARD_CMD: return message.fnr_forward_cmd;
    case NATURAL_CMD: return message.fnr_neutral_cmd;
    case REVERSE_CMD: return message.fnr_reverse_cmd;
    case ON_OVERRIDE: return message.engine_on_override;

    default:
        std::cerr << "unknown drive command get request\n";
    }
    return -1;
}

