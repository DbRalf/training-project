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
    message.message_counter += 1;


    return true;

}

// get the value from the relevant requesrt
int DRIVE_CMD::get(const int request){

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
        std::cerr << "undefined drive command get request\n";
    }
    return -1000;
}


std::array<std::byte,9> DRIVE_CMD::encode(){

    std::array<std::byte,9> out {}; // the return array
    
    // ------------ convert to byte array ------------
    // format: litlle endian
    out[0] = static_cast<std::byte>(message.throttle_vector      & 0xFF);
    out[1] = static_cast<std::byte>(message.throttle_vector >> 8 & 0xFF);

    out[2] = static_cast<std::byte>(message.steer_vector         & 0xFF);
    out[3] = static_cast<std::byte>(message.steer_vector    >> 8 & 0xFF);

    out[4] = static_cast<std::byte>(message.brake_vector         & 0xFF);
    out[5] = static_cast<std::byte>(message.brake_vector    >> 8 & 0xFF);
    
    out[6] = static_cast<std::byte>(
             ((message.required_engine_state & 1) << 0) |
             ((message.open_rear_ramp        & 1) << 1) |
             ((message.close_rear_ramp       & 1) << 2) |
             ((message.required_horn_state   & 1) << 3) |
             ((message.required_smoke_state  & 1) << 4) |
             ((message.lights_low_beams      & 1) << 5) |
             ((message.lights_high_beams     & 1) << 6) |
             ((message.lights_cat_eyes       & 1) << 7)
            );
    
    out[7] = static_cast<std::byte>(
             ((message.brake_light_allowed   & 1) << 0) |
             ((message.fnr_forward_cmd       & 1) << 1) |
             ((message.fnr_neutral_cmd       & 1) << 2) |
             ((message.fnr_reverse_cmd       & 1) << 3) |
             ((message.engine_on_override    & 1) << 4)
            );   
    
    out[8] = static_cast<std::byte> (message.message_counter     & 0xFF);

    return out;
}


void DRIVE_CMD::decode (const std::array<std::byte,9> &enc_mes){

    // decode little endian
    message.throttle_vector = (std::to_integer<uint16_t>(enc_mes[0])) | (std::to_integer<uint16_t>(enc_mes[1]) << 8);
    message.steer_vector    = (std::to_integer<uint16_t>(enc_mes[2])) | (std::to_integer<uint16_t>(enc_mes[3]) << 8);
    message.brake_vector    = (std::to_integer<uint16_t>(enc_mes[4])) | (std::to_integer<uint16_t>(enc_mes[5]) << 8);

    // decode bit flags
    message.required_engine_state  = std::to_integer<uint16_t>(enc_mes[6] >> 0) & 0x01u;
    message.open_rear_ramp         = std::to_integer<uint16_t>(enc_mes[6] >> 1) & 0x01u;
    message.close_rear_ramp        = std::to_integer<uint16_t>(enc_mes[6] >> 2) & 0x01u;
    message.required_horn_state    = std::to_integer<uint16_t>(enc_mes[6] >> 3) & 0x01u;
    message.required_smoke_state   = std::to_integer<uint16_t>(enc_mes[6] >> 4) & 0x01u;
    message.lights_low_beams       = std::to_integer<uint16_t>(enc_mes[6] >> 5) & 0x01u;
    message.lights_high_beams      = std::to_integer<uint16_t>(enc_mes[6] >> 6) & 0x01u;
    message.lights_cat_eyes        = std::to_integer<uint16_t>(enc_mes[6] >> 7) & 0x01u;

    message.brake_light_allowed    = std::to_integer<uint16_t>(enc_mes[7] >> 0) & 0x01u;
    message.fnr_forward_cmd        = std::to_integer<uint16_t>(enc_mes[7] >> 1) & 0x01u;
    message.fnr_neutral_cmd        = std::to_integer<uint16_t>(enc_mes[7] >> 2) & 0x01u;
    message.fnr_reverse_cmd        = std::to_integer<uint16_t>(enc_mes[7] >> 3) & 0x01u;
    message.engine_on_override     = std::to_integer<uint16_t>(enc_mes[7] >> 4) & 0x01u; 
    // decode byte
    message.message_counter        = std::to_integer<uint8_t>(enc_mes[8]);
}






PLATFORM_STATUS::PLATFORM_STATUS()
{
    message = {};
}


PLATFORM_STATUS::~PLATFORM_STATUS()
{
}


void PLATFORM_STATUS::print(){

    std::cout << "throttle_vector: " << message.throttle_vector << '\n';
    std::cout << "steer_vector: " << message.steer_vector << '\n';
    std::cout << "brake_vector: " << static_cast<int>(message.brake_vector) << '\n';
    std::cout << "required_engine_state: " << message.engine_state << '\n';
    std::cout << "open_rear_ramp: " << message.rear_ramp_state << '\n';
    std::cout << "close_rear_ramp: " << message.horn_state << '\n';
    std::cout << "required_horn_state: " << message.smoke_state << '\n';
    std::cout << "required_smoke_state: " << message.lights_low_beams << '\n';
    std::cout << "lights_low_beams: " << message.lights_high_beams << '\n';
    std::cout << "lights_high_beams: " << message.lights_cat_eyes << '\n';
    std::cout << "lights_cat_eyes: " << message.lights_cat_eyes << '\n';
    std::cout << "brake_light_allowed: " << message.brake_allowance << '\n';
    std::cout << "fnr_forward_cmd: " << message.fnr_forward_state << '\n';
    std::cout << "fnr_neutral_cmd: " << message.fnr_neutral_state << '\n';
    std::cout << "fnr_reverse_cmd: " << message.fnr_reverse_state << '\n';
    std::cout << "engine_on_override: " << message.unmanned_state << '\n';
    std::cout << "estop 1: " << message.estop1_alive << '\n';
    std::cout << "estop 2: " << message.estop2_alive << '\n';
    std::cout << "message_counter: " << static_cast<int>(message.message_counter) << '\n';
}            


void PLATFORM_STATUS::init(){
    
 /* ~ */

}   


int PLATFORM_STATUS::get(const int request){
    
    switch (request)
    {
    case STATUS_THROTTLE_VECTOR: return message.throttle_vector;
    case STATUS_STEER_VECTOR: return message.steer_vector;
    case STATUS_BRAKE_VECTOR: return message.brake_vector;
    case STATUS_ENGINE_STATE: return message.engine_state;
    case STATUS_RAMP_STATE: return message.rear_ramp_state;
    case STATUS_HORN_STATE: return message.horn_state;
    case STATUS_SMOKE_STATE: return message.smoke_state;
    case STATUS_LOW_BEAM: return message.lights_low_beams;
    case STATUS_HIGH_BEAM: return message.lights_high_beams;
    case STATUS_CAT_EYES: return message.lights_cat_eyes;
    case STATUS_BRAKE_ALLOWANCE: return message.brake_allowance;
    case STATUS_FORWARD_STATE: return message.fnr_forward_state;
    case STATUS_NATURAL_STATE: return message.fnr_neutral_state;
    case STATUS_REVERSE_STATE: return message.fnr_reverse_state;
    case STATUS_UNMANNED_STATE: return message.unmanned_state;
    case STATUS_ESTOP1_ALIVE: return message.estop1_alive;
    case STATUS_ESTOP2_ALIVE: return message.estop2_alive;
    case STATUS_MESSAGE_COUNTER: return message.message_counter;
    
    default:
        std::cerr << "undefined status get command \n";

    }
    return -1000;
}

    
bool PLATFORM_STATUS::set(){
    
    return 0;
}    


std::array<std::byte,9> PLATFORM_STATUS::encode(){
    std::array<std::byte,9> out {};


    return out;
}     


void PLATFORM_STATUS::decode(const std::array<std::byte,8> &enc_mes){
    

}