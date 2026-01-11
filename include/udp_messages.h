#ifndef UDP_MESSAGE_H
#define UDP_MESSAGE_H


#include <cstdint>
#include <keyboard_input.h>

/*
core idea for mesasges:
        hold the last message and only send a parital new message if it is different from the last one
        - lowers the bandwidth usage
        - avoids redundant changes
*/


#pragma pack(push, 1)

// DRIVE_CMD, 64 bit, HLC to LLC, Address hightolow :contentReference[oaicite:0]{index=0}
struct DRIVE_CMD_HTL
{
    std::uint16_t throttle_vector;   // U16, 0..500
    std::int16_t  steer_vector;      // S16, -500..500
    std::uint8_t  brake_vector;      // U8, 0..255

    std::uint16_t required_engine_state : 1;   // 0 off, 1 on
    std::uint16_t open_rear_ramp        : 1;   // 0 stop, 1 open
    std::uint16_t close_rear_ramp       : 1;   // 0 stop, 1 close
    std::uint16_t required_horn_state   : 1;   // 0 off, 1 on
    std::uint16_t required_smoke_state  : 1;   // 0 off, 1 on
    std::uint16_t lights_low_beams      : 1;   // 0 off, 1 on
    std::uint16_t lights_high_beams     : 1;   // 0 off, 1 on
    std::uint16_t lights_cat_eyes       : 1;   // 0 off, 1 on
    std::uint16_t brake_light_allowed   : 1;   // 0 off, 1 on
    std::uint16_t fnr_forward_cmd       : 1;   // 0..1
    std::uint16_t fnr_neutral_cmd       : 1;   // 0..1
    std::uint16_t fnr_reverse_cmd       : 1;   // 0..1
    std::uint16_t engine_on_override    : 1;   // 0..1
    std::uint16_t spare                 : 3;   // must be 0

    std::uint8_t  message_counter;            // 0..255
};

static_assert(sizeof(DRIVE_CMD_HTL) == 8, "DRIVE_CMD_HTL must be 8 bytes");

// Page 3: PLATFORM_STATUS_1, 64 bit, LLC to HLC, Address 0x34 :contentReference[oaicite:1]{index=1}
struct PLATFORM1_LTH
{
    std::uint16_t throttle_vector;   // U16, 0..500
    std::int16_t  steer_vector;      // S16, -500..500
    std::uint8_t  brake_vector;      // U8, 0..255

    std::uint16_t engine_state       : 2;   // 0 off, 1 on, 3 error
    std::uint16_t rear_ramp_state    : 2;   // 0 closed, 1 open, 2 mid, 3 error
    std::uint16_t horn_state         : 1;   // 0 off, 1 on
    std::uint16_t smoke_state        : 1;   // 0 off, 1 on
    std::uint16_t lights_low_beams   : 1;   // 0 off, 1 on
    std::uint16_t lights_high_beams  : 1;   // 0 off, 1 on
    std::uint16_t lights_cat_eyes    : 1;   // 0 off, 1 on
    std::uint16_t brake_allowance    : 1;   // 0 off, 1 on
    std::uint16_t fnr_forward_state  : 1;   // 0..1
    std::uint16_t fnr_neutral_state  : 1;   // 0..1
    std::uint16_t fnr_reverse_state  : 1;   // 0..1
    std::uint16_t unmanned_state     : 1;   // 0..1
    std::uint16_t estop1_alive       : 1;   // 0..1
    std::uint16_t estop2_alive       : 1;   // 0..1

    std::uint8_t  message_counter;         // 0..255
};

static_assert(sizeof(PLATFORM1_LTH) == 8, "PLATFORM1_LTH must be 8 bytes");

#pragma pack(pop)


class DRIVE_CMD
{
public:
    DRIVE_CMD(/* args */);
    ~DRIVE_CMD();

    void print();   // done
    void init();    // what are we initializing 
    bool get();     // get message? get struct? - bool for seccussfull execution
    bool set();     // set a new message or a small portion - bool for seccussfull execution
private:
    
    DRIVE_CMD_HTL message {};

};

#endif