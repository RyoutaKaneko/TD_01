#include "Matrix4.h"

//コンストラクタ
Matrix4::Matrix4() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = 0;
		}
	}
};
//デストラクタ
Matrix4::~Matrix4() {};

//引数付きの宣言
Matrix4::Matrix4(
	float mat00, float mat01, float mat02, float mat03,
	float mat10, float mat11, float mat12, float mat13,
	float mat20, float mat21, float mat22, float mat23,
	float mat30, float mat31, float mat32, float mat33
) {
	m[0][0] = mat00; m[0][1] = mat01; m[0][2] = mat02; m[0][3] = mat03;
	m[1][0] = mat10; m[1][1] = mat11; m[1][2] = mat12; m[1][3] = mat13;
	m[2][0] = mat20; m[2][1] = mat21; m[2][2] = mat22; m[2][3] = mat23;
	m[3][0] = mat30; m[3][1] = mat31; m[3][2] = mat32; m[3][3] = mat33;
};

//代入演算子オーバーロード
Matrix4& Matrix4::operator*=(const Matrix4& m2) {
	Matrix4 ans;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				ans.m[i][j] += m[i][k] * m2.m[k][j];

			}
		}
	}

	return ans;
}

Matrix4 Matrix4::operator*(const Matrix4& m2) {
	Matrix4 ans;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				ans.m[i][j] += m[i][k] * m2.m[k][j];

			}
		}
	}

	return ans;
}