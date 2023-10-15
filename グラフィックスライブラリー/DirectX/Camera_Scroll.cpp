//ゲームエンジンに実装する	Cameraのための実験コード

//scroll

//Note: カメラ と 背景 画像 は 逆 方向 に 動く、 つまり カメラ 
//が 左 に 動け ば 背景 は 右 方向 に 流れ、
//カメラ が 右 方向 に 動け ば 背景 は 左 方向 に 流れる、

#define PICTURE_WIDTH　1600				// 背景幅
#define VIEW_WIDTH  500
#define CAMERA_VEL	10.0f				// カメラ速さ

float fCamera_x; //カメラが映す中心座標
float fBack_x; //背景画像の左端のx座標


int InitBack( void )							// 最初に１回だけ呼ばれる
{
	fCamera_x = VIEW_WIDTH / 2.0f;				// カメラの初期位置
	fBack_x = VIEW_WIDTH / 2.0f - fCamera_x;	// 背景の初期位置 " - fCamera_ x”

	return 0;
}


int MoveBack( void )							// 毎フレーム呼ばれる
{
	// 左キーが押されていれば左へ
	if ( GetAsyncKeyState( VK_LEFT ) )
	{
		fCamera_x -= CAMERA_VEL;
		if ( fCamera_x < VIEW_WIDTH / 2.0f ) 
		{
			//カメラが左はじに行くまで
			fCamera_x = VIEW_WIDTH / 2.0f;
		}
	}
	// 右キーが押されていれば右へ
	if ( GetAsyncKeyState( VK_RIGHT ) )
	{
		fCamera_x += CAMERA_VEL;
		if ( fCamera_x > ( float )( PICTURE_WIDTH - VIEW_WIDTH / 2.0f ) )
		{
			//カメラが右はじに行くまで
			fCamera_x = ( float )( PICTURE_WIDTH - VIEW_WIDTH / 2.0f );
		}
	}

	fBack_x = VIEW_WIDTH / 2.0f - fCamera_x;	// 背景の位置

	return 0;
}

// 背景の多重スクロール
// 立体感をだす
//------------------------------------------------------------

//note:背景の横幅が小さいほど、スクロールの速度は低下する
//下記の場合、PICTURE_WIDTH3が一番遅くなるようにプログラムする
#define PICTURE_WIDTH1		1600				// 背景1幅
#define PICTURE_WIDTH2		1280				// 背景2幅
#define PICTURE_WIDTH3		873					// 背景3
float		fBack_x1, fBack_x2, fBack_x3;


int InitBack( void )							// 最初に１回だけ呼ばれる
{
	fCamera_x = VIEW_WIDTH / 2.0f;				// カメラの初期位置　
	fBack_x1 = 0.0f;							// 最前面背景の
	fBack_x2 = 0.0f;// ２つめのはいけい
	fBack_x3 = 0.0f;// 最奥の背景

	return 0;
}


int MoveBack( void )							// 毎フレーム呼ばれる
{
	// 左キーが押されていれば左へ
	if ( GetAsyncKeyState( VK_LEFT ) ) 
	{
		fCamera_x -= CAMERA_VEL;
		if ( fCamera_x < VIEW_WIDTH / 2.0f ) {
			fCamera_x = VIEW_WIDTH / 2.0f;
		}
	}
	// 右キーが押されていれば右へ
	if ( GetAsyncKeyState( VK_RIGHT ) ) {
		fCamera_x += CAMERA_VEL;
		if ( fCamera_x > ( float )( PICTURE_WIDTH1 - VIEW_WIDTH / 2.0f ) )
		{
			fCamera_x = ( float )( PICTURE_WIDTH1 - VIEW_WIDTH / 2.0f );
		}
	}
	fBack_x1 = VIEW_WIDTH / 2.0f - fCamera_x;
	//スクロール可能幅の比率で速度を決める
	fBack_x2 = ( float )( PICTURE_WIDTH2 - VIEW_WIDTH ) / ( PICTURE_WIDTH1 - VIEW_WIDTH ) * fBack_x1; 
	fBack_x3 = ( float )( PICTURE_WIDTH3 - VIEW_WIDTH ) / ( PICTURE_WIDTH1 - VIEW_WIDTH ) * fBack_x1;

	return 0;
}