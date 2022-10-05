#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

GameScene::GameScene() {
	for (int i = 0; i < 100; i++) {
		p1[i] = { 50,-4,-50 + addNum };
		p2[i] = { -50,-4,-50 + addNum };
		p3[i] = { -50 + addNum,-4,50 };
		p4[i] = { -50 + addNum,-4,-50 };
		addNum++;
	}
}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	/*debugCamera_ = new DebugCamera(1280, 720);*/

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();
	worldTransform_[0].Initialize();
	worldTransform_[1].Initialize();
	viewProjection_.Initialize();
	viewProjection_.eye = { 0,25,-15 };
	viewProjection_.UpdateMatrix();
	////デバックカメラの生成
	//debugCamera_ = new DebugCamera(1280, 720);
	//軸方向の表示を有効にする
	/*AxisIndicator::GetInstance()->SetVisible(true);*/
	////軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	//AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	////ライン描画
	//PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {
	//yの仮ベクトル
	Vector3 yTmpVec(0, 1, 0);
	yTmpVec.normalize();
	//正面仮ベクトル
	Vector3 frontTmp = viewProjection_.target - viewProjection_.eye;
	frontTmp.normalize();
	//右ベクトル
	Vector3 rightVec = yTmpVec.cross(frontTmp);
	rightVec.normalize();
	//左ベクトル
	Vector3 leftVec = frontTmp.cross(yTmpVec);
	leftVec.normalize();
	//正面ベクトル
	Vector3 frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();
	//背面ベクトル
	Vector3 behindVec = frontVec * -1;

	Vector3 move(0, 0, 0);

	float kRotSpeed = 0.005f;
	float kSpeed = 2;

	switch (scene) {
	case 0:
		//バイオ
		if (input_->TriggerKey(DIK_Q)) {
			scene = 1;
		}

		//移動
		if (input_->PushKey(DIK_W)) {
			move.x = sin(worldTransform_[0].rotation_.y);
			move.z = cos(worldTransform_[0].rotation_.y);
		}
		if (input_->PushKey(DIK_S)) {
			move.x = sin(worldTransform_[0].rotation_.y) * -1;
			move.z = cos(worldTransform_[0].rotation_.y) * -1;
		}

		worldTransform_[0].translation_ += move;

		//回転
		if (input_->PushKey(DIK_LEFT)) {
			worldTransform_[0].rotation_.y -= kRotSpeed;
		}
		if (input_->PushKey(DIK_RIGHT)) {
			worldTransform_[0].rotation_.y += kRotSpeed;
		}
		break;
	case 1:
		//カメラ
		if (input_->TriggerKey(DIK_Q)) {
			scene = 2;
		}

		if (input_->PushKey(DIK_W)) {
			worldTransform_[0].translation_ += frontVec;
		}
		if (input_->PushKey(DIK_S)) {
			worldTransform_[0].translation_ += behindVec;
		}
		if (input_->PushKey(DIK_A)) {
			worldTransform_[0].translation_ += leftVec;
		}
		if (input_->PushKey(DIK_D)) {
			worldTransform_[0].translation_ += rightVec;
		}

		//回転
		if (input_->PushKey(DIK_I)) {
			viewProjection_.eye.z += 1;
		}
		if (input_->PushKey(DIK_K)) {
			viewProjection_.eye.z -= 1;
		}
		if (input_->PushKey(DIK_J)) {
			viewProjection_.eye.x -= 1;
		}
		if (input_->PushKey(DIK_L)) {
			viewProjection_.eye.x += 1;
		}

		if (input_->PushKey(DIK_LEFT)) {
			viewProjection_.target.x -= 1;
		}
		if (input_->PushKey(DIK_RIGHT)) {
			viewProjection_.target.x += 1;
		}
		viewProjection_.UpdateMatrix();

		break;

	case 2:
		if (input_->TriggerKey(DIK_Q)) {
			scene = 3;
		}

		if (input_->PushKey(DIK_A)) {
			scaleX += 0.05f;
		}
		if (input_->PushKey(DIK_Z)) {
			scaleX -= 0.05f;
		}

		if (input_->PushKey(DIK_W)) {
			scaleY += 0.05f;
		}
		if (input_->PushKey(DIK_S)) {
			scaleY -= 0.05f;
		}

		if (input_->PushKey(DIK_E)) {
			scaleZ += 0.05f;
		}
		if (input_->PushKey(DIK_D)) {
			scaleZ -= 0.05f;
		}
		break;

	case 3:
		if (input_->TriggerKey(DIK_Q)) {
			scene = 0;
		}

		//回転
		if (input_->PushKey(DIK_LEFT)) {
			worldTransform_[0].rotation_.y -= kRotSpeed;
		}
		if (input_->PushKey(DIK_RIGHT)) {
			worldTransform_[0].rotation_.y += kRotSpeed;
		}

		if (input_->PushKey(DIK_DOWN)) {
			worldTransform_[0].rotation_.x -= kRotSpeed;
		}
		if (input_->PushKey(DIK_UP)) {
			worldTransform_[0].rotation_.x += kRotSpeed;
		}

		if (input_->PushKey(DIK_D)) {
			worldTransform_[0].rotation_.z -= kRotSpeed;
		}
		if (input_->PushKey(DIK_A)) {
			worldTransform_[0].rotation_.z += kRotSpeed;
		}
		break;
	}

	//スケーリング
	Matrix4 matScale;
	worldTransform_[0].scale_ = { scaleX,scaleY,scaleZ };

	matScale.m[0][0] = worldTransform_[0].scale_.x;
	matScale.m[1][1] = worldTransform_[0].scale_.y;
	matScale.m[2][2] = worldTransform_[0].scale_.z;
	matScale.m[3][3] = 1;

	//X軸回転
	Matrix4 matRotX;

	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cos(worldTransform_[0].rotation_.x);
	matRotX.m[1][2] = sin(worldTransform_[0].rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform_[0].rotation_.x);
	matRotX.m[2][2] = cos(worldTransform_[0].rotation_.x);
	matRotX.m[3][3] = 1;


	//Y軸回転
	Matrix4 matRotY;

	matRotY.m[0][0] = cos(worldTransform_[0].rotation_.y);
	matRotY.m[1][1] = 1;
	matRotY.m[0][2] = -sin(worldTransform_[0].rotation_.y);
	matRotY.m[2][0] = sin(worldTransform_[0].rotation_.y);
	matRotY.m[2][2] = cos(worldTransform_[0].rotation_.y);
	matRotY.m[3][3] = 1;

	//Z軸回転
	Matrix4 matRotZ;

	matRotZ.m[0][0] = cos(worldTransform_[0].rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform_[0].rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform_[0].rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform_[0].rotation_.z);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	//平行移動
	Matrix4 matTrans = MathUtility::Matrix4Identity();

	matTrans.m[0][0] = 1;
	matTrans.m[1][1] = 1;
	matTrans.m[2][2] = 1;
	matTrans.m[3][0] = worldTransform_[0].translation_.x;
	matTrans.m[3][1] = worldTransform_[0].translation_.y;
	matTrans.m[3][2] = worldTransform_[0].translation_.z;
	matTrans.m[3][3] = 1;

	////単位行列に代入
	//worldTransform_.matWorld_.m[0][0] = 1;
	//worldTransform_.matWorld_.m[1][1] = 1;
	//worldTransform_.matWorld_.m[2][2] = 1;
	//worldTransform_.matWorld_.m[3][3] = 1;

	//掛け算して代入
	worldTransform_[0].matWorld_ = matScale * matRotX * matRotY * matRotZ * matTrans;


	//行列を転送する
	worldTransform_[0].TransferMatrix();

	worldTransform_[1].matWorld_.m[3][0] = 3;
	worldTransform_[1].matWorld_.m[3][2] = 3;

	worldTransform_[1].TransferMatrix();

	debugText_->SetPos(0, 0);
	debugText_->Printf("%d", scene);

	/*debugCamera_->Update();*/
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_[0], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[1], viewProjection_, textureHandle_);

	//for (int i = 0; i < 100; i++) {
	//	PrimitiveDrawer::GetInstance()->DrawLine3d(p1[i], p2[i], redNum);
	//	PrimitiveDrawer::GetInstance()->DrawLine3d(p3[i], p4[i], blueNum);
	//}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}