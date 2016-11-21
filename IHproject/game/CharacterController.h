#pragma once

#include "CapsuleCollider.h"
#include "RigidBody.h"


class Game;
class CCharacterController{
public:
	CCharacterController() {

	}
	~CCharacterController()
	{

	}
	/*!
	* @brief	�������B
	*/
	void Init(float radius, float height, const D3DXVECTOR3& position);
	/*!
	* @brief	���s�B
	*/
	void Execute();
	/*!
	* @brief	���W���擾�B
	*/
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}
	/*!
	* @brief	���W��ݒ�B
	*/
	void SetPosition(const D3DXVECTOR3& pos)
	{
		m_position = pos;
	}
	/*!
	* @brief	�ړ����x��ݒ�B
	*/
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		m_moveSpeed = speed;
	}
	/*!
	* @brief	�ړ����x���擾�B
	*/
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/*!
	* @brief	�W�����v������B
	*/
	void Jump()
	{
		m_isJump = true;
		m_isOnGround = false;
	}
	/*!
	* @brief	�W�����v��������
	*/
	bool IsJump() const
	{
		return m_isJump;
	}
	/*!
	* @brief	�R���C�_�[���擾�B
	*/
	CCapsuleCollider* GetCollider()
	{
		return &m_collider;
	}
	/*!
	* @brief	�d�͂��擾�B
	*/
	void SetGravity(float gravity)
	{
		m_gravity = gravity;
	}

	bool GetOnGround()
	{
		return m_isOnGround;
	}
	/*!
	* @brief	���̂𕨗��G���W������폜�B�B
	*/
	void RemoveRigidBoby();
private:
	D3DXVECTOR3 		m_position = Vec3Zero;	//���W�B
	D3DXVECTOR3 		m_moveSpeed = Vec3Zero;	//�ړ����x�B 
	bool 				m_isJump = false;				//�W�����v���H
	bool				m_isOnGround = true;			//�n�ʂ̏�ɂ���H
	CCapsuleCollider	m_collider;						//�R���C�_�[�B
	float				m_radius = 0.0f;
	float				m_height = 0.0f;
	RigidBody			m_rigidBody;					//���́B
	float				m_gravity = -9.8f;				//�d�́B

	
};
