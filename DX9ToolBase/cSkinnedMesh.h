#pragma once
#include "cObject.h"

struct ST_BONE;

class cSkinnedMesh : public cObject
{
    friend class cMeshManager;

private:
    //하나만 생성
    ST_BONE*                    m_pRootFrame;
    DWORD                       m_dwWorkingPaletteSize;
    Matrix4*                    m_pmWorkingPalette;
    LPEFFECT                    m_pEffect;
    ST_SPHERE                   m_stBoundingSphere;

    // 객체마다 생성
    LPANIMCONTROLLER			m_pAnimController;
    Vector3                     m_vPosition;

	bool						isStop;

private:
    cSkinnedMesh();

    void Load(string szFolder, string szFilename);
    LPEFFECT LoadEffect(string szFilename);
    void Update(ST_BONE* pCurrent, Matrix4* pmatParent);
    void Render(ST_BONE* pBone = NULL);
	void SetAnimationIndex(int nIndex);
    void SetupBoneMatrixPtrs(ST_BONE* pBone);
    virtual HRESULT Destroy() override;

public:
    cSkinnedMesh(string szKey, string szFolder, string szFilename);
    ~cSkinnedMesh(void);

    void UpdateAndRender();

    void SetRandomTrackPosition();  // 테스트용
    void SetPosition(Vector3 v)
    {
        m_vPosition = v;
        m_stBoundingSphere.vCenter = v;
    }

    Vector3 GetPosition() { return m_vPosition; }
    ST_SPHERE* GetBoundingSphere()
    {
        return &m_stBoundingSphere;
    }

	HRESULT SetChangeAnim(IN int index);
	HRESULT SetAnimPlay(IN bool PlayState);
	HRESULT SetSliderBarByAnimPosition(IN int Pos);
    HRESULT SetStatePos(IN float Pos);

	HRESULT GetAnimTotalPosition(OUT float* TotalPos);
	HRESULT GetAnimCurPosition(OUT float* CurPos);
	HRESULT GetStateCount(OUT int* Count);
	HRESULT GetStateName(OUT string* name,IN int index);
	HRESULT GetAnimPlay(OUT bool* PlayState);
};
