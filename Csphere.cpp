#include "CSphere.h"

CSphere::CSphere(void)
{
    D3DXMatrixIdentity(&m_mLocal);
    ZeroMemory(&m_mtrl, sizeof(m_mtrl));
    m_radius = 0;
    m_velocity_x = 0;
    m_velocity_z = 0;
    m_pSphereMesh = NULL;

    chflag = 0;
}

CSphere::~CSphere(void) {}

bool CSphere::create(IDirect3DDevice9* pDevice, D3DXCOLOR color)
{
    if (NULL == pDevice)
        return false;

    m_mtrl.Ambient = color;
    m_mtrl.Diffuse = color;
    m_mtrl.Specular = color;
    m_mtrl.Emissive = d3d::BLACK;
    m_mtrl.Power = 5.0f;

    if (FAILED(D3DXCreateSphere(pDevice, getRadius(), 50, 50, &m_pSphereMesh, NULL)))
        return false;
    return true;
}

void CSphere::destroy(void)
{
    if (m_pSphereMesh != NULL) {
        m_pSphereMesh->Release();
        m_pSphereMesh = NULL;
        this->ball_exist = false;
    }
}

void CSphere::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
{
    if (NULL == pDevice)
        return;
    pDevice->SetTransform(D3DTS_WORLD, &mWorld);
    pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
    pDevice->SetMaterial(&m_mtrl);
    m_pSphereMesh->DrawSubset(0);
}

bool CSphere::hasIntersected(CSphere& ball)
{
    D3DXVECTOR3 position_this = this->getCenter();
    D3DXVECTOR3 position_other = ball.getCenter();
    double xDistance = abs((position_this.x - position_other.x) * (position_this.x - position_other.x));
    double zDistance = abs((position_this.z - position_other.z) * (position_this.z - position_other.z));
    double totalDistance = sqrt(xDistance + zDistance);

    if (totalDistance < (this->getRadius() + ball.getRadius()))
    {
        return true;
    }
    return false;
}

bool CSphere::colorcheck(CSphere& ball)
{
    if (this->hasIntersected(ball))
    {
        if (this->getColor() == ball.getColor())
            return true;
    }
    return false;
}



void CSphere::ballUpdate(float timeDiff)
{
    const float TIME_SCALE = 3.3;
    D3DXVECTOR3 cord = this->getCenter();
    double vx = abs(this->getVelocity_X());
    double vz = abs(this->getVelocity_Z());
    this->pre_center_x = cord.x;
    this->pre_center_z = cord.z;

    if (vx > 0.01 || vz > 0.01)
    {
        float tX = cord.x + TIME_SCALE * timeDiff * m_velocity_x;
        float tZ = cord.z + TIME_SCALE * timeDiff * m_velocity_z;
        this->setCenter(tX, cord.y, tZ);
    }
    else { this->setPower(0, 0); }
}

double CSphere::getVelocity_X()
{
    return this->m_velocity_x;
}

double CSphere::getVelocity_Z()
{
    return this->m_velocity_z;
}



void CSphere::setPower(double vx, double vz)
{
    this->m_velocity_x = vx;
    this->m_velocity_z = vz;
}

void CSphere::setCenter(float x, float y, float z)
{
    D3DXMATRIX m;
    center_x = x;   center_y = y;   center_z = z;
    D3DXMatrixTranslation(&m, x, y, z);
    setLocalTransform(m);
}

bool CSphere::getExist()
{
    return this->ball_exist;
}

float CSphere::getRadius(void)  const
{
    return (float)(M_RADIUS);
}

const D3DXMATRIX& CSphere::getLocalTransform(void) const
{
    return m_mLocal;
}

void CSphere::setLocalTransform(const D3DXMATRIX& mLocal)
{
    m_mLocal = mLocal;
}


D3DXVECTOR3 CSphere::getCenter(void) const
{
    D3DXVECTOR3 org(center_x, center_y, center_z);
    return org;
}

void CSphere::setColor(const D3DXCOLOR ball_color)
{
    if (ball_color == d3d::YELLOW)
    {
        this->ball_color = 1;
        this->m_mtrl.Ambient = ball_color;
        this->m_mtrl.Diffuse = ball_color;
        this->m_mtrl.Specular = ball_color;
    }
    else if (ball_color == d3d::RED)
    {
        this->ball_color = 2;
        this->m_mtrl.Ambient = ball_color;
        this->m_mtrl.Diffuse = ball_color;
        this->m_mtrl.Specular = ball_color;
    }
    else if (ball_color == d3d::BLUE)
    {
        this->ball_color = 3;
        this->m_mtrl.Ambient = ball_color;
        this->m_mtrl.Diffuse = ball_color;
        this->m_mtrl.Specular = ball_color;
    }
    else if (ball_color == d3d::GREEN)
    {
        this->ball_color = 4; //Green
        this->m_mtrl.Ambient = ball_color;
        this->m_mtrl.Diffuse = ball_color;
        this->m_mtrl.Specular = ball_color;
    }
    else //magenta -> 0
    {
        this->ball_color = 0;
        this->m_mtrl.Ambient = ball_color;
        this->m_mtrl.Diffuse = ball_color;
        this->m_mtrl.Specular = ball_color;
    }
}

void CSphere::revColor(int color)
{
    if (color == 1)
    {
        this->ball_color = 1;
        this->m_mtrl.Ambient = d3d::YELLOW;
        this->m_mtrl.Diffuse = d3d::YELLOW;
        this->m_mtrl.Specular = d3d::YELLOW;
    }
    else if (color == 2)
    {
        this->ball_color = 2;
        this->m_mtrl.Ambient = d3d::RED;
        this->m_mtrl.Diffuse = d3d::RED;
        this->m_mtrl.Specular = d3d::RED;
    }
    else if (color == 3)
    {
        this->ball_color = 3;
        this->m_mtrl.Ambient = d3d::BLUE;
        this->m_mtrl.Diffuse = d3d::BLUE;
        this->m_mtrl.Specular = d3d::BLUE;
    }
    else if (color == 4)
    {
        this->ball_color = 4; //Green
        this->m_mtrl.Ambient = d3d::GREEN;
        this->m_mtrl.Diffuse = d3d::GREEN;
        this->m_mtrl.Specular = d3d::GREEN;
    }
    else
    {
        this->ball_color = 0;
        this->m_mtrl.Ambient = d3d::MAGENTA;
        this->m_mtrl.Diffuse = d3d::MAGENTA;
        this->m_mtrl.Specular = d3d::MAGENTA;
    }
}

int CSphere::getColor()
{
    return this->ball_color;
}

double CSphere::getPreCenter_x() const
{
    return this->pre_center_x;
}

double CSphere::getPreCenter_z() const
{
    return this->pre_center_z;
}


void CSphere::setExist(bool a)
{
    this->ball_exist = a;
}

int CSphere::getChflag() {
    return chflag;
}

void CSphere::setChflag(int val) {
    chflag = val;
}

float CSphere::getDistance(CSphere& ball)
{
    float ax, az, bx, bz, temp, distance;

    ax = this->getCenter().x;
    az = this->getCenter().z;
    bx = ball.getCenter().x;
    bz = ball.getCenter().z;

    temp = (ax - bx) * (ax - bx) + (az - bz) * (az - bz);
    distance = sqrt(temp);

    return distance;
}