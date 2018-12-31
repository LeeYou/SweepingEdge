//�û��ؼ�/Ƥ��/����/��ֵ�㷨ע����
class SUserObjectDefaultRegister : public TObjRefImpl<ISystemObjectRegister>
{
public:
	void RegisterWindows(SObjectFactoryMgr *objFactory);
	//void RegisterSkins(SObjectFactoryMgr *objFactory);
	//void RegisterLayouts(SObjectFactoryMgr *objFactory);
	//void RegisterInterpolator(SObjectFactoryMgr *objFactory);
};
//Soui ������
class CSouiLoader
{
	SApplication *theApp;
	SComMgr *pComMgr;
public:
	//ͨ��������һ��ISystemObjectRegister������ע���û��ؼ������������SApplication�Ĳ���һ��
	CSouiLoader(HINSTANCE hInst,ISystemObjectRegister &pUserObjRegister=SUserObjectDefaultRegister(), LPCTSTR pszHostClassName = _T("SOUIHOST")) 
		:theApp(NULL),pComMgr(NULL)
	{		
		pComMgr = new SComMgr;
		CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
		CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
		BOOL bLoaded = pComMgr->CreateRender_GDI((IObjRef**)&pRenderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [render] failed!"));
		bLoaded = pComMgr->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("imgdecoder"));
		pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
		theApp = new SApplication(pRenderFactory, hInst, pszHostClassName);

		

		//ע���û��Զ���Ķ���
		pUserObjRegister.RegisterLayouts(theApp);
		pUserObjRegister.RegisterSkins(theApp);
		pUserObjRegister.RegisterWindows(theApp);
		pUserObjRegister.RegisterInterpolator(theApp);		
	}
	~CSouiLoader()
	{
		if (theApp)
			delete theApp;
		if (pComMgr)
			delete pComMgr;
	}
	SApplication *GetApp()
	{
		SASSERT(theApp);
		return theApp;
	}
	SComMgr *GetComMgr()
	{
		SASSERT(pComMgr);
		return pComMgr;
	}
};
//��ʹ����Դ����·��
void InitDir(TCHAR *Path=NULL);

void InitSystemRes(SApplication *theApp, SComMgr *pComMgr);

void InitUserRes(SApplication * theApp, SComMgr *pComMgr);

template<class T>
int Run(SApplication *theApp)
{
	T dlgMain;
	dlgMain.Create(GetActiveWindow(),WS_POPUPWINDOW);
	dlgMain.SendMessage(WM_INITDIALOG);
	dlgMain.CenterWindow(dlgMain.m_hWnd);
	dlgMain.ShowWindow(SW_SHOWNORMAL);
	return theApp->Run(dlgMain.m_hWnd);
}

