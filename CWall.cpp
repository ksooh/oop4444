#include "CWall.h"

CWall::CWall(void)
{
    D3DXMatrixIdentity(&m_mLocal);
    ZeroMemory(&m_mtrl, sizeof(m_mtrl));
    m_width = 0;
    m_depth = 0;
    m_pBoundMesh = NULL;
}
CWall::~CWall(void)
{

}

bool CWall::create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color)
{
    if (NULL == pDevice)
        return false;

    m_mtrl.Ambient = color;
    m_mtrl.Diffuse = color;
    m_mtrl.Specular = color;
    m_mtrl.Emissive = d3d::BLACK;
    m_mtrl.Power = 5.0f;

    m_width = iwidth;
    m_depth = idepth;

    if (FAILED(D3DXCreateBox(pDevice, iwidth, iheight, idepth, &m_pBoundMesh, NULL)))
        return false;
    return true;
}


void CWall::destroy(void)
{
    if (m_pBoundMesh != NULL) {
        m_pBoundMesh->Release();
        m_pBoundMesh = NULL;
    }
}



void CWall::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
{
    if (NULL == pDevice)
        return;
    pDevice->SetTransform(D3DTS_WORLD, &mWorld);
    pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
    pDevice->SetMaterial(&m_mtrl);
    m_pBoundMesh->DrawSubset(0);
}



// ��ģ�� Ȯ���ϰ�
bool CWall::hasIntersected(CSphere& ball)
{
    if (this->wall_position == 0)
    {
        if (ball.getCenter().z + ball.getRadius() > this->m_z - (this->m_depth / 2))
        {
            return true;
        }
    }
    else if (this->wall_position == 2)
    {
        if (ball.getCenter().x + ball.getRadius() > this->m_x - (this->m_width / 2))
        {
            return true;
        }
    }
    else if (this->wall_position == 3)
    {
        if (ball.getCenter().x - ball.getRadius() < this->m_x + (this->m_width / 2))
        {
            return true;
        }
    }
    return false;
}


// �浹 ���� (�ӵ��� ���� �ٲ��ֱ�)
void CWall::hitBy(CSphere& ball)
{

    if (this->hasIntersected(ball))
    {
        this->adjustPosition(ball);
        if (this->wall_position == 0) // ����
        {
            ball.setPower(ball.getVelocity_X(), -ball.getVelocity_Z());
        }
        else if (this->wall_position == 1) //�Ʒ�
        {
            return;
        }
        else if (this->wall_position == 2) //������
        {
            ball.setPower(-ball.getVelocity_X(), ball.getVelocity_Z());
        }
        else
        {
            ball.setPower(-ball.getVelocity_X(), ball.getVelocity_Z());
        }
    }
}

void CWall::setPosition(float x, float y, float z)
{
    D3DXMATRIX m;
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;

    D3DXMatrixTranslation(&m, x, y, z);
    setLocalTransform(m);
}


void CWall::adjustPosition(CSphere& ball) {
    ball.setCenter((ball.getCenter().x + ball.getPreCenter_x()) / 2, ball.getCenter().y, (ball.getCenter().z + ball.getPreCenter_z()) / 2);
    if (this->hasIntersected(ball))
    {
        ball.setCenter(ball.getPreCenter_x(), ball.getCenter().y, ball.getPreCenter_z());
    }
}