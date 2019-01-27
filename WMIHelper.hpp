#ifndef WMIHELPER_HPP
#define WMIHELPER_HPP
#warning this library is deprecated. it's unstable and not being developed anymore
#include <comdef.h>
#include <WbemIdl.h>

#pragma comment(lib, "wbemuuid.lib")

class WMIHelper {
public:
	static VARIANT getWMIValue(bstr_t wqlCommand, LPCWSTR object) {
		VARIANT nullVal = { VT_EMPTY };
		VariantInit(&nullVal);
		IWbemClassObject *pclsObj = NULL;
		ULONG uReturn = 0;
		IEnumWbemClassObject* pEnumerator = NULL;
		IWbemServices *pSvc = NULL;
		IWbemLocator *pLoc = NULL;
		HRESULT hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hres)) { return nullVal; }
		hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
		if (FAILED(hres)) { CoUninitialize(); return nullVal; }
		hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *)&pLoc);
		hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
		if (FAILED(hres)) { pLoc->Release(); CoUninitialize(); return nullVal; }
		hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
		if (FAILED(hres)) { pSvc->Release(); pLoc->Release(); CoUninitialize(); }
		hres = pSvc->ExecQuery(bstr_t("WQL"), wqlCommand, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
		if (FAILED(hres)) { pSvc->Release(); pLoc->Release(); CoUninitialize(); }
		VARIANT returnValue;
		while (pEnumerator) {
			VARIANT vtProp;
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
			if (0 == uReturn) { break; }
			hr = pclsObj->Get(object, 0, &vtProp, 0, 0);
			returnValue = vtProp;
			VariantClear(&vtProp);
		}
		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();
		CoUninitialize();
		return returnValue;

	}
};
#endif