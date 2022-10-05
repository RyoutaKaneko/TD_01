#pragma once
#pragma once
#pragma once

class Vector2 {
public:
	float x;
	float y;

public:
	//�R���X�g���N�^
	Vector2();
	Vector2(float x, float y);

	//�����o�֐�
	float length() const;
	Vector2& normalize();
	float dot(const Vector2& v) const;
	float cross(const Vector2& v) const;
	void DrawCir(Vector2 v, int r, int color);

	//�P�����Z�q�I�[�o�[���[�h
	Vector2 operator+() const;
	Vector2 operator-() const;

	//������Z�q�I�[�o�[���[�h
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
};

// 2�����Z�q�I�[�o�[���[�h
//�������Ȉ���(�����̌^�Ə���)�̃p�^�[���ɑΉ����邽�߁A�ȉ��̗p�ɏ������Ă���
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);