struct Sphere {
	DirectX::XMFLOAT3			v3Pos;					// 中心点の位置
	float				r;						// 半径
};

Sphere Sphere_1, Sphere_2; //球データ

// 球同士の当たり判定 (中心間の距離 < 半径の和(2次元と同じ))
int CheckHit( Sphere *pCheckSphere1, Sphere *pCheckSphere2 )
{
	float				dx, dy, dz;						// 球動詞の2点間の距離x,y,z座標の差分
	float				fDistanceSq;					// 球同士の距離の2乗
	int					nResult;						// 結果

	dx = pCheckSphere1->v3Pos.x - pCheckSphere2->v3Pos.x;
	dy = pCheckSphere1->v3Pos.y - pCheckSphere2->v3Pos.y;
	dz = pCheckSphere1->v3Pos.z - pCheckSphere2->v3Pos.z;
	fDistanceSq = dx * dx + dy * dy + dz * dz;

	if ( fDistanceSq < ( pCheckSphere1->r + pCheckSphere2->r ) *
					   ( pCheckSphere1->r + pCheckSphere2->r ) )
	{
		nResult = true;
	}
	else 
	{
		nResult = false;
	}

	return nResult;
}


int InitSpheres( void )									// 球の初期化
{
	// 球1
	Sphere_1.v3Pos = DirectX::XMFLOAT3( 0.0f, 0.0f, 0.0f );
	Sphere_1.r = R1;

	// 球2
	Sphere_2.v3Pos = DirectX::XMFLOAT3( 2.0f, 0.0f, 0.0f );
	Sphere_2.r = R2;

	return 0;
}


int MoveSpheres( void )									// 球の移動
{
	if ( GetAsyncKeyState( VK_SHIFT ) ) {
		// 左
		if ( GetAsyncKeyState( VK_LEFT ) ) {
			Sphere_1.v3Pos.x -= SPHERE_SPEED;
		}
		// 右
		if ( GetAsyncKeyState( VK_RIGHT ) ) {
			Sphere_1.v3Pos.x += SPHERE_SPEED;
		}
		// 上
		if ( GetAsyncKeyState( VK_UP ) ) {
			Sphere_1.v3Pos.y += SPHERE_SPEED;
		}
		// 下
		if ( GetAsyncKeyState( VK_DOWN ) ) {
			Sphere_1.v3Pos.y -= SPHERE_SPEED;
		}
		// 奥
		if ( GetAsyncKeyState( 'Z' ) ) {
			Sphere_1.v3Pos.z += SPHERE_SPEED;
		}
		// 手前
		if ( GetAsyncKeyState( 'X' ) ) {
			Sphere_1.v3Pos.z -= SPHERE_SPEED;
		}
	}
	else {
		// 左
		if ( GetAsyncKeyState( VK_LEFT ) ) {
			Sphere_2.v3Pos.x -= SPHERE_SPEED;
		}
		// 右
		if ( GetAsyncKeyState( VK_RIGHT ) ) {
			Sphere_2.v3Pos.x += SPHERE_SPEED;
		}
		// 上
		if ( GetAsyncKeyState( VK_UP ) ) {
			Sphere_2.v3Pos.y += SPHERE_SPEED;
		}
		// 下
		if ( GetAsyncKeyState( VK_DOWN ) ) {
			Sphere_2.v3Pos.y -= SPHERE_SPEED;
		}
		// 奥
		if ( GetAsyncKeyState( 'Z' ) ) {
			Sphere_2.v3Pos.z += SPHERE_SPEED;
		}
		// 手前
		if ( GetAsyncKeyState( 'X' ) ) {
			Sphere_2.v3Pos.z -= SPHERE_SPEED;
		}
	}

	return 0;
}