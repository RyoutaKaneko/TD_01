#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	uint32_t textureHandle_ = 0;
	WorldTransform worldTransform_[2];
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;
	float scaleX = 1;
	float scaleY = 1;
	float scaleZ = 1;
	Vector4 redNum = { 1,0,0,1 };
	Vector4 blueNum = { 0,0,1,1 };
	Vector3 p1[100];
	Vector3 p2[100];
	Vector3 p3[100];
	Vector3 p4[100];
	float addNum = 0;

	uint32_t scene = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
