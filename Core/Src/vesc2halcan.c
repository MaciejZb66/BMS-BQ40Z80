#include "vesc2halcan.h"

uint8_t vesc2halcan(CAN_TxHeaderTypeDef* txHeader, uint8_t* txData, size_t txDataSize, const VESC_RawFrame* vescRawFrame)
{
	if (txDataSize < vescRawFrame->can_dlc){
		return VESC2HALCAN_ERR_TXDATA;
	}
	txHeader->ExtId = *(uint32_t*)vescRawFrame & 0x1FFFFFFF; //Identifier
	txHeader->IDE = CAN_ID_EXT;//IdType
	txHeader->RTR = CAN_RTR_DATA; //TxFrameType

	// see FDCAN_data_length_code
	if (vescRawFrame->can_dlc >= 0u && vescRawFrame->can_dlc <= 8u){
		txHeader->DLC = vescRawFrame->can_dlc;
//	else if (vescRawFrame->can_dlc >= 12u && vescRawFrame->can_dlc <= 24u && vescRawFrame->can_dlc % 4u == 0u)
//		txHeader->DLC = 6u + (vescRawFrame->can_dlc / 4u);
//	else if (vescRawFrame->can_dlc == 32u)
//		txHeader->DLC = FDCAN_DLC_BYTES_32;
//	else if (vescRawFrame->can_dlc == 48u)
//		txHeader->DLC = FDCAN_DLC_BYTES_48;
//	else if (vescRawFrame->can_dlc == 64u)
//		txHeader->DLC = FDCAN_DLC_BYTES_64;
	}else{
		return VESC2HALCAN_ERR_DLC;
	}

//	txHeader->ErrorStateIndicator = FDCAN_ESI_ACTIVE;
//	txHeader->BitRateSwitch = FDCAN_BRS_OFF;
//	txHeader->FDFormat = FDCAN_CLASSIC_CAN;
//	txHeader->TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	txHeader->MessageMarker = 0x0;

	memcpy(txData, vescRawFrame->rawData, vescRawFrame->can_dlc);

	return VESC2HALCAN_OK;
}

uint8_t halcan2vesc(VESC_RawFrame* vescRawFrame, const CAN_RxHeaderTypeDef* rxHeader, const uint8_t* rxData)
{
	uint8_t realDlc = 0;
	realDlc = rxHeader->DLC;
//	switch (rxHeader->DLC)
//	{
//		case CAN_DLC_BYTES_0:
//		case CAN_DLC_BYTES_1:
//		case CAN_DLC_BYTES_2:
//		case CAN_DLC_BYTES_3:
//		case CAN_DLC_BYTES_4:
//		case CAN_DLC_BYTES_5:
//		case CAN_DLC_BYTES_6:
//		case CAN_DLC_BYTES_7:
//		case CAN_DLC_BYTES_8:
//			realDlc = (uint8_t)rxHeader->DLC;
//			break;
//		case CAN_DLC_BYTES_12:
//			realDlc = 12;
//			break;
//		case CAN_DLC_BYTES_16:
//			realDlc = 16;
//			break;
//		case CAN_DLC_BYTES_20:
//			realDlc = 20;
//			break;
//		case CAN_DLC_BYTES_24:
//			realDlc = 24;
//			break;
//		case CAN_DLC_BYTES_32:
//			realDlc = 32;
//			break;
//		case CAN_DLC_BYTES_48:
//			realDlc = 48;
//			break;
//		case CAN_DLC_BYTES_64:
//			realDlc = 64;
//			break;
//	}
	
	if (VESC_CAN_DLEN_MAX < realDlc) return VESC2HALCAN_ERR_RXDATA;

	*(uint32_t*)vescRawFrame = rxHeader->ExtId;//Identifier
	vescRawFrame->_reserved = VESC_CAN_EXTID_FLAG;
	vescRawFrame->can_dlc = realDlc;

	memcpy(vescRawFrame->rawData, rxData, realDlc);

	return VESC2HALCAN_OK;
}
