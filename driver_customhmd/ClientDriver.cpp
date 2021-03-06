#include "ClientDriver.h"
#include "hidapi.h"


//EVRInitError CClientDriver::Init(IDriverLog * pDriverLog, IClientDriverHost * pDriverHost, const char * pchUserDriverConfigDir, const char * pchDriverInstallDir)
EVRInitError CClientDriver::Init(EClientDriverMode eDriverMode, IDriverLog *pDriverLog, vr::IClientDriverHost *pDriverHost, const char *pchUserDriverConfigDir, const char *pchDriverInstallDir)
{
	if (eDriverMode == EClientDriverMode::ClientDriverMode_Watchdog)
		return VRInitError_Init_NotAvailableToWatchdogApps;
	m_pLog = new CDriverLog(pDriverLog);
	_LOG(__FUNCTION__" Conf: %s  Driver: %s", pchUserDriverConfigDir, pchDriverInstallDir);
	m_pDriverHost = pDriverHost;
	m_UserDriverConfigDir = pchUserDriverConfigDir;
	m_DriverInstallDir = pchDriverInstallDir;
	m_pSettings = m_pDriverHost->GetSettings(IVRSettings_Version);
	return VRInitError_None;
}

void CClientDriver::Cleanup()
{
	_LOG(__FUNCTION__);		
	m_pDriverHost = nullptr;
	m_UserDriverConfigDir.clear();
	m_DriverInstallDir.clear(); 
	delete m_pLog;
}

bool CClientDriver::BIsHmdPresent(const char * pchUserConfigDir)
{		
	//return false;
	auto ret = false;
	hid_init();
	hid_device *handle = hid_open(0x1974, 0x0001, NULL);
	if (handle)
	{
		ret = true;;
		hid_close(handle);
	}
	hid_exit();
	return ret;
}

EVRInitError CClientDriver::SetDisplayId(const char * pchDisplayId)
{
	_LOG(__FUNCTION__" %s", pchDisplayId);
	return VRInitError_None;
}

HiddenAreaMesh_t CClientDriver::GetHiddenAreaMesh(EVREye eEye)
{
	_LOG(__FUNCTION__" Eye: %d", eEye);
	HiddenAreaMesh_t hidden_area_mesh;
	hidden_area_mesh.pVertexData = nullptr;
	hidden_area_mesh.unTriangleCount = 0;
	return hidden_area_mesh;
}

uint32_t CClientDriver::GetMCImage(uint32_t * pImgWidth, uint32_t * pImgHeight, uint32_t * pChannels, void * pDataBuffer, uint32_t unBufferLen)
{
	_LOG(__FUNCTION__);
	return 0;
}
