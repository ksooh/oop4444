//CWall.h


#pragma once
#include "d3dUtility.h"
#include "Csphere.h"

class CWall {

private:

    float               m_x;
    float               m_y;
    float               m_z;
    float               m_width; // ���� ���̴°� ���� ���� ����
    float               m_depth; // ���� ���̴°� ���� ���� ����
    float               m_height;
    int wall_position;

public:
    CWall(void);
    ~CWall(void);

    bool create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color = d3d::WHITE);
    void destroy(void);
    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);
    // ��ģ�� Ȯ���ϰ� (�������� ���� Ȯ���ϱ�) -> gamemanger ���� ���� �ʿ�
    bool hasIntersected(CSphere& ball);

    // �浹 ���� (�ӵ��� ���� �ٲ��ֱ�)
    void hitBy(CSphere& ball);

    void setPosition(float x, float y, float z);


    void set_wallPosition(int numbering) { this->wall_position = numbering; }

    float getHeight(void) const { return M_HEIGHT; }

    void adjustPosition(CSphere& ball);



private:
    void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }

    D3DXMATRIX              m_mLocal;
    D3DMATERIAL9            m_mtrl;
    ID3DXMesh* m_pBoundMesh;
};