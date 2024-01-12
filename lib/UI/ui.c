// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Futuristic_Ebike

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void Particle1_Animation(lv_obj_t * TargetObject, int delay);
void Particle2_Animation(lv_obj_t * TargetObject, int delay);
void Particle3_Animation(lv_obj_t * TargetObject, int delay);
void Fash_Animation(lv_obj_t * TargetObject, int delay);
void Wave1_Animation(lv_obj_t * TargetObject, int delay);
void Wave2_Animation(lv_obj_t * TargetObject, int delay);
void Off_Animation(lv_obj_t * TargetObject, int delay);
void On_Animation(lv_obj_t * TargetObject, int delay);


// SCREEN: ui_Main
void ui_Main_screen_init(void);
void ui_event_Main(lv_event_t * e);
lv_obj_t * ui_Main;
lv_obj_t * ui_BG1;
lv_obj_t * ui_Fill_Capacity_Number_2;
lv_obj_t * ui_Fill_Capacity_Number_1;
lv_obj_t * ui_Label_Fill_Capacity;
lv_obj_t * ui_Unit_Litres;
lv_obj_t * ui_Slider_Extract;
lv_obj_t * ui_Slider_Fill;
lv_obj_t * ui_Group_Battery_Percent;
lv_obj_t * ui_Label_Number1;
lv_obj_t * ui_Label_Number2;
lv_obj_t * ui_Label_Number3;
lv_obj_t * ui_Label_Number4;
lv_obj_t * ui_Label_Number5;
lv_obj_t * ui_Group_Header;
lv_obj_t * ui_Label_Time;
lv_obj_t * ui_LabeL_PM;
lv_obj_t * ui_Label_Temp;
lv_obj_t * ui_Label_Celsius;
lv_obj_t * ui_Label_Oil_Change;
lv_obj_t * ui_Group_Footer;
lv_obj_t * ui_Image_Battery_icon;
lv_obj_t * ui_Label_Battery_Number;
lv_obj_t * ui_Label_Battery_Percent;
lv_obj_t * ui_Button_Group;
lv_obj_t * ui_BTN_Driving;
void ui_event_BTN_BG1(lv_event_t * e);
lv_obj_t * ui_BTN_BG1;
lv_obj_t * ui_ICN_Driving;
lv_obj_t * ui_BTN_Battery;
void ui_event_BTN_BG2(lv_event_t * e);
lv_obj_t * ui_BTN_BG2;
lv_obj_t * ui_ICN_Battery;
lv_obj_t * ui_BTN_Lock;
void ui_event_BTN_BG3(lv_event_t * e);
lv_obj_t * ui_BTN_BG3;
lv_obj_t * ui_ICN_Lock;
lv_obj_t * ui_Group_Driving;
lv_obj_t * ui_Group_Title;
lv_obj_t * ui_Title_BG;
lv_obj_t * ui_Label_Driving_Information;
lv_obj_t * ui_Group_Content;
lv_obj_t * ui_Group_Voltage;
lv_obj_t * ui_LabeL_Battery;
lv_obj_t * ui_Label_ODO_Number;
lv_obj_t * ui_Label_volts;
lv_obj_t * ui_Group_Trip;
lv_obj_t * ui_Label_Oil;
lv_obj_t * ui_Oil_Temp_Number;
lv_obj_t * ui_Label_unit;
lv_obj_t * ui_Group_Max_Speed;
lv_obj_t * ui_Label_Filled;
lv_obj_t * ui_Label_Max_Speed_Number;
lv_obj_t * ui_Label_kmh2;
lv_obj_t * ui_Group_AVG_Speed;
lv_obj_t * ui_Label_AVG_Speed;
lv_obj_t * ui_Label_AVG_Speed_Number;
lv_obj_t * ui_Label_kmh3;
lv_obj_t * ui_Group_ETA;
lv_obj_t * ui_Label_ETA;
lv_obj_t * ui_Label_ETA_Number;
lv_obj_t * ui_Group_Time;
lv_obj_t * ui_Label_Time1;
lv_obj_t * ui_Label_Arrival_Time_Number1;
lv_obj_t * ui_Group_Battery;
lv_obj_t * ui_Group_Title1;
lv_obj_t * ui_Title_BG1;
lv_obj_t * ui_Label_Battery_Information;
lv_obj_t * ui_Group_Content1;
lv_obj_t * ui_Group_Charging;
lv_obj_t * ui_LabeL_Charging;
lv_obj_t * ui_Label_Charging_Number;
lv_obj_t * ui_Label_Percent1;
lv_obj_t * ui_Group_Distance;
lv_obj_t * ui_Label_Distance;
lv_obj_t * ui_Label_Distance_Number;
lv_obj_t * ui_Label_km4;
lv_obj_t * ui_Group_Complete;
lv_obj_t * ui_Label_Complete;
lv_obj_t * ui_Label_Complete_Number;
lv_obj_t * ui_Label_Mins;
lv_obj_t * ui_Group_Battery_Indicator;
lv_obj_t * ui_Particle_Group;
lv_obj_t * ui_Image_Particle1;
lv_obj_t * ui_Wave_Group;
lv_obj_t * ui_Wave1;
lv_obj_t * ui_Image_Particle2;
lv_obj_t * ui_Wave2;
lv_obj_t * ui_Image_Particle3;
lv_obj_t * ui_Image_Battery_BG;
lv_obj_t * ui_Image_Flash;
lv_obj_t * ui_Group_Pin;
lv_obj_t * ui_Group_Title2;
lv_obj_t * ui_Title_BG2;
lv_obj_t * ui_Label_Unlock;
lv_obj_t * ui_Group_Pin1;
void ui_event_Button_Pin1(lv_event_t * e);
lv_obj_t * ui_Button_Pin1;
lv_obj_t * ui_Label_1;
lv_obj_t * ui_Pin_Add1;
void ui_event_Button_Pin2(lv_event_t * e);
lv_obj_t * ui_Button_Pin2;
lv_obj_t * ui_Label_2;
lv_obj_t * ui_Pin_Add2;
void ui_event_Button_Pin3(lv_event_t * e);
lv_obj_t * ui_Button_Pin3;
lv_obj_t * ui_Label_3;
lv_obj_t * ui_Pin_Add3;
void ui_event_Button_Pin4(lv_event_t * e);
lv_obj_t * ui_Button_Pin4;
lv_obj_t * ui_Label_4;
lv_obj_t * ui_Pin_Add4;
void ui_event_Button_Pin5(lv_event_t * e);
lv_obj_t * ui_Button_Pin5;
lv_obj_t * ui_Label_5;
lv_obj_t * ui_Pin_Add5;
void ui_event_Button_Pin6(lv_event_t * e);
lv_obj_t * ui_Button_Pin6;
lv_obj_t * ui_Label_6;
lv_obj_t * ui_Pin_Add6;
void ui_event_Button_Pin7(lv_event_t * e);
lv_obj_t * ui_Button_Pin7;
lv_obj_t * ui_Label_7;
lv_obj_t * ui_Pin_Add7;
void ui_event_Button_Pin8(lv_event_t * e);
lv_obj_t * ui_Button_Pin8;
lv_obj_t * ui_Label_8;
lv_obj_t * ui_Pin_Add8;
void ui_event_Button_Pin9(lv_event_t * e);
lv_obj_t * ui_Button_Pin9;
lv_obj_t * ui_Label_9;
lv_obj_t * ui_Pin_Add9;
void ui_event_Button_PinX(lv_event_t * e);
lv_obj_t * ui_Button_PinX;
lv_obj_t * ui_Pin_Add10;
lv_obj_t * ui_Image_X;
void ui_event_Button_Pin0(lv_event_t * e);
lv_obj_t * ui_Button_Pin0;
lv_obj_t * ui_Label_0;
lv_obj_t * ui_Pin_Add11;
void ui_event_Button_PinX1(lv_event_t * e);
lv_obj_t * ui_Button_PinX1;
lv_obj_t * ui_Pin_Add12;
lv_obj_t * ui_Image_Ok;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_particle_[3] = {&ui_img_particle_1_png, &ui_img_particle_2_png, &ui_img_particle_3_png};
const lv_img_dsc_t * ui_imgset_water_[2] = {&ui_img_water_1_png, &ui_img_water_2_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void Particle1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 19800);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, -120);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Particle2_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 7920);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, -120);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void Particle3_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 3960);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, -120);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void Fash_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 100);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 1200);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Wave1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 7000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, 103);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Wave2_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 5000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, -103);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Off_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 600);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 255, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_start(&PropertyAnimation_0);

}
void On_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_start(&PropertyAnimation_0);
    ui_anim_user_data_t * PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_1_user_data->target = TargetObject;
    PropertyAnimation_1_user_data->val = -1;
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 600);
    lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_1, 100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_1, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_1, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_1);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_Main(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        Particle1_Animation(ui_Image_Particle1, 0);
        Particle2_Animation(ui_Image_Particle2, 0);
        Particle3_Animation(ui_Image_Particle3, 0);
        Wave1_Animation(ui_Wave1, 0);
        Wave2_Animation(ui_Wave2, 0);
    }
}
void ui_event_BTN_BG1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_BTN_BG2, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_BTN_BG3, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_BTN_BG1, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
        On_Animation(ui_Group_Driving, 0);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_Group_Battery, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_Group_Pin, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_Group_Driving, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_BTN_BG1, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_BTN_BG2, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BTN_BG3, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
    }
}
void ui_event_BTN_BG2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_BTN_BG1, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_BTN_BG3, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_BTN_BG2, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
        On_Animation(ui_Group_Battery, 0);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_Group_Driving, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_Group_Pin, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_Group_Battery, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_BTN_BG2, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_BTN_BG1, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BTN_BG3, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
    }
}
void ui_event_BTN_BG3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_BTN_BG1, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_BTN_BG2, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_BTN_BG3, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
        On_Animation(ui_Group_Pin, 0);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_Group_Driving, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_Group_Battery, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_Group_Pin, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_BTN_BG1, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BTN_BG2, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BTN_BG3, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_Button_Pin1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add1, 0);
    }
}
void ui_event_Button_Pin2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add2, 0);
    }
}
void ui_event_Button_Pin3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add3, 0);
    }
}
void ui_event_Button_Pin4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add4, 0);
    }
}
void ui_event_Button_Pin5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add5, 0);
    }
}
void ui_event_Button_Pin6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add6, 0);
    }
}
void ui_event_Button_Pin7(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add7, 0);
    }
}
void ui_event_Button_Pin8(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add8, 0);
    }
}
void ui_event_Button_Pin9(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add9, 0);
    }
}
void ui_event_Button_PinX(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add10, 0);
    }
}
void ui_event_Button_Pin0(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add11, 0);
    }
}
void ui_event_Button_PinX1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        Fash_Animation(ui_Pin_Add12, 0);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_basic_init(dispp);
    lv_disp_set_theme(dispp, theme);
    ui_Main_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Main);
}
