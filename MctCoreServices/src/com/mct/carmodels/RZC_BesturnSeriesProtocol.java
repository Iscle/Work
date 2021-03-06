package com.mct.carmodels;

import com.mct.VehicleInterfaceProperties;
import com.mct.VehiclePropertyConstants;

import android.util.SparseIntArray;

public class RZC_BesturnSeriesProtocol
{
	// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//权限定义
	public static final int PROPERITY_PERMISSON_NO				= VehiclePropertyConstants.PROPERITY_PERMISSON_NO;			//NOTIFY ONLY
	public static final int PROPERITY_PERMISSON_GET				= VehiclePropertyConstants.PROPERITY_PERMISSON_GET; 			// GET ONLY
	public static final int PROPERITY_PERMISSON_SET				= VehiclePropertyConstants.PROPERITY_PERMISSON_SET; 			// SET ONLY
	public static final int PROPERITY_PERMISSON_GET_SET 	= VehiclePropertyConstants.PROPERITY_PERMISSON_GET_SET;	// GET_SET

	//CanBox->HU
	public static final int CH_CMD_STEERING_WHEEL_KEY 		= 0x20;
	public static final int CH_CMD_AIR_CONDITIONING_INFO 	= 0x21;
	public static final int CH_CMD_REAR_RADAR_INFO 				= 0x22;
	public static final int CH_CMD_FRONT_RADAR_INFO 			= 0x23;
	public static final int CH_CMD_PANEL_KEY 							= 0x24;
	public static final int CH_CMD_BASE_INFO 							= 0x28;
	public static final int CH_CMD_STEERING_WHEEL_ANGLE 	= 0x30;
	public static final int CH_CMD_PROTOCOL_VERSION_INFO 	= 0x7F;
	
	//HU->CanBox
	public static final int HC_CMD_SWITCH          						= 0x81;
	public static final int HC_CMD_REQ_CONTROL_INFO			= 0x8F;
	
	public static final int SWC_KEY_NONE									= 0x00;//无按键或者按键释放
	public static final int SWC_KEY_VOLUME_UP						= 0x01;//音量加
	public static final int SWC_KEY_VOLUME_DOWN					= 0x02;//音量键
	public static final int SWC_KEY_MENU_UP							= 0x03;//方向键-上
	public static final int SWC_KEY_MENU_DOWN						= 0x04;//方向键-下
	public static final int SWC_KEY_MUTE									= 0x06;//静音
	public static final int SWC_KEY_SRC									= 0x07;//源切换
	public static final int SWC_KEY_PHONE_ACCEPT					= 0x09;//接听
	public static final int SWC_KEY_PHONE_HANGUP					= 0x0A;//挂断
	public static final SparseIntArray SWC_KEY_TO_USER_KEY_TABLE = new SparseIntArray();
	static
	{
		SWC_KEY_TO_USER_KEY_TABLE.put(SWC_KEY_VOLUME_UP, VehiclePropertyConstants.USER_KEY_VOLUME_UP);
		SWC_KEY_TO_USER_KEY_TABLE.put(SWC_KEY_VOLUME_DOWN, VehiclePropertyConstants.USER_KEY_VOLUME_DOWN);
		SWC_KEY_TO_USER_KEY_TABLE.put(SWC_KEY_MENU_UP, VehiclePropertyConstants.USER_KEY_UP);
		SWC_KEY_TO_USER_KEY_TABLE.put(SWC_KEY_MENU_DOWN, VehiclePropertyConstants.USER_KEY_DOWN);
		SWC_KEY_TO_USER_KEY_TABLE.put(SWC_KEY_MUTE, VehiclePropertyConstants.USER_KEY_MUTE);
		SWC_KEY_TO_USER_KEY_TABLE.put(SWC_KEY_SRC, VehiclePropertyConstants.USER_KEY_SOURCE);
		SWC_KEY_TO_USER_KEY_TABLE.put(SWC_KEY_PHONE_ACCEPT, VehiclePropertyConstants.USER_KEY_PHONE_ACCEPT);
		SWC_KEY_TO_USER_KEY_TABLE.put(SWC_KEY_PHONE_HANGUP, VehiclePropertyConstants.USER_KEY_PHONE_HANGUP);
	}
	
	public static final int PANEL_KEY_POWER							= 0x01;
	public static final int PANEL_SCROLL_KEY_VOLUME_UP		= 0x02;
	public static final int PANEL_SCROLL_KEY_VOLUME_DOWN	= 0x03;
	public static final int PANEL_KEY_MUTE								= 0x04;
	public static final int PANEL_KEY_AST									= 0x05;//(高配为BACK)
	public static final int PANEL_KEY_SEEK_UP							= 0x06;//Seek+
	public static final int PANEL_KEY_SEEK_DOWN					= 0x07;//Seek-
	public static final int PANEL_KEY_SEL									= 0x08;//
	public static final int PANEL_SCROLL_KEY_TUNER_UP			= 0x09;//
	public static final int PANEL_SCROLL_KEY_TUNER_DOWN	= 0x0A;//
	public static final int PANEL_KEY_NUM1								= 0x0B;
	public static final int PANEL_KEY_NUM2								= 0x0C;
	public static final int PANEL_KEY_NUM3								= 0x0D;
	public static final int PANEL_KEY_NUM4								= 0x0E;
	public static final int PANEL_KEY_NUM5								= 0x0F;
	public static final int PANEL_KEY_NUM6								= 0x10;
	public static final int PANEL_KEY_F_DOWN							= 0x11;//(高配为PICKUP)
	public static final int PANEL_KEY_F_UP								= 0x12;//(高配为HANGUP)
	public static final int PANEL_KEY_RADIO								= 0x13;
	public static final int PANEL_KEY_USB									= 0x14;//(高配为PHONE)
	public static final int PANEL_KEY_RDM								= 0x15;//(高配为SRC)
	public static final int PANEL_KEY_RPT									= 0x16;//(高配为VOICE)
	public static final int PANEL_KEY_LINK								= 0x17;

	public static final SparseIntArray B50_PANEL_KEY_TO_USER_KEY_TABLE = new SparseIntArray();
	static
	{
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_POWER,VehiclePropertyConstants.USER_KEY_POWER);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_SCROLL_KEY_VOLUME_UP,VehiclePropertyConstants.USER_KEY_VOLUME_UP);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_SCROLL_KEY_VOLUME_DOWN, VehiclePropertyConstants.USER_KEY_VOLUME_DOWN);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_MUTE, VehiclePropertyConstants.USER_KEY_MUTE);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_AST, VehiclePropertyConstants.USER_KEY_AUDIO_SET);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_SEEK_UP, VehiclePropertyConstants.USER_KEY_UP);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_SEEK_DOWN, VehiclePropertyConstants.USER_KEY_DOWN);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_SEL, VehiclePropertyConstants.USER_KEY_OK);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_SCROLL_KEY_TUNER_UP, VehiclePropertyConstants.USER_KEY_RADIO_STEP_UP);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_SCROLL_KEY_TUNER_DOWN, VehiclePropertyConstants.USER_KEY_RADIO_STEP_DOWN);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM1, VehiclePropertyConstants.USER_KEY_NUM1);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM2, VehiclePropertyConstants.USER_KEY_NUM2);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM3, VehiclePropertyConstants.USER_KEY_NUM3);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM4, VehiclePropertyConstants.USER_KEY_NUM4);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM5, VehiclePropertyConstants.USER_KEY_NUM5);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM6, VehiclePropertyConstants.USER_KEY_NUM6);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_F_DOWN, VehiclePropertyConstants.USER_KEY_RADIO_STEP_DOWN);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_F_UP, VehiclePropertyConstants.USER_KEY_RADIO_STEP_UP);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_RADIO, VehiclePropertyConstants.USER_KEY_RADIO);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_USB, VehiclePropertyConstants.USER_KEY_USB);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_RDM, VehiclePropertyConstants.USER_KEY_PLAY_RANDOM);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_RPT, VehiclePropertyConstants.USER_KEY_PLAY_REPEAT);
		B50_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_LINK, VehiclePropertyConstants.USER_KEY_PHONE_LINK);
	}
	
	public static int panelKeyToUserKeyForB50(int panelKey)
	{
		return (B50_PANEL_KEY_TO_USER_KEY_TABLE.indexOfKey(panelKey) >= 0) ? B50_PANEL_KEY_TO_USER_KEY_TABLE.get(panelKey):-1;
	}
	/*
	public static final SparseIntArray B50_H_PANEL_KEY_TO_USER_KEY_TABLE = new SparseIntArray();
	static
	{
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_POWER,VehiclePropertyConstants.USER_KEY_POWER);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_VOLUME_UP,VehiclePropertyConstants.USER_KEY_VOLUME_UP);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_VOLUME_DOWN, VehiclePropertyConstants.USER_KEY_VOLUME_DOWN);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_MUTE, VehiclePropertyConstants.USER_KEY_MUTE);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_AST, VehiclePropertyConstants.USER_KEY_BACK);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_SEEK_UP, VehiclePropertyConstants.USER_KEY_RADIO_STEP_UP);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_SEEK_DOWN, VehiclePropertyConstants.USER_KEY_RADIO_STEP_DOWN);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_TUNER_UP, VehiclePropertyConstants.USER_KEY_UP);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_TUNER_DOWN, VehiclePropertyConstants.USER_KEY_DOWN);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM1, VehiclePropertyConstants.USER_KEY_NUM1);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM2, VehiclePropertyConstants.USER_KEY_NUM2);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM3, VehiclePropertyConstants.USER_KEY_NUM3);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM4, VehiclePropertyConstants.USER_KEY_NUM4);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM5, VehiclePropertyConstants.USER_KEY_NUM5);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_NUM6, VehiclePropertyConstants.USER_KEY_NUM6);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_F_DOWN, VehiclePropertyConstants.USER_KEY_PHONE_ACCEPT);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_F_UP, VehiclePropertyConstants.USER_KEY_PHONE_HANGUP);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_RADIO, VehiclePropertyConstants.USER_KEY_RADIO);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_USB, VehiclePropertyConstants.USER_KEY_BLUETOOTH);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_RDM, VehiclePropertyConstants.USER_KEY_SOURCE);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_RPT, VehiclePropertyConstants.USER_KEY_VOICE);
		B50_H_PANEL_KEY_TO_USER_KEY_TABLE.put(PANEL_KEY_LINK, VehiclePropertyConstants.USER_KEY_PHONE_LINK);
	}
	
	public static int panelKeyToUserKeyForB50H(int panelKey)
	{
		return (B50_H_PANEL_KEY_TO_USER_KEY_TABLE.indexOfKey(panelKey) >= 0) ? B50_H_PANEL_KEY_TO_USER_KEY_TABLE.get(panelKey):-1;
	}
	*/
	
	public static final int AC_LOWEST_TEMP 		= 18;//最低温度
	public static final int AC_HIGHEST_TEMP 	= 26;//最高温度
	
	public static final float EXTERN_LOWEST_TEMP  = -50.0f;
	public static final float EXTERN_HIGHEST_TEMP = 77.5f;
	
	//所有支持的属性集
	public static final int[] VEHICLE_CAN_PROPERITIES = new int[] { 
			VehicleInterfaceProperties.VIM_VEHICLE_MODEL_PROPERTY,
			VehicleInterfaceProperties.VIM_SUPPORTED_CAN_BOX_MODEL_PROPERTY,
			VehicleInterfaceProperties.VIM_SUPPORTED_VEHICLE_MODELS_PROPERTY,
			VehicleInterfaceProperties.VIM_CAN_SW_VERSION_PROPERTY,
			VehicleInterfaceProperties.VIM_CAN_REQ_COMMAND_PROPERTY,
			VehicleInterfaceProperties.VIM_KEY_PROPERTY,
			VehicleInterfaceProperties.VIM_MCU_USER_KEY_PROPERTY,
			
			VehicleInterfaceProperties.VIM_STEERING_WHEEL_POSN_SLIDE_PROPERTY,
			
			VehicleInterfaceProperties.VIM_AIR_CONDITIONING_PROPERTY,
			VehicleInterfaceProperties.VIM_AIR_CONDITIONING_COOL_MODE_PROPERTY,
			VehicleInterfaceProperties.VIM_AIR_CONDITIONING_CYCLE_MODE_PROPERTY,
			VehicleInterfaceProperties.VIM_HVAC_FAN_DIRECTION_PROPERTY,
			VehicleInterfaceProperties.VIM_HVAC_FAN_SPEED_PROPERTY,
			VehicleInterfaceProperties.VIM_INTERIOR_TEMP_PROPERTY,
			VehicleInterfaceProperties.VIM_EXTERIOR_TEMP_PROPERTY,

			VehicleInterfaceProperties.VIM_VEHICLE_FRONT_RADAR_PROPERTY,
			VehicleInterfaceProperties.VIM_VEHICLE_REAR_RADAR_PROPERTY,
			
			VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_DRIVER_PROPERTY,
			VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_PSNGR_PROPERTY,
			VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_REAR_LEFT_PROPERTY,
			VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_REAR_RIGHT_PROPERTY,
			VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_TRUNK_PROPERTY,
			
			VehicleInterfaceProperties.VIM_PARKING_BRAKES_PROPERTY,
			VehicleInterfaceProperties.VIM_SECURITY_ALERT_PROPERTY,
			
	};	
		
	// 属性读写权限表
	public static final SparseIntArray VEHICLE_CAN_PROPERITY_PERMISSION_TABLE = new SparseIntArray();
	static
	{
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_VEHICLE_MODEL_PROPERTY, PROPERITY_PERMISSON_GET_SET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_SUPPORTED_CAN_BOX_MODEL_PROPERTY, PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_SUPPORTED_VEHICLE_MODELS_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_CAN_SW_VERSION_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_CAN_REQ_COMMAND_PROPERTY,PROPERITY_PERMISSON_SET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_KEY_PROPERTY,PROPERITY_PERMISSON_NO);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_MCU_USER_KEY_PROPERTY,PROPERITY_PERMISSON_NO);
		
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_VEHICLE_AMPLIFIER_CONTROL_TYPE,PROPERITY_PERMISSON_NO);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_BALANCE_LVL_PROPERTY,PROPERITY_PERMISSON_GET_SET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_FADE_LVL_PROPERTY,PROPERITY_PERMISSON_GET_SET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_VOLUME_LVL_PROPERTY,PROPERITY_PERMISSON_GET_SET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_BASS_LVL_PROPERTY,PROPERITY_PERMISSON_GET_SET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_TREBLE_LVL_PROPERTY,PROPERITY_PERMISSON_GET_SET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_ALTO_LVL_PROPERTY,PROPERITY_PERMISSON_GET_SET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_SYNC_SPEED_VOLUME_STATUS_PROPERTY,PROPERITY_PERMISSON_GET_SET);
		
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_BATTERY_VOLTAGE_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_ODOMETER_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_ENGINE_SPEED_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_SPEEDO_METER_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_RMNG_FUEL_LVL_PROPERTY,PROPERITY_PERMISSON_GET);
		
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_STEERING_WHEEL_POSN_SLIDE_PROPERTY,PROPERITY_PERMISSON_GET);
		
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_AIR_CONDITIONING_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_AIR_CONDITIONING_COOL_MODE_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_AIR_CONDITIONING_CYCLE_MODE_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_HVAC_FAN_DIRECTION_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_HVAC_FAN_SPEED_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_INTERIOR_TEMP_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_EXTERIOR_TEMP_PROPERTY,PROPERITY_PERMISSON_GET);
		
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_VEHICLE_FRONT_RADAR_PROPERTY,PROPERITY_PERMISSON_GET);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_VEHICLE_REAR_RADAR_PROPERTY,PROPERITY_PERMISSON_GET);
		
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_DRIVER_PROPERTY,PROPERITY_PERMISSON_NO);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_PSNGR_PROPERTY,PROPERITY_PERMISSON_NO);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_REAR_LEFT_PROPERTY,PROPERITY_PERMISSON_NO);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_REAR_RIGHT_PROPERTY,PROPERITY_PERMISSON_NO);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_TRUNK_PROPERTY,PROPERITY_PERMISSON_NO);
	
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_PARKING_BRAKES_PROPERTY,PROPERITY_PERMISSON_NO);
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_SECURITY_ALERT_PROPERTY,PROPERITY_PERMISSON_NO);
	
		VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.put(VehicleInterfaceProperties.VIM_PARKING_ASSIST_SYSTEM_STATUS_PROPERTY,PROPERITY_PERMISSON_GET);
	}	

	// 属性值类型表
	public static final SparseIntArray VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE = new SparseIntArray();
	static
	{
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_VEHICLE_MODEL_PROPERTY, VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_SUPPORTED_CAN_BOX_MODEL_PROPERTY, VehiclePropertyConstants.DATA_TYPE_STRING);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_SUPPORTED_VEHICLE_MODELS_PROPERTY,VehiclePropertyConstants.DATA_TYPE_STRING);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_CAN_SW_VERSION_PROPERTY,VehiclePropertyConstants.DATA_TYPE_STRING);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_CAN_REQ_COMMAND_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_KEY_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_MCU_USER_KEY_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_VEHICLE_AMPLIFIER_CONTROL_TYPE,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_BALANCE_LVL_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_FADE_LVL_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_VOLUME_LVL_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_BASS_LVL_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_TREBLE_LVL_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_ALTO_LVL_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_SYNC_SPEED_VOLUME_STATUS_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_BATTERY_VOLTAGE_PROPERTY,VehiclePropertyConstants.DATA_TYPE_FLOAT);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_ODOMETER_PROPERTY,VehiclePropertyConstants.DATA_TYPE_FLOAT);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_ENGINE_SPEED_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_SPEEDO_METER_PROPERTY,VehiclePropertyConstants.DATA_TYPE_FLOAT);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_RMNG_FUEL_LVL_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_STEERING_WHEEL_POSN_SLIDE_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_AIR_CONDITIONING_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_AIR_CONDITIONING_COOL_MODE_PROPERTY,VehiclePropertyConstants.DATA_TYPE_STRING);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_AIR_CONDITIONING_CYCLE_MODE_PROPERTY,VehiclePropertyConstants.DATA_TYPE_STRING);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_HVAC_FAN_DIRECTION_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_HVAC_FAN_SPEED_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_INTERIOR_TEMP_PROPERTY,VehiclePropertyConstants.DATA_TYPE_STRING);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_EXTERIOR_TEMP_PROPERTY,VehiclePropertyConstants.DATA_TYPE_FLOAT);
		
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_VEHICLE_FRONT_RADAR_PROPERTY,VehiclePropertyConstants.DATA_TYPE_STRING);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_VEHICLE_REAR_RADAR_PROPERTY,VehiclePropertyConstants.DATA_TYPE_STRING);
		
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_DRIVER_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_PSNGR_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_REAR_LEFT_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_REAR_RIGHT_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_DOOR_OPEN_STATUS_TRUNK_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_PARKING_BRAKES_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_SECURITY_ALERT_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
		
		VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.put(VehicleInterfaceProperties.VIM_PARKING_ASSIST_SYSTEM_STATUS_PROPERTY,VehiclePropertyConstants.DATA_TYPE_INTEGER);
	}	
	
	public static int getProperityDataType(int prop)
	{
		return (VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.indexOfKey(prop) >= 0) ? VEHICLE_CAN_PROPERITY_DATA_TYPE_TABLE.get(prop) : -1;
	}

	public static int getProperityPermission(int prop)
	{
		return (VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.indexOfKey(prop) >= 0) ? VEHICLE_CAN_PROPERITY_PERMISSION_TABLE.get(prop) : -1;
	}
	
	public static int swcKeyToUserKey(int swcKey)
	{
		return (SWC_KEY_TO_USER_KEY_TABLE.indexOfKey(swcKey) >= 0) ? SWC_KEY_TO_USER_KEY_TABLE.get(swcKey):-1;
	}
		
}
